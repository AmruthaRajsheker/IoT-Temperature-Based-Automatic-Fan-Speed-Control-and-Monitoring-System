#include <DHT.h>

// DHT settings
#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Temperature sensor settings
const int tempPin = A0;  // Analog pin connected to the temperature sensor

// Fan settings
const int fanPin = 3;    // Digital pin connected to the fan control

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(fanPin, OUTPUT); // Set fan pin as output
}

void loop() {
  // Read temperature and humidity from DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read temperature from separate temperature sensor
  int tempSensorValue = analogRead(tempPin);
  float tempVoltage = tempSensorValue * (5.0 / 1023.0);  // Convert ADC reading to voltage
  float tempCelsius = (tempVoltage - 0.5) * 100;  // Convert voltage to Celsius

  // Control the fan based on temperature
  if (tempCelsius > 77.0) { // Adjust threshold as needed
    digitalWrite(fanPin, HIGH); // Turn on the fan
  } else {
    digitalWrite(fanPin, LOW); // Turn off the fan
  }

  // Print readings
  

  Serial.print("Temp Sensor - ");
  Serial.print("Temperature: ");
  Serial.print(tempCelsius);
  Serial.println("°C");

  delay(10000);  // Delay between readings
}