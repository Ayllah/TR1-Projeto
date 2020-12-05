#ifndef CAMADAENLACE_H
#define CAMADAENLACE_H

#include "camadafisica.h"

string decimalToBinary(int number);

/*************************************************************
* Camada Transmissora
*************************************************************/

/*************************************************************
*                       ENQUADRAMENTO
*************************************************************/
void CamadaEnlaceDadosTransmissora (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro);

/**
 * Protocolo que utiliza cabeçalhos para especificar o número de Bytes no quadro.
*/
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (vector<int> quadro);

/**
 * Cada quadro começa e termina com um byte especial, denominado de byte de flag. 
 * Caso o receptor perca a sincronização, ele pode encontrar o final do quadro atual
 * e o início do seguinte identificando apenas a presença de 2 bytes de flag consecutivos.
 * Quando há o padrão de byte de flag na carga útil, adiciona-se um byte especial de escape (ESC)
 * imediatamente antes de cada byte de flag que seja “acidental” no campo de dados.
 * Se caso ainda for encontrado  um byte ESC no campo de carga útil, realiza-se a mesma estratégia,
 * imediatamente antes do byte de escape, é adicionado outro byte ESC. 
*/
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (vector<int> quadro);

/**
 * Utiliza a inserção ao nível de bits, portanto os quadros podem ter qualquer número de bits.
 * Cada quadro começa e termina com um padrão de sequência de bits especial, o qual na prática
 * funciona como um byte de flag, composto por ‘01111110’ ou 0x7E em formato hexadecimal.
 * Para evitar que haja a ocorrência da sequência de bits especiais no campo de carga útil, toda
 * vez que identifica-se a presença de cinco bits ‘1’ nos dados, é inserido um bit ‘0’ após a essa
 *  sequência.
*/
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (vector<int> quadro);



/*************************************************************
*                      CONTROLE DE ERRO
*************************************************************/
vector<int> CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (vector<int> quadro);

/*************************************************************
* Camada Receptora
*************************************************************/

/*************************************************************
*                       ENQUADRAMENTO
*************************************************************/
void CamadaEnlaceDadosReceptora (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro);

/**
 * Recebe os quadros e identifica através dos cabeçalhos a quantidade de bytes de cada quadro
 * recebido e portanto o final dos dados recebidos. Com esses dados retira os cabeçalhos.
*/
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres (vector<int> quadro);

/**
 * Recebe os quadros, realiza as identificações das flags e as retira.
*/
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes (vector<int> quadro);

/**
 * Recebe os quadros, realiza a identificação das sequências especiais, as retira e logo após
 * verifica o caso da inserção dos 0 após sequências de '11111', caso existam, esses 0 que foram
 * adicionados são retirados.
*/
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits (vector<int> quadro);


/*************************************************************
*                      CONTROLE DE ERRO
*************************************************************/
vector<int> CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (vector<int> quadro);

#endif 	//CAMADAENLACE_H
