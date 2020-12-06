#include "camadafisica.h"
#include "camadaenlace.h"

string decimalToBinary(int number) {
	string binary = "";

	while(number > 0) {
		binary = to_string(number % 2) + binary;
		number /= 2;
	}

	int restante = 8 - binary.length();

	for (int i = 0; i < restante; i++){
    binary = "0" + binary;
	}
	// cout << "binary: " << binary << endl;

	return binary;
}

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

	cout << "------------------------------\n";
	cout << "      CAMADA TRANSMISSORA     \n";
	cout << "------------------------------\n";

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
	int tipoDeCodificacao = 0; 

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
	int erro, porcentagemDeErros;
	vector<int> fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
	vector<int> fluxoBrutoDeBitsPontoB;
	porcentagemDeErros = 10; //10%, 20%, 30%, 40%, ..., 100%

	cout << "Numero de bits no Fluxo bruto de Bits: " << fluxoBrutoDeBits.size() << endl;

	// pega o tamanho dos fluxos brutos de bits do ponto A e B
	int bitsfluxoBrutoDeBitsA = fluxoBrutoDeBitsPontoA.size();

	for (int i = 0; i < bitsfluxoBrutoDeBitsA; i++) {
		//verificar se o numero de 1 a 100 gerado está no valor da porcentagem de erro
		if (rand()%100 + 1 <= porcentagemDeErros ){ 
			fluxoBrutoDeBitsPontoB.push_back(!fluxoBrutoDeBitsPontoA[i]); // Inverte o Bit
			cout << "Erro no Bit [" << i << "]" << endl;
		}
		else{ 
			fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
		}
		
			
	}//fim do while

	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);

}//fim do metodo MeioDeTransmissao

/*************************************************************
* Camada Transmissora - Codificação
*********************************************************** */

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (vector<int> quadro) {
	return quadro;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

vector<int> CamadaFisicaTransmissoraCodificacaoManchester (vector<int> quadro) {
	vector <int> codigoManchester; 
	string codigoManchesterStr;

	int tam = quadro.size();

	for(int i = 0; i < tam; i++){
		if(quadro[i] == 0){
			codigoManchester.push_back(0);
			codigoManchester.push_back(1);
		}
		else if(quadro[i] == 1){
			codigoManchester.push_back(1);
			codigoManchester.push_back(0);
		}
	}

	cout << "Codigo Manchester: ";
	int size = codigoManchester.size();

	for(int i = 0; i < size; i++) {
		cout << codigoManchester[i];
	}
	cout << endl;

	return codigoManchester;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(vector<int> quadro){
	vector <int> codigoManchesterDif; 
	int tam = quadro.size();

	// numero de valores logicos 1 encontrados
	int transicao = 0;	

	// percorre ao contrario por conta da disposição do bitset
	for(int i = 0; i < tam; i++){
		if(quadro[i] == 1) {
			// incrementa o valor de transicao a cada valor logico 1 encontrado
			transicao++;	
			if(transicao % 2 == 0) {
				codigoManchesterDif.push_back(0);
				codigoManchesterDif.push_back(1);
			}else {
				codigoManchesterDif.push_back(1);
				codigoManchesterDif.push_back(0);
			}
		}

		if(quadro[i] == 0) {
			if(transicao % 2 == 0) {
				codigoManchesterDif.push_back(0);
				codigoManchesterDif.push_back(1);
			}else {
				codigoManchesterDif.push_back(1);
				codigoManchesterDif.push_back(0);
			}
		}
	}

	cout << "Codigo Manchester Diferencial: ";
	int size = codigoManchesterDif.size();

	for(int i = 0; i < size; i++) {
		cout << codigoManchesterDif[i];
	}
	cout << endl;

	return codigoManchesterDif;
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial

/*************************************************************
* 						Camada Enlace
*************************************************************/
void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
	quadro = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
	quadro = CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
	//chama proxima camada
	CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro) {
	int tipoDeEnquadramento = 0; //alterar de acordo com o teste
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
		case 2 : //insercao de bits
			quadroEnquadrado = 
		CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(quadro);
	}//fim do switch/case

	return quadroEnquadrado;
}//fim do metodo CamadaEnlaceTransmissoraEnquadramento

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
* Camada Transmissora - Controle de Erro
*********************************************************** */

vector<int> CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro) {
	int tipoDeControleDeErro = 0; //alterar de acordo com o teste
	vector<int> quadroCorrecao;

	switch (tipoDeControleDeErro) {
		case 0 : //bit de paridade par
			quadroCorrecao =
			CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
			break;
		case 1 : //bit de paridade impar
			quadroCorrecao =
			CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
			break;
		case 2 : //CRC
			quadroCorrecao = 
			CamadaEnlaceDadosTransmissoraControleDeErroCRC (quadro);
		// case 3 : //codigo de Hamming
		// 	quadroCorrecao = 
		// 	CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (quadro);
		// break;
	}//fim do switch/case

	return quadroCorrecao;
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (vector<int> quadro) {
	//implementacao do algoritmo
	int tam = quadro.size();
	int count;
	
	//Conta a quantidade de 1s no quadro
	for(int i = 0; i < tam; i++){	
		if(quadro[i] == 1)
			count ++;			
	}

	//Verifica se é par
	if((count % 2) == 0){
		quadro.push_back(0);
	}
	else{
		quadro.push_back(1);
	}

	tam = quadro.size();
	cout << "Quadro Bit com Paridade Par: ";
	for(int i = 0; i < tam; i++){	
		cout << quadro[i];
	}
	cout << "\n";

	return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar


vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (vector<int> quadro){
	//implementacao do algoritmo
	int tam = quadro.size();
	int count;
	
	//Conta a quantidade de 1s no quadro
	for(int i = 0; i < tam; i++){	
		if(quadro[i] == 1)
			count ++;			
	}

	//Verifica se é par
	if((count % 2) == 0){
		quadro.push_back(1);
	}
	else{
		quadro.push_back(0);
	}

	tam = quadro.size();
	cout << "Quadro Bit com Paridade Impar: ";
	for(int i = 0; i < tam; i++){	
		cout << quadro[i];
	}
	cout << "\n";

	return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar


vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro) {
//implementacao do algoritmo
//usar polinomio CRC-32(IEEE 802)
	vector<int> CRC;
	int tamGerador = 4, tamQuadroStr;
	int bitsQuadro = quadro.size();
	string polGerador = "1001", tempStr, tempStr2;
	string quadroStr = "";
	int i;

	for(i = 0; i < bitsQuadro; i++){
		quadroStr += (to_string(quadro[i]));	//Transforma em string
	}

	// insere os bits 0 do CRC
	quadroStr += "000";

	tamQuadroStr = quadroStr.length();
	
	//Enquanto o tamanho da mensagem for maior que 
	while (tamQuadroStr >= tamGerador){				 

		//o tamanho do polinomio gerador continua dividindo
		for (i = 0; i < tamGerador; i++) {
			if(quadroStr[i] == polGerador[i]){
				quadroStr[i] = '0';
			}else {
				quadroStr[i] = '1';
			}
		}

		//Apaga o primeiro indice
		if(quadroStr[0] == '0'){
			quadroStr.erase(quadroStr.begin());	
		}
		
		tamQuadroStr = quadroStr.length();
	}
	cout << "CRC Transmissora: " << quadroStr << endl;
	
	// Coloca CRC no final do quadro a ser enviado
	for (int i = 0; i < 3; i++) {
		
		// Code ASCII 0
		if (quadroStr[i] == 48)
			quadro.push_back(0);

		// Code ASCII 1
		if (quadroStr[i] == 49)
			quadro.push_back(1);
	}

	bitsQuadro = quadro.size();
	cout << "Quadro com CRC: ";
	for(int i = 0; i < bitsQuadro; i++){	
		cout << quadro[i];
	}
	cout << "\n";

	return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC


// vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (vector<int> quadro) {
// 	//implementacao do algoritmo

// }//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCodigoDehamming
