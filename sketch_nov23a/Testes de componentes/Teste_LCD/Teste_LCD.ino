#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definindo os pinos usados para a comunicação com o módulo RFID
#define SS_PIN 10    // Pino SDA do RFID
#define RST_PIN 9    // Pino de Reset do RFID
MFRC522 mfrc522(SS_PIN, RST_PIN); // Cria uma instância do MFRC522

// Definindo os pinos para o controle dos motores L298N
#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 8
#define ENA 5
#define ENB 6

// Endereço I2C e tamanho do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Substitua 0x27 se necessário

// IDs válidos dos cartões em formato hexadecimal (como strings)
String validCard1 = "4D359FBF6181";  // Cartão para ligar o motor
String validCard2 = "4172E11BF6180";  // Cartão para desligar o motor

// Variável para controlar o estado do motor (ligado ou desligado)
bool motorOn = false;

void setup() {
  Serial.begin(9600);     // Inicializa a comunicação serial
  SPI.begin();            // Inicializa a comunicação SPI
  mfrc522.PCD_Init();     // Inicializa o módulo RFID

  // Inicializa o LCD
  lcd.init();             
  lcd.backlight();        // Liga a luz de fundo
  lcd.clear();            // Limpa a tela
  lcd.setCursor(0, 0);    // Define o cursor na primeira linha
  lcd.print("Aproxime o"); // Exibe uma mensagem inicial
  lcd.setCursor(0, 1);    // Define o cursor na segunda linha
  lcd.print("cartão...");  // Exibe o resto da mensagem

  // Configura os pinos dos motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Liga os motores inicialmente (com a variável motorOn controlando o estado)
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  Serial.println("Aproxime o cartão para iniciar...");
}

void loop() {
  // Verifica se há um cartão RFID próximo
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.print("ID do cartão: ");
      
      String cardUID = "";  // Variável para armazenar o UID como string hexadecimal

      // Concatena o UID do cartão lido em formato hexadecimal
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardUID += String(mfrc522.uid.uidByte[i], HEX); // Converte o byte para hexadecimal e concatena
      }

      cardUID.toUpperCase();  // Converte toda a string para maiúsculas para garantir que não haja problemas de comparação
      Serial.println(cardUID); // Imprime o UID no monitor serial

      // Checa se o ID do cartão é um dos esperados
      if (checkCard(cardUID)) {
        if (cardUID == validCard1 && !motorOn) {
          // Exibe a mensagem de boas-vindas no LCD e liga os motores
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Bem-vindo!");
          forward();  // Motores girando para frente
          motorOn = true;  // Marca que o motor está ligado
        }
        else if (cardUID == validCard2 && motorOn) {
          // Exibe a mensagem de adeus no LCD e desliga os motores
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Adeus!");
          stopMotors();  // Para os motores
          motorOn = false;  // Marca que o motor está desligado
        }
      } else {
        // Exibe mensagem de "Cartão desconhecido" no LCD e para os motores
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Cartão desconhecido");
        stopMotors();  // Para os motores
      }

      mfrc522.PICC_HaltA();  // Para a comunicação com o cartão
    }
  }
}

// Função para checar se o UID do cartão é válido
bool checkCard(String cardUID) {
  // Verifica se o UID lido é um dos cartões permitidos
  if (cardUID == validCard1 || cardUID == validCard2) {
    return true;
  }
  return false;
}

// Função para mover os motores para frente
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Função para parar os motores
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
