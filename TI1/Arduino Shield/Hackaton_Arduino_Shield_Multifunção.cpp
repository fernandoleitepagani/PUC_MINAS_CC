#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <iostream.h>
#include <cstdlib.h>
#include <ctime.h>

/*-------------Globais--------------*/
int password[8];
volatile bool TimeOver = false;
volatile bool gotright = false;
volatile bool gotwrong = false;
const int pin_SW1 = A1; //pin do botao 1
const int pin_SW2 = A2; //pin do botao 2
const int pin_SW3 = A3; //pin do botao 3
/*-------------Funcoes---------------*/
void passwd(int passwd){
  srand(time(0));
  for (i=0;i<8;i++){
    int num = (rand()%3) + 1;
    passwd[i] = num;
  }
  return passwd;
}
void countdown(int time) {
  if (time > 10) {
    MFS.write((int) time)
    time--;  //contagem regressiva
  } 
  else {
    TimeOver = true;
    Timer.stop(); // Para o timer quando chegar a zero
  }
}
void visual_feedback(int right) {
  switch (right){
    case 1:
      MFS.writeLeds(LED_1, ON);
    case 2:
      MFS.writeLeds(LED-1, OFF);
      MFS.writeLeds(LED_2, ON);
    case 3:
      MFS.writeLeds(LED_1 | LED_2, ON);
    case 4:
      MFS.writeLeds(LED_1 | LED_2, OFF);
      MFS.writeLeds(LED_3, ON);
    case 5:
      MFS.writeLeds(LED_1 | LED_3, ON);
    case 6:
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2 | LED_3, ON);
    case 7:
      MFS.writeLeds(LED_1 | LED_2 | LED_3, ON);
    case 8:
      MFS.writeLeds(LED_1 | LED_2 | LED_3, OFF);
      MFS.writeLeds(LED_4, ON);
  }

}
void buzzer(){
//  const int buzzerPin = 3;
//  const int sensorPin = A0; 
  unsigned long previousMillis = 0;
  const long interval = 100;
  int buzzerState = LOW;
  unsigned long currentMillis = millis(); // o que kcts é millis()
  
  if (time <= 18 && time > 10) { // 18 para 10
    MFS.beep(10, // 100ms
             90) // silencio por 900ms
  }
  else if(timer <= 10) { // 10 para 0
    MFS.beep(100); // Beep por 1s
  }
/*---------------Inicializacao---------------*/

void setup(){
  password = passwd(password);
  int read = analogRead(A0); // lendo potenciometro
  int time = map(read, 0, 1023, 10, 90);
  MFS.write((int)time);
  if (SW1 == LOW || SW2 == LOW || SW3 == LOW){  //botao1, botao2 ou botao3 ---> pressinou
    Timer1.initialize(time);  // Define o intervalo para 90 segundos
    MFS.initialize(&Timer1); // inicializa a biblioteca
    MFS.write("GO");
  }
  serial.begin(9600);
}

void loop(){
  buzzer();
  countdown(time); //time--
  if (TimeOver == true) {
    MFS.write("0000");
    while(1); // Para o programa
  }
  int right = 0;
  if (gotright == true){
    right++;
    visual_feedback(right);
  }
  else if (gotwrong == true){
    right = 0;
    Timer1 *= 1.05;
    MFS.writeLeds(LED_1 | LED_2 | LED_3 | LED_4, OFF);
  }
  else if (right == 8){
    Timer1.stop();
    MFS.write("OFF");
    MFS.beep(6,4,3); //buzzer beep por 50ms, silencio por 0ms, repete 3 vezes
    while(1); // Para o programa
  }
}
