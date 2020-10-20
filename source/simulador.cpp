/*************************************************************
* Trabalho 1 - Teleinformática e Redes 1
* Ayllah Ahmad Lopes 170056465
* Daniel Moraes da Silva 180112333
* Luís Vinicius Capelletto 160134544
*********************************************************** */
#include "camadafisica.h"
#include <iostream>
#include <string>

using namespace std;

void AplicacaoReceptora (string mensagem);
void CamadaDeAplicacaoReceptora (int *quadro);
void CamadaFisicaReceptora (int *quadro);
void MeioDeComunicacao (int *fluxoBrutoDeBits);
void CamadaFisicaTransmissora (int *quadro);
void CamadaDeAplicacaoTransmissora (string mensagem);
void AplicacaoTransmissora ();

void main () {
	AplicacaoTransmissora();
}//fim do metodo main

void AplicacaoTransmissora () {
	string mensagem;
	cout << "Digite uma mensagem:" << endl;
	cin >> mensagem;
	//chama a proxima camada
	CamadaDeAplicacaoTransmissora(mensagem); //em um exemplo mais realistico, aqui seria dado um SEND do SOCKET
}//fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora (string mensagem) {
	int *quadro = mensagem; //trabalhar com bits!!!
	//chama a proxima camada
	CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (int *quadro) {
	int tipoDeCodificacao = 0; //alterar de acordo o teste
	int *fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!
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
}//fim do metodo CamadaFisicaTransmissora

/* Este metodo simula a transmissao da informacao no meio de
* comunicacao, passando de um pontoA (transmissor) para um
* ponto B (receptor)
*/
void MeioDeComunicacao (int *fluxoBrutoDeBits) {
	//OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!
	int *fluxoBrutoDeBitsPontoA, *fluxoBrutoDeBitsPontoB;
	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
	while (fluxoBrutoDeBitsPontoB.lenght!= fluxoBrutoDeBitsPontoA) {
		fluxoBrutoBitsPontoB += fluxoBrutoBitsPontoA; //BITS! Sendo transferidos
	}//fim do while

	//chama proxima camada
	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao

void CamadaFisicaReceptora (int *quadro) {
	int tipoDeDecodificacao = 0; //alterar de acordo o teste
	int *fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!
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


void CamadaDeAplicacaoReceptora (int *quadro) {
	string mensagem = *quadro; //estava trabalhando com bits
	//chama proxima camada
	AplicacaoReceptora(mensagem);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (string mensagem) {
	cout << "A mensagem recebida foi:" << mensagem << endl;
}//fim do metodo AplicacaoReceptora
