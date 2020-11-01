#ifndef CAMADAFISICA_H
#define CAMADAFISICA_H

#include <iostream>
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

/**
 * Recebe um quadro de 8 bits e utiliza a codificação Binária.
 * Na Codificação binária retorna o quadro de 8 bits com os mesmos
 * valores lógicos entre cada clock
*/
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (bitset<8> quadro);

/**
 * Recebe um quadro de 8 bits e utiliza a codificação Manchester.
 * Na codificação Manchester um 0 lógico gera uma transição de 0 para 1 
 * no centro do bit e um 1 lógico é gera uma transição de 1 para 0
*/
vector<int> CamadaFisicaTransmissoraCodificacaoManchester (bitset<8> quadro);

/**
 * Recebe um quadro de 8 bits e utiliza a codificação Manchester Diferencial.
 * Na codificação Manchester Diferencial a transição no meio do bit é usada apenas para
 * sincronização. A representação do bit é definida pela inversão “bit 0” ou não inversão 
 * “bit 1” no início do bit.
*/
vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(bitset<8> quadro);

/*************************************************************
* Camada Receptora
*************************************************************/

void AplicacaoReceptora (string mensagem);
void CamadaFisicaReceptora (vector<int> quadro, int tam);
void CamadaDeAplicacaoReceptora (vector<int> quadro);

/**
 * Recebe um quadro de 8 bits e utiliza a decodificação Binária.
 * Decodificação binária retorna o quadro de 8 bits com os mesmos 
 * valores lógicos entre cada clock
*/
vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (vector<int> quadro);

/**
 * Recebe um quadro de 8 bits e utiliza a decodificação Manchester.
 * Na decodificação Manchester um par 01 lógico gera o valor lógico 0 
 * e um par lógico 10 gera o valor lógico 1
*/
vector<int> CamadaFisicaReceptoraDecodificacaoManchester (vector<int> quadro);

/**
 * Recebe um quadro de 8 bits e utiliza a decodificação Manchester Diferencial.
 * Na decodificação Manchester Diferencial o primeiro par 01 lógico gera o 
 * valor lógico 0 e um primeiro par lógico 10 gera o valor lógico 1. 
 * Nas demais posições verifica-se o par lógico seguinte, caso seja igual ao 
 * anterior, é gerado o valor lógico 0, caso contrário gera-se o valor lógico 1
*/
vector<int> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(vector<int> quadro);

#endif 	//CAMADAFISICA_H
