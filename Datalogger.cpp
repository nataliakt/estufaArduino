/* GPA2 - IFC
  Criado Por: Natalia Kelim Thiel
  Data: 07/04/2016

  Descrição:
  Código fonte (source) da biblioteca para  uso do Data Logger

*/

#include "Datalogger.h"

Datalogger::Datalogger() {
  pinMode(53, OUTPUT); // Inicia o cartão sd
  if (!SD.begin(53)) {
    Erro::adicionarErro("Datalogger ou MicroSD não Encontrado");
  }
  //SD.remove("tmp.txt");
}

String Datalogger::salvar(Variavel *var) {
  String tempo = Rtc::getTempo();
  String data = Rtc::data(tempo);
  String arquivo = data.substring(0, 2) + data.substring(3, 5) + data.substring(6, 10) + "." + var->getArquivo();
  File file = SD.open(arquivo, FILE_WRITE); // Abrir o arquivo
  String mensagem = (String)var->getAtual() + "/" + tempo + ";";

  if (file) { // Se abrir:
    file.print(mensagem);
    file.close();
  } else {
    Serial.println("Erro ao abrir " + arquivo);
  }
  return tempo;
}

boolean Datalogger::interpretar(String data, Variavel *var) {
  String arquivo = data.substring(0, 2) + data.substring(3, 5) + data.substring(6, 10) + "." + var->getArquivo();
  File file = SD.open(arquivo);
  String leitura, variavel, tempo;
  int contador = 0;

  Display::limpar();
  Display::escrever(var->getTitulo() + "...", 0, 0);
  Display::escrever(data, 1, 0);
  if (file) {
    Display::escrever("Registros lidos:", 2, 0);
    while (file.available()) {
      // Limpando as variáveis
      variavel = "";
      tempo = "";
      leitura = "";
      // Percorre os caracteres da variavel
      while (leitura != "/") {
        variavel += leitura;
        leitura = (char)file.read();
      }
      // Limpa a variável leitura
      leitura = "";
      // Percorre os caracteres do tempo
      while (leitura != ";") {
        tempo += leitura;
        leitura = (char)file.read();
      }

      // Prepara a variavel char
      char variavelChar[variavel.length()];
      // atribui a variavel char o valor da variavel
      variavel.toCharArray(variavelChar, variavel.length());
      // converte de char[] para float
      float variavelFloat = strtod(variavelChar, NULL);

      var->atualizarMinMax(data, variavelFloat, tempo);
      contador++;
      Display::escrever((String)contador, 3, 0);
    }

    file.close();
  } else {
    Serial.println("Erro ao abrir " + arquivo);
    return false;
  }
  return true;
}
