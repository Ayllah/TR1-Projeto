#include "camadaenlace.h"

/*************************************************************
* Camada Transmissora - Enquadramento
*********************************************************** */

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (vector<int> quadro) {
	//implementacao do algoritmo
	int cont = 0;
	vector<int> quadroInt;

	int qtdBytesQuadro = quadro.size()/8; 
	int qtdQuadros = qtdBytesQuadro/4;																																						

	string headerStr;
	string headerBinaria;

	int indice = 0;

	// Caso a quantidade de bytes seja multiplo de 4
	if (qtdBytesQuadro % 4 == 0) {

		// todo header tera valor fixo de 5 Bytes
		headerStr = decimalToBinary(5);	// converte de formato decimal para string binaria

		// cria cada quadro a quadro
		for (int j = 0; j < qtdQuadros; j++){	

			// insere cada header (8 bits) no quadro de vetor de inteiros
			for (int i = 0; i < 8; i++) {

				// Code ASCII 0
				if (headerStr[i] == 48)
					quadroInt.push_back(0);

				// Code ASCII 1
				if (headerStr[i] == 49)
					quadroInt.push_back(1);
			}	

			// insere de 4 em 4 Bytes (32 bits) no quadro de vetor de inteiros
			for(int i = 0+indice; i < 32+indice; i++){																									
				quadroInt.push_back(quadro[i]);
			}				

			indice += 32; // pula para os 4 Bytes da proxima iteracao
		}																																														
	}	

	// Caso a quantidade de bytes nao seja multiplo de 4
	if (qtdBytesQuadro % 4 != 0) {

		int resto = qtdBytesQuadro % 4; 
		
		do { // pelo menos 1 quadro sera criado
			// caso tenha apenas 1 quadro com menos de 4 Bytes
			if (qtdQuadros == 0){
				headerStr = decimalToBinary(resto+1);	
			}else{
				headerStr = decimalToBinary(5);	
			}

			// insere cada header (8 bits) no quadro de vetor de inteiros
			for (int i = 0; i < 8; i++) {
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

				// insere quadro com o resto de bytes (resto * 8 bits)
				for(int i = 0+indice; i < indice + (resto*8); i++)																								
					quadroInt.push_back(quadro[i]);
					
			} else {
				// insere de 4 em 4 Bytes (32 bits) no quadro de vetor de inteiros
				for(int i = 0+indice; i < 32+indice; i++)																								
					quadroInt.push_back(quadro[i]);
			}					

			indice += 32;
			cont++;
		}while(cont <= qtdQuadros);
	}				

	int tam = quadroInt.size();
	cout << "Quadro ENQUADRADO (Contagem de Caracteres): ";
	for (int i = 0; i < tam; i++){
		cout << quadroInt[i];
	}
	cout << endl;

	return quadroInt;
}//fim do metodo CamadaEnlaceDadosTransmissoraContagemDeCaracteres

//implementacao do algoritmo para ENQUADRAR por insercao de Bytes
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (vector<int> quadro) {
	vector<int> quadroEnquadradoInt;
	int bitsQuadro = quadro.size();

	// Caso quadro seja vazio, retorne vetor vazio
	if (bitsQuadro == 0)
		return quadroEnquadradoInt;
		
	int i, j, indice = 0, contQuadros = 0, contFlag = 0, contESC = 0;
	int qtdBytesQuadro = bitsQuadro / 8; 
	int resto = qtdBytesQuadro % 4;
	int qtdQuadros = qtdBytesQuadro / 4;

	string byteFlag = "11111111"; 
	string byteESC = "00000000"; 

	string quadroEnquadradoStr = "";
	string byteStr = "";

	// Se tiver resto, tem q fazer 1 quadro a mais
	if (resto != 0) {
		qtdQuadros++;
	}

	// cria uma quadro em formato string
	string quadroStr = "";
	for (i = 0; i < bitsQuadro; i++) {
		quadroStr += to_string(quadro[i]);
	}

	do{ // pelo menos 1 quadro sera criado
		quadroEnquadradoStr += byteFlag;	// flag inicial 

		for (i = 1; i <= 4; i++){
			// pega cada byte individual da carga util
			for (j = indice; j <= (indice+7); j++){
				byteStr += quadroStr[j];	
			}

			// caso tenha padrão ESC ou Flag na carga util
			if (byteStr == byteFlag || byteStr == byteESC) {
				cout << "Existe Flag ou Escape na carga util!" << endl;

				// Caso tenha o padrão Flag na carga Util 
				if (byteStr == byteFlag){
					quadroEnquadradoStr += byteESC + byteStr;
					contFlag++;
				}

				// Caso tenha o padrão ESC na carga Util 
				if (byteStr == byteESC){
					quadroEnquadradoStr += byteESC + byteStr;
					contESC++;
				}
			}else {
				quadroEnquadradoStr += byteStr;
			}

			byteStr = "";	// reseta string temporaria de cada byte
			indice += 8;	// anda de byte em byte

			// caso indice seja maior que o tamanho do quadro, sai do loop
			if (indice >= bitsQuadro)	
				break;
		}
		
		quadroEnquadradoStr += byteFlag;	// flag final
		contQuadros++;

	}while(contQuadros < qtdQuadros);
	
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
	for (int i = 0; i < tam; i++){
		cout << quadroEnquadradoInt[i];
	}
	cout << endl;

	return quadroEnquadradoInt;
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBytes

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (vector<int> quadro) {
	vector<int> quadroEnquadradoInt;
	int bitsQuadro = quadro.size();

	// Caso quadro seja vazio, retorne vetor vazio
	if (bitsQuadro == 0)
		return quadroEnquadradoInt;

	int i, j, indice = 0, contQuadros = 0, conta5Bits = 0;
	int qtdBytesQuadro = bitsQuadro / 8; 
	int resto = qtdBytesQuadro % 4;
	int qtdQuadros = qtdBytesQuadro / 4;

	string sequenciaBits = "01111110"; 
	string quadroEnquadradoStr, byteStr;

	// Se tiver resto, tem q fazer 1 quadro a mais
	if (resto != 0) {
		qtdQuadros++;
	}

	// cria uma quadro em formato string
	string quadroStr = "";
	for (i = 0; i < bitsQuadro; i++) {
		quadroStr += to_string(quadro[i]);
	}

	do{
		quadroEnquadradoStr += sequenciaBits;	// sequencia de bits inicial

		// quadros de 4 bytes cada
		for (i = 1; i <= 4; i++){

			// pega cada byte individual da carga util
			for (j = indice; j <= (indice+7); j++){
				byteStr += quadroStr[j];	
			}

			// verifica bit a bit do byte
			for (int j = 0; j < 8; j++) {
				if(byteStr[j] == '1'){
					conta5Bits++;
				}
				if(byteStr[j] == '0'){
					conta5Bits = 0;
				}
				quadroEnquadradoStr += byteStr[j];	

				// Existe sequencia de 5 bits 1 na carga util (TRANSMISSAO)
				if(conta5Bits == 5){
					quadroEnquadradoStr += '0';	
					conta5Bits = 0;
				}
			}
			
			byteStr = "";	// reseta string temporaria de cada byte
			indice += 8;	// anda de byte em byte

			// caso indice seja maior que o tamanho do quadro, break
			if (indice >= bitsQuadro)	
				break;
		}
		
		quadroEnquadradoStr += sequenciaBits;	// sequencia de bits final
		contQuadros++;
	}while(contQuadros < qtdQuadros);

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
	cout << "Quadro ENQUADRADO (Insercao de bits): ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		cout << quadroEnquadradoInt[i];
	}
	cout << endl;

	return quadroEnquadradoInt;
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBits

/*************************************************************
* Camada Receptora - Desenquadramento
*********************************************************** */

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres (vector<int> quadro) {
	//implementacao do algoritmo para DESENQUADRAR
	int bitsQuadro = quadro.size();
	int indice = 0, indiceHeader = 0;
	string headerStr;

	while (indice < bitsQuadro){

		// pega o header em formato string binaria
		for (int i = indiceHeader; i < indiceHeader+8; i++) {
			headerStr += to_string(quadro[i]);
		}

		// converte string binaria para inteiro
		int headerInt = stoi(headerStr, 0, 2);

		headerStr = "";// reseta header 

	  // apaga os headers em seus respectivos indices
		quadro.erase(quadro.begin()+indiceHeader, quadro.begin()+indiceHeader+8);
		indiceHeader += (8*(headerInt-1));	// pula o numero de bytes da carga util

		indice += (8*headerInt); // pula os bytes de cada quadro
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

	int i, j, indice = 0;
	string quadroDesenquadradoStr, byteStr, byteStr2;

	int bitsQuadro = quadro.size();
	string byteFlag = "11111111"; 
	string byteESC = "00000000"; 

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

		// se não for byte de Flag ou ESC, faz parte da carga util
		if(byteStr != byteFlag && byteStr != byteESC){
			quadroDesenquadradoStr += byteStr;
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

	int i, j, conta5Bits = 0;
	string quadroDesenquadradoStr, byteStr, quadroSemFlags;

	int bitsQuadro = quadro.size();
	string sequenciaBits = "01111110"; 

	// cria uma quadro em formato string
	string quadroStr;
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

		quadroDesenquadradoStr += quadroSemFlags[i];// adciona o quinto bit 1

		// Existe sequencia de 5 bits 1 na carga util (RECEPTORA)
		if(conta5Bits == 5){
			i = i+1; // pula o indice 
			conta5Bits = 0; 
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
