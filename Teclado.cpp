/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 06/04/2016

  Descrição:
  Código fonte (source) da biblioteca para uso do Teclado Analógico

*/

#include "Teclado.h"

/*static*/int Teclado::_pino;
/*static*/boolean Teclado::mudanca;
/*static*/int Teclado::menu;
/*static*/int Teclado::x;
/*static*/int Teclado::_xMax;
/*static*/int Teclado::y;
/*static*/int Teclado::_yMax;

Teclado::Teclado() {
  _pino = A3;
  mudanca = false;
  menu = 0;
  x = 0;
  _xMax = 1;
  y = 0;
  _yMax = 2;
}

int Teclado::ler() { // Faz a leitura do pino e interpreta os valores
  int valor = analogRead(_pino);
  if (valor > 244 && valor < 264) { // Topo
    return 1;
  } else if (valor > 1005 && valor < 1025) { // Direita
    return 4;
  } else if (valor > 496 && valor < 516) { // Baixo
    return 3;
  } else if (valor > 193 && valor < 213) { // Esquerda
    return 2;
  } else if (valor > 328 && valor < 348) { // Meio
    return 5;
  } else { // Nenhum botão
    return -1;
  }
}

void Teclado::apertar(int botao) { // Faz algo quando o botão é apertado

  switch (botao) { // Seleciona Botão

    case 1: // Botão Topo
      if (y == 0) { // Se já estiver no mínimo vai para o máximo
        y = _yMax;
      } else { // Senão decrementa
        y--;
      }
      break;

    case 2: // Botão Direito
      if (x == _xMax) { // Se já estiver no máximo volta para o mínimo
        x = 0;
      } else { // Senão acrescenta mais 1
        x++;
      }
      break;

    case 3: // Botão Baixo
      if (y == _yMax) { // Se já estiver no máximo vai para o mínimo
        y = 0;
      } else { // Senão diminui 1
        y++;
      }
      break;

    case 4: // Botão Esquerdo
      if (x == 0) { // Se já estiver no mínimo vai para o máximo
        x = _xMax;
      } else { // Senão diminui 1
        x--;
      }
      break;

    case 5:
      _entrar();
      break;
  }
  mudanca = true; // Diz que houve uma mudança
}

void Teclado::_entrar() { // Escolhe a opção caso o botao meio seja pressionado
  switch (menu) {

    case 0: // No menu inicial, seleciona a opção
      menu = y + 1;
      x = 0;
      if(menu == 2)
        Registro::novo();
      if(menu == 3)
        Ajuste::novo();
      
      break;

    case 1: // Na exibição atual, volta ao menu inicial
      menu = 0;
      y = 0;
      break;

    case 2:
      if(Registro::exibindo){
        menu = 0;
        y = 0;
      }
      break;

    default:
      menu = 0;
      y = 0;
      break;
  }
}

void Teclado::deixarApertado(int botao) {
  if (botao == 5) {
    Teclado::menu = 0;
    Teclado::x = 0;
    Teclado::y = 0;
  }
}

