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
*************************************************************/

void AplicacaoTransmissora ();
void CamadaFisicaTransmissora (bitset<8> quadro);
void CamadaDeAplicacaoTransmissora (string mensagem);


/* 
*/
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (bitset<8> quadro);

/*	Essa função recebe um quadro de 8 bits e utiliza a codificação Manchester.
*	Na codificação Manchester um 0 lógico é indicado por uma transição de 0 
*   para 1 no centro do bit e um 1 lógico é indicado por uma transição de 1 
*	para 1 para 0. */
vector<int> CamadaFisicaTransmissoraCodificacaoManchester (bitset<8> quadro);


/*	Essa função recebe um quadro de 8 bits e utiliza a codificação Manchester Diferencial.
*	Na codificação Manchester Diferencial  a transição no meio do bit é usada apenas para 
*   sincronização. A representação do bit é definida pela inversão “bit 0” ou não inversão 
*  “bit 1” no início do bit.*/
vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(bitset<8> quadro);

/*************************************************************
* Camada Receptora
*************************************************************/

void AplicacaoReceptora (string mensagem);
void CamadaFisicaReceptora (vector<int> quadro, int tam);
void CamadaDeAplicacaoReceptora (vector<int> quadro);

vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (vector<int> quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoManchester (vector<int> quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro);

#endif 	//CAMADAFISICA_H
