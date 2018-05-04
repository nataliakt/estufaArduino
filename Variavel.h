/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 11/03/2016

  Descrição:
  Cabeçalho (header) da biblioteca para processos de variáveis

*/

#ifndef Variavel_h
#define Variavel_h

#include "Arduino.h"

class Variavel
{
  public:
    // Construtor (vazio)
    Variavel();
    // Atualiza mínima e máxima
    void atualizarMinMax(String data, float var, String varTempo);
    // Faz a média do array
    float media();
    // Formata casas decimais
    String formatar(String variavel, int casa, int maximo);
    // Retorna a atual
    float getAtual();
    // Seta a atual
    void setAtual(float atual);
    // Retorna a máxima e tempo dela
    float getMaxima();
    String getMaxTempo();
    // Retorna a mínima e tempo dela
    float getMinima();
    String getMinTempo();
    // Retorna o titulo
    String getTitulo();
    // Retorna o arquivo
    String getArquivo();
    // Le o sensor
    virtual float ler(){
      Serial.println("Variavel ler");
      return 0;
    };
    // Coleta a variável e armazena no array
    virtual boolean coletar() {
      Serial.println("Variavel coletar");
      return false;
    };
  protected:
    int _indice;
    float _atual;
    float _maxima;
    float _minima;
    String _maxTempo;
    String _minTempo;
    float _array[15];
    // inicial do arquivo no cartão SD
    String _arquivo;
    // titulo que aparece no display
    String _titulo;
  private:
    // Remove valores extrapolantes
    float _removeIsolados(float media);
};

#endif
