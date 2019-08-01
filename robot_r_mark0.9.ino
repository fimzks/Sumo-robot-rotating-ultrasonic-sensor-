#include <Servo.h>

#define Pecho 8
#define Ptrig 12
long duracion, distancia;   

Servo servo_sensor;
Servo servo_izquierda;
Servo servo_derecha;

int pos = 0;

void setup() {                
  Serial.begin (9600);      
  pinMode(Pecho, INPUT);     
  pinMode(Ptrig, OUTPUT);    
  pinMode(13, 1);  
  servo_sensor.attach(9);
  servo_izquierda.attach(11);//le asignamos un pin al servo(9)
  servo_derecha.attach(10);          
  }
  
void loop() {
  for (pos = 1; pos >= 0; pos -= 1) { 
    servo_derecha.write(pos);              
    delay(15);
  }
  for (pos = 180; pos <= 180; pos += 1) {
    servo_izquierda.write(pos); 
    delay(15);
  }
  servo_sensor.write(90);
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
  duracion = pulseIn(Pecho, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  
  if (distancia >= 500 || distancia <= 0){  // si la distancia es mayor a 500cm o menor a 0cm 
    Serial.println("---");                  // no mide nada
  }
  else {
    Serial.print(distancia);           // envia el valor de la distancia por el puerto serial
    Serial.println("cm");              // le coloca a la distancia los centimetros "cm"
    digitalWrite(13, 0);               // en bajo el pin 13
  }
  
   if (distancia <= 10 && distancia >= 1){
    digitalWrite(13, 1);                     // en alto el pin 13 si la distancia es menor a 10cm
    Serial.println("Alarma.......");         // envia la palabra Alarma por el puerto serial
  }
  delay(400);                                // espera 400ms para que se logre ver la distancia en la consola
}
