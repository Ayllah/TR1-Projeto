#ifndef CAMADAFISICA_H
#define CAMADAFISICA_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset> 

#include <stdlib.h>
#include <stdio.h>

using namespace std;

void MeioDeComunicacao (vector<int> fluxoBrutoDeBits);

/*************************************************************
* Camada Transmissora
*********************************************************** */

void AplicacaoTransmissora ();
void CamadaFisicaTransmissora (bitset<8> quadro);
void CamadaDeAplicacaoTransmissora (string mensagem);

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (bitset<8> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoManchester (bitset<8> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(bitset<8> quadro);

/*************************************************************
* Camada Receptora
*********************************************************** */

void AplicacaoReceptora (string mensagem);
void CamadaFisicaReceptora (vector<int> quadro);
void CamadaDeAplicacaoReceptora (vector<int> quadro);

vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (vector<int> quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoManchester (vector<int> quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro);

#endif 	//CAMADAFISICA_H
