#include "camadafisica.h"

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
	bitset<8> quadroBitset;
	string s;
	
	tamanhoMsg = mensagem.length();

	// loop em cada byte da mensagem de entrada
	for (int i = 0; i < tamanhoMsg; ++i){
    cout << "------------------------" << endl;

    int valorAscii = ((int)(mensagem[i]));

		// armazena em forma de bitset de 8 bits
    quadroBitset = valorAscii;	

		//chama a proxima camada
		CamadaFisicaTransmissora(quadroBitset);
	}

}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (bitset<8> quadro) {
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

	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, tamanhoMsg);
}//fim do metodo MeioDeTransmissao

/*************************************************************
* 						Camada Enlace
*************************************************************/
void CamadaEnlaceDadosTransmissora (bitset<8> quadro) {
    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    //chama proxima camada
    CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora


void CamadaEnlaceDadosTransmissoraEnquadramento (bitset<8> quadro) {
    int tipoDeEnquadramento= -1; //alterar de acordo com o teste
    vector<int> quadroEnquadrado;
	
    switch (tipoDeEnquadramento) {
        case -1 : //contagem de caracteres
            quadroEnquadrado =
            CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 0 : //insercao de bytes
            quadroEnquadrado =
            CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
        case 1 : //insercao de bits
            quadroEnquadrado = 
			CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(quadro);
    }//fim do switch/case
}//fim do metodo CamadaEnlaceTransmissoraEnquadramento

void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (bitset<8> quadro) {
    //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraContagemDeCaracteres

void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (bitset<8> quadro) {
    //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBytes

void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (bitset<8> quadro) {
    //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBits
