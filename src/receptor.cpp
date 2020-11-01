#include "camadafisica.h"

int tamanhoMsgRecepcao; // tamanho da mensagem de entrada
int cont = 0;
string msgRecebida = ""; // armazena resultado da decodificacao

void CamadaFisicaReceptora (vector<int> quadro, int tamanhoMsg) {
  // armazena tamanho da camada fisica transmissora
  tamanhoMsgRecepcao = tamanhoMsg;
	vector<int> fluxoBrutoDeBits; 

  // alterar de acordo o teste
	int tipoDeDecodificacao = 0; 
  
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

	CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora


void CamadaDeAplicacaoReceptora (vector<int> quadro) {
	string mensagem; 
	int valorAscii;	// Armazena o valor decimal na tabela Ascii de cada quadro
	char letra;

  // converte quadro de vetor de inteiros para string
	for (int i = 0; i < 8; i++){
		mensagem += to_string(quadro[i]);
	}
	cout << "Char em Binario Decodificado: "<< mensagem << endl;

  // pega valor decimal da tabela ASCII do string em binario
	valorAscii = stoi(mensagem, 0, 2);
	cout << "Valor ASCII: "<< valorAscii << endl;

  // casting do valor ASCII para char
	letra = (char)valorAscii;
	cout << "Letra: "<< letra << endl;

	msgRecebida += letra;

	AplicacaoReceptora(msgRecebida);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (string mensagem) {
  cont++;
  if(cont == tamanhoMsgRecepcao) {
    cout << "\n\nA mensagem recebida foi: " << mensagem << endl;
  }
}//fim do metodo AplicacaoReceptora 
