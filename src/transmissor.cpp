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


