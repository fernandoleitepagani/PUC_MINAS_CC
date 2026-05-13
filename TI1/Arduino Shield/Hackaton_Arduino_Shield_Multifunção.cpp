#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <iostream.h>
#include <cstdlib.h>
#include <ctime.h>

/*-------------Globais--------------*/
volatile bool gotright;
int password[8];
// volatile int segundos = 10; 
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
//void got_right_wrong(){
//  if got right
//    gotright == true;
//  else
//    gotwrong == true
//}
void visual_feedback(int right) {
  switch (right){
    case 1:
      state_bt1 = high;
    case 2:
      state_bt1 = LOW
      state_bt2 = high;
    case 3:
      state_bt1 = high;
      state_bt2 = high;
    case 4:
      state_bt1 = LOW
      state_bt2 = LOW
      state_bt3 = high;
    case 5:
      state_bt1 = high;
      state_bt3 = high;
    case 6:
      state_bt1 = LOW
      state_bt2 = high;
      state_bt3 = high;
    case 7:
      state_bt1 = high;
      state_bt2 = high;
      state_bt3 = high;
    case 8:
      state_bt1 = LOW;
      state_bt2 = LOW;
      state_bt3 = LOW;
      state_bt4 = high;
  }

}
void buzzer(){
  const int buzzerPin = 3;
  const int sensorPin = A0; 
  unsigned long previousMillis = 0;
  const long interval = 100;
  int buzzerState = LOW;
  unsigned long currentMillis = millis();
  
 if (timer >= 18 && timer <= 10) {
    
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      if (buzzerState == LOW) {
        buzzerState = HIGH;
      } 
      else {
        buzzerState = LOW;
      }
      digitalWrite(buzzerPin, buzzerState);
    }
  } 
  else if(timer < 10) {
  digitalWrite(buzzerPin, HIGH);
  buzzerState = HIGH;
  }
  else{
    digitalWrite(buzzerPin, LOW);
    buzzerState = LOW; 
  }
}

/*---------------Inicializacao---------------*/

void setup(){
  password = passwd(password);
  int read = analogRead(A0); // lendo potenciometro
  int time = map(read, 0, 1023, 10, 90);
  MFS.write((int)time);
  if (SW1 == LOW || SW2 == LOW || SW3 == LOW){  //botao1, botao2 ou botao3 ---> pressinou
    Timer1.initialize(time);         // Define o intervalo para 90 segundos
    MFS.initialize(&Timer1); // incializa a biblioteca
    Serial.begin(9600);
  }
}

void loop(){
  buzzer();
  countdown(time); //time-- 
  while (time > 87){
    MFS.write("GO!");
  }
  MFS.writeln(segundos);  
  if (TimeOver == true) {
    MFS.writeln("BOOM");
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
    state_bt1 = LOW;
    state_bt2 = LOW;
    state_bt3 = LOW;
    state_bt4 = LOW;
  }
}
//cowabunga
// yip yip big yahu
