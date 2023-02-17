const int BOUT_PIN=2;
const int HP_PIN=11;


int N=20; //diviseur de dt pour répétition clic

unsigned long t0=0;
unsigned long dt=1000000;
const int DT_RALENTI=2000;
int timeRepeat=DT_RALENTI/2/N;


void setup() {
pinMode(BOUT_PIN,INPUT);
pinMode(HP_PIN,OUTPUT);
attachInterrupt(digitalPinToInterrupt(BOUT_PIN), chrono, FALLING);

Serial.begin(9600);
}

void loop() {

if ((millis()-t0)>3000){dt=DT_RALENTI;}
  
if (dt<2000){timeRepeat=dt/2/N;}
else {timeRepeat=DT_RALENTI/2/N;}

digitalWrite(HP_PIN,HIGH);
delay(2*timeRepeat);
digitalWrite(HP_PIN,LOW);
delay(2*timeRepeat);
}

void chrono(){
  unsigned long dtTest=millis()-t0;
  if (dtTest>20){
    dt=dtTest;  
    Serial.println(dt);
    t0=millis();  
    }
}
