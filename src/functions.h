#include <Arduino.h>

void wait_for_button(int pin) 
{
    while (digitalRead(pin) == HIGH) 
    {
        if (Serial2.available()) 
        {
            Serial2.read();
            break;
        }
    }
}

void zacatek_kalibrace()
{
    Serial.println("Zacatek kalibrace "); 
    Serial2.println("Zacatek kalibrace ");
    long battery = 0; // napětí na děliči z AD převodníku 
    long napeti = 0; // napětí na baterce 
    battery = analogRead(batt);
    napeti = battery *13470 / 340;
    Serial.print("Napeti na baterii je: ");
    Serial.print(napeti);
    Serial.println(" mV");
    Serial2.print("Napeti na baterii je: ");
    Serial2.print(napeti);
    Serial2.println(" mV");
}

void kalibrace_wb()
{
    wait_for_button(t1); // čeká na stisk tlačítka - po stisku nacita bile hodnoty 
    Serial2.print("Bile hodnoty: ");
    Serial.print("Bile hodnoty: ");
  
    wb1_bila = analogRead(wb1);  
    Serial2.print(wb1_bila);  
    Serial2.print(" ");
    Serial.print(wb1_bila);  
    Serial.print(" ");
  
    wb2_bila = analogRead(wb2);  
    Serial2.print(wb2_bila);  
    Serial2.print(" ");
    Serial.print(wb2_bila);  
    Serial.print(" ");
  
    wb3_bila = analogRead(wb3);  
    Serial2.print(wb3_bila);  
    Serial2.print(" ");
    Serial.print(wb3_bila);  
    Serial.print(" ");

    wb4_bila = analogRead(wb4);  
    Serial2.print(wb4_bila);  
    Serial2.print(" ");
    Serial.print(wb4_bila);  
    Serial.print(" ");
  
    wb5_bila = analogRead(wb5);  
    Serial2.print(wb5_bila);  
    Serial2.print(" ");
    Serial.print(wb5_bila);  
    Serial.print(" ");
  
    wb6_bila = analogRead(wb6);  
    Serial2.print(wb6_bila);  
    Serial2.print(" ");
    Serial.print(wb6_bila);  
    Serial.print(" ");
  
    wb7_bila = analogRead(wb7);  
    Serial2.println(wb7_bila); 
    Serial.println(wb7_bila); 

    delay(100); // pocka na pusteni tlacitka 0.1 sec

    digitalWrite(d_or,LOW); 
    delay(200); 
    digitalWrite(d_or,HIGH); // probliknuti LED potvrdi nacteni hodnot 
  
    wait_for_button(t1); // čeká na stisk tlačítka - po stisku nacita cerne 1, 2, 3 
  
    Serial2.print("Cerne hodnoty: ");
    Serial.print("Cerne hodnoty: ");
    wb1_cerna = analogRead(wb1);  
    Serial2.print(wb1_cerna);  
    Serial2.print(" ");
    Serial.print(wb1_cerna);  
    Serial.print(" ");
 
    wb2_cerna = analogRead(wb2);  
    Serial2.print(wb2_cerna);  
    Serial2.print(" ");
    Serial.print(wb2_cerna);  
    Serial.print(" ");
  
    wb3_cerna = analogRead(wb3);  
    Serial2.print(wb3_cerna);  
    Serial2.print(" ");
    Serial.print(wb3_cerna);  
    Serial.print(" ");

    delay(100); // pocka na pusteni tlacitka 0.1 sec

    digitalWrite(d_or,LOW); 
    delay(200); 
    digitalWrite(d_or,HIGH); // probliknuti LED potvrdi nacteni hodnot 
    wait_for_button(t1); // čeká na stisk tlačítka - po stisku nacita cerne 4, 5, 6,7
  
    wb4_cerna = analogRead(wb4);  
    Serial2.print(wb4_cerna);  
    Serial2.print(" ");
    Serial.print(wb4_cerna);  
    Serial.print(" ");
  
    wb5_cerna = analogRead(wb5);  
    Serial2.print(wb5_cerna);  
    Serial2.print(" ");
    Serial.print(wb5_cerna);  
    Serial.print(" ");
  
    wb6_cerna = analogRead(wb6);  
    Serial2.print(wb6_cerna);  
    Serial2.print(" ");
    Serial.print(wb6_cerna);  
    Serial.print(" ");
  
    wb7_cerna = analogRead(wb7);  
    Serial2.println(wb7_cerna);
    Serial.println(wb7_cerna);
    delay(100); // pocka na pusteni tlacitka 0.1 sec
  
    digitalWrite(d_or,LOW); 
    delay(200); 
    digitalWrite(d_or,HIGH); // probliknuti LED potvrdi nacteni hodnot 
  
    Serial2.print("Prumer hodnot: ");
    Serial.print("Prumer hodnot: ");
    wb1_prumer = ((wb1_cerna + wb1_bila) / 2);  
    Serial2.print(wb1_prumer);  
    Serial2.print(" ");
    Serial.print(wb1_prumer);  
    Serial.print(" ");
  
    wb2_prumer = ((wb2_cerna + wb2_bila) / 2);  
    Serial2.print(wb2_prumer);  
    Serial2.print(" ");
    Serial.print(wb2_prumer);  
    Serial.print(" ");
  
    wb3_prumer = ((wb3_cerna + wb3_bila) / 2);  
    Serial2.print(wb3_prumer);  
    Serial2.print(" ");
    Serial.print(wb3_prumer);  
    Serial.print(" ");
  
    wb4_prumer = ((wb4_cerna + wb4_bila) / 2);  
    Serial2.print(wb4_prumer);  
    Serial2.print(" ");
    Serial.print(wb4_prumer);  
    Serial.print(" ");
  
    wb5_prumer = ((wb5_cerna + wb5_bila) / 2);  
    Serial2.print(wb5_prumer);  
    Serial2.print(" ");
    Serial.print(wb5_prumer);  
    Serial.print(" ");
  
    wb6_prumer = ((wb6_cerna + wb6_bila) / 2);  
    Serial2.print(wb6_prumer);  
    Serial2.print(" ");
    Serial.print(wb6_prumer);  
    Serial.print(" ");

    wb7_prumer = ((wb7_cerna + wb7_bila) / 2);  
    Serial2.print(wb7_prumer);  
    Serial2.println(" ");
    Serial.print(wb7_prumer);  
    Serial.println(" ");

}


void data_z_druhe_megy()
{
    long enc_l1 = 0;
    long enc_l2 = 0;
    long enc_l3 = 0;
    
    long enc_r1 = 0;
    long enc_r2 = 0;
    long enc_r3 = 0;

    Serial.print("Data: ");
    Serial2.print("Data: ");

    while( Serial3.available() ) // vyčistí datovou frontu 
    {
        Serial3.read();
    }
    int x = 0;
    Serial3.write(0x01); // posílám 1 abych mel na druhem mega preruseni, ktere posle data 
    while(x < 13)
    {
        long a = 0;
        if( Serial3.available() )
        { 
            a = Serial3.read();
            if(( a != 128) and (x==0) ) 
                x = -1; // snizim x o 1 
            Serial.print(a, DEC);
            Serial2.print(a, DEC);
            Serial.print(" ");
            Serial2.print(" ");
            if(x== 1)
            {
                us_1 = a;
            }
            if(x== 2)
            {
                us_2 = a;
            }
            if(x== 3)
            {
                us_3 = a;
            }    
            if(x== 4)
            {
                us_4 = a;
            }    
            if(x== 5)
            {
                enc_l1 = a*16777216;
            }
            if(x== 6)
            {
                enc_l2 = a*65536; 
            }        
            if(x== 7)
            {
                enc_l3 = a*256; 
            }        
            if(x== 8)
            {
                docasny_l = enc_l1 + enc_l2 + enc_l3 + a;
                if ( ( (docasny_l - enc_l) < 500) && ( (enc_l - docasny_l) < 500) )
                {
                    enc_l = docasny_l;
                }
                Serial.print(enc_l, DEC);
                Serial.print(" ");
                Serial2.print(enc_l, DEC);
                Serial2.print(" ");    
            }        
            if(x== 9)
            {
                enc_r1 = a*16777216;
            }
            if(x== 10)
            {
                enc_r2 = a*65536;
            }        
            if(x== 11)
            {
                enc_r3 = a*256;
            }        
            if(x== 12)
            {
                docasny_r = enc_r1 + enc_r2 + enc_r3 + a;
                if ( ( (docasny_r - enc_r) < 500) && ( (enc_r - docasny_r) < 500) ) 
                {
                    enc_r = docasny_r;
                }
                Serial.print(enc_r, DEC);
                Serial.print(" ");
                Serial2.print(enc_r, DEC);
                Serial2.print(" ");    
            }           
         ++x;     
        } 
       
    }    
    Serial2.println(" ");
    Serial.print(" us_1  ");    
    Serial.print(us_1 );
    Serial.print(" us_2  ");
    Serial.print(us_2);
    Serial.print(" us_3  ");
    Serial.print(us_3);
    Serial.print(" us_4  "); 
    Serial.print(us_4);
    Serial.print(" enc_l  ");
    Serial.print(enc_l);
    Serial.print(" enc_r  ");
    Serial.print(enc_r); 
    Serial.print(" ");  
    Serial.print(docasny_r, DEC);
    Serial.println("  ");
}

void dance()
{
    wait_for_button(t1); // čeká na stisk tlačítka - zahajeni tanecku
    delay(100); // pocka na pusteni tlacitka 0.1 sec

    // pojezd obou motoru dopredu a zpet 


    motorGo(MOTOR_2, CW, 80);
    while( enc_r < 900) // 454 na jednu otáčku kola 
    {
        data_z_druhe_megy();
    }    
    tvrdy_Stop(11);
    delay( 1000 );

    motorGo(MOTOR_1, CW, 80);
    while( enc_l < 900) // 454 na jednu otáčku kola 
    {
        data_z_druhe_megy();
    }    
    tvrdy_Stop(12);

    myservo.attach(46);   //servo je připojeno na pin 46
    myservo.write(90);   //natočení serva - otevření
    delay(1000);          //čekání než se servo natočí  
    myservo.write(0);     //natočení serva - zavření


    Stop(13);               // nastavení motorů do klidového stavu   
    Serial2.print("pripraven ke startu: ");
    Serial.print("pripraven ke startu: ");

    digitalWrite(d_or,LOW); // zapne diodu - indikace připravenosti ke startu 
    wait_for_button(t1); // čeká na start
    
}

void blikani()
{
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


}

void souradnice()
{
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
        for(uint8_t i=0; i<4; i++) Serial.println();
    }
     if( analogRead(wb6) < wb6_prumer )
    {
        souradnicovy_driver = 1;   
    }
}

