/* GPA2 - IFC
Criado Por: Natalia Kelim Thiel
Data: 07/04/2016

Descrição:
Cabeçalho (header) da biblioteca para uso do Data Logger

*/

#ifndef Datalogger_h
#define Datalogger_h

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"
#include "Erro.h"
#include "Rtc.h"
#include "Variavel.h"
#include "Display.h"

class Datalogger{
public:
  Datalogger();
  String static salvar(Variavel *var);
  boolean static interpretar(String data, Variavel *var);
};

#endif
