/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 16/06/2016

  Descrição:
  Cabeçalho (header) da biblioteca para manipulação dos ajustes

*/

#ifndef Ajuste_h
#define Ajuste_h

#include "Arduino.h"
#include "Rtc.h"
#include "Display.h"

class Ajuste {
  public:
    Ajuste();
    void static exibir();
    void static novo();
    void static escolher(int botao);
    void static setDia(int dia);
    void static setMes(int mes);
    void static setAno(int ano);
    void static setHora(int hora);
    void static setMinuto(int minuto);
    void static setSegundo(int segundo);
    int static diaMaximo(int mes);
    int static getPosicao();
    boolean static mudanca;
  private:
    int static _dia;
    int static _mes;
    int static _ano;
    int static _hora;
    int static _minuto;
    int static _segundo;
    int static _posicao;
    boolean static _setado;
};

#endif
