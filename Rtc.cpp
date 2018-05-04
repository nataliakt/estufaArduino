/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 06/04/2016

  Descrição:
  Código fonte (source) da biblioteca para o uso do RTC (Real Time Clock)

*/

#include "Rtc.h"

Rtc::Rtc() {
  setSyncProvider(RTC.get);
  if (timeStatus() != timeSet) {
    Erro::adicionarErro("RTC não Encontrado");
  }
  //setTime(17,42,20,12,5,2016);
  //RTC.set(now());
}

void Rtc::ajustar(int hora, int minuto, int segundo, int dia, int mes, int ano) {
  setTime(hora, minuto, segundo, dia, mes, ano);
  RTC.set(now());
}

String Rtc::getTempo() {
  String tempo = "";
  tempo += formatar(hour());
  tempo += ":";
  tempo += formatar(minute());
  tempo += ":";
  tempo += formatar(second());
  tempo += "/";
  tempo += formatar(day());
  tempo += "-";
  tempo += formatar(month());
  tempo += "-";
  tempo += year();
  return tempo;
}

String Rtc::formatar(int valor) {
  String formatado = (String)valor;
  if (valor < 10) {
    formatado = "0" + formatado;
  }
  return formatado.substring(0, 2);
}

String Rtc::hora(String tempo) {
  return tempo.substring(0, 5);
}

String Rtc::data(String tempo) {
  return tempo.substring(9, 19);
}

int Rtc::dia() {
  return day();
}

int Rtc::mes() {
  return month();
}

int Rtc::ano() {
  return year();
}

int Rtc::hora() {
  return hour();
}

int Rtc::minuto() {
  return minute();
}

int Rtc::segundo() {
  return second();
}

