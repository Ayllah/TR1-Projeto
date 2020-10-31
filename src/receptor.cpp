#include "camadafisica.h"


int tamReceptor; // tamanho da mensagem de entrada
int cont = 0;
string msg = ""; // armazena resultado da decodificacao

void CamadaFisicaReceptora (vector<int> quadro, int tam) {
  // armazena tamanho da camada fisica transmissora
  tamReceptor = tam;
	vector<int> fluxoBrutoDeBits; 

  // alterar de acordo o teste
	int tipoDeDecodificacao = 1; 
  
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
	int temp;
	char letra;

  // converte quadro de vetor de inteiros para string
	for (int i = 0; i < 8; ++i){
		mensagem += to_string(quadro[i]);
	}
	cout << "Char em Binario Decodificado:  "<< mensagem << endl;

  // pega valor da tabela ASCII do string em binario
	temp = stoi(mensagem, 0, 2);
	cout << "temp:  "<< temp << endl;

  // casting do valor ASCII para char
	letra = (char)temp;
	cout << "letra: "<< letra << endl;

	msg += letra;

	AplicacaoReceptora(msg);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (string mensagem) {
  
  cont++;
  if(cont == tamReceptor) {
    cout << "\n\nA mensagem recebida foi: " << mensagem << endl;
  }

}//fim do metodo AplicacaoReceptora 