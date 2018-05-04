// Includes Externos
#include "TimerOne.h" // Interrupção para ler os botões

// Includes Internos
#include "Display.h"
#include "Rtc.h"
#include "Temperatura.h"
#include "Luminosidade.h"
#include "Teclado.h"
#include "Datalogger.h"
#include "Registro.h"
#include "Ajuste.h"

// Declarações
Temperatura tmp;
Luminosidade ldr;

// Variáveis
int contagem = 0; // Número de execuções do loop()
int botaoAnt = 0; // Botão anterior apertado
int botaoTempo = 0; // Tempo que o botão está apertado
int varSize = 2; // Número de variáveis
Variavel *variavel[] = {&tmp, &ldr}; // Array das variáveis

void interrupcao() {
  // Lê o botão
  int botao = Teclado::ler();
  // Verifica se é igual ao anterior
  if (botaoAnt == botao) {
    // Botão pressionado ainda
    botaoTempo++;
  } else {

    // Verifica se o botão foi precionado normalmente
    if (botaoTempo < 20 && botaoTempo > 0) {
      if (Teclado::menu == 2 && Registro::getPosicao() != 3) { // Se estiver no menu registros
        // Muda as datas exibidas
        Registro::escolher(botaoAnt);
      } if(Teclado::menu == 3 && Ajuste::getPosicao() != 6){
        // Muda a data e hora exibidas
        Ajuste::escolher(botaoAnt);
      } else {
        // Executa uma ação de apertar
        Teclado::apertar(botaoAnt);
      }
    } else if (botaoTempo >= 10) {
      Teclado::deixarApertado(botaoAnt);
    }

    // Resseta o tempo
    botaoTempo = 0;
    // O botão atual é o botão anterior
    botaoAnt = botao;
  }
}

void setup() {
  // "Begin's"
  Serial.begin(9600);

  // Instâncias não utilizadas
  Display lcd;
  Rtc rtc;
  Datalogger dat;
  Teclado tec;
  Registro reg;
  Ajuste aju;

  if (Erro::getErro() == "") {
    iniciar();
    Timer1.initialize(30000); // Inicializa o Timer1 e configura para um período de 0,05 segundos
    Timer1.attachInterrupt(interrupcao); // Configura para a função interrupcao()
  }
}

void loop() {
  delay(250);
  // Se não houverem erros o programa executa normalmente
  if (Erro::getErro() == "") {
    if (contagem == 8) { // Dois segundos
      coletarVariaveis();
      contagem = 0;
    }

    switch (Teclado::menu) {
      case 0: // Caso menu inicial
        Display::menu(Teclado::y);
        break;
      case 1: // Caso Atual
        if (Teclado::mudanca) {
          selecionarVariavel();
          Teclado::mudanca = false;
        }
        Display::tempoAtual(Rtc::hora(Rtc::getTempo()));
        break;
      case 2: // Caso Registros
        if (Registro::mudanca || Teclado::mudanca) {
          Registro::mudanca = false;
          Teclado::mudanca = false;
          Registro::exibir();
        }
        break;
      case 3: // Caso Ajustes
        if (Ajuste::mudanca || Teclado::mudanca) {
          Ajuste::exibir();
          Ajuste::mudanca = false;
          Teclado::mudanca = false;
        }
        break;
    }

    contagem++;
  } else {
    // Exibe os erros no lcd
    Display::escrever(Erro::getErro(), 0, 0 );
  }
}

void iniciar() { // Interpreta as leituras iniciais
  for (int i = 0; i < varSize; i++) {
    float limpa;
    do {
      limpa = variavel[i]->ler(); // Primeira leitura desconsiderada
    } while (limpa == 85);
    variavel[i]->setAtual(variavel[i]->ler()); // Lê a temperatura atual
    Datalogger::salvar(variavel[i]); // Salva a temperatura atual
    Datalogger::interpretar(Rtc::data(Rtc::getTempo()), variavel[i]); // Interpreta o arquivo
  }
}

void coletarVariaveis() { // Coleta variaveis e faz a media
  // Percorre todas as variáveis
  for (int i = 0; i < varSize; i++) {
    if (variavel[i]->coletar()) {
      //Serial.println("MEDIA");
      variavel[i]->setAtual(variavel[i]->media()); // Faz a média dos favores do array e remove valores absurdos
      String tempo = Datalogger::salvar(variavel[i]); // Salva as informações no cartão e armazena a hora salva na variavel
      variavel[i]->atualizarMinMax(Rtc::data(Rtc::getTempo()), variavel[i]->getAtual(), tempo); // Atualiza temperatura maior ou menor se nescessário
      Teclado::mudanca = true;
    }
  }
}

void selecionarVariavel() {
  Display::limpar();
  Display::baseAtual(variavel[Teclado::x]->getTitulo());
  Display::atual(variavel[Teclado::x]->formatar((String)variavel[Teclado::x]->getMinima(), 1, 6), // Mínima
                 Rtc::hora((String)variavel[Teclado::x]->getMinTempo()), // Hora Máxima
                 variavel[Teclado::x]->formatar((String)variavel[Teclado::x]->getAtual(), 1, 6), // Atual
                 Rtc::hora((String)Rtc::hora(Rtc::getTempo())), // Hora Atual
                 variavel[Teclado::x]->formatar((String)variavel[Teclado::x]->getMaxima(), 1, 6), // Máxima
                 Rtc::hora((String)variavel[Teclado::x]->getMaxTempo())); // Hora Máxima

}
