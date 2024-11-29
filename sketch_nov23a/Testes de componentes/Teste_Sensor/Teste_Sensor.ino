// Defina os pinos dos sensores
#define INF_DIR_PIN A0 // Sensor Direito
#define INF_ESQ_PIN A1 // Sensor Esquerdo

// Defina o limite para diferenciar branco e preto
#define LIMITE 1000

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Serial.println("Testando sensores com limite de 1000:");
}

void loop() {
  // Leitura do sensor direito
  int valorInfDir = analogRead(INF_DIR_PIN);
  // Leitura do sensor esquerdo
  int valorInfEsq = analogRead(INF_ESQ_PIN);

  // Exibe os valores lidos para ambos os sensores
  Serial.print("InfDir (Direito): ");
  Serial.print(valorInfDir);
  Serial.print(" - Cor: ");
  if (valorInfDir > LIMITE) {
    Serial.println("Branco");
  } else {
    Serial.println("Preto");
  }

  Serial.print("InfEsq (Esquerdo): ");
  Serial.print(valorInfEsq);
  Serial.print(" - Cor: ");
  if (valorInfEsq > LIMITE) {
    Serial.println("Branco");
  } else {
    Serial.println("Preto");
  }

  // Pausa de 1,5 segundos entre as leituras
  delay(1500); // 1500 milissegundos (1,5 segundos)
}
