/*

Realiza a montaxe para controlar tres servos empregando tres potenciómetros independentes.
O programa debe ser reactivo a cada potenciómetro, de maneira que se poida accionar 8 veces 
por segundo como moito. Maior frecuencia de accionamento pode reducir o tempo de vida das 
engranaxes internas.

Este programa pretende simular o comportamento dun brazo robótico de dous eixos e pinza. 

De maneira que: 
(a) un dos servos move o brazo nun ángulo horizontal (acimut), 
(b) outro servo move o brazo no ángulo de altura (sobre o horizonte) e 
(c) o terceiro abre e pecha a pinza. 

O servo (a) ten unha precisión de 12º,o servo (b) unha precisión de 5º e o servo (c) unha
precisión de 0.5º.

A precisión ten que ver con que o servo non se pode mover continuamente, se non a 'saltos' 
dun número determinado de graos.

Autor: Carlos Simil
Fecha: Maio 2025

*/


#include <Servo.h>

Servo servoA, servoB, servoC;

int potA = A0, potB = A1, potC = A2;
int valA, valB, valC;
int posA = 90, posB = 90, posC = 90;

void setup() {
  servoA.attach(9);
  servoB.attach(10);
  servoC.attach(11);
}

void loop() {
  valA = analogRead(potA);
  valB = analogRead(potB);
  valC = analogRead(potC);

  // Servo (a): precisión de 12º
  
  valA = map(valA, 0, 1023, 0, 15) * 12;
  if (valA != posA) {
    servoA.write(valA);
    posA = valA;
  }

  // Servo (b): precisión de 5º
  
  valB = map(valB, 0, 1023, 0, 36) * 5;
  if (valB != posB) {
    servoB.write(valB);
    posB = valB;
  }

  // Servo (c): precisión de 0.5º
  
  valC = map(valC, 0, 1023, 0, 360) * 0.5;
  if (valC != posC) {
    servoC.write(valC);
    posC = valC;
  }

  delay(125); // Accionamento 8 veces por segundo
}
