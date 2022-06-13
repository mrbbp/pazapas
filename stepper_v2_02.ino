/*
   # pazapas
  code Arduino pour l'exploitattion d'un moteur pas à pas 28BYJ (pas cher, peu de couple) - env. 64 pas / tour
  
  montage: 
     - l'interrupteur placé en D2 -> GND permet d'inverser le sens de rotation (lorsque le circuit est ouvert, direction(var) est inversée)
     - le potard en A0 ajoute un delai entre chaque pas du moteur.
  
  code source: https://forum.arduino.cc/t/change-direction-of-stepper-motor/363918
  le code n'utilise pas de lib (donne plus de couple, cf le thread)
  
  forké par mrbbp pour le DNMADe Design graphique numérique, Rennes
  Juin 2022

*/

#define IN1  7
#define IN2  8
#define IN3  9
#define IN4  10
int Steps = 4096; //4096 or 768
int cstep = 0;
int direction = 1;
int inteOld;

void setup()
{
  //Serial.begin(115200);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}

void loop(){
  int sensorReading = analogRead(A0);
  int inte = digitalRead(2);
  if (inte != inteOld) {
    direction *= -1;
    inteOld = inte;
    delay(200);
    //Serial.println(direction);
  }
  for(int x=0;x<16;x++){
    sequence();
    //delay(1);
    delayMicroseconds(1000);
  }
  //Serial.println("Boom!!");
  //delay(1000);
  int motorSpeed = map(sensorReading, 10, 1023, 0, 100);
  //Serial.println(motorSpeed);
  delay(motorSpeed);
}

void sequence()
{
  //stepp
  switch(cstep)
  {
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
  }
  cstep += direction;
  if (cstep > 7) {  cstep = 0;}
  if( cstep < 0) { cstep = 7;}
}
