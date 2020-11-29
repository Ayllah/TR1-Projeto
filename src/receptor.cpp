#include "camadafisica.h"
#include "camadaenlace.h"

/*************************************************************
* 						Camada Fisica
*************************************************************/

void CamadaFisicaReceptora (vector<int> quadro) {
	vector<int> fluxoBrutoDeBits;

  // alterar de acordo o teste
	int tipoDeDecodificacao = 2;
  
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
		// pega cada caractere(Byte) da string em bits
		for (int j = i*8; j <= i*8+7; j++){
			letraMsg += mensagem[j];
		}

		cout << "----------------------------" << endl;
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
* Camada Receptora - Decodificação
*********************************************************** */

// Decodificação BINARIA
vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (vector<int> quadro) {
	int tam = quadro.size();
	cout << "BINARIO DECODIFICADO: ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		cout << quadro[i];
	}
	cout << endl;
	return quadro; 
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria

// Decodificação MANCHESTER
vector<int> CamadaFisicaReceptoraDecodificacaoManchester (vector<int> quadro) {
	
	vector<int> manchesterDecodificado; 
	string parBits;	// armazena pares de bits do quadro codificado em manchester

	int tam = quadro.size();

	for(int i = 0; i < tam; i++) {
		// forma o par de bits
		parBits += to_string(quadro[i]);
		parBits += to_string(quadro[i + 1]);

		// decodificando para codificacao manchester usual 
		if(parBits == "01"){
			manchesterDecodificado.push_back(0);
		}
		else if(parBits == "10"){
			manchesterDecodificado.push_back(1);
		}
		i++; // i tem que incrementar de novo para ir de par em par
		parBits = "";// reseta string de par de bits
	}

	int size = manchesterDecodificado.size();
	cout << "MANCHESTER DECODIFICADO: ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < size; i++){
		cout << manchesterDecodificado[i];
	}
	cout << endl;

	return manchesterDecodificado;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester

// Decodificação MANCHESTER DIFERENCIAL
vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro){
	vector<int> manchesterDifDecodificado; 

	// armazenam pares de bits do quadro codificado em manchester diferencial
	string parBits;		
	string parBitsSeguinte;	

	int tam = quadro.size();

	for(int i = 0; i < tam; i++) {
		// forma o par de bits
		parBits += to_string(quadro[i]);
		parBits += to_string(quadro[i + 1]);

		// caso for o primeiro par de bits no quadro
		if(i == 0){		
			// decodificando para codificacao manchester usual 
			if(parBits == "01"){
				manchesterDifDecodificado.push_back(0);
			}
			else if(parBits == "10"){
				manchesterDifDecodificado.push_back(1);
			}
		}

		// caso nao seja o ultimo par de bits do quadro
		if(i < tam - 2){
			// forma o par de bits seguinte
			parBitsSeguinte += to_string(quadro[i + 2]);
			parBitsSeguinte += to_string(quadro[i + 3]);
	
			// caso sejam iguais -> valor logico 0
			if(parBits == parBitsSeguinte){
				manchesterDifDecodificado.push_back(0);
			}
			else if(parBits != parBitsSeguinte){
				manchesterDifDecodificado.push_back(1);
			}
		}	 

		i++; // i tem que incrementar de novo para ir de par em par
		// reseta pares de bits
		parBits = "";
		parBitsSeguinte = "";					
	}

	int size = manchesterDifDecodificado.size();
	cout << "MANCHESTER DIFERENCIAL DECODIFICADO: ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < size; i++){
		cout << manchesterDifDecodificado[i];
	}
	cout << endl;

	return manchesterDifDecodificado;
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

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
