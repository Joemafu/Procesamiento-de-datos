#include <Servo.h>

Servo servo;

int grados;
int sube;
int botonIntercambio;
int botonIntercambioAnterior=1;
int estadoServo=90;
int abierto=1;
const int pingPin = 11;
int sensorReading = 0;

void setup()
{
  servo.attach(5, 500,2500);//estos parámetros marcan el grado de inclinación (0 a 180).

  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
  pinMode(11, INPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(7, HIGH);
  pinMode(A0, INPUT);
  pinMode(4,OUTPUT);
}

void loop()
{
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  servo.write(estadoServo);

  botonIntercambio=digitalRead(13);
  sensorReading = analogRead(A0);
  Serial.println(sensorReading);



  Serial.print("Valor del pulsador ");
  Serial.println(botonIntercambio);

  if(abierto==1)
  {
    if(cm<=40)
  	{
   	  estadoServo=0;
      if(sensorReading>26)
      {
       	digitalWrite(2, HIGH);
      }else{
        digitalWrite(2, LOW);
      }
  	 }
  	if(cm>40)
  	{
  	  estadoServo=90;
      digitalWrite(2, LOW);
  	 }
  }else
  {
    estadoServo=90;
    digitalWrite(2, LOW);
  }

  if(botonIntercambio!=botonIntercambioAnterior)
  {
    botonIntercambioAnterior=botonIntercambio;
    if (botonIntercambio==0)
    {
      if(abierto==0)
      {
     	digitalWrite(12, LOW);
      	digitalWrite(7, HIGH);
        abierto=1;
      }else
      {
        digitalWrite(12, HIGH);
      	digitalWrite(7, LOW);
        abierto=0;
      }

    }
  }
  if(estadoServo>0)
  {
    digitalWrite(4, HIGH);
  }else
  {
   	digitalWrite(4, LOW);
  }


}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
