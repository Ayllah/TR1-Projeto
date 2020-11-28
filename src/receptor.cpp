#include "camadafisica.h"
#include "camadaenlace.h"

/*************************************************************
* 						Camada Fisica
*************************************************************/

void CamadaFisicaReceptora (vector<int> quadro) {
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

	CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora


void CamadaDeAplicacaoReceptora (vector<int> quadro) {
	string mensagem, mensagemRecebida, letraMsg; 
	int valorAscii;	// Armazena o valor decimal na tabela Ascii de cada quadro
	char letra;

	int tam = quadro.size();

  // converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		mensagem += to_string(quadro[i]);
	}
	// cout << "Quadro de Bits Decodificado: "<< mensagem << endl;

	for (int i = 0; i < tam/8; i++){
		// pega cada caractere(Byte) da string em bits
		for (int j = i*8; j <= i*8+7; j++){
			letraMsg += mensagem[j];
		}

		cout << "-------------------" << endl;
		cout << "Letra em bits: " << letraMsg << endl;

		// pega valor decimal da tabela ASCII do string em binario
		valorAscii = stoi(letraMsg, 0, 2);
		cout << "Valor ASCII: "<< valorAscii << endl;

		// casting do valor ASCII para char
		letra = (char)valorAscii;
		cout << "Letra: "<< letra << endl;
		
		letraMsg = "";
		mensagemRecebida += letra;
	}

	AplicacaoReceptora(mensagemRecebida);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (string mensagem) {
	cout << "\n\nA mensagem recebida foi: " << mensagem << endl;
}//fim do metodo AplicacaoReceptora 

/*************************************************************
* 						Camada Enlace
*************************************************************/

void CamadaEnlaceDadosReceptora (vector<int> quadro) {
	quadro = CamadaEnlaceDadosReceptoraEnquadramento(quadro);
	//chama proxima camada
	CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro) {
	int tipoDeEnquadramento = 0; //alterar de acordo com o teste
	vector<int> quadroDesenquadrado;

	switch (tipoDeEnquadramento) {
		case 0 : //contagem de caracteres
			quadroDesenquadrado =
			CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
			break;
		case 1 : //insercao de bytes
			quadroDesenquadrado =
			CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
			break;
		case 2 : //insercao de bits
			quadroDesenquadrado =
			CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits(quadro);
	}//fim do switch/case

	return quadroDesenquadrado;
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento
