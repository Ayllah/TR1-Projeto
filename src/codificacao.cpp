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
	vector<int> codigoManchester; 
	string codigoManchesterStr;

	cout << "Char em Binario: " << quadro << endl;

	for(int i = 7; i >= 0; i--){
		if(quadro[i] == 0){
			codigoManchester.push_back(01);
			codigoManchesterStr += "01";
		}
		else if(quadro[i] == 1){
			codigoManchester.push_back(10);
			codigoManchesterStr += "10";
		}
	}

	cout << "Char em Codigo Manchester String: " << codigoManchesterStr << endl;

	cout << "Char em Codigo Manchester Vetor Int: ";
	for(int i = 0; i < codigoManchester.size(); i++) {
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
	
	vector<int> cod; 

	for(int i = 0; i < 8; i++){
		if(quadro[i] == 01){
			cod.push_back(0);
		}
		else if(quadro[i] == 10){
			cod.push_back(1);
		}
		//cout << "cod: " << cod[i] << endl;
	}

	/*for (vector<int>::iterator it = cod.begin(); it != cod.end(); ++it)
		cout << ' ' << *it;
		cout << '\n';	*/

	return cod;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester

// Decodificação MANCHESTER DIFERENCIAL
vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro){

}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

