/* GPA2 - IFC
Criado Por: Natalia Kelim Thiel
Data: 06/04/2016

Descrição:
Cabeçalho (header) da biblioteca para o uso do Sensor de Luminosidade (LDR)

*/

#ifndef Luminosidade_h
#define Luminosidade_h

#include "Arduino.h"
#include "Variavel.h"

#include "Erro.h"
#include "LDR.h" // Sensor

class Luminosidade : public Variavel{
public:
  Luminosidade();
  virtual float ler();
  virtual boolean coletar();
private:
  LDR *_sensor;
};

#endif
