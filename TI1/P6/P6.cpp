#include <LiquidCrystal.h>

//Pinos
const int PIN_PH        = A0;
const int PIN_TEMP      = A1;
const int PIN_LDR       = A2;
const int PIN_O2        = A3;
const int PIN_CONTRASTE = 6;

const int PIN_LED       = 4;   // LED indicador de agua boa
const int PIN_BUZZER    = 5;   // Buzzer indicador de agua ruim

//Intervalos de qualidade
const float PH_MIN   = 6.5;
const float PH_MAX   = 8.5;
const float O2_MIN   = 6.0;   // %
const int   LDR_MIN  = 400;   // 0–1023
const float TEMP_MIN = 10.0;  // °C
const float TEMP_MAX = 30.0;  // °C

//Outros
const float AREF_VOLT    = 3.3;
const int   LCD_CONTRAST = 75;

//Buzzer
const int BUZZER_FREQ    = 2000; // Hz

//Sistema de pontos
const unsigned long INTERVALO_LOOP   = 10000;  // ms entre leituras (mesmo valor do delay() do loop)
const unsigned long TEMPO_PARA_PONTO = 60000;  // ms de agua boa continua para ganhar 1 ponto

//LCD
// RS=D13, EN=D12, D4=D11, D5=D10, D6=D9, D7=D8
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

//Variáveis globais
float calibrate_air = 1600.0;
float tempC;
float oxygenPct;
float phValue;
int   ldrRaw;

bool phOK;
bool o2OK;
bool ldrOK;
bool tempOK;
bool aguaLimpa;

//Variaveis do sistema de pontos
unsigned long tempoAguaLimpaAcumulado = 0; // ms consecutivos com agua boa
unsigned int  pontos = 0;

//FUNÇÕES

void calibrate() {
  float sum = 0;
  Serial.println(F("Calibrando O2 no ar..."));
  for (int i = 0; i < 10; i++) {
    sum += (analogRead(PIN_O2) * (AREF_VOLT * 1000.0) / 1024.0);
    delay(100);
  }
  calibrate_air = sum / 10.0;
  if (calibrate_air <= 0 || isnan(calibrate_air)) calibrate_air = 1600.0;
  Serial.print(F("Calibracao: "));
  Serial.print(calibrate_air);
  Serial.println(F(" mV"));
}

float adcParaVolt(int leitura) {
  return (leitura * AREF_VOLT) / 1024.0;
}

void lerTemperatura() {
  float v = adcParaVolt(analogRead(PIN_TEMP));
  tempC   = (v - 0.5) * 100.0;
  tempOK  = (tempC >= TEMP_MIN && tempC <= TEMP_MAX);
  Serial.print(F("Temperatura: "));
  Serial.print(tempC, 1);
  Serial.print(F(" C  intervalo: "));
  Serial.print(TEMP_MIN, 0); Serial.print(F("-")); Serial.print(TEMP_MAX, 0);
  Serial.println(tempOK ? F(" [OK]") : F(" [INADEQUADO]"));
}

void lerPH() {
  phValue = analogRead(PIN_PH) * (14.0 / 1023.0);
  phOK    = (phValue >= PH_MIN && phValue <= PH_MAX);
  Serial.print(F("pH: "));
  Serial.print(phValue, 2);
  Serial.print(F("  intervalo: "));
  Serial.print(PH_MIN, 1); Serial.print(F("-")); Serial.print(PH_MAX, 1);
  Serial.println(phOK ? F(" [OK]") : F(" [INADEQUADO]"));
}

void lerOxigenio() {
  int   raw        = analogRead(PIN_O2);
  float voltage_mv = (raw / 1023.0) * (AREF_VOLT * 1000.0);
  oxygenPct        = constrain((voltage_mv / calibrate_air) * 20.9, 0.0, 100.0);
  o2OK             = (oxygenPct >= O2_MIN);
  Serial.print(F("O2: "));
  Serial.print(oxygenPct, 1);
  Serial.print(F(" %  minimo: "));
  Serial.print(O2_MIN, 1);
  Serial.println(o2OK ? F("% [OK]") : F("% [INADEQUADO]"));
}

void lerTurbidez() {
  ldrRaw = analogRead(PIN_LDR);
  ldrOK  = (ldrRaw >= LDR_MIN);
  Serial.print(F("LDR: "));
  Serial.print(ldrRaw);
  Serial.print(F("  minimo: "));
  Serial.print(LDR_MIN);
  Serial.println(ldrOK ? F(" [OK]") : F(" [INADEQUADO]"));
}

//Avalia qualidade e imprime
void avaliarQualidade() {
  aguaLimpa = phOK && o2OK && ldrOK && tempOK;

  Serial.print(F(">>> Agua: "));
  Serial.println(aguaLimpa ? F("LIMPA") : F("SUJA"));

  if (!aguaLimpa) {
    Serial.print(F("    Causas:"));
    if (!phOK)   Serial.print(F(" pH"));
    if (!o2OK)   Serial.print(F(" O2"));
    if (!tempOK) Serial.print(F(" Temperatura"));
    if (!ldrOK)  Serial.print(F(" Turbidez"));
    Serial.println();
  }
  Serial.println(F("-----------------------------"));
}

//Controla LED e buzzer de acordo com a qualidade da agua
void atualizarAtuadores() {
  if (aguaLimpa) {
    // Agua boa: acende o LED e desliga o buzzer
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_BUZZER, LOW);
  } else {
    // Agua ruim: apaga o LED e liga o buzzer
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_BUZZER, HIGH);
  }
}

//Atualiza o sistema de pontos: soma tempo continuo de agua boa e converte em pontos
void atualizarPontuacao() {
  if (aguaLimpa) {
    tempoAguaLimpaAcumulado += INTERVALO_LOOP;

    while (tempoAguaLimpaAcumulado >= TEMPO_PARA_PONTO) {
      pontos++;
      tempoAguaLimpaAcumulado -= TEMPO_PARA_PONTO;
      Serial.print(F(">>> Ponto conquistado! Total: "));
      Serial.println(pontos);
    }
  } else {
    // Zera o progresso ao detectar agua ruim
    tempoAguaLimpaAcumulado = 0;
  }
}

void atualizarLCD() {
  lcd.setCursor(0, 0);
  lcd.print(F("pH:"));
  lcd.print(phValue, 2);
  lcd.print(F(" O2:"));
  if (oxygenPct < 10.0) lcd.print(F(" "));
  lcd.print(oxygenPct, 1);
  lcd.print(F("%"));

  // --- Linha 1: Temperatura + Status geral ---
  lcd.setCursor(0, 1);
  lcd.print(F("T:"));
  if (tempC < 10.0 && tempC >= 0.0) lcd.print(F(" ")); // alinha dígitos
  lcd.print(tempC, 1);
  lcd.print(F("C"));

  if (aguaLimpa) {
    lcd.print(F(" >>LIMPA"));
  } else {
    lcd.print(F(" >> SUJA"));
    // Indicadores compactos dos parâmetros com falha
    int causas = (!phOK ? 1:0) + (!o2OK ? 1:0) + (!tempOK ? 1:0) + (!ldrOK ? 1:0);
    lcd.print(causas > 2 ? F("!") : F(" "));
  }
}

//BLUETOOTH
void enviarDadosBluetooth() {
  Serial.print(F("pH:"));     Serial.print(phValue, 2);
  Serial.print(F(",O2:"));    Serial.print(oxygenPct, 1);
  Serial.print(F(",LDR:"));   Serial.print(ldrRaw);
  Serial.print(F(",Temp:"));  Serial.print(tempC, 1);
  Serial.print(F(",Status:")); Serial.print(aguaLimpa ? F("LIMPA") : F("SUJA"));
  Serial.print(F(",Pontos:")); Serial.println(pontos);
}

//ROTINA DE TESTE
void rotateTeste() {
  Serial.println();
  Serial.println(F("============================="));
  Serial.println(F("   MODO DE TESTE INICIADO    "));
  Serial.println(F("============================="));

  //TESTE DO LCD
  Serial.println(F("\n[1] Testando LCD..."));

  lcd.clear();
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) lcd.print('#');
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) lcd.print('#');
  Serial.println(F("    Todas as celulas preenchidas com '#'"));
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("  ** TESTE **   "));
  lcd.setCursor(0, 1);
  lcd.print(F(" Entradas/Saidas"));
  Serial.println(F("    Mensagem de teste exibida"));
  delay(1000);

  //TESTE DAS ENTRADAS ANALÓGICAS
  Serial.println(F("\n[2] Testando entradas analogicas..."));
  Serial.println(F("    Pino     | ADC (0-1023) | Tensao (V)"));
  Serial.println(F("    ---------|-------------|----------"));

  const int   pinos[]  = { A0,         A1,         A2,         A3         };
  const char* nomes[]  = { "A0 pH    ", "A1 TMP36 ", "A2 LDR   ", "A3 O2    " };
  const int   N        = 4;

  for (int i = 0; i < N; i++) {
    int   adc  = analogRead(pinos[i]);
    float v    = (adc * AREF_VOLT) / 1024.0;

    Serial.print(F("    "));
    Serial.print(nomes[i]);
    Serial.print(F(" |     "));
    if (adc < 1000) Serial.print(' ');
    if (adc < 100)  Serial.print(' ');
    if (adc < 10)   Serial.print(' ');
    Serial.print(adc);
    Serial.print(F("    |   "));
    Serial.println(v, 3);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(nomes[i]);
    lcd.print(F(" ADC:"));
    lcd.print(adc);
    lcd.setCursor(0, 1);
    lcd.print(F("Tensao: "));
    lcd.print(v, 3);
    lcd.print(F(" V"));
    delay(900);
  }

  //TESTE DA SAÍDA PWM D6
  Serial.println(F("\n[3] Testando saida PWM D6 (contraste LCD)..."));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("PWM D6: subindo "));
  Serial.println(F("    Subindo  0 -> 255"));
  for (int pwm = 0; pwm <= 255; pwm += 5) {
    analogWrite(PIN_CONTRASTE, pwm);
    lcd.setCursor(0, 1);
    lcd.print(F("Valor: "));
    lcd.print(pwm);
    lcd.print(F("   "));
    delay(25);
  }

  lcd.setCursor(0, 0);
  lcd.print(F("PWM D6:descendo "));
  Serial.println(F("    Descendo 255 -> 0"));
  for (int pwm = 255; pwm >= 0; pwm -= 5) {
    analogWrite(PIN_CONTRASTE, pwm);
    lcd.setCursor(0, 1);
    lcd.print(F("Valor: "));
    lcd.print(pwm);
    lcd.print(F("   "));
    delay(25);
  }

  analogWrite(PIN_CONTRASTE, LCD_CONTRAST);
  Serial.print(F("    Contraste restaurado para "));
  Serial.println(LCD_CONTRAST);

  //TESTE DO LED E BUZZER
  Serial.println(F("\n[4] Testando LED e buzzer..."));

  Serial.println(F("    LED ON / Buzzer OFF"));
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_BUZZER, LOW);
  delay(600);

  Serial.println(F("    LED OFF / Buzzer ON"));
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_BUZZER, HIGH);
  delay(600);
  digitalWrite(PIN_BUZZER, LOW);

  //FIM
  Serial.println(F("\n============================="));
  Serial.println(F("   TESTE CONCLUIDO           "));
  Serial.println(F("   Retomando monitoramento..."));
  Serial.println(F("=============================\n"));

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(F("Teste concluido!"));
  lcd.setCursor(0, 1);
  lcd.print(F("Retomando...    "));
  delay(1500);
  lcd.clear();
}

//SETUP
void setup() {
  Serial.begin(9600);

  analogWrite(PIN_CONTRASTE, LCD_CONTRAST);
  analogReference(EXTERNAL);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(F("Iniciando..."));
  delay(1500);
  lcd.clear();

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_BUZZER, LOW);

  calibrate();

  Serial.println(F("Sistema pronto!"));
  Serial.println(F("Intervalos adequados:"));
  Serial.print(F("  pH: "));   Serial.print(PH_MIN,1);   Serial.print(F(" - ")); Serial.println(PH_MAX,1);
  Serial.print(F("  O2: >= ")); Serial.print(O2_MIN,1);  Serial.println(F(" %"));
  Serial.println(F("-----------------------------"));
  Serial.println(F("  Digite 't' para teste E/S  "));
  Serial.println(F("-----------------------------"));
}

//LOOP
void loop() {
  if (Serial.available() > 0) {
    char tecla = Serial.read();
    if (tecla == 't' || tecla == 'T') {
      rotateTeste();
      return;
    }
  }

  lerPH();
  lerTemperatura();
  lerOxigenio();
  lerTurbidez();
  avaliarQualidade();
  atualizarAtuadores();
  atualizarPontuacao();
  atualizarLCD();
  enviarDadosBluetooth();

  delay(1000);
}

