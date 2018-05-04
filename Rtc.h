/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 06/04/2016

  Descrição:
  Cabeçalho (header) da biblioteca para o uso do RTC (Real Time Clock)

*/

#ifndef Rtc_h
#define Rtc_h

#include "Arduino.h"

#include "Erro.h" // Interna

#include "TimeLib.h" // Formataçao e Aquisição
#include "Wire.h" // Comunicação
#include "DS1307RTC.h" // Componente

class Rtc {
  public:
    Rtc();
    void static ajustar(int hora, int minuto, int segundo, int dia, int mes, int ano);
    // Formata adicionando 0 no começo
    String static formatar(int valor);
    String static getTempo();
    String static hora(String tempo);
    String static data(String tempo);
    int static dia();
    int static mes();
    int static ano();
    int static hora();
    int static minuto();
    int static segundo();
};

#endif
