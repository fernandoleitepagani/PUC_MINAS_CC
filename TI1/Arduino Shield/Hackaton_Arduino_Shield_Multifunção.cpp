#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <cstdlib.h>
#include <ctime.h>

/*-------------Globais--------------*/
int password[8];
volatile bool TimeOver = false;
volatile bool gotright = false;
volatile bool gotwrong = false;
int read; // ler potenciometro
int time;
float delay;
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
void countdown(int time1) {
  if (time1 > 10) {
    MFS.write((int) time1)
    time1--;  //contagem regressiva
  } 
  else {
    TimeOver = true;
    Timer.stop(); // Para o timer quando chegar a zero
  }
}
float delay(){
  float delay = 100;
  return delay;
}
void visual_feedback(int right) {
  switch (right){
    case 1:
      MFS.writeLeds(LED_1, ON);
    case 2:
      MFS.writeLeds(LED_1, OFF);
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
  if (time1 <= 18 && time1 > 10) { // 18 para 10
    MFS.beep(10, // 100ms
             90) // silencio por 900ms
  }
  else if(time1 <= 10) { // 10 para 0
    MFS.beep(100); // Beep por 1s
  }
/*---------------Inicializacao---------------*/

void setup(){
  password = passwd(password);
  read = analogRead(A0); // lendo potenciometro
  time1 = map(read, 0, 1023, 10, 90);
  MFS.write((int)time1);
  Timer1.initialize(time1);  // Define o intervalo para 90 segundos
  MFS.initialize(&Timer1); // inicializa a biblioteca
  if (SW1 == LOW || SW2 == LOW || SW3 == LOW){  //botao1, botao2 ou botao3 ---> pressinou
    serial.begin(9600);
    MFS.write("GO");
  }
}

void loop(){
  buzzer();
  countdown(time1); //time1--
  delay = delay();
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
    delay = delay()*0.95;
    MFS.writeLeds(LED_1 | LED_2 | LED_3 | LED_4, OFF);
  }
  else if (right == 8){
    Timer1.stop();
    MFS.write("OFF");
    MFS.beep(6,4,3); //buzzer beep por 50ms, silencio por 0ms, repete 3 vezes
    while(1); // Para o programa
  }
  delay(delay);
}
