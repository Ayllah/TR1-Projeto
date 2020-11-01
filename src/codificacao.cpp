/*************************************************************
* Camada Transmissora - Codificação
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
		}
		else if(quadro[i] == 1){
			codigoManchester.push_back(1);
			codigoManchester.push_back(0);
		}
	}

	cout << "Char em Codigo Manchester em Vetor de inteiros: ";
	int size = codigoManchester.size();

	for(int i = 0; i < size; i++) {
		cout << codigoManchester[i];
	}
	cout << endl;

	return codigoManchester;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(bitset<8> quadro){
	vector <int> codigoManchesterDif; 

	// numero de valores logicos 1 encontrados
	int transicao = 0;	

	cout << "Char em Binario: " << quadro << endl;

	// percorre ao contrario por conta da disposição do bitset
	for(int i = 7; i >= 0; i--){
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

	cout << "Char em Codigo Manchester Diferencial em Vetor de inteiros: ";
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
		parBits = "";// reseta string de par de bits
	}

	return manchesterDecodificado;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester

// Decodificação MANCHESTER DIFERENCIAL
vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro){
	vector<int> manchesterDifDecodificado; 

	// armazenam pares de bits do quadro codificado em manchester diferencial
	string parBits;		
	string parBitsSeguinte;	

	for(int i = 0; i < 16; i++) {
		// forma o par de bits
		parBits += to_string(quadro[i]);
		parBits += to_string(quadro[i + 1]);

		// caso for o primeiro par de bits no quadro
		if(i == 0){		
			// decodificando para codificacao binaria usual 
			if(parBits == "01"){
				manchesterDifDecodificado.push_back(0);
			}
			else if(parBits == "10"){
				manchesterDifDecodificado.push_back(1);
			}
		}

		// caso nao seja o ultimo par de bits do quadro
		if(i < 14){
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

	return manchesterDifDecodificado;
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

