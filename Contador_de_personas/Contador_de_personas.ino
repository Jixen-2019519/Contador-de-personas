/*
  Fundacion Kinal
  Centro Educativo Tecnico Laborla Kinal
  Electronica
  Grado: Quinto
  Seccion: A
  Curso: Taller de eleectronica digital y reparacion de computadoras I
  Nombre: Juan Manuel Sebastian Ixen Coy
  Carne: 2019519
  Fecha: 04/05
*/
#include <LiquidCrystal.h>

#define RS 6
#define E 7
#define D7 2
#define D6 3
#define D5 4
#define D4 5
#define trig A1
#define echo A0
#define Buzzer 8

int Distancia;
int Duracion;
int conteo = 0;
int Fre = 440;

LiquidCrystal LCD_Jixen(RS, E, D4, D5, D6, D7);

byte persona[] = {
  B01110,
  B01110,
  B01110,
  B10101,
  B01110,
  B00100,
  B01110,
  B01010
};


void setup() {
  
 LCD_Jixen.begin(16, 2);
  LCD_Jixen.setCursor(0, 0);
  LCD_Jixen.print("Personas:");
  LCD_Jixen.setCursor(0, 0);
  LCD_Jixen.createChar(1, persona);

  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(Buzzer, OUTPUT);
  
}

void loop() {
  LCD_Jixen.write(1);

 
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  Duracion = pulseIn(echo, HIGH);
  Distancia = Duracion / 59;
  Serial.println(Distancia);
  delay(500);

  if (Distancia > 6 && Distancia < 10) {
    conteo = incrementarConteo(conteo);
  }

  actualizarDisplay(conteo);
  reproducirBuzzer(conteo);
}

int incrementarConteo(int conteoActual) {
  return conteoActual + 1;
}

void actualizarDisplay(int conteoActual) {
  if (conteoActual < 16) {
    int columna = 0;
    int i = 0;
    while (i < conteoActual) {
      if (columna == 0) {
        LCD_Jixen.setCursor(i, 1);
        LCD_Jixen.write(1);
        columna = 1;
        i++;
      } else if (columna == 1) {
        LCD_Jixen.setCursor(i, 1);
        LCD_Jixen.write(1);
        columna = 0;
        i++;
      }
    }
    for (i = i; i < 16; i++) {
      LCD_Jixen.setCursor(i, 1);
      LCD_Jixen.write(' ');
    }
  } else {
    LCD_Jixen.setCursor(15, 1);
    LCD_Jixen.write(1);
    delay(500);
    LCD_Jixen.setCursor(15, 1);
    LCD_Jixen.write(1);
    delay(500);
  }
}

void reproducirBuzzer(int conteoActual) {
  if (conteoActual >= 16) {
    tone(Buzzer, Fre, 440);
  } else {
    noTone(Buzzer);
  }
}
