/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 16/06/2016

  Descrição:
  Código fonte (source) da biblioteca para manipulação dos ajustes

*/

#include "Ajuste.h"

/*static*/int Ajuste::_dia;
/*static*/int Ajuste::_mes;
/*static*/int Ajuste::_ano;
/*static*/int Ajuste::_hora;
/*static*/int Ajuste::_minuto;
/*static*/int Ajuste::_segundo;
/*static*/int Ajuste::_posicao;
/*static*/boolean Ajuste::_setado;
/*static*/boolean Ajuste::mudanca;

Ajuste::Ajuste() {
  novo();
}

void Ajuste::novo() {
  _dia = Rtc::dia();
  _mes = Rtc::mes();
  _ano = Rtc::ano();
  _hora = Rtc::hora();
  _minuto = Rtc::minuto();
  _segundo = Rtc::segundo();
  _posicao = 0;
  mudanca = false;
  _setado = false;
}

void Ajuste::setDia(int dia) {
  if (dia > diaMaximo(_mes)) { // Se o dia for maior que o dia máximo
    _dia = 1; // Dia 1 do próximo mes
    setMes(_mes + 1); // O proximo mês

  } else if (dia <= 0) { // Se o dia for menor ou igual a 0
    setMes(_mes - 1);
    _dia = diaMaximo(_mes);

  } else {
    _dia = dia;
  }
}

void Ajuste::setMes(int mes) {
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

void Ajuste::setAno(int ano) {
  _ano = ano;
}

void Ajuste::setHora(int hora) {
  if (hora < 0) {
    _hora = 23;
  } else if (hora > 23) {
    _hora = 0;
  } else {
    _hora = hora;
  }
}

void Ajuste::setMinuto(int minuto) {
  if (minuto < 0) {
    _minuto = 59;
    setHora(_hora - 1);
  } else if (minuto > 59) {
    _minuto = 0;
    setHora(_hora + 1);
  } else {
    _minuto = minuto;
  }
}

void Ajuste::setSegundo(int segundo) {
  if (segundo < 0) {
    _segundo = 59;
    setMinuto(_minuto - 1);
  } else if (segundo > 59) {
    _segundo = 0;
    setMinuto(_minuto + 1);
  } else {
    _segundo = segundo;
  }
}

int Ajuste::diaMaximo(int mes) {
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

void Ajuste::escolher(int botao) {
  switch (botao) { // Seleciona Botão
    case 1: // Botão Topo
      switch (_posicao) {
        // Data
        case 0:
          setDia(_dia + 1);
          break;
        case 1:
          setMes(_mes + 1);
          break;
        case 2:
          setAno(_ano + 1);
          break;
        // Hora
        case 3:
          setHora(_hora + 1);
          break;
        case 4:
          setMinuto(_minuto + 1);
          break;
        case 5:
          setSegundo(_segundo + 1);
          break;
      }
      break;

    case 2: // Botão Direito
      if (_posicao == 5) {
        _posicao = 0;
      } else {
        _posicao++;
      }
      break;

    case 3: // Botão Baixo
      switch (_posicao) {
        // Data
        case 0:
          setDia(_dia - 1);
          break;
        case 1:
          setMes(_mes - 1);
          break;
        case 2:
          setAno(_ano - 1);
          break;
        // Hora
        case 3:
          setHora(_hora - 1);
          break;
        case 4:
          setMinuto(_minuto - 1);
          break;
        case 5:
          setSegundo(_segundo - 1);
          break;
      }
      break;

    case 4: // Botão Esquerdo
      if (_posicao == 0) {
        _posicao = 5;
      } else {
        _posicao--;
      }
      break;

    case 5: // Salvar
      _posicao = 6;
      break;
  }
  mudanca = true;
}

void Ajuste::exibir() {
  Display::limpar();
  if (_posicao == 6) {
    if (!_setado) {
      Rtc::ajustar(_hora, _minuto, _segundo, _dia, _mes, _ano);
    }
    Display::escrever("Tempo alterado com", 0, 0);
    Display::escrever("SUCESSO para:", 1, 0);
    Display::escrever(Rtc::formatar(_dia) + "-" + Rtc::formatar(_mes) + "-" + _ano, 2, 0);
    Display::escrever(Rtc::formatar(_hora) + ":" + Rtc::formatar(_minuto) + ":" + Rtc::formatar(_segundo), 2, 12);
    Display::escrever("Aperte para sair", 3, 0);
  } else {
    switch (_posicao) {
      case 0:
        Display::escrever("__", 0, 0);
        break;
      case 1:
        Display::escrever("__", 0, 3);
        break;
      case 2:
        Display::escrever("____", 0, 6);
        break;
      case 3:
        Display::escrever("__", 0, 12);
        break;
      case 4:
        Display::escrever("__", 0, 15);
        break;
      case 5:
        Display::escrever("__", 0, 18);
        break;
    }
    Display::escrever(Rtc::formatar(_dia) + "-", 1, 0);
    Display::escrever(Rtc::formatar(_mes) + "-", 1, 3);
    Display::escrever((String)_ano, 1, 6);
    Display::escrever(Rtc::formatar(_hora) + ":", 1, 12);
    Display::escrever(Rtc::formatar(_minuto) + ":", 1, 15);
    Display::escrever(Rtc::formatar(_segundo), 1, 18);
    Display::escrever("Aperte = SALVAR", 2, 0);
    Display::escrever("Manter = SAIR", 3, 0);
  }
}

int Ajuste::getPosicao() {
  return _posicao;
}
