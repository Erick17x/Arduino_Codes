// Corte do sensor ajustado para sua observação
#define valorCorte 980  // Ajuste este valor com base nas leituras dos sensores

// Leitura dos sensores
int valorDir = analogRead(sensorDir);
int valorEsq = analogRead(sensorEsq);

// Ações com base na detecção da linha
if (valorDir > valorCorte && valorEsq > valorCorte) {
  // Sobre a linha preta, continuar movendo para frente
  digitalWrite(motorEsq, HIGH);
  digitalWrite(motorDir, HIGH);
  digitalWrite(esqFrente, HIGH);
  digitalWrite(esqTras, LOW);
  digitalWrite(dirFrente, HIGH);
  digitalWrite(dirTras, LOW);
}
else if (valorDir < valorCorte && valorEsq < valorCorte) {
  // Sobre a linha branca, continuar movendo para frente
  digitalWrite(motorEsq, HIGH);
  digitalWrite(motorDir, HIGH);
  digitalWrite(esqFrente, HIGH);
  digitalWrite(esqTras, LOW);
  digitalWrite(dirFrente, HIGH);
  digitalWrite(dirTras, LOW);
}
else {
  // Ajuste para seguir a linha caso o robô saia um pouco da linha branca

  if (valorDir < valorCorte) {
    // Virar à esquerda (linha branca no sensor direito)
    digitalWrite(motorEsq, HIGH);
    digitalWrite(motorDir, LOW);
    digitalWrite(esqFrente, HIGH);
    digitalWrite(esqTras, LOW);
    digitalWrite(dirFrente, LOW);
    digitalWrite(dirTras, LOW);
  }
  else if (valorEsq < valorCorte) {
    // Virar à direita (linha branca no sensor esquerdo)
    digitalWrite(motorEsq, LOW);
    digitalWrite(motorDir, HIGH);
    digitalWrite(esqFrente, LOW);
    digitalWrite(esqTras, LOW);
    digitalWrite(dirFrente, HIGH);
    digitalWrite(dirTras, LOW);
  }
}
