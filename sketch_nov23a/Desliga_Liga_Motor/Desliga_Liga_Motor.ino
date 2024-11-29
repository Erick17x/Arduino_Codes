#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Defina o endereço I2C e o tamanho do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço 0x27 (verifique se está correto)

void setup() {
  lcd.init();              // Inicializa o LCD
  lcd.backlight();         // Liga a luz de fundo

  lcd.clear();             // Limpa a tela
  lcd.setCursor(0, 0);     // Define o cursor na primeira linha
  lcd.print("Mensagem");   // Exibe o texto "Mensagem"

  lcd.setCursor(0, 1);     // Define o cursor na segunda linha
  lcd.print("Eterna!");     // Exibe o texto "Eterna!"
}

void loop() {
  // O loop está vazio, pois a mensagem permanece na tela
}
