const int pResistor = A0;  // Photoresistor at Arduino analog pin A0
const int ledPin=9;        // Led pin at Arduino pin 9

int value;		   // Store value from photoresistor (0-1023)

void setup()
{
 pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)
}

void loop()
{
  value = analogRead(pResistor);
  Serial.print(value);
  delay(500); //Small delay
}
