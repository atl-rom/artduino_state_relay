unsigned long interval = 200;
//byte flag=1;
unsigned long previousMillis=0;

unsigned long currentMillis = 0;
int pin = 10;   //pin3 for mosfets, pin 10 for relays

 
int V0 = 05;

int V1 = 20;

int V2 = 1000;

int V3 = 1020;
void setup()
{
 
 
   pinMode(pin, OUTPUT);
  Serial.begin(9600);

  }




void loop()
{





    static enum { IN_RANGE, OUT_OF_RANGE, TIMEOUT } state;
    static uint32_t time_exited_range;
    int V = analogRead(A0);
    delay(1);//delay betweem reads for stability
    switch (state) {
    case IN_RANGE:
        if (V < V0 || V >= V3) {
            digitalWrite(pin, LOW);
            state = OUT_OF_RANGE;
            time_exited_range = millis();
        }
        break;
    case OUT_OF_RANGE:
        if (V >= V1 && V < V2) {
            digitalWrite(pin, HIGH);
            state = IN_RANGE;
        } else if (millis() - time_exited_range >= 2000) {
            digitalWrite(pin, HIGH);
            state = TIMEOUT;
        }
        break;
    case TIMEOUT:
        if (V >= V1 && V < V2) {
            state = IN_RANGE;
        }
        break;
    }





   
}
