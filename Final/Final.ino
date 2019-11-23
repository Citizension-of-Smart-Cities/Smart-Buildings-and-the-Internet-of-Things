/********************************
 * Libraries included
 *******************************/

#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>
#include <SimpleDHT.h>

/********************************
 * Constants and objects
 *******************************/

char const * TOKEN = "tokenhere"; // Assign your Ubidots TOKEN
char const * VARIABLE_LABEL_1 = "temperature"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_2 = "humidity"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_3 = "light"; // Assign the unique variable label to send the data

int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

const int pResistor = A0;  // Photoresistor at Arduino analog pin A0

int value;       // Store value from photoresistor (0-1023)

byte mac[] = { 0x69, 0x69, 0x69, 0x69, 0x69, 0x69 };

Ubidots client(TOKEN);

/********************************
 * Main Functions
 *******************************/

void setup() 
{
  pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)
  Serial.begin(9600);
  //client.setDebug(true);// uncomment this line to visualize the debug message
  /* start the Ethernet connection */
  Serial.print(F("Starting ethernet..."));
  if (!Ethernet.begin(mac)) 
  {
    Serial.println(F("failed"));
  } else {
    Serial.println(Ethernet.localIP());
  }
  /* Give the Ethernet shield a second to initialize */
  delay(2000);
  Serial.println(F("Ready"));
}

void loop() 
{

  Ethernet.maintain();

  /* Sensors readings */
  value = analogRead(pResistor);
  
  Serial.println(value);
  
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
  
  client.add(VARIABLE_LABEL_1, temperature);
  client.add(VARIABLE_LABEL_2, humidity);
  client.add(VARIABLE_LABEL_3, value);
  client.sendAll();
  delay(5000);
}
