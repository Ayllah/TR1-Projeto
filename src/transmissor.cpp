#include "camadafisica.h"

void AplicacaoTransmissora () {
	//string mensagem;
	std::string mensagem;
	cout << "Digite uma mensagem:" << endl;
	getline(std::cin, mensagem );
	//chama a proxima camada
	CamadaDeAplicacaoTransmissora(mensagem); //em um exemplo mais realistico, aqui seria dado um SEND do SOCKET
}//fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora (std::string mensagem) {
	std::bitset<8> bitArr;
	int quadro[8];
	std::string s;

	for (int i = 0; i < mensagem.length(); ++i){
    	int temp = ((int)(mensagem[i]));
    	bitArr = temp;
    	//std::cout << "bitArr: " << bitArr << std::endl;
		//s = std::bitset<8>(temp).to_string();
		//std::cout << "s: " << s << std::endl;

    	//trabalhar com bits!!!
		//chama a proxima camada
		CamadaFisicaTransmissora(bitArr);
	}


}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (std::bitset<8> quadro) {
	int tipoDeCodificacao = 1; //alterar de acordo o teste
	std::vector<int> fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!
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
void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits) {
	//OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!
	std::vector<int> fluxoBrutoDeBitsPontoA;
	std::vector<int> fluxoBrutoDeBitsPontoB;
	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

	while (fluxoBrutoDeBitsPontoB.size()!= fluxoBrutoDeBitsPontoA.size()) {
		fluxoBrutoDeBitsPontoB = fluxoBrutoDeBitsPontoA; //BITS! Sendo transferidos
	}//fim do while

	//chama proxima camada
	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao

