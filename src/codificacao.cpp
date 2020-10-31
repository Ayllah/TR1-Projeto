/*************************************************************
* Camada Transmissora
*********************************************************** */
#include "camadafisica.h"

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (bitset<8> quadro) {
	vector<int> codigoBinario;

	cout << "Char Codificado em Binario: " << quadro << endl;

	// insere ao final do vetor de inteiros
	for(int i = 7; i >= 0; i--) {
		codigoBinario.push_back(quadro[i]);
	}

	return codigoBinario;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

vector<int> CamadaFisicaTransmissoraCodificacaoManchester (bitset<8> quadro) {
	vector <int> codigoManchester; 
	string codigoManchesterStr;

	cout << "Char em Binario: " << quadro << endl;

	for(int i = 7; i >= 0; i--){
		if(quadro[i] == 0){
			codigoManchester.push_back(0);
			codigoManchester.push_back(1);
			codigoManchesterStr += "01";
		}
		else if(quadro[i] == 1){
			codigoManchester.push_back(1);
			codigoManchester.push_back(0);
			codigoManchesterStr += "10";
		}
	}

	cout << "Char em Codigo Manchester String: " << codigoManchesterStr << endl;
	cout << "Char em Codigo Manchester Vetor Int: ";

	// tamanho do binario em codificacao manchester
	int size = codigoManchester.size();

	for(int i = 0; i < size; i++) {
		cout << codigoManchester[i];
	}
	cout << endl;

	return codigoManchester;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(bitset<8> quadro){
	//implementacao do algoritmo
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial


/*************************************************************
* Camada Receptora
*********************************************************** */

// Decodificação BINARIA
vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (vector<int> quadro) {
	return quadro;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria

// Decodificação MANCHESTER
vector<int> CamadaFisicaReceptoraDecodificacaoManchester (vector<int> quadro) {
	
	vector<int> manchesterDecodificado; 
	string parBits;	// armazena pares de bits do quadro codificado em manchester

	for(int i = 0; i < 16; i++) {
		// forma o par de bits
		parBits += to_string(quadro[i]);
		parBits += to_string(quadro[i + 1]);

		// decodificando para codificacao binaria usual 
		if(parBits == "01"){
			manchesterDecodificado.push_back(0);
		}
		else if(parBits == "10"){
			manchesterDecodificado.push_back(1);
		}
		i++; // i tem que incrementar de novo para ir de par em par
		// reseta string de par de bits
		parBits = "";
	}

	return manchesterDecodificado;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester

// Decodificação MANCHESTER DIFERENCIAL
vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro){

}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

