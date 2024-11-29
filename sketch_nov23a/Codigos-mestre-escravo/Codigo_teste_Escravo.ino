#include <Wire.h>

// Configuração dos motores
#define ENA 9
#define IN1 7 
#define IN2 8 
#define ENB 6
#define IN3 3
#define IN4 2

// Configuração dos sensores infravermelhos
#define INF_ESQ A1
#define INF_DIR A0

// Corte do sensor
#define valorCorte 890 // Baseado nos valores informados

// Variáveis para controle dos motores
const int velocidade = 200;

void setup() {
  // Inicializa os pinos dos motores como saída
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Inicializa os sensores infravermelhos como entrada
  pinMode(INF_ESQ, INPUT);
  pinMode(INF_DIR, INPUT);

  // Inicializa a comunicação I2C
  Wire.begin(10); // Endereço do escravo
  Wire.onReceive(recebeComando); // Função de callback para receber comandos

  // Inicializa os motores desligados
  pararMotores();
}

void loop() {
  // O escravo espera o comando do mestre
}

// Função chamada quando o mestre envia comandos
void recebeComando(int comando) {
  // Aqui, o mestre envia '1' para ligar os motores
  if (Wire.available()) {
    int comandoRecebido = Wire.read(); // Lê o comando enviado pelo mestre
    
    if (comandoRecebido == 1) { // Comando para ligar os motores
      seguirLinha(); // Chama a função para seguir a linha
    } else {
      pararMotores(); // Comando para parar os motores
    }
  }
}

// Função para seguir a linha branca
void seguirLinha() {
  int valorEsq = analogRead(INF_ESQ); // Leitura do sensor esquerdo
  int valorDir = analogRead(INF_DIR); // Leitura do sensor direito

  if (valorEsq < valorCorte && valorDir < valorCorte) {
    // Ambos os sensores detectam branco -> Frente
    moverFrente();
  } else if (valorEsq < valorCorte && valorDir >= valorCorte) {
    // Esquerdo detecta branco e direito detecta preto -> Virar à direita
    virarDireita();
  } else if (valorEsq >= valorCorte && valorDir < valorCorte) {
    // Esquerdo detecta preto e direito detecta branco -> Virar à esquerda
    virarEsquerda();
  } else {
    // Ambos detectam preto -> Parar
    pararMotores();
  }
}

// Funções para controle dos motores
void moverFrente() {
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void virarDireita() {
  analogWrite(ENA, 100);
  analogWrite(ENB, 100); // Reduz a velocidade do motor direito
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void virarEsquerda() {
  analogWrite(ENA, 100); // Reduz a velocidade do motor esquerdo
  analogWrite(ENB, 100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void pararMotores() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
