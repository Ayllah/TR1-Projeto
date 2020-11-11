#ifndef CAMADAENLACE_H
#define CAMADAENLACE_H

#include "camadafisica.h"

/*************************************************************
* Camada Transmissora
*************************************************************/
void CamadaEnlaceDadosTransmissora (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (vector<int> quadro);

/*************************************************************
* Camada Receptora
*************************************************************/
void CamadaEnlaceDadosReceptora (vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits (vector<int> quadro);

#endif 	//CAMADAENLACE_H
