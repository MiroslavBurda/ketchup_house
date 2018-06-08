#include <Arduino.h>

#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1 - levy
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2 - pravy
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

const uint8_t MIN = 30; // minimální proud do motoru
const uint8_t add = 10; // krok pro přidávání rychlosti
const float corr = 50; // přidání levému motoru v procentech

short usSpeed = 40;  //default motor speed
uint8_t speed_left = MIN; 
uint8_t speed_right = MIN; 

unsigned short usMotor_Status = BRAKE;

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
    if(motor == MOTOR_1)
    {
        if(direct == CW)
        {
            digitalWrite(MOTOR_A1_PIN, LOW); 
            digitalWrite(MOTOR_B1_PIN, HIGH);
        }
        else if(direct == CCW)
        {
            digitalWrite(MOTOR_A1_PIN, HIGH);
            digitalWrite(MOTOR_B1_PIN, LOW);      
        }
        else
        {
            digitalWrite(MOTOR_A1_PIN, LOW);
            digitalWrite(MOTOR_B1_PIN, LOW);            
        }
        analogWrite(PWM_MOTOR_1, pwm); 
        speed_left = pwm; 
        Serial2.print("MGL: "); 
        Serial2.print(pwm);
        Serial2.println(" ");
        Serial.print("MGL: ");
        Serial.print(pwm);
        Serial.println(" ");
    }
    else if(motor == MOTOR_2)
    {
        if(direct == CW)
        {
            digitalWrite(MOTOR_A2_PIN, LOW);
            digitalWrite(MOTOR_B2_PIN, HIGH);
        }
        else if(direct == CCW)
        {
            digitalWrite(MOTOR_A2_PIN, HIGH);
            digitalWrite(MOTOR_B2_PIN, LOW);      
        }
        else
        {
            digitalWrite(MOTOR_A2_PIN, LOW);
            digitalWrite(MOTOR_B2_PIN, LOW);            
        }
           analogWrite(PWM_MOTOR_2, pwm);
        speed_right = pwm; 
        Serial2.print("MGR: "); 
        Serial2.print(pwm);
        Serial2.println(" ");
        Serial.print("MGR: "); 
        Serial.print(pwm);
        Serial.println(" ");
    }
}

void tvrdy_Stop( uint8_t num)
{
    motorGo(MOTOR_1, BRAKE, 255);
    motorGo(MOTOR_2, BRAKE, 255);
    Serial.print("Stop ");
    Serial2.print("Stop ");
    Serial.println(num);
    Serial2.println(num);

}
void Stop( uint8_t num)
{
    motorGo(MOTOR_1, BRAKE, 150);
    motorGo(MOTOR_2, BRAKE, 150);
    Serial.print("Stop ");
    Serial2.print("Stop ");
    Serial.println(num);
    Serial2.println(num);
}
void meky_Stop( uint8_t num)
{
    motorGo(MOTOR_1, BRAKE, 50);
    motorGo(MOTOR_2, BRAKE, 50);
    Serial.print("Stop ");
    Serial2.print("Stop ");
    Serial.println(num);
    Serial2.println(num);
}

void Forward(uint8_t Speed)
{
    uint8_t muj_speed = MIN;  
    while (muj_speed < Speed)
    {
        if ( (muj_speed + add) < Speed )
        { 
            muj_speed = muj_speed + add;
        }      
        else
        { 
            muj_speed = Speed;
        }  
        Serial2.print("Forward: "); 
        Serial2.println(muj_speed); 
        motorGo(MOTOR_1, CW, muj_speed);
        motorGo(MOTOR_2, CW, muj_speed);
        delay(10); 
    }
   /* int muj_speed2 = muj_speed*(1 + corr/100);
    Serial.print("Speed muj levy: " );  // ?????????? jak to že to funguje? 
    Serial.println(muj_speed2); 
    if(muj_speed2 > 255) 
    {
        muj_speed2 = 255;   
    }*/
    motorGo(MOTOR_1, CW, muj_speed ); // asi to potřebuje nastavit ještě jednou ??? 
    Serial2.print("Speed L: " );
    Serial2.print(speed_left);
    Serial2.print(" Speed R: " );
    Serial2.println(speed_right);
}

void IncreaseSpeed(uint8_t upg_speed_l, uint8_t upg_speed_r) // levý motor zapisuju první
{
    int muj_speed_l = speed_left; 
    int Speed_l = speed_left + upg_speed_l; 
    if(Speed_l > 255) 
    {
        Speed_l = 255;   
    }
    while (muj_speed_l < Speed_l)
    {
        if ( (muj_speed_l + add) < Speed_l) 
        {
            muj_speed_l = muj_speed_l + add;
        }                
        else 
        {
            muj_speed_l = Speed_l;
        }
        Serial2.print("forward_left: "); 
        Serial2.println(muj_speed_l); 
        motorGo(MOTOR_1, CW, muj_speed_l);
        delay(10); 
    }
    speed_left = muj_speed_l;
    Serial2.print("Speed L: ");
    Serial2.print(speed_left);
  
    int muj_speed_r = speed_right; 
    int Speed_r = speed_right + upg_speed_r; 
    if(Speed_r > 255) 
    {
        Speed_r = 255;  
    }
    while (muj_speed_r < Speed_r)
    {
        if (Speed_r > muj_speed_r + add) 
        {
            muj_speed_r = muj_speed_r + add;  
        }
        else 
        {
            muj_speed_r = Speed_r;
        }
        Serial2.print("forward_right: "); 
        Serial2.println(muj_speed_r); 
        usMotor_Status = CW;
        motorGo(MOTOR_2, 1, muj_speed_r);
        delay(10); 
    }
    speed_right = muj_speed_r;
    Serial2.print(" Speed R: " );
    Serial2.println(speed_right);
}

void last_position() // kde byla naposledy viděna černá?
{
    if (analogRead(wb1) > wb1_prumer)
    {
        minula_predni_wb = 1;
    }
    if (analogRead(wb3) > wb3_prumer)
    {
        minula_predni_wb = 3;
    }
    if (analogRead(wb2) > wb2_prumer)
    {
        minula_predni_wb = 2;
    }

    if (analogRead(wb4) > wb4_prumer)
    {
        minula_zadni_wb = 4;
    }
    if (analogRead(wb7) > wb7_prumer)
    {
        minula_zadni_wb = 7;
    }
    if (analogRead(wb5) > wb5_prumer)
    {
        minula_zadni_wb = 5;
    }
}

void jizda_rovne(uint8_t V ) // rychlost se udává v cm/s
{ 
    int plynulost;    

    if( nastaveni_enc == 1 )
    {
        l_enc = enc_l;
        r_enc = enc_r;
        nastaveni_enc = 0;
    }
    enc_final_l = enc_l - l_enc;
    enc_final_r = enc_r - r_enc;

    plynulost = ((enc_final_l - enc_final_r)*1.3);
    V1 = (V - plynulost );
    V2 = (V + plynulost );
    
    if( V1 > 255)
    {
        V1 = 255;
    }
    if( V2 > 255)
    {
        V2 = 255;
    }
    
    if( V1 >= 0 )
    {
        motorGo(MOTOR_1, 1, V1 );
    }
    if( V1 < 0 )
    {
        V1 = -V1;
        motorGo(MOTOR_1, 0, V1 );
    }
    if( V2 >= 0 )
    {
        motorGo(MOTOR_2, 1, V2 ); 
    }
    if( V2 < 0 )
    {
        V2 = -V2;
        motorGo(MOTOR_2, 0, V2 ); 
    }
    Serial.print("enc_final_r ");
    Serial.print(enc_final_r );
    Serial.print("enc_final_l ");
    Serial.print(enc_final_l );
    Serial.print("enc_l ");
    Serial.print(enc_l );
    Serial.print("enc_r ");
    Serial.print(enc_r );
    Serial.print("V1  ");
    Serial.print(V1);
    Serial.print("V2  "); 
    Serial.print(V2);
    Serial.print(" plynulost  "); 
    Serial.println(plynulost);
}
void jizda_lehce_leva(uint8_t V, float pomer_l ) // rychlost se udává v cm/s
{ 
    int plynulost;    

    if( nastaveni_enc == 1 )
    {
        l_enc = enc_l;
        r_enc = enc_r;
        nastaveni_enc = 0;
    }
    enc_final_l = enc_l - l_enc;
    enc_final_r = ((enc_r - r_enc)/pomer_l);

    plynulost = ((enc_final_l - enc_final_r)*1.5);
    V1 = (V - plynulost );
    V2 = (V + plynulost );
    
    if( V1 > 255)
    {
        V1 = 255;
    }
    if( V2 > 255)
    {
        V2 = 255;
    }
    
    if( V1 >= 0 )
    {
        motorGo(MOTOR_1, 1, V1 );
    }
    if( V1 < 0 )
    {
        V1 = -V1;
        motorGo(MOTOR_1, 0, V1 );
    }
    if( V2 >= 0 )
    {
        motorGo(MOTOR_2, 1, V2 ); 
    }
    if( V2 < 0 )
    {
        V2 = -V2;
        motorGo(MOTOR_2, 0, V2 ); 
    }
    
}
void jizda_lehce_prava(uint8_t V, float pomer_r ) // rychlost se udává v cm/s , cim vetsi pomer_r, tim ostrejsi zatacka
{
    int plynulost;    

    if( nastaveni_enc == 1 )
    {
        l_enc = enc_l;
        r_enc = enc_r;
        nastaveni_enc = 0;
    }
    enc_final_l = ((enc_l - l_enc)/pomer_r);
    enc_final_r = enc_r - r_enc;

    plynulost = ((enc_final_l - enc_final_r)*1.5);
    V1 = (V - plynulost );
    V2 = (V + plynulost );
    
    if( V1 > 255)
    {
        V1 = 255;
    }
    if( V2 > 255)
    {
        V2 = 255;
    }
    
    if( V1 >= 0 )
    {
        motorGo(MOTOR_1, 1, V1 );
    }
    if( V1 < 0 )
    {
        V1 = -V1;
        motorGo(MOTOR_1, 0, V1 );
    }
    if( V2 >= 0 )
    {
        motorGo(MOTOR_2, 1, V2 ); 
    }
    if( V2 < 0 )
    {
        V2 = -V2;
        motorGo(MOTOR_2, 0, V2 ); 
    }
}

void jizda_po_care() 
{
    bool hc;
    if( minula_predni_wb == 2 )
        {
            jizda_rovne(rychlost );
        }
    
    if( ( analogRead(wb1) > wb1_prumer ) && ( analogRead(wb2) < wb2_prumer ) )
    {    
        if( minula_predni_wb != 1 ) // prave vyhnul na senzor 1
        {
            nastaveni_enc = 1;
            hc = 1;
        }        
        jizda_lehce_leva(rychlost, 2.5);
    }
    if( analogRead(wb2) > wb2_prumer )
    {
        if( analogRead(wb4) > wb4_prumer )
        {          
            nastaveni_enc = 1;
            if( minula_zadni_wb != 4 )
            {
                nastaveni_enc = 1;
                hc = 1;
            }
            jizda_lehce_prava(rychlost, 2 );
        } 
        if( analogRead(wb5) > wb5_prumer ) 
        {    // jizda rovne 
            if( minula_zadni_wb != 5 )
            {
                nastaveni_enc = 1;
                hc = 1;
            }
            jizda_rovne(rychlost );
        }
        if( analogRead(wb7) > wb7_prumer )
        {
            if( minula_zadni_wb != 7 )
            {
                nastaveni_enc = 1;
                hc = 1;
            }
            jizda_lehce_leva(rychlost, 2 );
        } 
    }
    if(( analogRead(wb3) > wb3_prumer) && ( analogRead(wb2) < wb2_prumer ) )
    {
        if( minula_predni_wb != 3 )
        {
            nastaveni_enc = 1;
            hc = 1;
        }
        jizda_lehce_prava(rychlost, 2.5 );
    }
    if( ( analogRead(wb1) < wb1_prumer ) && ( analogRead(wb2) < wb2_prumer ) && ( analogRead(wb3) < wb3_prumer ) )
    {  // hledame ztracenou caru - zadny predni senzor nevidi caru 
        if( minula_predni_wb == 1 )
        {
            jizda_lehce_leva(rychlost, 4 );
            if( hc == 1 )
            {
                nastaveni_enc = 1;  
                hc = 0;
            }
        }
        if( minula_predni_wb == 3 )
        {
            jizda_lehce_prava(rychlost, 4 );
            if( hc == 1 )
            {
                nastaveni_enc = 1;  
                hc = 0;
            }
        }
    }
            
    if( ( ( ( analogRead(wb4) < wb4_prumer ) && ( analogRead(wb5) < wb5_prumer ) ) && ( analogRead(wb7) < wb7_prumer ) )
      && ( ( ( analogRead(wb1) > wb1_prumer ) || ( analogRead(wb2) > wb2_prumer ) ) || ( analogRead(wb3) > wb3_prumer ) ) )
    {   // pokud zadní senzory nevidí černou, ale alespon jeden přední ano
        if( minula_predni_wb == 1 )
        {
            jizda_lehce_leva(rychlost, 2.5 );
            if( hc == 1 )
            {
                nastaveni_enc = 1;  
                hc = 0;
            }
           
        }
        if( minula_predni_wb == 3 )
        {
            jizda_lehce_prava(rychlost, 2.5 );
            if( hc == 1 )
            {
                nastaveni_enc = 1;
                hc = 0;
            }
        }
    }
    last_position();
}

void srovnat_s_carou()
{
    last_position();
    while( (analogRead(wb2) < wb2_prumer) && ( analogRead(wb5) < wb5_prumer ) )
    {
        last_position();
        if (minula_predni_wb == 2)
        {
            if( minula_zadni_wb == 4 )
            {
                while( analogRead(wb3) < wb3_prumer )
                {
                    motorGo(MOTOR_2, 1, rychlost_2);
                }
                meky_Stop(21);
                    delay(5);
                while (analogRead(wb5) < wb5_prumer)
                {
                    motorGo(MOTOR_1, 1, rychlost_2);
                }
                meky_Stop(22);
                delay(5);
            }
            if (minula_zadni_wb == 7)
            {
                last_position();
                while( (analogRead(wb1) < wb1_prumer) && (analogRead(wb1) < wb1_prumer) )
                {
                    motorGo(MOTOR_1, 2, rychlost_2);
                }
                meky_Stop(23);
                delay(5);
                while (analogRead(wb2) < wb2_prumer)
                {
                    motorGo(MOTOR_2, 2, rychlost_2);
                }
                meky_Stop(24);
                delay(5);
            }
        }
        last_position();
        if (minula_zadni_wb == 5)
        {
            if (minula_predni_wb == 1)
            {
                last_position();
                while (analogRead(wb7) < wb7_prumer)
                {
                    motorGo(MOTOR_2, 2, rychlost_2);
                }
                meky_Stop(25);
                delay(5);
                while (analogRead(wb2) < wb2_prumer)
                {
                    motorGo(MOTOR_1, 2, rychlost_2);
                }
                meky_Stop(26);
                delay(5);
            }
            if (minula_predni_wb == 3)
            {
                last_position();
                while ((analogRead(wb2) < wb2_prumer) && (analogRead(wb7) < wb7_prumer))
                {
                    motorGo(MOTOR_2, 2, rychlost_2);
                }
                meky_Stop(27);
                delay(5);
                while (analogRead(wb5) < wb5_prumer)
                {
                    motorGo(MOTOR_1, 2, rychlost_2);
                }
                meky_Stop(28);
                delay(5);
            }
        }
        if ( ( minula_zadni_wb == 1 ) && ( minula_zadni_wb == 4 ) )
        {
            if (minula_predni_wb == 1)
            {
                last_position();
                while (analogRead(wb2) < wb2_prumer)
                {
                    motorGo(MOTOR_2, 1, rychlost_2);
                }
                meky_Stop(29);
                delay(5);
            }
        }
        if ( ( minula_zadni_wb == 3 ) && ( minula_zadni_wb == 7 ) )
        {
            if (minula_predni_wb == 1)
            {
                last_position();
                while (analogRead(wb2) < wb2_prumer)
                {
                    motorGo(MOTOR_2, 2, rychlost_2);
                }
                meky_Stop(30);
                delay(5);
            }
        }
    }
}

void motorSetup()                        
{
    pinMode(MOTOR_A1_PIN, OUTPUT);
    pinMode(MOTOR_B1_PIN, OUTPUT);

    pinMode(MOTOR_A2_PIN, OUTPUT);
    pinMode(MOTOR_B2_PIN, OUTPUT);

    pinMode(PWM_MOTOR_1, OUTPUT);
    pinMode(PWM_MOTOR_2, OUTPUT);

    pinMode(CURRENT_SEN_1, OUTPUT);
    pinMode(CURRENT_SEN_2, OUTPUT);  

    pinMode(EN_PIN_1, INPUT_PULLUP);  // OPRAVA Z OUTPUT 
    pinMode(EN_PIN_2, INPUT_PULLUP);  // tento pin by si melo obsluhovat vnh a ja bych ho mel pravidelne cist a kontrolovat   
}