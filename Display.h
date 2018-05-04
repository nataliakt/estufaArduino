/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 11/03/2016

  Descrição:
  Cabeçalho (header) da biblioteca para o uso do LCD 20x4

*/

#ifndef Display_h
#define Display_h

#include "Arduino.h"

class Display;

#include "Wire.h" // Comunicação
#include "LiquidCrystal_I2C.h" // Biblioteca para uso do Módulo
#include "Rtc.h"

class Display
{
  public:
    // Construtor iniciando lcd
    Display();
    // Escreve no lcd na posição
    void static escrever(String texto, int linha, int coluna);
    // Limpa o lcd
    void static limpar();
    // Escreve o menu no lcd e marca a posição
    void static menu(int posicao);
    // Escreve a base do atual com um título
    void static baseAtual(String titulo);
    // Atualiza as informações atuais
    void static atual(String min, String minTempo, String atual, String atualTempo, String max, String maxTempo);
    // Atualiza o tempo atual
    void static tempoAtual(String atualTempo);
  private:
    LiquidCrystal_I2C static *_lcd;
    byte static _grau[];
};

#endif
