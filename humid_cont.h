#define HUMIDITY_SWITCH 5 
#define HUMIDITY_SWITCH_LOOP 20


bool humidControl(bool hum_state) {
  //humidifier in ON mode, do 2 iteration: ->PULSE->OFF
  //humidifier in OFF mode, do 1 iteration: ->ON

   int i = 1; //the amount of iterations
   if (hum_state){  
     i = 2;
   }
   while (i != 0){
    digitalWrite(HUMIDITY_SWITCH,HIGH);
    delay(1000);
    digitalWrite(HUMIDITY_SWITCH,LOW);
    delay(1000);
    i--;
   }
   return !hum_state;

}