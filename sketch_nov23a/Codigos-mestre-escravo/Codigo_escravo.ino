#include <Wire.h>

// Configuração das portas dos motores
#define ENA 9
#define IN1 8
#define IN2 7
#define ENB 6
#define IN3 3
#define IN4 2

// Sensores infravermelhos
#define INF_ESQ A1
#define INF_DIR A0

// Corte do sensor (ajustado para linha branca)
#define valorCorte 759 // Valor mais baixo para detectar linha branca

// Configuração do sensor ultrassônico
#define TRIG_PIN 4
#define ECHO_PIN 5

void setup() {
  // Configuração dos motores
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configuração do ultrassom
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configuração dos sensores infravermelhos
  pinMode(INF_ESQ, INPUT);
  pinMode(INF_DIR, INPUT);

  // Inicializa a comunicação I2C e Serial
  Wire.begin(8);  // Endereço do escravo
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);  // Monitor Serial para debug

  Serial.println("Arduino Escravo Inicializado");
}

void loop() {
  // Medição do ultrassom
  long duration, distance;

  // Envia o pulso TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Calcula a duração e a distância
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.034) / 2;  // Converte para cm

  // Exibe a distância no monitor serial
  //Serial.print("Distancia: ");
  //Serial.print(distance);
  //Serial.println(" cm");

  //delay(500);  // Atualiza a cada 500 ms

 // Leitura dos sensores infravermelhos
  int valorEsq = analogRead(INF_ESQ);
  int valorDir = analogRead(INF_DIR);

  // Imprime os valores no monitor serial
  Serial.print("Sensor Esquerdo: ");
  Serial.print(valorEsq);
  Serial.print(" | Sensor Direito: ");
  Serial.println(valorDir);

  delay(500); // Atualiza os valores a cada 500 ms
}

void receiveEvent(int bytes) {
  // Recebe o comando do Mestre
  int command = Wire.read();

  if (command == 1) {  // Ligar os motores
    // Motor Esquerdo
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 255);  // Velocidade máxima

    // Motor Direito
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 255);  // Velocidade máxima

    Serial.println("Motores Ligados!");
  }

}
