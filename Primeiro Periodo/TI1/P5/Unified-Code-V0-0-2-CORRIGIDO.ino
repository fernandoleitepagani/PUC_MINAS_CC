#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <stdlib.h>
#include <time.h>

#define TRIG_PIN A4       
#define ECHO_PIN A5      
#define LED_R 3
#define LED_G 5     
#define LED_B 6    
#define BUZZER_PIN 11     
#define BTN_PIN 2       

const int SEQ_MAX = 10;           // Tamanho máximo da sequência
const int TIMEOUT_MS = 5000;      // Timeout de 5 segundos
const int DELAY_ENTRE_NIVEIS = 500; // Delay entre apresentação de níveis (ms)
const int VELOCIDADE_MIN = 300;   // Velocidade mínima de apresentação
const int VELOCIDADE_DECR = 50;   // Decréscimo de velocidade por rodada

// Notas musicais para cada nível
const int NOTA[5] = {0, 262, 294, 330, 392}; // Dó, Ré, Mi, Sol

// Cores RGB para cada nível
const byte COR_R[5] = {0, 255, 0, 0, 255};     // Vermelho, Verde, Azul, Amarelo
const byte COR_G[5] = {0, 0, 255, 0, 255};
const byte COR_B[5] = {0, 0, 0, 255, 0};

int sequencia[SEQ_MAX];       // Sequência do jogo
int seqTamanho = 1;           // Tamanho atual da sequência (começa em 1)
int velocidade = 1000;        // Velocidade de apresentação em ms

void gerarSequencia() {
  for (int i = 0; i < SEQ_MAX; i++) {
    sequencia[i] = random(1, 5); // Números de 1 a 4
  }
}

float obterDistancia() {
  // Envia pulso de 10 microsegundos no TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duracao = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout de 30ms
  if (duracao == 0) return 0;

  float distancia = duracao * 0.034 / 2.0;
  return distancia;
}

int mapearNivel(float distancia) {
  if (distancia <= 10) return 1;        // 0-10 cm → Nível 1 (Vermelho/Dó)
  else if (distancia <= 20) return 2;   // 10-20 cm → Nível 2 (Verde/Ré)
  else if (distancia <= 30) return 3;   // 20-30 cm → Nível 3 (Azul/Mi)
  else if (distancia <= 40) return 4;   // 30-40 cm → Nível 4 (Amarelo/Fá)
  else return 0;                         // Fora do alcance
}

void definirCor(byte r, byte g, byte b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

void apagarLED() {
  definirCor(0, 0, 0);
}

void acenderNivel(int nivel, int duracao) {
  if (nivel < 1 || nivel > 4) {
    apagarLED();
    noTone(BUZZER_PIN);
    return;
  }
  definirCor(COR_R[nivel], COR_G[nivel], COR_B[nivel]);

  tone(BUZZER_PIN, NOTA[nivel], duracao);
  delay(duracao);

  apagarLED();
  noTone(BUZZER_PIN);
}

void apresentarSequencia() {
  delay(400);
  for (int i = 0; i < seqTamanho; i++) {
    int nivel = sequencia[i];
    acenderNivel(nivel, velocidade);
    delay(DELAY_ENTRE_NIVEIS);
  }
}

bool lerResposta(int nivelEsperado) {
  unsigned long tempoInicio = millis();

  while (millis() - tempoInicio < TIMEOUT_MS) {
    float distancia = obterDistancia();
    int nivelLido = mapearNivel(distancia);

    if (nivelLido > 0) {
      definirCor(COR_R[nivelLido], COR_G[nivelLido], COR_B[nivelLido]);
    } else {
      apagarLED();
    }

    if (MFS.getButton() == BUTTON_1_PRESSED) {
      delay(100); // Debounce
      break;
    }
  }
  apagarLED();
  delay(100);
  float distanciaFinal = obterDistancia();
  int nivelFinal = mapearNivel(distanciaFinal);
  MFS.write(nivelFinal);
  delay(200);

  if (nivelFinal == nivelEsperado) {
    definirCor(COR_R[nivelFinal], COR_G[nivelFinal], COR_B[nivelFinal]);
    tone(BUZZER_PIN, 500, 200); // Bip curto de acerto
    delay(300);
    apagarLED();
    return true;
  }

  return false;
}

void sinalizarErro() {
  MFS.write("Err");
  MFS.beep(2, 2, 3, 1, 1); // 3 bips rápidos

  for (int i = 0; i < 3; i++) {
    definirCor(255, 0, 0); // Vermelho
    delay(300);
    apagarLED();
    delay(200);
  }

  delay(500);
}

void sinalizarVitoria() {
  MFS.write("GooD");
  MFS.beep(1, 1, 2, 1, 1); // 2 bips curtos

  for (int n = 1; n <= 4; n++) {
    acenderNivel(n, 150);
    delay(100);
  }

  delay(500);
}

void efeitoArcoIris() {
  MFS.write("LVEL");
  MFS.beep(3, 1, 2, 1, 1); // 2 bips mais longos

  for (int ciclo = 0; ciclo < 3; ciclo++) {
    for (int n = 1; n <= 4; n++) {
      definirCor(COR_R[n], COR_G[n], COR_B[n]);
      delay(150);
    }
  }
  apagarLED();
  delay(500);
}

void setup() {
  Serial.begin(9600);

  Timer1.initialize(1000000);
  MFS.initialize(&Timer1);

  pinMode(TRIG_PIN, OUTPUT);    
  pinMode(ECHO_PIN, INPUT);    
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  randomSeed(analogRead(A0));
  MFS.beep();
  delay(500);
  MFS.write("GO");
  delay(1000);
}

void loop() {
  // Inicializa o jogo
  seqTamanho = 1;
  velocidade = 1000;
  gerarSequencia();

  while (seqTamanho <= SEQ_MAX) {
    MFS.write(seqTamanho);
    delay(800);

    apresentarSequencia();

    bool acertouSequencia = true;
    for (int i = 0; i < seqTamanho; i++) {
      MFS.write(i + 1); // Mostra posição atual na sequência

      if (!lerResposta(sequencia[i])) {
        acertouSequencia = false;
        break; 
      }

      delay(300);
    }

    if (!acertouSequencia) {
      sinalizarErro();
      delay(2000);
      return; // Volta ao início do loop() → novo jogo
    }

    // Verifica se deve fazer efeito especial 
    if (seqTamanho % 5 == 0) {
      efeitoArcoIris();
    } else {
      sinalizarVitoria();
    }

    // Prepara para próxima rodada
    seqTamanho++;

    if (velocidade - VELOCIDADE_DECR >= VELOCIDADE_MIN) {
      velocidade -= VELOCIDADE_DECR;
    }

    delay(800);
  }

  // Venceu o jogo inteiro
  MFS.write("WIN");
  efeitoArcoIris();
  efeitoArcoIris();
  delay(3000);

  delay(2000);
}
