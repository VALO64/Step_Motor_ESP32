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

// Variables para controlar el motor
bool isMotorOn = false; // Estado general del motor (encendido o apagado)
bool isMotorRunning = false;
bool clockwise = true;
bool continuousMode = false; // Modo de giro continuo
int stepsToMove = 0; // Cantidad de pasos que debe moverse el motor

// Objeto Bluetooth
BluetoothSerial SerialBT;

// Declaraciones de funciones
void stepClockwise();
void stepCounterClockwise();
void processCommand(String command);

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

  // Si el motor está encendido y en modo continuo, continúa girando
  if (isMotorOn && isMotorRunning && continuousMode) {
    if (clockwise) {
      stepClockwise();
    } else {
      stepCounterClockwise();
    }
  }

  // Si el motor está encendido y debe moverse un número específico de pasos
  if (isMotorOn && stepsToMove > 0) {
    if (clockwise) {
      stepClockwise();
    } else {
      stepCounterClockwise();
    }
    stepsToMove--;

    // Detener el motor si ha terminado de moverse los pasos especificados
    if (stepsToMove == 0) {
      isMotorRunning = false;
    }
  }
}

// Función para procesar los comandos
void processCommand(String command) {
  command.trim(); // Elimina espacios en blanco al inicio y al final

  if (command == "ON") {
    isMotorOn = true; // Encender el motor
  } else if (command == "OFF") {
    isMotorOn = false; // Apagar el motor
    isMotorRunning = false; // Detener cualquier movimiento
    continuousMode = false;
  } else if (command == "RUN") {
    if (isMotorOn) { // Solo si el motor está encendido
      isMotorRunning = true;
      continuousMode = true; // Activar modo de giro continuo
    }
  } else if (command == "STOP") {
    isMotorRunning = false; // Detener cualquier movimiento
    continuousMode = false; // Desactivar modo de giro continuo
  } else if (command == "CLOCKWISE") {
    clockwise = true;
  } else if (command == "COUNTERCLOCKWISE") {
    clockwise = false;
  } else if (command.startsWith("DELAY ")) {
    delayTime = command.substring(6).toInt();
    if (delayTime < 3) delayTime = 3; // Velocidad máxima
    if (delayTime > 10) delayTime = 10; // Velocidad mínima
  } else if (command.startsWith("MOVE ")) {
    if (isMotorOn) { // Solo si el motor está encendido
      int degrees = command.substring(5).toInt();
    
      if (degrees < 0) {
        clockwise = false; // Cambiar dirección si los grados son negativos
        degrees = -degrees; // Hacer los grados positivos
      } else {
        clockwise = true; // Mantener la dirección si los grados son positivos
      }

      stepsToMove = degrees * 4096 / 360; // Convertir grados a pasos
      isMotorRunning = true; // Encender el motor para moverse
      continuousMode = false; // Desactivar modo de giro continuo
    }
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
