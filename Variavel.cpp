/* GPA2 - IFC
Criado Por: Natalia Kelim Thiel
Data: 11/03/2016

Descrição:
Código fonte (source) da biblioteca para processos de variáveis

*/

#include "Arduino.h"
#include "Variavel.h"

Variavel::Variavel(){}

void Variavel::atualizarMinMax(String data, float var, String varTempo){
  String varHora = varTempo.substring(0, 8); // Hora da variavel
  String varData = varTempo.substring(9, 19); // Data da variavel

  String maxHora = _maxTempo.substring(0, 8); // Hora da máxima
  String maxData = _maxTempo.substring(9, 19); // Data da máxima

  String minHora = _minTempo.substring(0, 8); // Hora da mínima
  String minData = _minTempo.substring(9, 19); // Data da mínima

  if (varData.compareTo(data) == 0) { // Se a data da variavel for a mesma passada
    if (maxData.compareTo(data) == 0) { // Se a data do maximo for data passada então compara
      if (var >= _maxima) { // Se a variavel for maior ou igual que a máxima
        _maxima = var;
        _maxTempo = varTempo;
      }
    } else { // Se a data do máximo não for data passada apenas adiciona a variável
      _maxima = var;
      _maxTempo = varTempo;
    }

    if (minData.compareTo(data) == 0) { // Se a data do mínimo for data passada então compara
      if (var <= _minima) { // Se a variável for menor ou igual a mínima
        _minima = var;
        _minTempo = varTempo;
      }
    } else { // Se a data do mínimo não for data passada apenas adiciona a variavel
      _minima = var;
      _minTempo = varTempo;
    }
  }
}

float Variavel::_removeIsolados(float media){
  float soma = 0; // Soma dos selecionados
  int restantes = 0; // Número de normais
  for (int i = 0; i < 15; i++) { // Percorre
    if (!(_array[i] < media - 10 || _array[i] > media + 10)) { // Se a variavel for isolada, ela não é somada
      soma += _array[i]; // Adiciona a soma
      restantes++; // Incrementa para saber quantos elemetos permanecem
    }
  }
  return soma / restantes;
}

float Variavel::media(){

  float soma = 0;
  float media = 0;

  for (int i = 0; i < 15; i++) { // Percorre as posiçõe
    soma += _array[i]; // Soma o elemento
  }
  media =  soma / 15; // Faz a média
  return _removeIsolados(media); // Remove valores isolados
}

String Variavel::formatar(String variavel, int casa, int maximo){
  int tamanho = variavel.length(); // Tamanho da variavel
  int ponto = tamanho; // Posição do ponto
  String nova = ""; // Nova string formatada
  int contador = 0; // Contador de casa atual
  for(int i = 0; i < tamanho - 1; i++){ // Percorre todas as letras
    if(variavel.substring(i, i + 1) == "."){ // Se o caracter for ponto (.)
      ponto = i; // Atribui a posição ao ponto
      if(casa > 0){ // Se casas deciamais maior que 0 adiciona o ponto
        nova += variavel.substring(i, i + 1);
      }
    }else if(i < ponto){ // Escreve os numeros antes da vírgula
      nova += variavel.substring(i, i + 1);
    }else if(contador < casa){ // Escreve os valores depois da vírgula
      nova += variavel.substring(i, i + 1);
      contador++;
    }
  }
  tamanho = nova.length(); // Atrubui o tamanho novo
  if (tamanho <= maximo) { // Se o comprimento for até máximo é suportado
    return nova;
  } else {
    return "ERRO"; // Erro quando excede o permitido
  }
}
void Variavel::setAtual(float atual){
  _atual = atual;
}
float Variavel::getAtual(){
  return _atual;
}
float Variavel::getMaxima(){
  return _maxima;
}
float Variavel::getMinima(){
  return _minima;
}
String Variavel::getMaxTempo(){
  return _maxTempo;
}
String Variavel::getMinTempo(){
  return _minTempo;
}
String Variavel::getArquivo(){
  return _arquivo;
}
String Variavel::getTitulo(){
  return _titulo;
}
