// zeleny 1.68 k modry 10 k 
// souradnice 0,0 je levy dolni roh 

#include <Arduino.h>
#include <Servo.h>     //zahrnutí knihovny pro ovládání servo motoru 
#include "constants.h"
#include "vnh2sp30.h"
#include "functions.h" 

bool value_old_l = digitalRead(enc_l);
bool value_old_r = digitalRead(enc_r);

    int pocet_cyklu = 0;
    long zacatek = 0;

void setup() 
{
    #include "ini.txt" 
    zacatek_kalibrace();
    kalibrace_wb();
    data_z_druhe_megy();
    //dance();
    zac = millis();
    wait_for_button(t1); // čeká na stisk tlačítka
    delay(500);  // na oddělání ruky
    //srovnat_s_carou();
    Forward(80);
    zacatek = millis();
}

void loop() 
{    
    data_z_druhe_megy();

    jizda_rovne(rychlost );

    if( (millis() - zac) > 500) // blikani prubezne
    {
        zac = millis();
        if (lastState == true)  
        {
            lastState = false;
        }
        else 
        {
            lastState = true;
            digitalWrite(d_or, lastState);
        }
    }    

    if( ( analogRead(wb6) > wb6_prumer ) && ( souradnicovy_driver == 1 ) )
    {
        if( na_souradnici == 1 ) // na kladném smeru osy X
        {
            ++X;
            Serial.print(" X ");
            Serial.print(X);
            Serial.print(" Y ");
            Serial.println(Y);
            souradnicovy_driver = 0;
        }
        if( na_souradnici == 2 ) // na kladnám smeru osy Y
        {
            ++Y;
            Serial.print(" X ");
            Serial.print(X);
            Serial.print(" Y ");
            Serial.println(Y);
            souradnicovy_driver = 0;
        }
        if( na_souradnici == 3 ) // na záporném smeru osy X
        {
            --X;
            Serial.print(" X ");
            Serial.print(X);
            Serial.print(" Y ");
            Serial.println(Y);
            souradnicovy_driver = 0;
        }   
        if( na_souradnici == 4 ) // na záporném smeru osy X
        {
            --Y;
            Serial.print(" X ");
            Serial.print(X);
            Serial.print(" Y ");
            Serial.println(Y);
            souradnicovy_driver = 0;
        }
    }
    if( analogRead(wb6) < wb6_prumer )
    {
        souradnicovy_driver = 1;   
    }
            
    if( ( ( ( 1 <= X ) && ( X < 5 ) ) && ( Y == 0 ) ) && ( povoleni_k_jizde = 1 ) )
    {  // jizda vpred po spodni rade 
        jizda_po_care();
    }
    if( ( ( ( 1 <= Y ) && ( Y < NZ ) ) && ( X == 6 ) ) && ( povoleni_k_jizde = 1 ) )
    {     // jizda nahoru po pravem okraji 
        jizda_po_care();
    }
    if( ( ( ( 1 < X ) && ( X <= 5 ) ) && ( Y == (NZ + 1) ) ) && ( povoleni_k_jizde = 1 ) )
    {
        jizda_po_care();
    }
    if( ( ( ( 1 < Y ) && ( Y <= NZ ) ) && ( X == 0 ) ) && ( povoleni_k_jizde = 1 ) )
    {
        jizda_po_care();
    }
    if( (( X == 5 ) && ( Y == 0 )) || (( X == 0 ) && ( Y == 1 )) || (( X == 6 ) && ( Y == NZ )) || (( X == 1 ) && ( Y == (NZ + 1) )) )
    {   // zataci  
        Serial.print( "right_encoder " );
        Serial.println( right_encoder );
        myservo.write(0);
        souradnicovy_driver = 0;  // behem zataceni nechceme menit X
        if( driver_zataceni == 1 )
        {
            tvrdy_Stop(1);
            right_encoder = enc_r;
            driver_zataceni = 0;
        }
        if(analogRead(wb6) > wb6_prumer)
        {
            Stop(2);
        }
        if( ( enc_r - right_encoder) < 900 ) // 454 na jednu otáčku kola 
        {
            motorGo(MOTOR_2, CW, 80);
        }
        if( ( enc_r - right_encoder) >= 900)
        {
            Stop(3);
            srovnat_s_carou();
            nastaveni_enc = 1;
            driver_zataceni = 1;
            if(( X == 5 ) && ( Y == 0 ))
            {
                ++X;
                ++Y;
                na_souradnici = 2;
                Serial.print(" X ");
                Serial.print(X);
                Serial.print(" Y ");
                Serial.println(Y);
            }
            if(( X == 0 ) && ( Y == 1 ))
            {
                ++X;
                --Y;
                na_souradnici = 1;
                Serial.print(" X ");
                Serial.print(X);
                Serial.print(" Y ");
                Serial.println(Y);
            }
            if(( X == 6 ) && ( Y == NZ ))
            {
                --X;
                ++Y;
                na_souradnici = 3;
                Serial.print(" X ");
                Serial.print(X);
                Serial.print(" Y ");
                Serial.println(Y);
            }
            if(( X == 1 ) && ( Y == (NZ + 1) ))
            {
                --X;
                --Y;
                na_souradnici = 4;
                Serial.print(" x ");
                Serial.print(X);
                Serial.print(" Y ");
                Serial.println(Y);
            }
        } 
        
    }
    if( povoleni_k_jizde == 0 )
    {
        motorGo(MOTOR_1, 0, 60 );
        motorGo(MOTOR_2, 0, 60 );
    }

    ++ pocet_cyklu;
    Serial.println("****************************");
    Serial2.println("****************************");
   /* Serial.print("pocet ");
    Serial2.print("pocet ");
    Serial.print(pocet_cyklu);
    Serial2.print(pocet_cyklu);
    Serial.print(" ms ");
    Serial2.print(" ms ");
    Serial.print( (millis()-zacatek) );
    Serial2.print( (millis() - zacatek) );
    Serial.println( );
    Serial2.println( );*/
}