//Importando as bibliotecas necessárias
const express = require('express'); 
const path =require('path');   
const app = express();
let resultado;

//Configurando nosso servidor para que ele possa compreender o JSON
const bodyParser = require("body-parser");
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

const router = express.Router(); 
app.use(express.static(__dirname));

//Criando uma rota para que nosso arquivo html seja carregado pelo NODE
router.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/index.html'));
  //__dirname : It will resolve to your project folder.
});

//Inserir as novas rotas que vc irá criar aqui em baixo:

router.post('/resultado', function(req,res){ 
    res.header("Access-Control-Allow-Origin", "*");
    resultado = req.body
});

router.get('/esp', function(res){
    res.send(resultado)
});

// A estrutura é basicamente:
/* 
    router.TIPO DA ROTA [POS OU GET]('/ENDEREÇO DA ROTA', (req, res) => {
        // aqui vc inseri o que quer que a rota faça
    })
*/

//Fazendo com que o servidor ouça a porta 3000
app.use('/', router); 
app.listen(3000, () => {
  console.log('Servidor NODE rodando em: http://localhost:3000/')
}); 