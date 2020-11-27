#include "camadafisica.h"
#include "camadaenlace.h"

/*************************************************************
* 						Camada Fisica
*************************************************************/

void CamadaFisicaReceptora (vector<int> quadro) {
	vector<int> fluxoBrutoDeBits;

  // alterar de acordo o teste
	int tipoDeDecodificacao = 0;
  
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
	int tipoDeEnquadramento = 2; //alterar de acordo com o teste
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
		case 2 : //insercao de bits
			quadroDesenquadrado =
			CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits(quadro);
	}//fim do switch/case

	return quadroDesenquadrado;
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres (vector<int> quadro) {
	//implementacao do algoritmo para DESENQUADRAR
	int bitsQuadro = quadro.size();
	int count = 0;
	int count2 = 0;
	string headerStr;

	while (count2 < bitsQuadro){

		for (int i = count+1; i < 8+count; i++) {
			headerStr += to_string(quadro[i]);
		}

		int headerInt = stoi(headerStr, 0, 2);
		// cout << "headerInt: " << headerInt << endl;

		headerStr = "";// reseta header em formato string

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

	int bitsQuadro = quadro.size();
	string byteFlag = "11111111"; 
	string byteESC = "00000000"; 

	string quadroDesenquadradoStr = "";
	string byteStr = "";
	string byteStr2 = "";
	int i, j, indice = 0;

	// cria uma quadro em formato string
	string quadroStr = "";
	for (i = 0; i < bitsQuadro; i++) {
		quadroStr += to_string(quadro[i]);
	}

	// Caso quadro seja vazio, retorne vetor vazio
	if (bitsQuadro == 0)
		return quadroDesenquadradoInt;

	while(indice < bitsQuadro){
		// pega um byte 
		for (j = indice; j <= (indice+7); j++){
			byteStr += quadroStr[j];	
		}

		// caso seja um byte ESC
		if(byteStr == byteESC){
			// próximo byte -> pega 8 indices a frente
			for (j = (indice+8); j <= (indice+7); j++){
				byteStr2 += quadroStr[j];	
			}
			// adicionar próximo byte
			quadroDesenquadradoStr += byteStr2;
			indice += 16;	 // pula o proximo byte já adicionado
			byteStr2 = ""; // reseta string temporaria 2
		}else {
			indice += 8;	// anda de byte em byte
		}
		// se não for byte de Flag ou ESC, faz parte da carga util
		if(byteStr != byteFlag && byteStr != byteESC){
			quadroDesenquadradoStr += byteStr;
		}

		byteStr = "";	// reseta string temporaria de cada byte
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

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits (vector<int> quadro) {
vector<int> quadroDesenquadradoInt;

	int bitsQuadro = quadro.size();
	string sequenciaBits = "01111110"; 
	string sequencia5Bits = "11111";

	string quadroDesenquadradoStr = "";
	string byteStr = "";
	int i, j, conta5Bits = 0;
	
	// cria uma quadro em formato string
	string quadroStr = "";
	string quadroSemFlags = "";
	for (i = 0; i < bitsQuadro; i++) {
		quadroStr += to_string(quadro[i]);
	}

	// Caso quadro seja vazio, retorne vetor vazio
	if (bitsQuadro == 0)
		return quadroDesenquadradoInt;

	// Retira as sequencia de bits do quadro Enquadrado
	for(i = 0; i < bitsQuadro; i++) {
		// verifica se já passou do ultimo byte do quadro
		if(i < bitsQuadro - 8){
			// verifica byte a byte 
			for (j = i; j < (i+8); j++){
				byteStr += quadroStr[j];	
			}

			// Se existe byte igual a sequencia de bits na carga util
			if(byteStr == sequenciaBits){
				i += 7; // pula os indices desse byte
			}else{
				quadroSemFlags += quadroStr[i]; // adiciona bit a bit
			}
		}
		byteStr = "";	// reseta string temporaria de cada byte
	}

	int tamQuadroSemFlags = quadroSemFlags.length();

	for (i = 0; i < tamQuadroSemFlags; i++) {

		if(quadroSemFlags[i] == '1'){
			conta5Bits++;
		}
		if(quadroSemFlags[i] == '0'){
			conta5Bits = 0; // reseta contador de 5 bits
		}

		// Existe sequencia de 5 bits 1 na carga util (RECEPTORA)
		if(conta5Bits == 5){
			quadroDesenquadradoStr += quadroSemFlags[i];// adciona o quinto bit 1
			i = i+1; // pula o indice 
			conta5Bits = 0; 
		}else{
			quadroDesenquadradoStr += quadroSemFlags[i];
		}
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
	cout << "Quadro DESENQUADRADO (Insercao de bits): ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		cout << quadroDesenquadradoInt[i];
	}
	cout << endl;

	return quadroDesenquadradoInt;
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoDeBits
