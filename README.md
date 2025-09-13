# Simple LoRa Communication – Heltec WiFi LoRa 32 (ESP32 + SX1276)

This project provides a minimal example of sending and receiving plain text over LoRa using a **Heltec WiFi LoRa 32** development board.  
Flash the same sketch onto two boards: what one sends, the other receives (and vice versa through each Serial Monitor).

---

## 🧩 Hardware Required

- 2 × Heltec WiFi LoRa 32 boards (V2 or compatible SX1276/SX1278)
- USB cable
- Proper LoRa antenna (MANDATORY)

> Never power or transmit without an antenna attached: you can permanently damage the RF stage.

---

## 📁 Main File

- `lora_communication.ino` – minimal LoRa send/receive text example.

---

## 🔧 Dependencies & Setup

1. Open Arduino IDE (or PlatformIO).
2. Install LoRa library:  
   - Arduino IDE: Tools > Manage Libraries… → search “LoRa” (by Sandeep Mistry) → Install.  
   - PlatformIO: `lib_deps = sandeepmistry/LoRa`
3. Install ESP32 board support:  
   - Preferences → Additional Boards Manager URLs:  
     `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Tools > Board > Boards Manager… → search “esp32” → Install.
4. Select board: `Heltec WiFi LoRa 32 (V2)` (or matching model).
5. Serial baud rate in Monitor: `9600`.

---

## 📡 Pin Configuration (Heltec default)

| Signal | ESP32 Pin |
|--------|-----------|
| NSS / SS | 18 |
| RST | 14 |
| DIO0 | 26 |
| SCK | 5 (SPI) |
| MOSI | 27 |
| MISO | 19 |

In code:
```cpp
#define SS 18
#define RST 14
#define DIO0 26
LoRa.setPins(SS, RST, DIO0);
```

---

## 🌍 Frequency Selection

Code line:
```cpp
LoRa.begin(868E6);  // EU868
```

Adjust for your regulatory region:
- Europe: `868E6`
- North America: `915E6`
- Some Asia regions: `433E6`

> Always verify local spectrum regulations (duty cycle, maximum EIRP, channelization).

---

## ▶️ How to Use

1. Flash the sketch on both boards.
2. Open a Serial Monitor on each (9600 baud, “Newline” enabled recommended).
3. Type a message on one board → press Enter.
4. Observe the output on the other board: `Message received : <text>`
5. Type back from the other board to reply.

---

## 🧪 Example Interaction

Serial input:
```
Hello LoRa network
```

Console output:
```
Envoi du message : Hello LoRa network
Message envoyé !
Message reçu : Hello LoRa network
```

---

## 📈 Possible Enhancements

| Goal | Improvement |
|------|-------------|
| Device identification | Prefix with an ID: `DEV_A:payload` |
| Reliability | Add ACK + retry on timeout |
| Link diagnostics | Print RSSI & SNR |
| Security | Encrypt payload (AES-128) |
| Structured data | Custom frame header (id, type, len, checksum) |
| Memory stability | Replace `String` with static char buffers |
| Range tuning | Adjust SF/BW/CR and Tx power |
| Power saving | Use deep sleep, put radio in standby |
| Logging | Add timestamps or sequence numbers |

Example to show RSSI / SNR:
```cpp
int rssi = LoRa.packetRssi();
float snr = LoRa.packetSnr();
Serial.printf("RSSI: %d dBm | SNR: %.2f dB\n", rssi, snr);
```

---

## ⚙️ Radio Parameter Tuning

```cpp
LoRa.setSpreadingFactor(7);       // 6–12 (higher = longer range, lower bitrate)
LoRa.setSignalBandwidth(125E3);   // 62.5E3, 125E3, 250E3, 500E3
LoRa.setCodingRate4(5);           // 5–8 (higher = more redundancy)
LoRa.setTxPower(17);              // Respect regional RF limits
```

> Experiment in your environment to find the balance between range, airtime, and reliability.

---

## 🛡️ Compliance & Good Practices

- Respect regional duty cycle or airtime limits (e.g., 1% in parts of EU868).
- Add delays or scheduling if transmitting frequently.
- Avoid sending large or constant chatter for fair spectrum use.

---

## 🧵 Simple Device ID Variant

Sending with ID:
```cpp
String deviceId = "DEV_A";
LoRa.beginPacket();
LoRa.print(deviceId + ":" + outgoing);
LoRa.endPacket();
```

Parsing on receive:
```cpp
if (incoming.indexOf(':') > 0) {
  String from = incoming.substring(0, incoming.indexOf(':'));
  String payload = incoming.substring(incoming.indexOf(':') + 1);
  Serial.println("From " + from + " => " + payload);
}
```

---

## 🧪 Debugging Tips

| Issue | Check |
|-------|-------|
| No packets received | Same frequency & parameters on both boards |
| init failed | Pins + antenna + library version |
| Garbled text | Serial settings / power stability |
| Short range | Antenna quality, SF increase, ensure proper power setting |



## 🤝 Contributing

PRs welcome: protocol abstraction, encryption, OLED status (Heltec has onboard OLED), low-power modes, reliability layer, etc.

---

## ✅ Suggested Roadmap

1. Add RSSI/SNR in reception log  
2. Introduce frame structure (ID + msgType + seq + length + checksum)  
3. Implement ACK & retransmission policy  
4. Add optional AES payload encryption  
5. Low-power cycle between receive windows  
6. Abstract into a `LoRaMessenger` class

---

## 📚 References

- LoRa Arduino Library: https://github.com/sandeepmistry/arduino-LoRa
- Heltec Documentation: https://heltec.org
- ETSI EN300.220 (EU SRD regulations overview)

---

## ✨ Author

Adapted for Heltec LoRa32 by (ARMOUMAD / handle).


