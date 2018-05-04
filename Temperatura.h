/* GPA2 - IFC
Criado Por: Natalia Kelim Thiel
Data: 01/04/2016

Descrição:
Cabeçalho (header) da biblioteca para o uso do Sensor DS18B20 (Temperatura)

*/

#ifndef Temperatura_h
#define Temperatura_h

#include "Arduino.h"
#include "Variavel.h"
#include "Erro.h"
#include "OneWire.h" // Comunicação

class Temperatura : public Variavel{
public:
  Temperatura();
  virtual float ler();
  virtual boolean coletar();
private:
  OneWire *_ds;
};

#endif
