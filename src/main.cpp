#include <Arduino.h>
//Step Motor 28BYJ-48
// Oscar Alberto Valles Limas
// ESP32 Devkit
const int IN1 = 18; // Azul
const int IN2 = 19; // Rosa
const int IN3 = 21; // Amarillo
const int IN4 = 22; // Naranja

// Tiempo de retardo entre pasos para controlar la velocidad
int delayTime = 3; // Ajusta este valor para controlar la velocidad del motor 3 max vel 10 min

// Declaración de la función antes de su uso
void stepClockwise();

void setup() {
  // Configuración de los pines como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Llamar a la función para girar el motor en sentido horario
  stepClockwise();
}
/*Sentido de las manecillas del reloj
void stepClockwise() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delayMicroseconds(delayTime * 1000);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delayMicroseconds(delayTime * 1000);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  delayMicroseconds(delayTime * 1000);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delayMicroseconds(delayTime * 1000);
}*/

/*void stepClockwise() { //Sentido contrario de mas manecillas del reloj
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delayMicroseconds(delayTime * 1000);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  delayMicroseconds(delayTime * 1000);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delayMicroseconds(delayTime * 1000);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delayMicroseconds(delayTime * 1000);
}
*/