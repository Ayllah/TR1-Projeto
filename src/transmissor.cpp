#include "camadafisica.h"

int tam; // Armazena tamanho da entrada 

void AplicacaoTransmissora () {
	//string mensagem;
	string mensagem;
	cout << "Digite uma mensagem: ";
	getline(cin, mensagem );
	
	CamadaDeAplicacaoTransmissora(mensagem); 
}//fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora (string mensagem) {
	bitset<8> bitArr;
	// int quadro[8];
	string s;
  tam = mensagem.length();

	for (int i = 0; i < tam; ++i){
    cout << "------------------------" << endl;

    //trabalhar com bits!!!
    int temp = ((int)(mensagem[i]));
    bitArr = temp;

    // cout << "bitArr: " << bitArr << endl;
		// s = bitset<8>(temp).to_string();
		// cout << "s: " << s << endl;

		//chama a proxima camada
		CamadaFisicaTransmissora(bitArr);
	}

}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (bitset<8> quadro) {
	vector<int> fluxoBrutoDeBits; 

  //alterar de acordo o teste
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

	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, tam);
}//fim do metodo MeioDeTransmissao

