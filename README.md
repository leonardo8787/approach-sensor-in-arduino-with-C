
<h1>approach-sensor-in-arduino-with-C</h1>

this programming was developed to rotate on an UNO arduino plate, which is connected to electronic devices that form an ultrasonic prosuming sensor.

<h2>how the programming was made</h2>


~~~
#include <Ultrasonic.h>
~~~
include ultrasonic library

~~~
#define pino_trigger 4
#define pino_echo 5
~~~
sets the value of the pins

~~~
const int ledVerde = 13;
const int ledAmarelo = 12;
const int ledVermelho = 11;
const int buzzer = 9;
~~~
sets the values of the LEDs and buzzer

~~~
float seno;
int frequencia;
~~~
defines the scope of the variables

~~~
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
~~~
defines the exits of the pins

~~~
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
~~~
defines the logic of the operation of the alarm, such as approximation and connection of the buzzer. It also sets the buzzer speed and sensor delay.
~~~
void tocaBuzzer(){
 for(int x=0;x<180;x++){
  seno=(sin(x*3.1416/180));
  frequencia = 2000+(int(seno*1000));
  tone(buzzer,frequencia);
  delay(2);
}
}
~~~
defines the operation of the buzzer.
