/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 18/05/2016

  Descrição:
  Cabeçalho (header) da biblioteca para manipulação dos registros

*/

#ifndef Registro_h
#define Registro_h

#include "Arduino.h"
#include "Rtc.h"
#include "Variavel.h"
#include "Temperatura.h"
#include "Luminosidade.h"
#include "Datalogger.h"
#include "Teclado.h"

class Registro{
  public:
    Registro();
    void static novo();
    void static escolher(int botao);
    void static setDia(int dia);
    void static setMes(int mes);
    void static setAno(int ano);
    int static getDia();
    int static getMes();
    int static getAno();
    int static diaMaximo(int mes);
    void static exibir();
    boolean static mudanca;
    int static getPosicao();
    boolean static exibindo;
  private:
    int static  _dia;
    int static _mes;
    int static _ano;
    int static _posicao; // Posição onde alterar (dia, mes, ano ou exibindo)
    Variavel static *_variavel[];
    int static _varAtual;
    boolean static _existencia;
};

#endif

