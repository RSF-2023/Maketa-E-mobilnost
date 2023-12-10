

#include <FastLED.h>

#define NUM_LEDS 12

// dopolni z številkami pinov
#define DATA_PIN 3
#define small_switch 5
#define big_switch 2
#define cable_switch 4
#define bus_red_lamp 8
#define quality_zelena 9
#define quality_rumena 10
#define quality_oranzna 11
#define quality_rdeca 12

// Define the array of leds
CRGB leds[NUM_LEDS];
unsigned short green_level = 0;
unsigned short strip_state = 0;
unsigned long time_new, time_old=0;
unsigned short currentStateCable,previousStateCable = LOW;

void setup() { 
    pinMode(quality_rdeca,OUTPUT);//
    pinMode(quality_oranzna,OUTPUT);//
    pinMode(quality_rumena ,OUTPUT);//
    pinMode(quality_zelena,OUTPUT);//
    pinMode(bus_red_lamp,OUTPUT);//
    pinMode(small_switch,INPUT);
    pinMode(big_switch,INPUT);
    pinMode(cable_switch,INPUT);
     FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
     FastLED.setBrightness(12);

       for(int i = 0; i<NUM_LEDS; i++){
     leds[i]= CRGB::Blue;
    }
    
    FastLED.show();
     Serial.begin(9600);
}
void loop() { 

    currentStateCable = digitalRead(cable_switch);
  
  //leds[0] = CRGB::Red;
  if(currentStateCable==HIGH&&previousStateCable == HIGH){strip_state++; strip_state = strip_state%4;}
  if(currentStateCable==LOW&&previousStateCable == HIGH){ for(int i = 0; i < NUM_LEDS; i++){leds[i]=CRGB::Blue;} FastLED.show();}

  Serial.println(strip_state);
  time_new = millis();

  

  if(((time_new - time_old)>300)&&digitalRead(cable_switch)==HIGH){


    
  switch(strip_state){
       case 0: for(int i = 0; i < NUM_LEDS; i++){leds[i]=CRGB::Black;} leds[0] = CRGB::Red; leds[7] = CRGB::Red;leds[8] = CRGB::Red; FastLED.show(); break;
       case 1: for(int i = 0; i < NUM_LEDS; i++){leds[i]=CRGB::Black;} leds[0] = CRGB::Red; leds[7] = CRGB::Red;leds[8] = CRGB::Red; leds[1] = CRGB::Orange;leds[6] = CRGB::Orange;leds[9] = CRGB::Orange; FastLED.show(); break;
       case 2: for(int i = 0; i < NUM_LEDS; i++){leds[i]=CRGB::Black;} leds[0] = CRGB::Red; leds[7] = CRGB::Red;leds[8] = CRGB::Red; leds[1] = CRGB::Orange;leds[6] = CRGB::Orange;leds[9] = CRGB::Orange;leds[2] = CRGB::Yellow;leds[5] = CRGB::Yellow;leds[10] = CRGB::Yellow; FastLED.show(); break;
       case 3: for(int i = 0; i < NUM_LEDS; i++){leds[i]=CRGB::Black;} leds[0] = CRGB::Red; leds[7] = CRGB::Red;leds[8] = CRGB::Red; leds[1] = CRGB::Orange;leds[6] = CRGB::Orange;leds[9] = CRGB::Orange;leds[2] = CRGB::Yellow;leds[5] = CRGB::Yellow;leds[10] = CRGB::Yellow; leds[3] = CRGB::Green;leds[4] = CRGB::Green; leds[11] = CRGB::Green;  FastLED.show();    break;           
       default: for(int i = 0; i < NUM_LEDS; i++){leds[i]=CRGB::Blue;} FastLED.show(); break;
    }
    time_old = time_new;
  }
  digitalWrite(bus_red_lamp,!digitalRead(small_switch));  
  green_level = digitalRead(small_switch)+digitalRead(big_switch)+digitalRead(cable_switch);  
    
  if(green_level == 1){digitalWrite(quality_rdeca,LOW);digitalWrite(quality_oranzna,HIGH);digitalWrite(quality_rumena,LOW);digitalWrite(quality_zelena,LOW);}
  else if(green_level == 2){digitalWrite(quality_rdeca,LOW);digitalWrite(quality_oranzna,LOW);digitalWrite(quality_rumena,HIGH);digitalWrite(quality_zelena,LOW);}
  else if(green_level == 3){digitalWrite(quality_rdeca,LOW);digitalWrite(quality_oranzna,LOW);digitalWrite(quality_rumena,LOW);digitalWrite(quality_zelena,HIGH);}
  else{digitalWrite(quality_rdeca,HIGH);digitalWrite(quality_oranzna,LOW);digitalWrite(quality_rumena,LOW);digitalWrite(quality_zelena,LOW);}


  previousStateCable = currentStateCable;
  delay(1);
  
}
