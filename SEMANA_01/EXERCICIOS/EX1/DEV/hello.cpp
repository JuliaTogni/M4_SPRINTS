#include <iostream>
#include <string>

using namespace std; // para referenciar uma classe ou um objeto da biblioteca padrão C++ precisa referenciar o namespace std

// exercícios realizados em call com outros estudantes do INTELI

// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente
// entre dois valores mínimo e máximo e retorna esse valor

int ajustePercentual(int value, int minValue, int maxValue)
{
	int intervalo = maxValue - minValue;

	int porcentagem = (value * 100) / intervalo; // calculando a porcentagem

	return porcentagem;
}

// 2 - Faça uma função que simule a leitura de um sensor lendo o
// valor do teclado ao final a função retorna este valor

int leComando()
{
	string input; // os valores inputados são do tipo string, e será convertido posteriormente

	cin >> input;

	return stoi(input); // A função stoi converte a sequência de caracteres em str em um valor do tipo int e retorna o valor.
}

// para testar o exercício 2
/*
int main()
{
  cout << "Digite o Comando (0 ou 1):";
	int cmd = leComando();
	cout << "Comando Recebido: " << cmd << endl;
}
*/

// 3 - Faça uma função que armazena uma medida inteira qualquer
// em um vetor fornecido. Note que como C não possui vetores
// nativos da linguagem, lembre-se que você precisa passar o
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em
// uma área de memória fora do vetor

int insereVetor(int elemento, int valorMax, int lastPos, int *Vetor)
{
	if (lastPos < valorMax)
	{
		Vetor[lastPos] = elemento;
		return lastPos + 1;
	}
	else
	{
		return lastPos;
	}
}

// 4 - Faça uma função que recebe um vetor com 4 posições que contém
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a
// segunda é esta maior distância.

char *direcaoDist(int *Vetor)
{
	int maiorDistancia = Vetor[0];
	int indice = 0;
	char *direcoes[4] = {(char *)"Direita", (char *)"Esquerda", (char *)"Frente", (char *)"Tras"};
	for (int i = 0; i < 4; i++)
	{
		if (Vetor[i] > maiorDistancia)
		{
			maiorDistancia = Vetor[i];
			indice = i;
		}
	}
	return direcoes[indice];
}

int maiorDist(int *Vetor)
{
	int maiorDistancia = Vetor[0];
	for (int i = 0; i < 4; i++)
	{
		if (Vetor[i] > maiorDistancia)
		{
			maiorDistancia = Vetor[i];
		}
	}
	return maiorDistancia;
}

// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e
// retorna verdadeiro ou falso

int continuar()
{
	int entrada;
	cout << "Digite 0 para parar o mapeamento e 1 para continuar o mapeamento:" << endl;
	cin >> entrada;
	return entrada;

	if (entrada == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda",
// "Frente", "Tras").
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno
// para uma movimentação futura.
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja
// enviado pelo usuário.
//
//      Complete a função com a chamada das funções já criadas

int dirigeRobo(int *Vetor,int maxv){
	int maxVetor = maxv;
	int *vetorMov = Vetor;
	int lastPosVetor = 0;
	int dirigido = 1;		
	while(dirigido){		
    for (int i = 0; i < 4; i++){
      int medida = leComando();
      medida = ajustePercentual(medida, 0, 830);
		  lastPosVetor = insereVetor(medida, maxVetor, lastPosVetor, vetorMov);
    }		
		dirigido = continuar();		
	}
	return lastPosVetor;
}

void tragetoPercorrido(int *v,int distacia){		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< distacia; i+=4){
		char *direcao = direcaoDist(&(vetorMov[i]));
    int maiordir = maiorDist(&(vetorMov[i]));
		cout << "Movimentando para "<< direcao<< " distancia ="<< maiordir << endl;
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int movimentacao[maxVetor*4];
	int lastPosVet = 0;
	
	lastPosVet = dirigeRobo(movimentacao,maxVetor);
	tragetoPercorrido(movimentacao,lastPosVet);
	
	return 0;
}


int dirige(int *v, int maxv)
{
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;
	while (dirigindo)
	{
		int medida = /// .. Chame a função de de leitura da medida para a "Direita"
			medida = ajustePercentual(medida, 0, 830);
		posAtualVetor = // Chame a função para armazenar a medida no vetor
						///////////////////////////////////////////////////////////////////////////
			// Repita as chamadas acima para a "Esquerda", "Frente", "Tras"
			// ................
			///////////////////////////////////////////////////////////////////////////
			dirigindo = leComando();
	}
	return posAtualVetor;
}

// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado
// na maior distância a cada movimento
void percorre(int *v, int tamPercorrido)
{
	int *vetorMov = v;
	int maiorDir = 0;

	for (int i = 0; i < tamPercorrido; i += 4)
	{
		char *direcao = direcaoDist(&(vetorMov[i]), &maiorDir);
		printf("Movimentando para %s distancia = %i\n", direcao, maiorDir);
	}
}

int main(int argc, char **argv)
{
	int maxVetor = 100;
	int vetorMov[maxVetor * 4];
	int posAtualVet = 0;

	posAtualVet = dirige(vetorMov, maxVetor);
	percorre(vetorMov, posAtualVet);

	return 0;
}