// ============================================================
//  Simon Sensorial — Unified Code V0.1.0
//  Plataforma: Arduino Uno + MultiFunctionShield + HC-SR04
//  LED RGB externo na protoboard
// ============================================================

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <stdlib.h>
// <time.h> removido — desnecessário no Arduino

#define TRIG_PIN A4
#define ECHO_PIN A5
#define LED_R 9
#define LED_G 10
#define LED_B 11
#define BTN_PIN 2
#define N           10      // tamanho máximo da sequência
#define TIMEOUT_MS  5000    // tempo de espera por resposta (ms)

const byte LED_MFS[5] = { 0, LED_1, LED_2, LED_3, LED_4 };

struct LevelData { byte r, g, b; int frequence; };

const LevelData LEVELS[4] = {
  {255,   0,   0, 262},  // Nível 1 — Vermelho / Dó
  {  0, 255,   0, 294},  // Nível 2 — Verde    / Ré
  {  0,   0, 255, 330},  // Nível 3 — Azul     / Mi
  {255, 150,   0, 349},  // Nível 4 — Amarelo  / Fá
};

// ─────────────────────────────────────────────────────────
//  Variáveis globais
// ─────────────────────────────────────────────────────────
int sequence_num[N];
int seq_size    = 1;
int showSeqVel  = 1000;  // velocidade de apresentação (ms) — diminui com o progresso

const int VEL_MIN  = 300;
const int VEL_DECR = 50;

void set_LED(int r, int g, int b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

void show_level(int lv, int duration) {
  if (lv < 1 || lv > 4) {
    set_LED(0, 0, 0);
    return;
  }
  LevelData d = LEVELS[lv - 1];
  set_LED(d.r, d.g, d.b);
  int on_units = max(1, duration / 10);
  MFS.beep(on_units, 1, 1, 1, 0);

  delay(duration);
  set_LED(0, 0, 0);
}

void sequence() {
  for (int i = 0; i < N; i++) {
    sequence_num[i] = (rand() % 4) + 1;  // valores 1-4
  }
}

void show_sequence() {
  delay(400);
  for (int i = 0; i < seq_size; i++) {
    int n = sequence_num[i];

    MFS.writeLeds(LED_MFS[n], ON);
    show_level(n, showSeqVel);
    MFS.writeLeds(LED_MFS[n], OFF);

    delay(400);
  }
}

float get_distance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH);
  if (duration == 0) return -1;
  return duration * 0.034 / 2.0;
}

int map_level(float distance) {
  if (distance <= 0)  return 0;
  if (distance <= 10) return 1;
  if (distance <= 20) return 2;
  if (distance <= 30) return 3;
  if (distance <= 40) return 4;
  return 0;
}

bool check_answer(int esperado) {
  unsigned long t0 = millis();
  int lido = 0;

  while (millis() - t0 < TIMEOUT_MS) {
    float dist = get_distance();
    lido = map_level(dist);

    if (lido > 0) show_level(lido, 80);
    else set_LED(0, 0, 0);

    if (MFS.getButton() == BUTTON_1_PRESSED) break;
  }

  set_LED(0, 0, 0);
  lido = map_level(get_distance());
  MFS.write(lido);

  if (lido == esperado) {
    MFS.writeLeds(LED_MFS[lido], ON);
    MFS.beep(2, 1, 1, 1, 0);
    delay(400);
    MFS.writeLeds(LED_MFS[lido], OFF);
    return true;
  }
  return false;
}
void show_error() {
  MFS.write("Err");
  MFS.blinkDisplay(DIGIT_ALL, ON);
  MFS.beep(3, 3, 3, 1, 1);
  for (int i = 0; i < 3; i++) {
    set_LED(255, 0, 0);
    delay(300);
    set_LED(0, 0, 0);
    delay(150);
  }
  MFS.blinkDisplay(DIGIT_ALL, OFF);
}
void show_victory() {
  MFS.write("BOM");
  for (int n = 1; n <= 4; n++) {
    MFS.writeLeds(LED_MFS[n], ON);
    show_level(n, 220);
    MFS.writeLeds(LED_MFS[n], OFF);
    set_LED(0, 0, 0);
  }
}
void rainbow() {
  MFS.write("ARC");
  MFS.blinkLeds(LED_ALL, ON);

  for (int h = 0; h < 360; h += 6) {
    float x = 1.0 - abs(fmod(h / 60.0, 2) - 1);
    float r1 = 0, g1 = 0, b1 = 0;
    if      (h <  60) { r1 = 1; g1 = x;         }
    else if (h < 120) { r1 = x; g1 = 1;         }
    else if (h < 180) {         g1 = 1; b1 = x; }
    else if (h < 240) {         g1 = x; b1 = 1; }
    else if (h < 300) { r1 = x;         b1 = 1; }
    else              { r1 = 1;         b1 = x; }
    set_LED(r1 * 255, g1 * 255, b1 * 255);
    delay(18);
  }

  MFS.blinkLeds(LED_ALL, OFF);
  MFS.writeLeds(LED_ALL, OFF);
  set_LED(0, 0, 0);
}
void setup() {
  Serial.begin(9600);

  Timer1.initialize(1000000);
  MFS.initialize(&Timer1);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BTN_PIN,  INPUT_PULLUP);
  pinMode(LED_R,    OUTPUT);
  pinMode(LED_G,    OUTPUT);
  pinMode(LED_B,    OUTPUT);

  long seed = 0;
  for (int i = 0; i < 8; i++) {
    seed ^= (long)analogRead(A1) << i;
    delay(5);
  }
  srand(seed);

  sequence();

  MFS.beep();
  delay(1000);
}

void loop() {
  while (seq_size <= N) {

    MFS.write(seq_size);
    delay(800);

    show_sequence();
    bool acertou = true;
    for (int i = 0; i < seq_size; i++) {
      MFS.write(i + 1);
      if (!check_answer(sequence_num[i])) {
        acertou = false;
        break;
      }
      delay(300);
    }

    if (!acertou) {
      show_error();
      delay(2000);
      seq_size   = 1;
      showSeqVel = 1000;
      sequence();
      return;
    }
    if (seq_size % 5 == 0) rainbow();
    else show_victory();
    seq_size++;
    if (showSeqVel - VEL_DECR >= VEL_MIN) showSeqVel -= VEL_DECR;
    delay(800);
  }

  // ── Zerou o jogo! ─────────────────────────────────────
  MFS.write("WIN");
  rainbow();
  rainbow();
  delay(3000);

  // Reinicia para nova partida
  seq_size   = 1;
  showSeqVel = 1000;
  sequence();
}
