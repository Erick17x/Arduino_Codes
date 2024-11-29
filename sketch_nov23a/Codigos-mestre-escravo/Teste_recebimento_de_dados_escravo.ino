#include <Wire.h>

void setup() {
  Wire.begin(8); // Define o endereço I2C do escravo
  Wire.onRequest(enviarDados); // Define a função de resposta
}

void loop() {
  // O loop do escravo continua com o monitoramento de motores e ultrassom
}

// Função chamada quando o mestre solicita dados
void enviarDados() {
  String statusMotor = "Motores: ON"; // Substitua pelo estado real
  String statusUltrassom = "Obstaculo: 15cm"; // Substitua pela distância real

  // Formata os dados em uma mensagem legível
  String mensagem = statusMotor + " | " + statusUltrassom;
  
  // Limita a mensagem a 32 bytes (máximo do I2C)
  if (mensagem.length() > 32) {
    mensagem = mensagem.substring(0, 32);
  }

  // Envia a mensagem via I2C
  Wire.write(mensagem.c_str());
}
