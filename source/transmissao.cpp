#include "camadafisica.h"

void AplicacaoTransmissora (void) {
	string mensagem;
	cout << "Mensagem: ";

	// guarda entrada com espaços inclusive
	getline(cin, mensagem);

	// chama a proxima camada
	CamadaDeAplicacaoTransmissora(mensagem); 
}// fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora (string mensagem) {

	string msgBinaria = "";

	// transforma string em string de bits equivalente
	for (char &_char : mensagem) {
		msgBinaria += bitset<8>(_char).to_string();
	}

	int tamanho = msgBinaria.length();
	int *quadro = new int[tamanho]; // trabalhar com bits!!!

	// cria o quadro de bits
	for (int i = 0; i < tamanho; i++) {
		quadro[i] = msgBinaria[i];

		// Code ASCII 0
		if (quadro[i] == 48)
			quadro[i] = 0;

		// Code ASCII 1
		if (quadro[i] == 49)
			quadro[i] = 1;
	}

	cout << "Camada de Aplicacao Transmissora - Quadro: ";
	for (int i = 0; i < tamanho; i++) {
		cout << quadro[i];
	}
	cout << "\n";

	//chama a proxima camada
	CamadaFisicaTransmissora(quadro, tamanho);
}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (int* quadro, int tamanho) {

	//alterar de acordo o teste
	int codificacao = 0; 

	//ATENÇÃO: trabalhar com BITS!!!
	int* fluxoBrutoDeBits = new int[tamanho]; 

	switch (codificacao) {
		case 0 : //codificao binaria
			fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
			cout << "CamadaFisicaTransmissora - Fluxo Bruto de Bits: ";
			
			for (int i = 0; i < tamanho; i++)
				cout << fluxoBrutoDeBits[i];

			cout << "\n";
			break;
		//case 1 : //codificacao manchester
			//fluxoBrutoDeBits =
			//CamadaFisicaTransmissoraCodificacaoManchester(quadro);
			// break;
		//case 2 : //codificacao manchester diferencial
			//fluxoBrutoDeBits =
			//CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
			// break;
	}//fim do switch/case

	// MeioDeComunicacao(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora

/* Este metodo simula a transmissao da informacao no meio de
* comunicacao, passando de um pontoA (transmissor) para um
* ponto B (receptor)
*/
/* void MeioDeComunicacao (int fluxoBrutoDeBits []) {
	//OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!

	int* fluxoBrutoDeBitsPontoA, *fluxoBrutoDeBitsPontoB;

	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

	while (fluxoBrutoDeBitsPontoB.lenght != fluxoBrutoDeBitsPontoA) {

		//BITS! Sendo transferidos
		fluxoBrutoBitsPontoB += fluxoBrutoBitsPontoA; 



	}//fim do while

	//chama proxima camada
	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao */



