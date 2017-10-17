/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 16.10.2017 11:04:53
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/
const int ID = 1;
const float TABLE_LN = 70.0;

const byte TRG_PIN = 2;
const byte ECH_PIN = 3;

const unsigned long TIMEOUT = 25000UL;
const float SOUND_SPEED = 34.0 / 1000;

bool LAST_STATE = false;
int COUNT = 0;

void notifyChange(int state, float dist);

void setup()
{

      Serial.begin(115200);
      
      pinMode(TRG_PIN, OUTPUT);
      digitalWrite(TRG_PIN, LOW);
      pinMode(ECH_PIN, INPUT);
      
      Serial.print(F("Started!"));

}

void loop()
{
    bool occupied;
    digitalWrite(TRG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRG_PIN, LOW);
    
    long mesure = pulseIn(ECH_PIN, HIGH, TIMEOUT);
    
    //resultat en cm
    float dist = mesure / 2.0 * SOUND_SPEED;
    
    
    if (dist < TABLE_LN) {
      occupied = true;
    } else {
      occupied = false;
    }

    if (occupied != LAST_STATE) {
      Serial.print("changed state !");
      Serial.println();
      COUNT++;
    } else {
      COUNT = 0;
    }

    if (COUNT > 2) {
      COUNT = 0;
      LAST_STATE = occupied;
      notifyChange(occupied, dist);
    }
    
   
    
    delay(1000);

}


void notifyChange (bool state, float dist) {
   Serial.print("{id : ");
    Serial.print(ID);
    Serial.print(F(", distance : "));
    Serial.print(dist);
    Serial.print("cm, Occupied : ");
    Serial.print(state);
    Serial.print("}");
    Serial.println();
}

