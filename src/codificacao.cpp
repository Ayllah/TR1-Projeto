/*************************************************************
* Camada Transmissora
*********************************************************** */
#include "camadafisica.h"

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (bitset<8> quadro) {

	vector<int> cod;

	for(int i = 0; i <= 7; i++) {
		cod.push_back(quadro[i]);
	}

	for(int i = 0; i <= 7; i++) {
		cout << cod[i] << endl;
	}

	return cod;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

vector<int> CamadaFisicaTransmissoraCodificacaoManchester (bitset<8> quadro) {
	//implementacao do algoritmo
	vector<int> cod; 

	cout << "quadro: ";
	for(int i = 0; i <= 7; i++) {
		cout << quadro[i];
	}
	cout << endl;

	for(int i = 7; i >= 0; i--){
		if(quadro[i] == 0){
			cod.push_back(01);
			//cout << "cod: " << cod[i] << endl;
		}
		else if(quadro[i] == 1){
			cod.push_back(10);
			//cout << "cod: " << cod[i] << endl;
		}
			
	}

	return cod;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(bitset<8> quadro){
	//implementacao do algoritmo
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial


/*************************************************************
* Camada Receptora
*********************************************************** */

vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (vector<int> quadro) {
	//implementacao do algoritmo para DECODIFICAR
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria

vector<int> CamadaFisicaReceptoraDecodificacaoManchester (vector<int> quadro) {
	//implementacao do algoritmo para DECODIFICAR
	vector<int> cod; 

	cout << "quadro: ";
	for(int i = 0; i <= 7; i++) {
		cout << quadro[i];
	}
	cout << endl;

	for(int i = 0; i < 8; i++){
		if(quadro[i] == 01){
			cod.push_back(0);
			//cout << "cod: " << cod[i] << endl;
		}
		else if(quadro[i] == 10){
			cod.push_back(1);
			//cout << "cod: " << cod[i] << endl;
		}
			
	}

	cout << "quadro: ";
	for(int i = 0; i <= 7; i++) {
		cout << quadro[i];
	}
	cout << endl;

	/*for (vector<int>::iterator it = cod.begin(); it != cod.end(); ++it)
		cout << ' ' << *it;
		cout << '\n';	*/

	return cod;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester

vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro){
	//implementacao do algoritmo para DECODIFICAR
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

