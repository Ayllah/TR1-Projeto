#include "camadafisica.h"
#include "camadaenlace.h"

/*************************************************************
* 						Camada Fisica
*************************************************************/

void CamadaFisicaReceptora (vector<int> quadro) {
	vector<int> fluxoBrutoDeBits; 

  // alterar de acordo o teste
	int tipoDeDecodificacao = 1; 
  
	switch (tipoDeDecodificacao) {
		case 0 : //codificao binaria
			fluxoBrutoDeBits =
			CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
			break;
		case 1 : //codificacao manchester
			fluxoBrutoDeBits =
			CamadaFisicaReceptoraDecodificacaoManchester(quadro);
			break;
		case 2 : //codificacao manchester diferencial
			fluxoBrutoDeBits =
			CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(quadro);
			break;
	}//fim do switch/case

	CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora


void CamadaDeAplicacaoReceptora (vector<int> quadro) {
	string mensagem, mensagemRecebida, letraMsg; 
	int valorAscii;	// Armazena o valor decimal na tabela Ascii de cada quadro
	char letra;

	int tam = quadro.size();

  // converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		mensagem += to_string(quadro[i]);
	}
	// cout << "Quadro de Bits Decodificado: "<< mensagem << endl;

	for (int i = 0; i < tam/8; i++){

		for (int j = i*8; j <= i*8+7; j++){
			letraMsg += mensagem[j];
		}

		cout << "-------------------" << endl;
		cout << "Letra em bits: " << letraMsg << endl;

		// pega valor decimal da tabela ASCII do string em binario
		valorAscii = stoi(letraMsg, 0, 2);
		cout << "Valor ASCII: "<< valorAscii << endl;

		// casting do valor ASCII para char
		letra = (char)valorAscii;
		cout << "Letra: "<< letra << endl;
		
		letraMsg = "";
		mensagemRecebida += letra;
	}

	AplicacaoReceptora(mensagemRecebida);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (string mensagem) {
	cout << "\n\nA mensagem recebida foi: " << mensagem << endl;
}//fim do metodo AplicacaoReceptora 

/*************************************************************
* 						Camada Enlace
*************************************************************/

void CamadaEnlaceDadosReceptora (vector<int> quadro) {
	quadro = CamadaEnlaceDadosReceptoraEnquadramento(quadro);
	//chama proxima camada
	CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro) {
	int tipoDeEnquadramento = 1; //alterar de acordo com o teste
	vector<int> quadroDesenquadrado;

	switch (tipoDeEnquadramento) {
		case 0 : //contagem de caracteres
			quadroDesenquadrado =
			CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
			break;
		case 1 : //insercao de bytes
			quadroDesenquadrado =
			CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
			break;
		// case 2 : //insercao de bits
		// 	quadroDesenquadrado =
		// 	CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits(quadro);
	}//fim do switch/case

	return quadroDesenquadrado;
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres (vector<int> quadro) {
	//implementacao do algoritmo para DESENQUADRAR
	int tamQuadro = quadro.size();
	int count = 0;
	int count2 = 0;
	string headerStr;

	while (count2 < tamQuadro){

		for (int i = count+1; i < 8+count; i++) {
			headerStr += to_string(quadro[i]);
		}

		int headerInt = stoi(headerStr, 0, 2);
		// cout << "headerInt: " << headerInt << endl;

		headerStr = "";

		quadro.erase(quadro.begin()+count, quadro.begin()+count+8);
		count += (8*(headerInt-1));

		count2 += (8*headerInt);
	}

	int tam = quadro.size();
	cout << "Quadro DESENQUADRADO (Contagem de Caracteres): ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		cout << quadro[i];
	}
	cout << endl;
    
	return quadro;
}//fim do metodo CamadaEnlaceDadosReceptoraContagemDeCaracteres

//implementacao do algoritmo para DESENQUADRAR por insercao de Bytes
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes (vector<int> quadro) {
	vector<int> quadroDesenquadradoInt;

	int tamQuadro = quadro.size();
	string byteFlag = "11111111"; 
	string byteESC = "00000000"; 

	string quadroDesenquadradoStr = "";
	string tempStr = "";
	string tempStr2 = "";
	int i, j, indice = 0;

	// cria uma quadro em formato string
	string quadroStr = "";
	for (i = 0; i < tamQuadro; i++) {
		quadroStr += to_string(quadro[i]);
	}

	// Caso quadro seja vazio, retorne vetor vazio
	if (tamQuadro == 0)
		return quadroDesenquadradoInt;

	while(indice < tamQuadro){
		// pega um byte 
		for (j = indice; j <= (indice+7); j++){
			tempStr += quadroStr[j];	
		}

		// caso seja um byte ESC, adicionar próximo byte
		if(tempStr == byteESC){

			for (j = (indice+8); j <= (indice+7); j++){
				tempStr2 += quadroStr[j];	
			}

			quadroDesenquadradoStr += tempStr2;
			indice += 16;	 // pula o proximo byte já adicionado
			tempStr2 = ""; // reseta string temporaria
		}else {
			indice += 8;	// anda de byte em byte
		}
		
		if(tempStr != byteFlag && tempStr != byteESC){
			quadroDesenquadradoStr += tempStr;
		}

		tempStr = "";	// reseta string temporaria de cada byte
	}

	int tamDesenquadrado = quadroDesenquadradoStr.size();

	// cria o quadro de vetor de inteiros
	for (i = 0; i < tamDesenquadrado; i++) {
		// Code ASCII 0
		if (quadroDesenquadradoStr[i] == 48)
			quadroDesenquadradoInt.push_back(0);

		// Code ASCII 1
		if (quadroDesenquadradoStr[i] == 49)
			quadroDesenquadradoInt.push_back(1);
	}

	int tam = quadroDesenquadradoInt.size();

	cout << "Quadro DESENQUADRADO (Insercao de Bytes): ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		cout << quadroDesenquadradoInt[i];
	}
	cout << endl;

	return quadroDesenquadradoInt;
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoDeBytes

// vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits (vector<int> quadro) {
// 	//implementacao do algoritmo para DESENQUADRAR
// }//fim do metodo CamadaEnlaceDadosReceptoraInsercaoDeBits
