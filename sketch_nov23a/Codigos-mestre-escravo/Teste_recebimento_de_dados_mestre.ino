#include <Wire.h>

// Variáveis para controle de leitura
unsigned long ultimoEnvio = 0;
const unsigned long intervaloLeitura = 2000; // Intervalo de leitura em 2 segundos

void setup() {
  Wire.begin(); // Inicia o mestre I2C
  Serial.begin(9600);
  Serial.println("Iniciando mestre...");
}

void loop() {
  // Controla a frequência de leitura
  if (millis() - ultimoEnvio >= intervaloLeitura) {
    // Solicita dados do escravo
    Wire.requestFrom(8, 32); // Solicita até 32 bytes do escravo com endereço 8
    
    String dadosRecebidos = "";
    while (Wire.available()) {
      char c = Wire.read();
      dadosRecebidos += c;
    }

    // Exibe apenas se houver dados válidos
    if (dadosRecebidos.length() > 0) {
      Serial.println("Dados do escravo:");
      Serial.println(dadosRecebidos);
    } else {
      Serial.println("Nenhuma resposta do escravo.");
    }

    ultimoEnvio = millis(); // Atualiza o tempo da última leitura
  }

  delay(100); // Pequeno atraso para evitar sobrecarga
}
