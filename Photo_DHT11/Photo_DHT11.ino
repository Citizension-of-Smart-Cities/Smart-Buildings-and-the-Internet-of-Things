#include <SimpleDHT.h>

int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

const int pResistor = A0;  // Photoresistor at Arduino analog pin A0

int value;       // Store value from photoresistor (0-1023)

void setup()
{
  pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)
  Serial.begin(115200);
}

void loop()
{
  value = analogRead(pResistor);
  Serial.print(value);
  Serial.print("\n");
   // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" %");
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
