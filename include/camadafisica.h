#ifndef CAMADAFISICA_H
#define CAMADAFISICA_H


#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <bits/stdc++.h> 


/*************************************************************
* Camada Transmissora
*********************************************************** */

std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::bitset<8> quadro);
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::bitset<8> quadro);
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::bitset<8> quadro);

/*************************************************************
* Camada Receptora
*********************************************************** */

std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (std::vector<int> quadro);
std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester (std::vector<int> quadro);
std::vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(std::vector<int> quadro);

#endif 	//CAMADAFISICA_H
