#include <DHT.h>
#include <SPI.h>
#include <MFRC522.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define MOTIONPIN 2
#define BUZZERPIN 5
#define RFID_RST_PIN 9
#define RFID_SS_PIN 10
#define GREEN_LED_PIN 6
#define RED_LED_PIN 7

DHT dht(DHTPIN, DHTTYPE);
MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);

const float TEMP_THRESHOLD = 30.0;
const float HUM_THRESHOLD = 70.0;
const float FEELS_LIKE_THRESHOLD = 35.0; // Example value

bool systemArmed = true;

void setup() {
  Serial.begin(9600);
  pinMode(MOTIONPIN, INPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);
  
  dht.begin();
  SPI.begin();
  rfid.PCD_Init();
  
  Serial.println("System Initialized");
}

void loop() {
  if (systemArmed) {
    handleMotion();
    handleTemperatureHumidity();
  }
  handleRFID();
  delay(1000);
}

void handleMotion() {
  int motionState = digitalRead(MOTIONPIN);
  if (motionState == HIGH) {
    triggerAlarm();
    Serial.println("Motion detected!");
  }
}

void handleTemperatureHumidity() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  float feelsLikeTemp = calculateFeelsLikeTemp(temp, hum);
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" *C, Hum: ");
  Serial.print(hum);
  Serial.println(" %");

  if (temp > TEMP_THRESHOLD || hum > HUM_THRESHOLD) {
    triggerAlarm();
    Serial.println("Temperature or Humidity threshold crossed!");
  }
}

void handleRFID() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  if (isKnownRFIDCard()) {
    systemArmed = !systemArmed;
    if (systemArmed) {
      Serial.println("System Armed");
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
    } else {
      Serial.println("System Disarmed");
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(BUZZERPIN, LOW);  
    }
  }
}

bool isKnownRFIDCard() {
  // Check against known RFID cards (UIDs)
  return true;
}

void triggerAlarm() {
  digitalWrite(BUZZERPIN, HIGH);
  delay(2000);
  digitalWrite(BUZZERPIN, LOW);
}

float calculateFeelsLikeTemp(float temp, float hum) {
  // Simple formula for feels-like temperature
  return temp + (0.5 * (hum / 100) * (temp - 14.4)) + 46.4;
}
