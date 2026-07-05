/*
  =========================================================================
  PROJETO 1 - "Medindo Alturas com o Arduino: O Teorema de Pitágoras em Ação"
  Guia Pedagógico: Arduino e Matemática (Marra & Fonseca, UFV/PROFMAT, 2026)


  LÓGICA DO PROJETO 1 (mantida igual ao original):
  O Arduino mede continuamente a distância inclinada até o topo da
  estrutura (hipotenusa "d") e mostra no display LCD. A base "b"
  (cateto adjacente) é medida MANUALMENTE com trena pelos alunos, e a
  altura h = sqrt(d² - b²) é calculada por eles com uma calculadora.
  */


#include <LiquidCrystal.h>

// ---------------- Pinagem da montagem atual ----------------
const int TRIG_PIN     = 12;
const int ECHO_PIN     = 11;
const int LASER_PIN    = 13;
const int CONTRAST_PIN = 9; 

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7


const int NUM_AMOSTRAS = 5;               
const unsigned long TIMEOUT_US = 30000UL; 

// Configura contraste (LCD do Bernardo deve resolver e adaptamos essa parte aqui) CONFERIR COM ELE!!!!!!!!!!!!!!!!!!!!!
const int CONTRAST_VALUE = 30;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LASER_PIN, OUTPUT);
  pinMode(CONTRAST_PIN, OUTPUT);

  digitalWrite(LASER_PIN, HIGH); // laser ligado continuamente para auxiliar a mira
  analogWrite(CONTRAST_PIN, CONTRAST_VALUE); // gera o "contraste" 

  lcd.begin(16, 2);
  lcd.print("Projeto 1");
  lcd.setCursor(0, 1);
  lcd.print("Pitagoras");
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hipotenusa (d):"); // nao muda durante o loop
}

// Faz varias leituras do HC-SR04 e retorna a media em centimetros.
// Retorna -1 se nenhuma leitura valida foi obtida (fora de alcance).
float medirDistanciaCM() {
  float soma = 0;
  int leiturasValidas = 0;

  analogWrite(9,512);

  for (int i = 0; i < NUM_AMOSTRAS; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    unsigned long duracao = pulseIn(ECHO_PIN, HIGH, TIMEOUT_US);

    if (duracao > 0) {
      float distancia = duracao * 0.0343 / 2.0; // velocidade do som ~343 m/s
      soma += distancia;
      leiturasValidas++;
    }
    delay(15); // pequeno intervalo entre disparos consecutivos
  }

  if (leiturasValidas == 0) return -1;
  return soma / leiturasValidas;
}

void loop() {
  float distanciaCM = medirDistanciaCM();

  // limpa a segunda linha antes de escrever o novo valor
  lcd.setCursor(0, 1);
  lcd.print("                "); // 16 espacos
  lcd.setCursor(0, 1);

  if (distanciaCM < 0) {
    lcd.print("Fora de alcance");
  } else {
    lcd.print(distanciaCM, 1);
    lcd.print(" cm");
  }

  // Dica para os alunos: para usar a formula h = sqrt(d^2 - b^2) em
  // metros (como no exemplo do guia, "3 metros"), basta dividir o
  // valor mostrado aqui (em cm) por 100 antes do calculo.

  delay(300); // taxa de atualizacao do display
}

//REZAR PRA DAR CERTO!!!!!
