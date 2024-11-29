#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuração do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço I2C do LCD

void setup() {
  // Inicializa o LCD
  lcd.begin(16, 2); // Adicionado os argumentos corretos
  lcd.backlight();

  // Configuração da comunicação I2C
  Wire.begin(); // Mestre
  Serial.begin(9600); // Monitor Serial para debug

  // Sequência de inicialização no LCD
  lcd.clear();
  lcd.print("Inicializando");
  delay(3000);

  lcd.clear();
  lcd.print("Ola");
  lcd.setCursor(0, 1);
  lcd.print("Vamos correr?");
  delay(5000);

  // Contagem regressiva
  for (int i = 5; i > 0; i--) {
    lcd.clear();
    lcd.print("Iniciando em: ");
    lcd.setCursor(0, 1);
    lcd.print(i);
    delay(1000);
  }

  // Envia comando para o escravo ligar os motores
  Wire.beginTransmission(8); // Endereço do escravo
  Wire.write(1); // Comando para ligar os motores
  Wire.endTransmission();

  lcd.clear();
  lcd.print("Motores ligados");
  lcd.setCursor(0, 1);
  lcd.print("Boa corrida!");
}

void loop() {
  // Monitor Serial para verificar operação
  Serial.println("Comando enviado para ligar os motores.");
  delay(2000);
}
