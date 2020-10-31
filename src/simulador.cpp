/*************************************************************
* Trabalho 1 - Teleinformática e Redes 1
* Ayllah Ahmad Lopes 170056465
* Daniel Moraes da Silva 180112333
* Luís Vinicius Capelletto 160134544
*********************************************************** */
#include "camadafisica.h"


using namespace std;


void AplicacaoReceptora (std::string mensagem);
void CamadaDeAplicacaoReceptora (std::vector<int> quadro);
void CamadaFisicaReceptora (std::vector<int> quadro);
void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits);
void CamadaFisicaTransmissora (std::bitset<8> quadro);
void CamadaDeAplicacaoTransmissora (std::string mensagem);
void AplicacaoTransmissora ();

int main () {
	AplicacaoTransmissora();
}//fim do metodo main

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

void CamadaFisicaReceptora (std::vector<int> quadro) {
	int tipoDeDecodificacao = 1; //alterar de acordo o teste
	std::vector<int> fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!
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

	//chama proxima camada
	CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora


void CamadaDeAplicacaoReceptora (std::vector<int> quadro) {
	std::string mensagem; //estava trabalhando com bits
	int temp;
	char letra;
	std::string mensagem2;
	std::string mensagem3;
	std::vector<char> teste;

	/*for (int i = 0; i < 8; ++i){
		mensagem += to_string(quadro[i]);
	}
	cout << "A mensagem recebida foi:" << mensagem << endl;

	int temp = stoi(mensagem);
	char letra = (char)temp;
	cout << "A mensagem recebida foi:" << letra << endl;*/

	for (int i = 0; i < 8; ++i){
		mensagem += to_string(quadro[i]);
	}
	//std::cout << "mensagem:  "<< mensagem << std::endl;
	temp = stoi(mensagem,0,2);
	//std::cout << "temp:  "<< temp << std::endl;
	//std::cout << "letra:  "<< (char)temp << std::endl;

	letra = (char)temp;
	std::cout << "letra:  "<< letra << std::endl;

	mensagem2 += letra;
	//std::cout << "mensagem:  "<< mensagem2 << std::endl;

	mensagem3 += mensagem2;
	//std::cout << "mensagem:  "<< mensagem3 << std::endl;
	//chama proxima camada
	AplicacaoReceptora(mensagem3);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (std::string mensagem) {
	cout << "A mensagem recebida foi:" << mensagem << endl;
}//fim do metodo AplicacaoReceptora 