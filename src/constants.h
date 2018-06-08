const int  wb4 = A9; //hneda toto jsou barvy drátů k šesti senzorům 
const int  wb2 = A12;//modra
const int  wb3 = A10;//bila
const int  wb1 = A11;//zelena
const int  wb5 = A14;//cerna
const int  wb6 = A13;//zluta
const int  wb7 = A15;//žlutošedý pruhovaný
const int  batt = A8; // napěťový dělič na baterce 
const int d_or = 40;// dioda oranžová 
const int   t1 = 44; // tlačítko 1 


//int battery = 0; // napětí na děliči z AD převodníku 
//int napeti = 0; // napětí na baterce 
int wb1_bila, wb2_bila, wb3_bila, wb4_bila, wb5_bila, wb6_bila, wb7_bila;
int wb1_cerna, wb2_cerna, wb3_cerna, wb4_cerna, wb5_cerna, wb6_cerna, wb7_cerna;
int wb1_prumer, wb2_prumer, wb3_prumer, wb4_prumer, wb5_prumer, wb6_prumer,wb7_prumer; 
// X,Y - souradnice pruseciku ctverce , NZ - nekdo zavazi 
int Y = 0;
int X = 3;
int NZ = 2; // Nekdo Zavazi

//ultrazvuk
const int pTrig_bok = A7;
const int pEcho_bok = A6;
const int pTrig_vlevo = 32;
const int pEcho_vlevo = 52;
const int pTrig_stred = 48;
const int pEcho_stred = 49;
const int pTrig_vpravo = 14;
const int pEcho_vpravo = 15;

int us_1;
int us_2;
int us_3;
int us_4;

bool povoleni_pro_US = 0;
int specialni_povoleni_pro_US = 1;

// servo
int pos = 0;
Servo myservo; 
// myservo.attach(46); tohle je az u tanecku, aby se servo nezacalo tocit predcasne

bool lastState = false;  
int rychlost = 60;
int rychlost_2 = 70;
long zac;
// motora
int rychlost_m1 = 80;
int rychlost_m2 = 80;

    // enkodery
    long enc_r = 0;    // 454 pulzu na otacku kola 
    long enc_l = 0;    // 454 pulzu na otacku kola 

    long l_enc;
    long r_enc;

    int enc_final_l;
    int enc_final_r;

    long docasny_l = 0;
    long docasny_r = 0;

    int right_encoder;
    int left_encoder;

    long R_encoder_l; // realna poyice leveho encoder
    long R_encoder_r; // realna poyice praveho encoder
    long V_encoder_l; // virtualni poyice leveho encoder
    long V_encoder_r; // virtualni poyice praveho encoder

    bool nastaveni_enc = 1;
    bool nastaveni_enc_l = 1;
    bool nastaveni_enc_r = 1;

    int encoder_1;
    int encoder_2;

    int V1;
    int V2;


// pomocne promene: 1 - povoleno, 0 - zakazano
bool souradnicovy_driver = 1;
int na_souradnici = 1;
bool povoleni_k_jizde = 1; // budou blokovat ultrazvuky 
bool driver_zataceni = 1;

int minula_predni_wb;
int minula_zadni_wb;
int docasna_minula_predni_wb;
int docasna_minula_zadni_wb;