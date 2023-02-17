#include <Adafruit_NeoPixel.h>

class JOUEUR {
  
  private:
    byte m_color[3];
  	byte m_pin; 
  	bool m_avance;
    unsigned int m_pos;
    unsigned int m_start;
    unsigned int m_end;

  public:
  	JOUEUR();
  	void init(byte pin,byte r,byte v, byte b,unsigned int depart,unsigned int arrivee);
    int getPos();
  	byte getPin();

    
  	void setPos(int pos);  	
  	byte getColor(int i);  
    void checkButton();  
};


const int NUM_LED=150;
const int PIN_RUB=6;

const int ARRIVE=NUM_LED-2;

Adafruit_NeoPixel ruban(NUM_LED, PIN_RUB, NEO_GRB + NEO_KHZ800);

const byte PIN_BOUT[]={2,3,4,5};
const byte PIN_LED_CHECK=12; 

JOUEUR joueur[4];
int NUM_JOUEUR=4;

void setup()
{  
  Serial.begin(9600);
  
  initGame();

  for (int i=0;i<NUM_JOUEUR;i++){
  pinMode(joueur[i].getPin(), INPUT_PULLUP);
  }

  pinMode(PIN_LED_CHECK,OUTPUT);
  
  ruban.begin();

  Serial.println("Initialisation terminée");
    
}

void loop()
{  
 ruban.clear();
  
 for (int i=0;i<NUM_JOUEUR;i++){

   
    joueur[i].checkButton();
    
    bool occupe=false;
    for (int j=0;j<i;j++){
    	if(joueur[i].getPos()==joueur[j].getPos()) occupe=true;
    }
    
    if(occupe) ruban.setPixelColor(joueur[i].getPos(),ruban.Color(200,200,200));
    else ruban.setPixelColor(joueur[i].getPos(),ruban.Color(joueur[i].getColor(0),joueur[i].getColor(1),joueur[i].getColor(2)));
 
  }  
  
  ruban.setPixelColor(ARRIVE,ruban.Color(255,0,0));
   
  ruban.show();
  
  checkArrive();
    
}

void checkArrive(){
  
  for (int i=0;i<NUM_JOUEUR;i++){
    if (joueur[i].getPos()==ARRIVE){
       
       for(int t=0;t<10;t++){ 
        ruban.clear();
        for(int j=0;j<NUM_LED;j++){
        ruban.setPixelColor(j,ruban.Color(0,0,0));
        }
       
          for(int j=0;j<NUM_LED;j++){
            ruban.setPixelColor(j,ruban.Color(joueur[i].getColor(0),joueur[i].getColor(1),joueur[i].getColor(2)));
      	    ruban.show();
            delay(2);
          }
       }    
      delay(5000);
      initGame();
    }
   
	}
}

void initGame(){
 joueur[0].init(PIN_BOUT[0],0,255,0,0,ARRIVE); //(pin, r, v, b, depart, arrivee)
 joueur[1].init(PIN_BOUT[1],255,255,0,1,ARRIVE);
 joueur[2].init(PIN_BOUT[2],255,0,255,ARRIVE/4,ARRIVE);
 joueur[3].init(PIN_BOUT[3],0,0,255,ARRIVE/2,ARRIVE);
}


JOUEUR::JOUEUR()
{
  m_pos=0;
  m_end=100;
  m_avance=false;
}

void JOUEUR::init(byte pin,byte r,byte v, byte b,unsigned int depart,unsigned int arrivee)
{
  m_pin=pin;
  m_color[0]=r;
  m_color[1]=v;
  m_color[2]=b;
  m_pos=depart;
  m_end=arrivee;
}

void JOUEUR::checkButton(){
  
  if((!digitalRead(m_pin))){
    if (m_avance){
      delay(10);
      m_pos=(m_pos+1)%(m_end+1) ;
      m_avance=false;
      Serial.println("Press");
    }
  }
  else m_avance=true;     
  }

int JOUEUR::getPos(){
  return m_pos;
}

byte JOUEUR::getPin(){
  return m_pin;
}

void JOUEUR::setPos(int pos)
{
  m_pos=pos;
}

byte JOUEUR::getColor(int i){
	return m_color[i];
}
