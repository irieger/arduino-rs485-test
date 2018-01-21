#define TX_PIN 10


void setup()
{
    pinMode(TX_PIN, OUTPUT);
    digitalWrite(TX_PIN, HIGH);

    Serial.begin(115200);
    Serial2.begin(115200);
    Serial.println("Setup done");
}



unsigned int value = 0;

void loop()
{
    int c;

    while(!Serial.available() && Serial2.available() < 2);

    if (Serial2.available() >= 2)
    {
        Serial2.readBytes((byte*) &value, 2);
        Serial.print("< ");
        Serial.println(value);
        value = 0;
    }

    if (Serial.available())
    {
        c = Serial.read();
        if ((c>='0') && (c<='9'))
            value = 10 * value + c - '0';
        else if (c=='s')
        {
            Serial.print("> ");
            Serial.println(value);
            digitalWrite(TX_PIN, HIGH);
            delayMicroseconds(1200);
            Serial2.write((byte*) &value, 2);
            delayMicroseconds(1200);
            digitalWrite(TX_PIN, LOW);
            value = 0;
        }
    }
    
    delay(2);
}

