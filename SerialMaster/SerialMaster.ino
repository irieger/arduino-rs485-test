#define TX_PIN 10

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    pinMode(TX_PIN, OUTPUT);
    digitalWrite(TX_PIN, HIGH);

    Serial.begin(115200);
    Serial2.begin(115200);
    Serial.println("Setup done");
}



byte start_byte_1 = 0x3C;
byte start_byte_2 = 0xC3;

unsigned int value = 0;

byte c;


void loop()
{
    int c;

    while(!Serial.available() && Serial2.available() < 4);

    digitalWrite(LED_BUILTIN, HIGH);

    if (Serial2.available() >= 4)
    {
        if (Serial2.read() == start_byte_1)
        {
            if (Serial2.read() == start_byte_2)
            {
                value  = Serial2.read();
                value += (((unsigned int) Serial2.read()) << 8) & 0xFF00;
                Serial.print("< ");
                Serial.println(value);
                value = 0;
            }
        }
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
            Serial2.write(start_byte_1);
            Serial2.write(start_byte_2);
            Serial2.write((byte) (value & 0x00FF));
            Serial2.write((byte) (value >> 8));
            Serial2.flush();
            delayMicroseconds(1200);
            digitalWrite(TX_PIN, LOW);
            value = 0;
        }
    }
    
    delay(2);

    digitalWrite(LED_BUILTIN, LOW);
}

