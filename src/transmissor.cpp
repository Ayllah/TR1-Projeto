#include "camadafisica.h"
#include "camadaenlace.h"

/*************************************************************
* 						Camada Fisica
*************************************************************/

int tamanhoMsg; // Armazena tamanho da entrada 

void AplicacaoTransmissora () {
	string mensagem;
	cout << "Digite uma mensagem: ";

	// Armazena mensagem de entrada a ser enviada
	getline(cin, mensagem );
	
	CamadaDeAplicacaoTransmissora(mensagem); 
}//fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora (string mensagem) {
	string msgBinaria = "";

	// transforma string em string de bits equivalente
	for (char &_char : mensagem) {
		msgBinaria += bitset<8>(_char).to_string();
	}

	int tamanho = msgBinaria.length();
	vector<int> quadro; 

	// cria o quadro de bits
	for (int i = 0; i < tamanho; i++) {
		//quadro.push_back(msgBinaria[i]);

		// Code ASCII 0
		if (msgBinaria[i] == 48)
			quadro.push_back(0);

		// Code ASCII 1
		if (msgBinaria[i] == 49)
			quadro.push_back(1);
	}

	cout << "Quadro de Bits: ";
	for (int i = 0; i < tamanho; i++) {
		cout << quadro[i];
	}
	cout << "\n";

	CamadaEnlaceDadosTransmissora(quadro);
}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (vector<int> quadro) {
	vector<int> fluxoBrutoDeBits; 

  // alterar de acordo o teste
	int tipoDeCodificacao = 1; 

	switch (tipoDeCodificacao) {
		case 0 : //codificao binaria
			fluxoBrutoDeBits =
			CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
			break;
		case 1 : //codificacao manchester
			fluxoBrutoDeBits =
			CamadaFisicaTransmissoraCodificacaoManchester(quadro);
			break;
		case 2 : //codificacao manchester diferencial
			fluxoBrutoDeBits =
			CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
			break;
	}//fim do switch/case

	MeioDeComunicacao(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora */

/* Este metodo simula a transmissao da informacao no meio de
* comunicacao, passando de um pontoA (transmissor) para um
* ponto B (receptor)
*/
void MeioDeComunicacao (vector<int> fluxoBrutoDeBits) {
	//OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!
	vector<int> fluxoBrutoDeBitsPontoA;
	vector<int> fluxoBrutoDeBitsPontoB;
	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

	while (fluxoBrutoDeBitsPontoB.size() != fluxoBrutoDeBitsPontoA.size()) {
		fluxoBrutoDeBitsPontoB = fluxoBrutoDeBitsPontoA; // BITS Sendo transferidos
	}//fim do while

	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao

/*************************************************************
* 						Camada Enlace
*************************************************************/
void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
	quadro = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
	//chama proxima camada
	CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora


vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro) {
	int tipoDeEnquadramento = 1; //alterar de acordo com o teste
	vector<int> quadroEnquadrado;

	switch (tipoDeEnquadramento) {
		case 0 : //contagem de caracteres
			quadroEnquadrado =
			CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
			break;
		case 1 : //insercao de bytes
			quadroEnquadrado =
			CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
			break;
		// case 2 : //insercao de bits
		// 	quadroEnquadrado = 
		// CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(quadro);
	}//fim do switch/case

	return quadroEnquadrado;
}//fim do metodo CamadaEnlaceTransmissoraEnquadramento

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (vector<int> quadro) {
	//implementacao do algoritmo
	int cont = 0;
	vector<int> contQuadro;
	vector<int> quadroInt;

	//int tamQuadro = quadro.size();

	int qtdBytesQuadro = quadro.size()/8; 

	string headerStr;
	string headerBinaria;

	int tamHeaderStr;

	int indice = 0;

	if (qtdBytesQuadro % 4 == 0) {
		int qntQuadros = qtdBytesQuadro/4;																																						

		headerStr = decimalToBinary(5);	
		tamHeaderStr = headerStr.length();

		cout << "tamHeaderStr: " << tamHeaderStr << endl;

		for (int j = 0; j < qntQuadros; j++){	

			for (int i = 0; i < tamHeaderStr; i++) {
				//quadro.push_back(msgBinaria[i]);

				// Code ASCII 0
				if (headerStr[i] == 48)
					quadroInt.push_back(0);

				// Code ASCII 1
				if (headerStr[i] == 49)
					quadroInt.push_back(1);
			}	

			for(int i = 0+indice; i < 32+indice; i++){																									
				quadroInt.push_back(quadro[i]);
			}				

			indice += 32;
		}																																														
	}	

	if (qtdBytesQuadro % 4 != 0) {
			int resto = qtdBytesQuadro % 4; 
			int qtdQuadros = qtdBytesQuadro/4;																																

		do{

			if (qtdQuadros == 0){
				headerStr = decimalToBinary(resto+1);	
			}else{
				headerStr = decimalToBinary(5);	
			}

			tamHeaderStr = headerStr.length();

			for (int i = 0; i < tamHeaderStr; i++) {
				//quadro.push_back(msgBinaria[i]);

				// Code ASCII 0
				if (headerStr[i] == 48)
					quadroInt.push_back(0);

				// Code ASCII 1
				if (headerStr[i] == 49)
					quadroInt.push_back(1);	
			}																																														
	
			// Caso ultimo loop
			if(cont == qtdQuadros) {  

				headerStr = decimalToBinary(resto+1);	
				for(int i = 0+indice; i < indice + (resto*8); i++)																								
					quadroInt.push_back(quadro[i]);
					
			} else {
				for(int i = 0+indice; i < 32+indice; i++)																								
					quadroInt.push_back(quadro[i]);
			}					

			// cout << "headerStr: " << headerStr << endl;

			indice += 32;
			cont++;
		}while(cont <= qtdQuadros);
	}				

	int tam = quadroInt.size();

	cout << "Quadro ENQUADRADO (Contagem de Caracteres): ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		cout << quadroInt[i];
	}
	cout << endl;

	return quadroInt;
	
}//fim do metodo CamadaEnlaceDadosTransmissoraContagemDeCaracteres

//implementacao do algoritmo para ENQUADRAR por insercao de Bytes
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (vector<int> quadro) {
	vector<int> quadroEnquadradoInt;
	
	int tamQuadro = quadro.size();
	int qtdBytesQuadro = tamQuadro / 8; 

	string byteFlag = "11111111"; 
	string byteESC = "00000000"; 

	string quadroEnquadradoStr = "";
	string tempStr = "";

	int i, j, indice = 0, cont = 0, contFlag = 0, contESC = 0;
	int resto = qtdBytesQuadro % 4;
	int qtdQuadros = qtdBytesQuadro / 4;

	// Se tiver resto, tem q fazer 1 quadro a mais
	if (resto != 0) {
		qtdQuadros++;
	}

	// cria uma quadro em formato string
	string quadroStr = "";
	for (i = 0; i < tamQuadro; i++) {
		quadroStr += to_string(quadro[i]);
	}

	// Caso quadro seja vazio, retorne vetor vazio
	if (tamQuadro == 0)
		return quadroEnquadradoInt;

	do{
		quadroEnquadradoStr += byteFlag;	// flag inicial 
		for (i = 1; i <= 4; i++){
			// pega cada byte individual da carga util
			for (j = indice; j <= (indice+7); j++){
				tempStr += quadroStr[j];	
			}

			// caso tenha padrão ESC ou Flag na carga util
			if (tempStr == byteFlag || tempStr == byteESC) {
				cout << "Existe Flag ou Escape na carga util!" << endl;
				// Caso tenha o padrão Flag na carga Util 
				if (tempStr == byteFlag){
					quadroEnquadradoStr += byteESC + tempStr;
					contFlag++;
				}
				// Caso tenha o padrão ESC na carga Util 
				if (tempStr == byteESC){
					quadroEnquadradoStr += byteESC + tempStr;
					contESC++;
				}
			}else {
				quadroEnquadradoStr += tempStr;
			}

			tempStr = "";	// reseta string temporaria de cada byte
			indice += 8;	// anda de byte em byte

			if (indice >= tamQuadro)	// caso indice seja o tamanho do quadro, break
				break;
		}
		
		quadroEnquadradoStr += byteFlag;	// flag final
		cont++;

	}while(cont < qtdQuadros);
	
	// Tem padrão Flag e ESC na carga util- apenas aviso
	if(contFlag > 0 && contESC > 0){
		cout << "Existe Flag e Escape na carga util!" << endl;
	}

	int tamEnquadrado = quadroEnquadradoStr.size();

	// cria o quadro de vetor de inteiros
	for (i = 0; i < tamEnquadrado; i++) {
		// Code ASCII 0
		if (quadroEnquadradoStr[i] == 48)
			quadroEnquadradoInt.push_back(0);

		// Code ASCII 1
		if (quadroEnquadradoStr[i] == 49)
			quadroEnquadradoInt.push_back(1);
	}

	int tam = quadroEnquadradoInt.size();

	cout << "Quadro ENQUADRADO (Insercao de Bytes): ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		cout << quadroEnquadradoInt[i];
	}
	cout << endl;

	return quadroEnquadradoInt;

}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBytes

// vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (vector<int> quadro) {
// 	//implementacao do algoritmo
// }//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBits
