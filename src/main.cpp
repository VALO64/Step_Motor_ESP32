#include <Arduino.h>
#include <BluetoothSerial.h>

// Step Motor 28BYJ-48
// Oscar Alberto Valles Limas
// ESP32 Devkit
const int IN1 = 18; // Azul
const int IN2 = 19; // Rosa
const int IN3 = 21; // Amarillo
const int IN4 = 22; // Naranja

// Tiempo de retardo entre pasos para controlar la velocidad
int delayTime = 3; // Ajusta este valor para controlar la velocidad del motor, 3 max vel, 10 min

// Declaración de la función antes de su uso
void stepClockwise();
void stepCounterClockwise();
void processCommand(String command); // Declaración de la función para evitar errores

// Variables para controlar el motor
bool isMotorOn = false;
bool clockwise = true;

// Objeto Bluetooth
BluetoothSerial SerialBT;

void setup() {
  // Configuración de los pines como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Iniciar comunicación serie
  Serial.begin(9600);

  // Iniciar Bluetooth con el nombre del dispositivo
  SerialBT.begin("ESP32_StepMotor"); // Cambia el nombre si lo deseas
  Serial.println("Bluetooth iniciado, listo para emparejar");
}

void loop() {
  // Comprobar si hay datos disponibles en el puerto serie
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Leer el comando hasta el salto de línea
    processCommand(command);
  }

  // Comprobar si hay datos disponibles en Bluetooth
  if (SerialBT.available() > 0) {
    String command = SerialBT.readStringUntil('\n'); // Leer el comando hasta el salto de línea
    processCommand(command);
  }

  // Mover el motor si está encendido
  if (isMotorOn) {
    if (clockwise) {
      stepClockwise();
    } else {
      stepCounterClockwise();
    }
  }
}

// Función para procesar los comandos
void processCommand(String command) {
  command.trim(); // Elimina espacios en blanco al inicio y al final

  if (command == "ON") {
    isMotorOn = true;
  } else if (command == "OFF") {
    isMotorOn = false;
  } else if (command == "CLOCKWISE") {
    clockwise = true;
  } else if (command == "COUNTERCLOCKWISE") {
    clockwise = false;
  } else if (command.startsWith("DELAY ")) {
    delayTime = command.substring(6).toInt();
    if (delayTime < 3) delayTime = 3; // Velocidad máxima
    if (delayTime > 10) delayTime = 10; // Velocidad mínima
  }
}

// Función para girar el motor en sentido horario
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
}

// Función para girar el motor en sentido antihorario
void stepCounterClockwise() {
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
