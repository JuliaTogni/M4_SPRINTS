const Genius = {
    Cores: ["verde", "vermelho", "amarelo", "azul"],
    notas: [261.6, 293.7, 329.6, 392.0], /* Um tom específico para cada cor */
  
    sequenciaGabarito: [],
    sequenciaDoJogador: [],
    gameOver: true,
    contagemDeRodadas: 0,
    limiteDeRodadas: 1,
  
    titulo: document.querySelector("#controls > h1"),
    botaoDePlay: document.querySelector("#controls > button"),
  
    comecarJogo() {
      this.contagemDeRodadas = 0; /* Inicializando o jogo setando as variáveis */
      this.gameOver = false;
      this.sequenciaGabarito = [];
      this.botaoDePlay.innerHTML = "Recomeçar";
      this.escrever("Genius!");
      this.habilitarBotoes();
      this.novaRodada();
    },
  
    novaRodada() {
      this.contagemDeRodadas++; /* Vai adicionando uma unidade na contagem das rodadas, lembrando que são 8 ao total */
      this.sequenciaDoJogador = []; /* Vai armazenando a sequência clicada pelo jogador no array */
      this.gerarToque();
      setTimeout(() => { this.tocarSequencia() }, 1000)
    },
  
    jogar(indiceDaCor) {
      this.tocarNota(indiceDaCor);
  
      if (this.gameOver) return;

  
      this.sequenciaDoJogador.push(indiceDaCor);
  
      this.sequenciaDoJogador.forEach((jogada, index) => { /* Verifica se a jogada do jogador é igual a sequência do gabarito */
        if (jogada != this.sequenciaGabarito[index]) {
          this.finalizarJogo("Você Perdeu!"); /* Colocar o arduíno aqui */
          $.ajax({ 
            url: "http://localhost:3000/resultado", 
            method: "POST", 
            data: { 
                 resultado: "PERDEU" 
             }
        })
        }
      });
  
      if (this.gameOver) return;
  
      if (this.sequenciaDoJogador.length == this.sequenciaGabarito.length) { /* Realiza a comparação entre os array's de jogadas do jogador com o gabarito */
        if (this.contagemDeRodadas >= this.limiteDeRodadas) {
          this.finalizarJogo("Você Ganhou!");
          $.ajax({ 
            url: "http://localhost:3000/resultado", 
            method: "POST", 
            data: { 
                 resultado: "GANHOU" 
             }
        })
        } else {
          this.novaRodada();
        }
      }
    },
  
    gerarToque() {
      const randomInt = this.gerarNumeroAleatorio(); /* Gera uma sequência aleatória cada vez que inicializa o jogo */
      this.sequenciaGabarito.push(randomInt);
    },
  
    gerarNumeroAleatorio() {
      return Math.floor(Math.random() * 4); 
    },
  
    tocarSequencia() {
      this.desabilitarBotoes(); /* Desabilita os botões quando a sequencia está sendo mostrada */
  
      let iteradorDaSequencia = 0; /* Variável que vai interando a seuqnência */
      let deveClarear = true;
  
      const velocidade = 500;
  
      const intervalo = setInterval(() => {
        const indiceDaCor = this.sequenciaGabarito[iteradorDaSequencia]; 
        const cor = this.Cores[indiceDaCor]; /* Utiliza a  */
        const botaoDeCor = document.getElementById(cor);
  
        if (deveClarear) {
          botaoDeCor.classList.add('active')
          this.tocarNota(indiceDaCor);
        } else {
          botaoDeCor.classList.remove('active')
          iteradorDaSequencia++;
        }
  
        if (iteradorDaSequencia >= this.sequenciaGabarito.length) {
          clearInterval(intervalo);
          this.habilitarBotoes();
        }
  
        deveClarear = !deveClarear;
      }, velocidade);
    },
  
    habilitarBotoes() {
      const botoes = document.querySelectorAll("#buttons > button");
      botoes.forEach((botao) => {
        botao.removeAttribute("disabled");
      });
    },
  
    desabilitarBotoes() {
      const botoes = document.querySelectorAll("#buttons > button");
      botoes.forEach((botao) => {
        botao.setAttribute("disabled", "disabled");
      });
    },
  
    finalizarJogo(mensagem) {
      this.gameOver = true;
      this.escrever(mensagem);
      this.desabilitarBotoes();
    },
  
    escrever(texto) {
      this.titulo.innerHTML = texto;
    },
  
    tocarNota(indiceDaNota) {
      const synth = new Tone.Synth().toDestination();
      synth.triggerAttackRelease(this.notas[indiceDaNota], "8n");
    },
  };
  
  document.querySelector("#controls button").onclick = () => {
    Genius.comecarJogo();
  };

  document.querySelector("botaoDePlay").onclick = () => {
    Genius.comecarJogo();
  };

  document.querySelectorAll("#buttons > button").forEach((botao, index) => {
    botao.onclick = () => {
      Genius.jogar(index);
    };
  });