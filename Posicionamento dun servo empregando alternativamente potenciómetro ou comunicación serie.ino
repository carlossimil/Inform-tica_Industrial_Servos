/*

Xuntar a reactividade ao potenciómetro coa reactividade á comunicación serie.

O programa debe ser reactivo ao potenciómetro, pero ademais, se existe unha orde 
en forma de texto na entrada serie, débese priorizar a orde lida. 

É dicir, compróbase a entrada serie, se hai entrada execútase, se non existe orde 
en forma de texto, posiciónase o servo onde indique o potenciómetro. Ademais, se a 
posicióndo potenciómetro non variou, o servo debe permanecer na posición indicada
polo monitor serie. No momento en que muden ou ben a posición do potenciómetro ou ben
a orde do monitor serie, o servo debe reposicionarse. Sempre tendo en conta a prioridade 
do monitor serie sobre o potenciómetro.

O servo só se pode accionar un máximo de 0.15 veces por segundo, tanto para o 
potenciómetro como para o monitor serie.

As ordes que se poden admitir por comunicación serie son: 
(a) 'esquerda', 
(b) 'diagonal esquerda', 
(c) 'centro', (
d) 'diagonal dereita', 
(e) 'dereita', ou ben 
(f) un número enteiro entre 0 e 180. 

As ordes textuais deben estar en minúsculas e deben corresponder a un reparto equitativo 
entre 0 e 180º.

Autor: Carlos Simil
Fecha: Maio 2025

*/


#include <Servo.h>

Servo servoA;  


int posA = 90;
int lastPosA = -1; // Últimas posicións para detectar cambios
unsigned long lastUpdate = 0;  // Última actualización
const long updateInterval = 666;  // Intervalo de actualización (0.15 veces por segundo)

void setup() {
  servoA.attach(9);
  Serial.println("Listo para recibir ordes.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Eliminar espazos en branco ao redor

    if (command == "esquerda") {
      posA = 0;
    } else if (command == "diagonal esquerda") {
      posA = 45;
    } else if (command == "centro") {
      posA = 90;
    } else if (command == "diagonal dereita") {
      posA = 135;
    } else if (command == "dereita") {
      posA = 180;
    } else if (command.toInt() >= 0 && command.toInt() <= 180) {
      posA = command.toInt();
    }
    lastUpdate = millis();  // Actualizar o tempo da última actualización
  }

  // Control do potenciómetro
  int valA = analogRead(A5);


  valA = map(valA, 0, 1023, 0, 180);


  // Actualizar os servos só se a posición cambiou ou se pasou o intervalo de actualización
  if ((millis() - lastUpdate >= updateInterval) || (valA != lastPosA)) {
    servoA.write(valA);
    lastPosA = valA;
  }
}
