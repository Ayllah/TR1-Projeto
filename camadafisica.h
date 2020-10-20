#ifndef CAMADAFISICA_H
#define CAMADAFISICA_H

/*************************************************************
* Camada Transmissora
*********************************************************** */

int[] CamadaFisicaTransmissoraCodificacaoBinaria (int quadro []);
int[] CamadaFisicaTransmissoraCodificacaoManchester (int quadro []);
int[] CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int quadro []);

/*************************************************************
* Camada Receptora
*********************************************************** */

int[] CamadaFisicaReceptoraCodificacaoBinaria (int quadro []);
int[] CamadaFisicaReceptoraCodificacaoManchester (int quadro []);
int[] CamadaFisicaReceptoraCodificacaoManchesterDiferencial(int quadro[]);

#endif 	//CAMADAFISICA_H
