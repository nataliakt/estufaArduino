/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 18/05/2016

  Descrição:
  Código fonte (source) da biblioteca para manipulação dos registros

*/

#include "Registro.h"

/*static*/int Registro::_dia;
/*static*/int Registro::_mes;
/*static*/int Registro::_ano;
/*static*/int Registro::_posicao;
/*static*/boolean Registro::mudanca;
/*static*/Variavel *Registro::_variavel[2];
/*static*/int Registro::_varAtual;
/*static*/boolean Registro::_existencia;
/*static*/boolean Registro::exibindo;

Registro::Registro() {
  novo();
}

void Registro::novo() {
  Registro::_dia = Rtc::dia();
  Registro::_mes = Rtc::mes();
  Registro::_ano = Rtc::ano();
  Registro::_posicao = 0;
  Registro::mudanca = true;
  Registro::_existencia = false;
  Registro::exibindo = false;
  delete _variavel[0];
  delete _variavel[1];
  _variavel[0] = new Temperatura();
  _variavel[1] = new Luminosidade();
}

void Registro::setDia(int dia) {
  if (dia > diaMaximo(_mes)) { // Se o dia for maior que o dia máximo
    _dia = 1; // Dia 1 do próximo mes
    setMes(_mes + 1); // O proximo mês

  } else if (dia <= 0) { // Se o dia for menor ou igual a 0
    setMes(_mes - 1);
    _dia = diaMaximo(getMes());

  } else {
    _dia = dia;
  }
}

void Registro::setMes(int mes) {
  if (mes > 12) {
    _mes = 1;
    setAno(_ano + 1);
    if (_dia > diaMaximo(_mes)) {
      _dia = diaMaximo(_mes);
    }

  } else if (mes <= 0) {
    _mes = 12;
    setAno(_ano - 1);
    if (_dia > diaMaximo(_mes)) {
      _dia = diaMaximo(_mes);
    }

  } else {
    _mes = mes;
    if (_dia > diaMaximo(_mes)) {
      _dia = diaMaximo(_mes);
    }

  }
}

void Registro::setAno(int ano) {
  _ano = ano;
}

int Registro::getDia() {
  return _dia;
}

int Registro::getMes() {
  return _mes;
}

int Registro::getAno() {
  return _ano;
}

int Registro::diaMaximo(int mes) {
  switch (mes) { // Verifica o dia máximo do mês
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
      break;

    case 2:
      return 29;
      break;

    default:
      return 31;
      break;
  }
}

void Registro::escolher(int botao) {
  switch (botao) { // Seleciona Botão
    case 1: // Botão Topo
      if (_posicao == 0) {
        setDia(_dia + 1);
      } else if (_posicao == 1) {
        setMes(_mes + 1);
      } else if (_posicao == 2) {
        setAno(_ano + 1);
      }
      break;

    case 2: // Botão Direito
      if (_posicao == 2) {
        _posicao = 0;
      } else {
        _posicao++;
      }
      break;

    case 3: // Botão Baixo
      if (_posicao == 0) {
        setDia(_dia - 1);
      } else if (_posicao == 1) {
        setMes(_mes - 1);
      } else if (_posicao == 2) {
        setAno(_ano - 1);
      }
      break;

    case 4: // Botão Esquerdo
      if (_posicao == 0) {
        _posicao = 2;
      } else {
        _posicao--;
      }
      break;

    case 5:
      _posicao = 3;
      exibindo = false;
      break;
  }
  mudanca = true;
}

void Registro::exibir() {
  Display::limpar();
  if (_posicao == 3) {
    exibindo = true;
    if (_existencia) {
      Display::baseAtual(_variavel[Teclado::x]->getTitulo());
      Display::escrever(" Data ", 1, 7);
      Display::atual(_variavel[Teclado::x]->formatar((String)_variavel[Teclado::x]->getMinima(), 1, 6), // Mínima
                 Rtc::hora((String)_variavel[Teclado::x]->getMinTempo()), // Hora Máxima
                 Rtc::formatar(_dia) + "-" + Rtc::formatar(_mes), // Data
                 (String)_ano, // Ano
                 _variavel[Teclado::x]->formatar((String)_variavel[Teclado::x]->getMaxima(), 1, 6), // Máxima
                 Rtc::hora((String)_variavel[Teclado::x]->getMaxTempo())); // Hora Máxima
    } else {
      // Busca os registros
      String data = Rtc::formatar(_dia) + "-" + Rtc::formatar(_mes) + "-" + (String)_ano;
      if (data != Rtc::data(Rtc::getTempo()) && Datalogger::interpretar(data, _variavel[0])) {
        Datalogger::interpretar(data, _variavel[1]);
        _existencia = true;
        mudanca = true;
      } else {
        _existencia = false;
        Display::escrever("Nenhum registro ou", 0, 0);
        Display::escrever("data igual a atual!", 1, 0);
        Display::escrever("Centro = Voltar", 3, 0);
      }
      
    }
  } else {
    if (_posicao == 0) {
      Display::escrever("__", 0, 6);
    } else if (_posicao == 1) {
      Display::escrever("__", 0, 9);
    } else {
      Display::escrever("____", 0, 12);
    }
    Display::escrever("Data: ", 1, 0);
    Display::escrever(Rtc::formatar(_dia), 1, 6);
    Display::escrever(Rtc::formatar(_mes), 1, 9);
    Display::escrever((String)_ano, 1, 12);
    Display::escrever("Aperte = BUSCAR", 2, 0);
    Display::escrever("Manter = SAIR", 3, 0);
  }
}

int Registro::getPosicao() {
  return _posicao;
}

