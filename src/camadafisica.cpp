/*************************************************************
* Camada Transmissora
*********************************************************** */
#include "camadafisica.h"

std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::bitset<8> quadro) {

}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::bitset<8> quadro) {
	//implementacao do algoritmo
	std::vector<int> cod; 

		/*std::cout << "quadro: " << quadro[0] << std::endl;
		std::cout << "quadro: " << quadro[1] << std::endl;
		std::cout << "quadro: " << quadro[2] << std::endl;
		std::cout << "quadro: " << quadro[3] << std::endl;
		std::cout << "quadro: " << quadro[4] << std::endl;
		std::cout << "quadro: " << quadro[5] << std::endl;
		std::cout << "quadro: " << quadro[6] << std::endl;
		std::cout << "quadro: " << quadro[7] << std::endl;
		std::cout << "------------------------------" << std::endl;*/

	for(int i = 7; i >= 0; i--){
		if(quadro[i] == 0){
			cod.push_back(01);
			//std::cout << "cod: " << cod[i] << std::endl;
		}
		else if(quadro[i] == 1){
			cod.push_back(10);
			//std::cout << "cod: " << cod[i] << std::endl;
		}
			
	}
    	return cod;
	
}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

std::vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::bitset<8> quadro){
	//implementacao do algoritmo
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial


/*************************************************************
* Camada Receptora
*********************************************************** */

std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (std::vector<int> quadro) {
	//implementacao do algoritmo para DECODIFICAR
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria

std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester (std::vector<int> quadro) {
	//implementacao do algoritmo para DECODIFICAR
	std::vector<int> cod; 

		/*std::cout << "quadro: " << quadro[0] << std::endl;
		std::cout << "quadro: " << quadro[1] << std::endl;
		std::cout << "quadro: " << quadro[2] << std::endl;
		std::cout << "quadro: " << quadro[3] << std::endl;
		std::cout << "quadro: " << quadro[4] << std::endl;
		std::cout << "quadro: " << quadro[5] << std::endl;
		std::cout << "quadro: " << quadro[6] << std::endl;
		std::cout << "quadro: " << quadro[7] << std::endl;
		std::cout << "------------------------------" << std::endl;*/

	for(int i = 0; i < 8; i++){
		if(quadro[i] == 01){
			cod.push_back(0);
			//std::cout << "cod: " << cod[i] << std::endl;
		}
		else if(quadro[i] == 10){
			cod.push_back(1);
			//std::cout << "cod: " << cod[i] << std::endl;
		}
			
	}

		/*std::cout << "cod: " << cod[0] << std::endl;
		std::cout << "cod: " << cod[1] << std::endl;
		std::cout << "cod: " << cod[2] << std::endl;
		std::cout << "cod: " << cod[3] << std::endl;
		std::cout << "cod: " << cod[4] << std::endl;
		std::cout << "cod: " << cod[5] << std::endl;
		std::cout << "cod: " << cod[6] << std::endl;
		std::cout << "cod: " << cod[7] << std::endl;
		std::cout << "------------------------------" << std::endl;*/

		/*for (std::vector<int>::iterator it = cod.begin(); it != cod.end(); ++it)
    	std::cout << ' ' << *it;
  		std::cout << '\n';	*/

    	return cod;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester

std::vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(std::vector<int> quadro){
	//implementacao do algoritmo para DECODIFICAR
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

