//Code to control 2 pump using a H bridge, we power them using the Vin and the direction is controlled by SW, they are used in a single direction and 
//output pump is a bit faster than the input one. There are 2 buttons to speed up and down the pump with some limitation to the velocity.

#include "define.h"
#include "pin.h"



int duty_bin1 = 186;  //a 199 funzionano entrambi i motori    initial duty cicle
int duty_bin2 =  duty_bin1 - DIFF_PWM;


int k = 0;
int flag_loop=1;  // se 1 entro nel case che controlla gli stati on e off         1 enter the switch case to control motor status



void setup() {

  Serial.begin(9600); // open the serial port at 9600 bps, used for debugging
  pinMode(power_pump_button, INPUT);
  pinMode(up_pump_button, INPUT);
  pinMode(down_pump_button, INPUT);
   
  pinMode(enable_PWM_1, OUTPUT);
  pinMode(direction_pin_1, OUTPUT);
  pinMode(enable_PWM_2, OUTPUT);
  pinMode(direction_pin_2, OUTPUT);

  digitalWrite(direction_pin_1, LOW);
  digitalWrite(direction_pin_2, LOW);
  analogWrite(enable_PWM_1,0);
  analogWrite(enable_PWM_2,0);
  
  TCCR2B = TCCR2B & B11111000 | B00000001; //  PWM frequency of 31372 Hz on pin 3 (and 11)
  

}

void loop() {
  //start and stop of both pumps
  button_state = debounce(last_state, power_pump_button);
  if (last_state == LOW && button_state == HIGH) 
    {
    k = k + 1;
    Serial.println(k);
    flag_loop=1;
    } 
  last_state = button_state;

  //increase Duty cicle
  up_button_state = debounce(up_last_state, up_pump_button);
  if (up_last_state == LOW && up_button_state == HIGH) 
    {
    duty_bin1=duty_bin1+1;
    if (duty_bin1>PWM_MAX){
      duty_bin1=PWM_MAX;}
    duty_bin2=duty_bin1-DIFF_PWM;

    flag_loop=1;
    } 
  up_last_state = up_button_state;

  //decrease dc
  down_button_state = debounce(down_last_state, down_pump_button);
  if (down_last_state == LOW && down_button_state == HIGH) 
    {
    duty_bin1=duty_bin1-1;
    if (duty_bin1<PWM_MIN){
      duty_bin1=PWM_MIN;}
    duty_bin2=duty_bin1-DIFF_PWM;

    flag_loop=1;
    } 
  down_last_state = down_button_state;


  if (flag_loop==1)
    {
    switch (k) {
      case 1: {
        
        digitalWrite(direction_pin_2, HIGH);
        analogWrite(enable_PWM_2,duty_bin2);
        digitalWrite(direction_pin_1, HIGH);
        analogWrite(enable_PWM_1,duty_bin1);
        
        Serial.print("valore PWM impostato a ");   //codice per valutare funzionamento con PC, non serve sennò stampare su  seriale     control code when using a PC
        Serial.println(duty_bin1);
        Serial.println(k);
        flag_loop=0;

        }
      break; 
      case 2:{

        analogWrite(enable_PWM_1,0);
        digitalWrite(direction_pin_1, LOW);
        analogWrite(enable_PWM_2,0);
        digitalWrite(direction_pin_2, LOW);

        Serial.println(k);
        Serial.println("spento PWM");
        k = 0;
        Serial.println(k);
        flag_loop=0;
        } 
      break;      
      }
    }
}  


//debounce funtion
bool debounce(boolean last, int pin)
{
  bool current = digitalRead(pin);
  if (last != current)
    {
    delay(5);
    current = digitalRead(pin);
    }
  return current;
}


