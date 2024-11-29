#include <SPI.h>
#include <MFRC522.h>

// Definindo os pinos usados para a comunicação com o módulo RFID
#define SS_PIN 10    // Pino SDA do RFID
#define RST_PIN 9    // Pino de Reset do RFID
MFRC522 mfrc522(SS_PIN, RST_PIN); // Cria uma instância do MFRC522

// Atualizando os pinos para controle do motor
#define IN1 2   // Controle do motor 1
#define IN2 4   // Controle do motor 1
#define IN3 7   // Controle do motor 2
#define IN4 8   // Controle do motor 2
#define ENA 5   // Velocidade do motor 1
#define ENB 6   // Velocidade do motor 2

// IDs dos cartões para comparação
byte cardUID1[] = {0x4, 0xD3, 0x59, 0xF, 0xBF, 0x61, 0x81}; // Liga motores
byte cardUID2[] = {0x4, 0x17, 0x2E, 0x11, 0xBF, 0x61, 0x80}; // Desliga motores

void setup() {
  Serial.begin(9600);     // Inicializa a comunicação serial
  SPI.begin();            // Inicializa a comunicação SPI
  mfrc522.PCD_Init();     // Inicializa o módulo RFID
  Serial.println("Aproxime o cartão do leitor...");

  // Configurando os pinos dos motores como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Inicializa os motores desligados
  stopMotors();
}

void loop() {
  // Verifica se há um cartão RFID próximo
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.print("ID do cartão lido: ");
      
      // Exibe o ID do cartão no monitor serial
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        if (i < mfrc522.uid.size - 1) Serial.print(":"); // Adiciona separador ':'
      }
      Serial.println();  // Nova linha para melhor leitura

      // Verifica se o ID do cartão lido é o mesmo que o do cartão desejado
      if (compareUID(mfrc522.uid.uidByte, cardUID1, mfrc522.uid.size)) {
        Serial.println("Cartão 1 reconhecido! Ligando motores...");
        startMotors();
      } else if (compareUID(mfrc522.uid.uidByte, cardUID2, mfrc522.uid.size)) {
        Serial.println("Cartão 2 reconhecido! Desligando motores...");
        stopMotors();
      } else {
        Serial.println("Cartão desconhecido.");
      }

      mfrc522.PICC_HaltA();  // Para a comunicação com o cartão
    }
  }
}

// Função para comparar o UID lido com o do cartão especificado
bool compareUID(byte* uid1, byte* uid2, byte uidLength) {
  for (byte i = 0; i < uidLength; i++) {
    if (uid1[i] != uid2[i]) {
      return false; // Retorna falso se houver diferença
    }
  }
  return true;
}

// Função para ligar os motores
void startMotors() {
  Serial.println("Ligando os motores...");
  analogWrite(ENA, 150);   // Velocidade do motor 1
  analogWrite(ENB, 150);   // Velocidade do motor 2
  digitalWrite(IN1, HIGH); // Motor 1 no sentido horário
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Motor 2 no sentido horário
  digitalWrite(IN4, LOW);
}

// Função para desligar os motores
void stopMotors() {
  Serial.println("Desligando os motores...");
  analogWrite(ENA, 0);    // Desliga motor 1
  analogWrite(ENB, 0);    // Desliga motor 2
  digitalWrite(IN1, LOW); // Motor 1 desligado
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); // Motor 2 desligado
  digitalWrite(IN4, LOW);
}
