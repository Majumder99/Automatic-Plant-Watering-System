//Relay
#define relay_input 3
int soil = 0;
int moisture = 0;

//Soil sensor
#define soil_power_pin 8
#define soil_output A0

//Water sensor
#define water_power_pin 7
#define water_status A5
int water_level = 0;

//Humidity
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float temp = 0;

//Buzzer
#define buzzer_pin 4


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay_input, OUTPUT);
  pinMode(water_power_pin, OUTPUT);
  digitalWrite(water_power_pin, LOW);
  pinMode(soil_power_pin, OUTPUT);
  digitalWrite(soil_power_pin, LOW);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  // humidity
  float humi  = dht.readHumidity();

  if (isnan(humi)) {
    Serial.println(temp);    
  } else {
    temp = humi;
    Serial.println(humi);
    digitalWrite(soil_power_pin, HIGH);
    delay(20); // milisec
    soil = analogRead(soil_output);
    Serial.println(soil);
    digitalWrite(soil_power_pin, LOW);

    moisture = map(soil, 0 , 1023, 100, 0);
    Serial.println(moisture);

    if (moisture >= 75) {
      digitalWrite(relay_input, HIGH); //cutout relay
    } else {
      if (humi >= 100) {
        digitalWrite(relay_input, HIGH);//relay cut
      } else {
        digitalWrite(water_power_pin, HIGH);
        delay(20);
        water_level = analogRead(water_status);
        Serial.println(water_level);
        digitalWrite(water_power_pin, LOW);
        if(water_level <= 500){
          digitalWrite(relay_input, LOW);
        }else{
          tone(buzzer_pin, 1000);
          delay(1000);
          noTone(buzzer_pin);
          delay(1000);
        }
 
      }
    }
  }
  delay(500);
}
