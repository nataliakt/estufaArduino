/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 01/04/2016

  Descrição:
  Código fonte (source) da biblioteca para gerenciamento de erros

  Requisitos:
  <nenhum>
*/

#include "Arduino.h"
#include "Erro.h"

/*static*/ String Erro::_erro;

Erro::Erro() {

}

void Erro::adicionarErro(String erro) {
  _erro += erro + "; ";
}

String Erro::getErro(){
  return _erro;
}

