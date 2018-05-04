/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 11/03/2016

  Descrição:
  Código fonte (source) da biblioteca para o uso do LCD 20x4

*/

#include "Display.h"

/*static*/ LiquidCrystal_I2C *Display::_lcd;
/*static*/ byte Display::_grau[8] = { // "desenha" a bolinha do grau ( º )
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

Display::Display() {
  _lcd = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Inicializa o LCD
  _lcd->begin(20, 4); // 20 colunas, 4 linhas
  _lcd->createChar(0, _grau); // Cria o caractere grau
  _lcd->setBacklight(HIGH); // Acende a luz principal
  limpar();
}

void Display::escrever(String texto, int linha, int coluna) {
  Display::_lcd->setCursor(coluna, linha); // Posiciona o cursor
  Display::_lcd->print(texto); // Escreve no lcd
  /*while (texto != "") {
    Display::_lcd->setCursor(coluna, linha); // Posiciona o cursor
    if (texto.length() > 20) {
      Display::_lcd->print(texto.substring(0, 20)); // Escreve no lcd
      linha++;
      coluna = 0;
      if (linha == 4)linha = 0;
      texto = texto.substring(20, texto.length());
    }else{
      Display::_lcd->print(texto); // Escreve no lcd
      texto = "";
    }
  }*/
}

void Display::limpar() {
  _lcd->clear();
}

void Display::menu(int posicao) {
  escrever(" ====== MENU ====== ", 0, 0); // Escreve o título

  String selecao = (posicao == 0 ? "--" : "  "); // Verifica se está selecionado
  escrever("    " + selecao + " Atual " + selecao + "     ", 1, 0); // Escreve a opção

  selecao = (posicao == 1 ? "--" : "  ");
  escrever("  " + selecao + " Registros " + selecao + "   ", 2, 0);

  selecao = (posicao == 2 ? "--" : "  ");
  escrever("   " + selecao + " Ajustes " + selecao + "    ", 3, 0);
}

void Display::baseAtual(String titulo) {
  escrever("<", 0, 1); // Flecha esquerda
  escrever(titulo, 0, (int)((20 - titulo.length()) / 2)); // Exibe o título no centro
  escrever(">", 0, 18); // Flecha direita
  escrever(" Min. |Atual | Max. ", 1, 0);
  escrever("      |      |      ", 2, 0);
  escrever("      |      |      ", 3, 0);
}

void Display::atual(String minima, String minTempo, String atual, String atualTempo, String maxima, String maxTempo) {
  // Mínimo
  escrever(minima, 2, 0); // Exibe mínimo
  escrever(minTempo, 3, 0); // Exibe o tempo mínimo

  // Atual
  escrever(atual, 2, 7); // Exibe atual
  escrever(atualTempo, 3, 7); // Exibe o tempo atual

  // Máximo
  escrever(maxima, 2, 14); // Exibe máximo
  escrever(maxTempo, 3, 14); // Exibe o tempo máximo
  
}
void Display::tempoAtual(String tempoAtual) {
  escrever(tempoAtual, 3, 7); // Exibe o tempo atual
}

