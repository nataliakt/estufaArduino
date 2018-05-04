/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 01/04/2016

  Descrição:
  Cabeçalho (header) da biblioteca para gerenciamento de erros

  Requisitos:
  <nenhum>
*/

#ifndef Erro_h
#define Erro_h

#include "Arduino.h"

class Erro
{
  public:
    Erro();
    // Adiciona mensagens de erro à String _erro
    void static adicionarErro(String erro);
    String static getErro();
  private:
    String static _erro;
};

#endif
