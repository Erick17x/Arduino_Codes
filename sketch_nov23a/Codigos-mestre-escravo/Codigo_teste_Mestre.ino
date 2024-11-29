#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuração do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço I2C do LCD, 16 colunas e 2 linhas

void setup() {
  // Inicializa a comunicação I2C e o LCD
  Wire.begin(); 
  lcd.init();    // Inicializa o LCD
  lcd.backlight();

  // Exibe mensagens iniciais no LCD
  lcd.setCursor(0, 0);
  lcd.print("Inicializando");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ola");
  lcd.setCursor(0, 1);
  lcd.print("Vamos correr?");
  delay(3000);

  // Contagem regressiva
  for (int i = 5; i > 0; i--) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando em:");
    lcd.setCursor(0, 1);
    lcd.print(i);
    delay(1000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motores Ligados");

  // Envia comando para o escravo ligar os motores
  Wire.beginTransmission(10); // Endereço do escravo
  Wire.write(1);             // Comando para ligar os motores
  Wire.endTransmission();
}

void loop() {
  // O mestre pode realizar outras tarefas aqui
}
