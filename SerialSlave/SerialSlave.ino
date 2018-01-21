#define TX_PIN 10


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    pinMode(TX_PIN, OUTPUT);
    digitalWrite(TX_PIN, LOW);

    Serial.begin(115200);
    Serial2.begin(115200);
    Serial.println("Setup done");
}



unsigned int value = 0;

void loop()
{
    // Wait for byte on serial
    while(Serial2.available() < 2);

    Serial2.readBytes( (byte*) &value, 2 );
    Serial.print("Got value: ");
    Serial.println(value);

    value = value >> 2;
    digitalWrite(LED_BUILTIN, HIGH);

    delay(2);

    digitalWrite(TX_PIN, HIGH);
    delayMicroseconds(1200);
    Serial2.write((byte*) &value, 2);
    delayMicroseconds(1200);
    digitalWrite(TX_PIN, LOW);
    
    digitalWrite(LED_BUILTIN, LOW);

    value = 0;
}
