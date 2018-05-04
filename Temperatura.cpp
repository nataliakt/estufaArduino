/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 01/04/2016

  Descrição:
  Código fonte (source) da biblioteca para o uso do Sensor DS18B20 (Temperatura)

*/

#include "Arduino.h"
#include "Temperatura.h"

Temperatura::Temperatura() {
  _indice = 0;
  _titulo = "TEMPERATURA"; 
  _arquivo = "tmp";
}

float Temperatura::ler() {
  
  OneWire ds(3); // pino do sensor
  
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
    //no more sensors on chain, reset search
    ds.reset_search();
    return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);


  for (int i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float TRead = ((MSB << 8) | LSB);
  float Temperature = TRead / 16;
  //Serial.println("Temperatura: " + (String)Temperature);
  return Temperature;
}

boolean Temperatura::coletar() { // Adiciona no array mais uma temperatura
  if (_indice < 15) { // Se for menor que 15 adiciona no array
    _array[_indice] = ler(); // Adiciona a temperatura em um array
    _indice++;
    return false;
  } else { // Se maior que 15 então reinicia o contador
    _indice = 0;
    return true;
  }
}
