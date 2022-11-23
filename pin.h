

int enable_PWM_1 = 11; //pompa ingresso    input pump
int direction_pin_1 = 12;

int enable_PWM_2 = 3; //pompa uscita       output pump
int direction_pin_2 = 4;

int power_pump_button = 13; //pin pulsante on e off
int up_pump_button = 7;
int down_pump_button = 8;



bool last_state = LOW;
bool button_state = LOW;

bool up_last_state = LOW;
bool up_button_state = LOW;

bool down_last_state = LOW;
bool down_button_state = LOW;
