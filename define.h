
int const PWM_MAX = 256;  //100% duty cicle PWM
int const PWM_MIN = 170;  //PWM duty cicle min per far andare i motore
int const DIFF_PWM = 2;   //diff tra i due motori, al momento è bassa perchè a livello HW un motore va meno dell'altro a parità di programmazione         diff btw pumps, duty cicle output > dc input to prevent overflow
