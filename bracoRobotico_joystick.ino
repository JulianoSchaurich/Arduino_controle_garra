#include <Servo.h>
#define servoGarra 7
#define servoBraco 6
#define servoBase 5

Servo SG;
Servo SBr;
Servo SBa;

#define SW 4
#define VRy A7
#define VRx A6

int valorVRy = 90, valorVRx = 90, valorSW = 0, valorSW_aux = 1, valor_servo_garra = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(SW, INPUT_PULLUP); //1 - SOLTO, 0 - PRESSIONADO
  pinMode(VRy, INPUT); //1023 - ESQUERDA, 0 -DIREITA
  pinMode(VRx, INPUT); //1023 - BAIXO, 0 - CIMA
  
//  pinMode(8, OUTPUT);
//  digitalWrite(8, HIGH);
  
  SG.attach(servoGarra);
  SG.write(60);
  SBr.attach(servoBraco);
  SBr.write(90);
  SBa.attach(servoBase);
  SBa.write(90);
}

void loop() {
  valores_joystick();
  braco_robotico();

  Serial.println(valorSW_aux);
  Serial.println(valorVRx);
  Serial.println(valorVRy);

  delay(100);
}

void valores_joystick()
{
  valorSW_aux = valorSW;
  
  valorVRy = map(analogRead(VRy), 0, 1023, 0, 180);
  valorVRx = map(analogRead(VRx), 0, 1023, 0, 180);
  valorSW = digitalRead(SW);
}

void braco_robotico()
{ 
  SBr.write(valorVRx);
  SBa.write(valorVRy);
  
  if(valorSW == 0)
  {
    SG.write(60);
  }
  else
  {
    SG.write(0);
  }
}
