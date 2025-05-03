/*

Realiza unha montaxe na que un servo (alimentado por unha batería externa) se conecte no pin PWM D03 (3~) 
como entrada de control (saída para Arduíno) e un potenciómetro se conecte no pin analóxico A05 como entrada 
do Arduíno. A continuación realiza un programa en C++ de Arduíno, de maneira que o potenciómetro controle o 
ángulo de xiro do servo, supoñendo que este pode xirar un máximo de 180º.

O programa debe ser reactivo ao potenciómetro, de maneira que se poida accionar 8 veces por segundo como moito. 
Maior frecuencia de accionamento pode reducir o tempo de vida das engranaxes internas.

A precisión do potenciómetro é de 10º, de maneira que conforme o potenciómetro se move cara á esquerda 
(sentido horario) o servo móvese cara á esquerda en ángulos de 10, 20, 30, etc sucesivamente. O movemento 
antihorario do potenciómetro permite recuperar as posicións do servo coa mesma precisión

Autor: Carlos Simil
Fecha: Maio 2025

*/


#include <Servo.h>

Servo primerServo;

int pinPot = A5;
int pinServo = 3;



void setup() {
primerServo.attach(pinServo);
}

void loop() {

int valorPot = analogRead(pinPot);  // Lectura dos valores do potenciometro
int angulo = map(valorPot, 0, 1023, 0, 180); // Mapear valores do potenciómetro cos grados do servo

angulo = (angulo / 10) * 10;  // Movemento de 10 grados
primerServo.write(angulo);
delay (125); // 1000 ms / 8 = 125ms
  
}

