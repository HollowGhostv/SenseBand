#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 450

NewPing US(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

int V_PIN = 10;

void setup() {
  // Inicializa la comunicación serial y el pin de salida
  Serial.begin(9600);
  pinMode(V_PIN, OUTPUT);
}

void loop() {
  // Mide la distancia
  float distance = US.ping_cm();
  
  // Inicializa la potencia de vibración
  int PL = 0;

   Serial.print("La distancia es de ");
   Serial.print(distance);
   Serial.println(" cm");
   Serial.print("Potencia de vibracion: "); 
   Serial.println(PL);


  // Solo se ajusta la potencia si se detecta una distancia válida
  if (distance > 0) {
    // Mapea la distancia a la potencia del vibrador
    // Cuanto más cerca esté el objeto, mayor será la potencia
    PL = map(distance, 0, MAX_DISTANCE, 255, 0); // 255 para 0 cm, 0 para MAX_DISTANCE
    PL = constrain(PL, 0, 255); // Asegura que PL esté entre 0 y 255

    // Controla la potencia del vibrador
    analogWrite(V_PIN, PL);

    // Imprime la distancia y la potencia en el Monitor Serial
    // Mensaje de advertencia si el objeto está muy cerca
    if (distance <= 10) {
      Serial.println("CUIDADO");
    }
  } else { 
    // Si no se detecta nada, espera un segundo y muestra un mensaje
    delay(3000);
    Serial.println("No se ha detectado nada");
  }

  // Retraso para evitar lecturas excesivas
  delay(100);
}