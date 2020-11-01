#include "camadafisica.h"

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
	// int quadro[8];
	string s;
  tamanhoMsg = mensagem.length();

	// loop em cada byte da mensagem de entrada
	for (int i = 0; i < tamanhoMsg; ++i){
    cout << "------------------------" << endl;

    int valorAscii = ((int)(mensagem[i]));

		// armazena em forma de bitset de 8 bits
    quadroBitset = valorAscii;	

    // cout << "quadroBitset: " << quadroBitset << endl;
		// s = bitset<8>(valorAscii).to_string();
		// cout << "s: " << s << endl;

		//chama a proxima camada
		CamadaFisicaTransmissora(quadroBitset);
	}

}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (bitset<8> quadro) {
	vector<int> fluxoBrutoDeBits; 

  // alterar de acordo o teste
	int tipoDeCodificacao = 2; 

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

