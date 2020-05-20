#include <DHT.h>

#define BIT_PER_SEC 9600
#define DHT_TYPE    DHT22 // AM2302
#define DHT_PIN     2     // PWM for temperature/humidity
#define SUN_DO_PIN  3     // PWM for sunlight digital output
#define SUN_AO_PIN  0     // for sunlight analog output
#define M_TIME      2000  // seconds between each measurement

// initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {

  Serial.begin(BIT_PER_SEC);
  
  dht.begin();
  
  // getting output of sunlight from SUN_DO_PIN
  pinMode(SUN_DO_PIN, OUTPUT);
}

void loop() {

  delay(M_TIME);

  // reading temp|hum takes about 250 millisec
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  // validate the read values for hum/temp
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read temperature and humidity");

    // set the values as inadequate so the interpreter will know
    humidity = -1;
    temp = -100;
  }

  // reading sunlight intensity (divide by 1023=max)
  int sunlight = analogRead(SUN_AO_PIN);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %  |  Temperature: ");
  Serial.print(temp);
  Serial.print(" *C  |  Sunlight: ");
  Serial.print(sunlight);
  Serial.println(" %");
}
