#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <stdlib.h>
#include <time.h>

/*-------------Globais--------------*/
int password[8];
volatile bool TimeOver = false;
int read_pot;
int time1;
float delay1;
int right = 0;
int sequenceIndex = 0;
bool gameStarted = false; // jogo só inicia quando um botão for pressionado

/*-------------Funções---------------*/

// FIX #4: removido "return password" de função void — array global é preenchido diretamente
void passwd() {
  srand(analogRead(A0)); // usa leitura analógica como semente (mais confiável no Arduino)
  for (int i = 0; i < 8; i++) {
    password[i] = (rand() % 3) + 1;
  }
}

// FIX #3: countdown agora opera diretamente na variável global time1 (sem parâmetro)
void countdown() {
  if (time1 > 0) {
    MFS.write(time1);
    time1--;
  } else {
    TimeOver = true;
    Timer1.stop();
  }
}

// FIX #5: adicionado break em cada case para evitar fall-through
void visual_feedback(int right) {
  switch (right) {
    case 1:
      MFS.writeLeds(LED_1, ON);
      break;
    case 2:
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, ON);
      break;
    case 3:
      MFS.writeLeds(LED_1 | LED_2, ON);
      break;
    case 4:
      MFS.writeLeds(LED_1 | LED_2, OFF);
      MFS.writeLeds(LED_3, ON);
      break;
    case 5:
      MFS.writeLeds(LED_1 | LED_3, ON);
      break;
    case 6:
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2 | LED_3, ON);
      break;
    case 7:
      MFS.writeLeds(LED_1 | LED_2 | LED_3, ON);
      break;
    case 8:
      MFS.writeLeds(LED_1 | LED_2 | LED_3, OFF);
      MFS.writeLeds(LED_4, ON);
      break;
  }
}

void buzzer() {
  if (time1 <= 18 && time1 > 10) {
    MFS.beep(10, 90); // beep de 100ms, silêncio de 900ms
  } else if (time1 <= 10 && time1 > 0) {
    MFS.beep(100); // beep de 1s
  }
}

// FIX #6: lógica de sequência corrigida com índice persistente
void check_buttons() {
  int buttonvalue = 0;

  // FIX #7: guardar getButton() numa variável — chamar múltiplas vezes consome o evento
  byte btn = MFS.getButton();

  // Aguarda primeiro botão para iniciar o jogo
  if (!gameStarted) {
    if (btn == BUTTON_1_PRESSED || btn == BUTTON_2_PRESSED || btn == BUTTON_3_PRESSED) {
      gameStarted = true;
      MFS.write("GO");  // exibe "GO" brevemente
      delay(1000);      // mantém por 1 segundo
      MFS.write(time1); // mostra o tempo e começa a contagem
    }
    return; // não processa sequência ainda
  }

  if (btn == BUTTON_1_PRESSED) {
    buttonvalue = 1;
  } else if (btn == BUTTON_2_PRESSED) {
    buttonvalue = 2;
  } else if (btn == BUTTON_3_PRESSED) {
    buttonvalue = 3;
  } else {
    return; // nenhum botão pressionado
  }

  if (buttonvalue == password[sequenceIndex]) {
    // Acertou a posição atual da sequência
    sequenceIndex++;
    right++;
    visual_feedback(right);
  } else {
    // Errou — reinicia sequência, LEDs e acelera o timer em 5%
    sequenceIndex = 0;
    right = 0;
    delay1 *= 0.95;
    MFS.writeLeds(LED_1 | LED_2 | LED_3 | LED_4, OFF);
  }

  // Verificação de vitória
  if (right == 8) {
    Timer1.stop();
    MFS.write("GG");
    MFS.beep(6, 4, 3); // beep 50ms, silêncio 0ms, 3 vezes
    while (1); // trava o programa
  }
}

/*---------------Inicialização---------------*/
void setup() {
  Serial.begin(9600);

  passwd(); // gera a senha

  read_pot = analogRead(A0);
  time1 = map(read_pot, 0, 1023, 10, 90); // tempo entre 10s e 90s

  // FIX #1: Timer1 recebe microssegundos — multiplicar por 1.000.000
  // FIX #2: MFS.initialize() chamado ANTES de qualquer MFS.write()
  Timer1.initialize((long)time1 * 1000000UL);
  MFS.initialize(&Timer1); // inicializa a biblioteca primeiro

  delay1 = 1000.0; // delay inicial: 1 segundo por tick do countdown
  MFS.write("----"); // aguardando início — exibe traços até botão ser pressionado
}

/*---------------Loop Principal---------------*/
void loop() {
  if (TimeOver) {
    MFS.write("0000");
    while (1); // trava o programa
  }

  check_buttons();

  if (!gameStarted) {
    delay((int)delay1);
    return; // não faz countdown nem buzzer enquanto aguarda início
  }

  buzzer();
  countdown();

  delay((int)delay1);
}
