#include <TimerOne.h>
#include <MultiFuncShield.h>
#include <iostream.h>
#include <cstdlib.h>
#include <ctime.h>

/*-------------Globais--------------*/
volatile bool gotright;
int password[8];
volatile int segundos = 10; 
volatile bool TimeOver = false;

/*-------------Funcoes---------------*/
void passwd(){
  srand(time(0));
  for (i=0;i<8;i++){
    int num = (rand()%3) + 1;
    passwd[i] = num;
  }
  return passwd;
} 
void countdown() {
  if (segundos > 10) {
    segundos--;  //contagem regressiva
  } 
  else {
    TimeOver = true;
    Timer.stop(); // Para o timer quando chegar a zero
  }
}
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
  const int buzzerPin = 9;
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
  password = passwd();
  //botao1, botao2 ou botao3 ---> pressinou
  int read = analogRead(A0);
  int time = map(read, 0, 1023, 10, 90);
  timer.initialize(time);         // Define o intervalo para 90 segundos
  timer.attachInterrupt(countdown);   // função que fará a subtração
  Serial.begin(9600);
}

void loop(){
  buzzer();

  Serial.print("Tempo restante: ");
  Serial.println(segundos);  
  if (TimeOver = =true) {
    Serial.println("BOOM! Tempo esgotado.");
    while(1); // Para o programa
  }
  while (time > 87){
    serial.print("GO!");
  }
  int right = 0;
  if (gotright == true){
    right++;
    visual_feedback(right);
  }
  else{
    right = 0;
    timer *= 1.05;
    state_bt1 = LOW;
    state_bt2 = LOW;
    state_bt3 = LOW;
    state_bt4 = LOW;
  }
}
//cowabunga
// yip yip big yahu
