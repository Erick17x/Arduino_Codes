#include <Wire.h>

#define MOTOR_COMMAND 1  // Comando para ligar os motores

void setup() {
  Wire.begin();  // Inicializa o mestre
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("Iniciando sistema...");
  delay(2000);
  
  Serial.println("Enviando comando para ligar os motores...");
  Wire.beginTransmission(8);   // Comunica com o escravo no endereço 8
  Wire.write(MOTOR_COMMAND);   // Envia comando para ligar os motores
  Wire.endTransmission();
}

void loop() {
  // Código adicional, se necessário
}
