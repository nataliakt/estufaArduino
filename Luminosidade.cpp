/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 06/04/2016

  Descrição:
  Código fonte (source) da biblioteca para o uso do Sensor de Luminosidade (LDR)

*/

#include "Luminosidade.h"

Luminosidade::Luminosidade() {
  _indice = 0;
  _titulo = "LUMINOSIDADE";
  _arquivo = "ldr";
  //LDR _sensor(0);
  pinMode(0, INPUT);
}

float Luminosidade::ler() {
  float lum = analogRead(0);
  lum = pow((55000000 / (50000 / ((5 * (lum / 1024))) - 10000)), (1 / 1.8745)); // converte em lux
  //Serial.println("Luminosidade: " + (String)lum);
  return lum;
}

boolean Luminosidade::coletar() { // Adiciona no array mais uma temperatura
  if (_indice < 15) { // Se for menor que 15 adiciona no array
    _array[_indice] = ler(); // Adiciona em um array
    _indice++;
    return false;
  } else { // Se maior que 15 então reinicia o contador
    _indice = 0;
    return true;
  }
}
