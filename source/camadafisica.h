#ifndef CAMADAFISICA_H
#define CAMADAFISICA_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <bitset>
#include <vector>
#include <math.h>

using namespace std;

void MeioDeComunicacao(int*,int);

/*************************************************************
* Camada Transmissora
*********************************************************** */

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(string);
void CamadaFisicaTransmissora(int*, int);

int* CamadaFisicaTransmissoraCodificacaoBinaria (int quadro []);
int* CamadaFisicaTransmissoraCodificacaoManchester (int quadro []);
int* CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int quadro []);

/*************************************************************
* Camada Receptora
*********************************************************** */

void AplicacaoReceptora (string mensagem); 
void CamadaDeAplicacaoReceptora (int quadro []);
void CamadaFisicaReceptora (int*);

int* CamadaFisicaReceptoraCodificacaoBinaria (int quadro []);
int* CamadaFisicaReceptoraCodificacaoManchester (int quadro []);
int* CamadaFisicaReceptoraCodificacaoManchesterDiferencial(int quadro[]);

#endif 	//CAMADAFISICA_H
