#include "camadafisica.h"

/*************************************************************
* Camada Transmissora - Codificação
*********************************************************** */

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (vector<int> quadro) {
	return quadro;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

vector<int> CamadaFisicaTransmissoraCodificacaoManchester (vector<int> quadro) {
	vector <int> codigoManchester; 
	string codigoManchesterStr;

	int tam = quadro.size();

	for(int i = 0; i <= tam; i++){
		if(quadro[i] == 0){
			codigoManchester.push_back(0);
			codigoManchester.push_back(1);
		}
		else if(quadro[i] == 1){
			codigoManchester.push_back(1);
			codigoManchester.push_back(0);
		}
	}

	cout << "Codigo Manchester: ";
	int size = codigoManchester.size();

	for(int i = 0; i < size; i++) {
		cout << codigoManchester[i];
	}
	cout << endl;

	return codigoManchester;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(vector<int> quadro){
	vector <int> codigoManchesterDif; 
	int tam = quadro.size();

	// numero de valores logicos 1 encontrados
	int transicao = 0;	

	// percorre ao contrario por conta da disposição do bitset
	for(int i = 0; i <= tam; i++){
		if(quadro[i] == 1) {
			// incrementa o valor de transicao a cada valor logico 1 encontrado
			transicao++;	
			if(transicao % 2 == 0) {
				codigoManchesterDif.push_back(0);
				codigoManchesterDif.push_back(1);
			}else {
				codigoManchesterDif.push_back(1);
				codigoManchesterDif.push_back(0);
			}
		}

		if(quadro[i] == 0) {
			if(transicao % 2 == 0) {
				codigoManchesterDif.push_back(0);
				codigoManchesterDif.push_back(1);
			}else {
				codigoManchesterDif.push_back(1);
				codigoManchesterDif.push_back(0);
			}
		}
	}

	cout << "Codigo Manchester Diferencial: ";
	int size = codigoManchesterDif.size();

	for(int i = 0; i < size; i++) {
		cout << codigoManchesterDif[i];
	}
	cout << endl;

	return codigoManchesterDif;
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial


/*************************************************************
* Camada Receptora - Decodificação
*********************************************************** */

// Decodificação BINARIA
vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (vector<int> quadro) {
	int tam = quadro.size();
	cout << "BINARIO DECODIFICADO: ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < tam; i++){
		cout << quadro[i];
	}
	cout << endl;
	return quadro; 
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria

// Decodificação MANCHESTER
vector<int> CamadaFisicaReceptoraDecodificacaoManchester (vector<int> quadro) {
	
	vector<int> manchesterDecodificado; 
	string parBits;	// armazena pares de bits do quadro codificado em manchester

	int tam = quadro.size();

	for(int i = 0; i < tam; i++) {
		// forma o par de bits
		parBits += to_string(quadro[i]);
		parBits += to_string(quadro[i + 1]);

		// decodificando para codificacao manchester usual 
		if(parBits == "01"){
			manchesterDecodificado.push_back(0);
		}
		else if(parBits == "10"){
			manchesterDecodificado.push_back(1);
		}
		i++; // i tem que incrementar de novo para ir de par em par
		parBits = "";// reseta string de par de bits
	}

	int size = manchesterDecodificado.size();
	cout << "MANCHESTER DECODIFICADO: ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < size; i++){
		cout << manchesterDecodificado[i];
	}
	cout << endl;

	return manchesterDecodificado;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester

// Decodificação MANCHESTER DIFERENCIAL
vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro){
	vector<int> manchesterDifDecodificado; 

	// armazenam pares de bits do quadro codificado em manchester diferencial
	string parBits;		
	string parBitsSeguinte;	

	int tam = quadro.size();

	for(int i = 0; i < tam; i++) {
		// forma o par de bits
		parBits += to_string(quadro[i]);
		parBits += to_string(quadro[i + 1]);

		// caso for o primeiro par de bits no quadro
		if(i == 0){		
			// decodificando para codificacao manchester usual 
			if(parBits == "01"){
				manchesterDifDecodificado.push_back(0);
			}
			else if(parBits == "10"){
				manchesterDifDecodificado.push_back(1);
			}
		}

		// caso nao seja o ultimo par de bits do quadro
		if(i < tam - 2){
			// forma o par de bits seguinte
			parBitsSeguinte += to_string(quadro[i + 2]);
			parBitsSeguinte += to_string(quadro[i + 3]);
	
			// caso sejam iguais -> valor logico 0
			if(parBits == parBitsSeguinte){
				manchesterDifDecodificado.push_back(0);
			}
			else if(parBits != parBitsSeguinte){
				manchesterDifDecodificado.push_back(1);
			}
		}	 

		i++; // i tem que incrementar de novo para ir de par em par
		// reseta pares de bits
		parBits = "";
		parBitsSeguinte = "";					
	}

	int size = manchesterDifDecodificado.size();
	cout << "MANCHESTER DIFERENCIAL DECODIFICADO: ";
	// converte quadro de vetor de inteiros para string
	for (int i = 0; i < size; i++){
		cout << manchesterDifDecodificado[i];
	}
	cout << endl;

	return manchesterDifDecodificado;
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

