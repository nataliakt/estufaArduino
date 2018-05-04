/* GPA2 - IFC
Criado Por: Natalia Kelim Thiel
Data: 06/04/2016

Descrição:
Cabeçalho (header) da biblioteca para uso do Teclado Analógico

*/

#ifndef Teclado_h
#define Teclado_h

#include "Arduino.h"
#include "Registro.h"
#include "Ajuste.h"

class Teclado{
public:
  Teclado();
  int static ler();
  void static apertar(int botao);
  void static deixarApertado(int botao);
  // 0 - Inicial, 1 - Atual
  int static menu;
  // Posição na horizontal (Esquerda, Direita)
  int static x;
  // Posição na vertical (Topo, Baixo)
  int static y;
  // Se houve mudança nos menus
  boolean static mudanca;
private:
  // Pino analógico
  int static _pino;
  // Posição máxima na horizontal (Esquerda, Direita)
  int static _xMax;
  // Posição máxima na vertical (Topo, Baixo)
  int static _yMax;
  // Faz as configurações quando entra em algum menu
  void static _entrar();
};

#endif
