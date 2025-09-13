#include <SPI.h>
#include <LoRa.h>

// Configuration LoRa
#define SS 18
#define RST 14
#define DIO0 26

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialisation de LoRa...");

  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(868E6)) {  // Changez la fréquence selon vos modules (433E6, 866E6, ou 915E6)
    Serial.println("Échec de l'initialisation LoRa !");
    while (1);
  }

  Serial.println("Module LoRa prêt !");
  Serial.println("Entrez un message pour l'envoyer.");
}

void loop() {
  // Envoi d'un message saisi dans le Moniteur Série
  if (Serial.available() > 0) {
    String outgoing = Serial.readStringUntil('\n'); // Lire le message saisi
    outgoing.trim(); // Supprimer les espaces inutiles

    if (outgoing.length() > 0) {
      Serial.println("Envoi du message : " + outgoing);

      // Envoi via LoRa
      LoRa.beginPacket();
      LoRa.print(outgoing);
      LoRa.endPacket();

      Serial.println("Message envoyé !");
    }
  }

  // Réception des messages
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    Serial.println("Message reçu : " + incoming);
  }
}