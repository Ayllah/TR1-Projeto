#include "camadafisica.h"

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