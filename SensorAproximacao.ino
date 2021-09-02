#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

const int ledVerde = 13;
const int ledAmarelo = 12;
const int ledVermelho = 11;
const int buzzer = 9;

float seno;
int frequencia;
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
   
  //Definindo pinos digitais
  pinMode(ledVerde,OUTPUT); //13 como de saída.
  pinMode(ledAmarelo,OUTPUT); //12 como de saída.
  pinMode(ledVermelho,OUTPUT); //11 como de saída.
  pinMode(buzzer, OUTPUT); 
}
 
void loop()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);
  delay(100);

  //Apagando todos os leds
  digitalWrite(ledVerde,LOW);  
  digitalWrite(ledAmarelo,LOW);
  digitalWrite(ledVermelho,LOW);

  pinMode(buzzer, OUTPUT); 
  
  if(cmMsec > 20){
    digitalWrite(ledVerde,HIGH);
    noTone(buzzer);
  }
  if(cmMsec > 10 and cmMsec < 20){
    digitalWrite(ledAmarelo,HIGH);
    noTone(buzzer);
  }
  if(cmMsec < 10){
    digitalWrite(ledVermelho,HIGH);
    tocaBuzzer();
  }
}

void tocaBuzzer(){
 for(int x=0;x<180;x++){
  seno=(sin(x*3.1416/180));
  frequencia = 2000+(int(seno*1000));
  tone(buzzer,frequencia);
  delay(2);
}
}
