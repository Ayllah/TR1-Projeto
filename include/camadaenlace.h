#ifndef CAMADAENLACE_H
#define CAMADAENLACE_H

#include "camadafisica.h"

/*************************************************************
* Camada Transmissora
*************************************************************/
void CamadaEnlaceDadosTransmissora (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (vector<int> quadro);

/*************************************************************
* Camada Receptora
*************************************************************/
void CamadaEnlaceDadosReceptora (vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres (vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes (vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits (vector<int> quadro);

#endif 	//CAMADAENLACE_H
