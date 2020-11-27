#include "camadaenlace.h"

/*************************************************************
* Camada Transmissora - Enquadramento
*********************************************************** */

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (vector<int> quadro) {
	//implementacao do algoritmo
	int cont = 0;
	vector<int> contQuadro;
	vector<int> quadroInt;

	//int bitsQuadro = quadro.size();

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
	int bitsQuadro = quadro.size();

	// Caso quadro seja vazio, retorne vetor vazio
	if (bitsQuadro == 0)
		return quadroEnquadradoInt;
		
	string byteFlag = "11111111"; 
	string byteESC = "00000000"; 

	string quadroEnquadradoStr = "";
	string byteStr = "";

	int i, j, indice = 0, cont = 0, contFlag = 0, contESC = 0;
	int qtdBytesQuadro = bitsQuadro / 8; 
	int resto = qtdBytesQuadro % 4;
	int qtdQuadros = qtdBytesQuadro / 4;

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

			if (indice >= bitsQuadro)	// caso indice seja o tamanho do quadro, break
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

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (vector<int> quadro) {
	vector<int> quadroEnquadradoInt;
	int bitsQuadro = quadro.size();

	// Caso quadro seja vazio, retorne vetor vazio
	if (bitsQuadro == 0)
		return quadroEnquadradoInt;

	string sequenciaBits = "01111110"; 
	string sequencia5Bits = "11111";

	string quadroEnquadradoStr = "";
	string byteStr = "";

	int i, j, indice = 0, cont = 0, conta5Bits = 0;
	int qtdBytesQuadro = bitsQuadro / 8; 
	int resto = qtdBytesQuadro % 4;
	int qtdQuadros = qtdBytesQuadro / 4;

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

			if (indice >= bitsQuadro)	// caso indice seja o tamanho do quadro, break
				break;
		}
		
		quadroEnquadradoStr += sequenciaBits;	// sequencia de bits final
		cont++;
	}while(cont < qtdQuadros);

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
