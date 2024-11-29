#include <Wire.h>

#define ENA 9
#define IN1 8
#define IN2 7
#define ENB 6
#define IN3 3
#define IN4 2

void setup() {
  Wire.begin(8);  // Inicializa o escravo no endereço 8
  Wire.onReceive(receiveEvent);  // Define o manipulador para receber dados

  // Configuração dos pinos do motor
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Escravo pronto para receber comandos.");
}

void loop() {
  // Código adicional, se necessário
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    int command = Wire.read();
    if (command == 1) {  // Comando para ligar os motores
      Serial.println("Ligando motores na velocidade máxima!");
      
      // Motor esquerdo
      analogWrite(ENA, 100);  // Velocidade máxima
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

      // Motor direito
      analogWrite(ENB, 100);  // Velocidade máxima
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
  }
}
