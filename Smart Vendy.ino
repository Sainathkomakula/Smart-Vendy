  
 /*

 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST           8             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)       9            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

#include <SPI.h>
#include <Keypad_I2C.h>
#include <MFRC522.h>

#include <EEPROM.h>
#include <Keypad.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7);
 
#define I2CADDR 0x38

int INA1 =4;
int INA2 =5;
int INA3 =6;
int INA4 =7;

int INB1 =20;
int INB2 =21; 
int INB3 =22;
int INB4 =23;

#define SS_PIN 9
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


String Array="40 50 62 7E"; // Authorized user
int Steps = 0; //Initializing Step count
int KitKat; // Quantity of Kitkat
int Oreo;// Quantity of Oreo
int add=0; // address used to storeBalace amount of user
boolean Direction = true;// 
unsigned long last_time; // Timing variable to allow stepper for rotation
unsigned long currentMillis ; //Timing variable to allow stepper for rotation

int steps_left;// variable to store number of steps to move stepper 
long time;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {   
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
}; // Digitran keypad, bit numbers of PCF8574 i/o port
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6}; //connect to the column pinouts of the keypad

Keypad_I2C kpd (makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);

//unsigned long loopCount = 0; 
//unsigned long timer_t = 0;
//int count_check=1;
byte nuidPICC[4]; // Storing byte of RFID card
int user_address=0;//address used to storeBalace amount of user

int slot_one_price=10; // Price of content in slot 1
int slot_two_price=15;// Price of content in slot 2
//int amount=0;
int Total_amount; // variable used to represent  Amoout of user 

// fuction  to set direction of stepper motor shaft movement( clockwise or anticlockwise)
void SetDirection(){
  if(Direction==1){ Steps++;} // clockwise
  if(Direction==0){ Steps--; }// anticlockwise
  if(Steps>7){Steps=0;} 
  if(Steps<0){Steps=7; }
}

void stepper(int xw,int IN1,int IN2,int IN3,int IN4){
  for (int x=0;x<xw;x++){
    SetDirection();
    switch(Steps){
       case 0:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       case 1:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, HIGH);
       break; 
       case 2:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 3:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 4:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 5:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
         case 6:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 7:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       default:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);       break; 

    }
  }  
} 
void customStepRev(int movestep, int slot_check){
   steps_left=(-1)*movestep;
   Direction==-1;
   while(steps_left<0){
      currentMillis = micros();
      if(currentMillis-last_time>=1000){
      
      if(slot_check==1)
      stepper(1, INA1, INA2, INA3,INA4); 
      else
        stepper(1, INB1, INB2, INB3,INB4); 
      time=time+micros()-last_time;
      last_time=micros();
      steps_left++;
      }
    }
   //Serial.println(time);
   delay(2000);
} 

void setup() 
{

   // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);

   lcd.home (); // set cursor to 0,0


   
  pinMode(INA1, OUTPUT); 
  pinMode(INA2, OUTPUT); 
  pinMode(INA3, OUTPUT); 
  pinMode(INA4, OUTPUT); 
 pinMode(INB1, OUTPUT); 
  pinMode(INB2, OUTPUT); 
  pinMode(INB3, OUTPUT); 
  pinMode(INB4, OUTPUT); 
  
 kpd.begin( );     
   kpd.setDebounceTime(10);  // setDebounceTime(mS)
   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  lcd.begin(16, 2);//Initiate LCD 16 X 2 
   lcd.print("Scan RFID Card");
 
  //lcd.print("Scan RFID Card");
  Serial1.begin(57600);// Baud rate used for Serial communication between MPU and MCU 
  Serial.begin(9600);// Baud rate used for Serial communication with PC to Arduino
 


Serial.println("Please Scan your RFID");
//lcd.print("Scan RFID Card");
 

}
void loop() 
{

  User_check(user_address);
char key = kpd.getKey(); // capturing key character from Keypad 
if (key=='*')
{
   Serial.println(key);
   
  //Balance_check(user_address);
   Topup(user_address); // Calling Topup function to recharge ot Topup RFID 
  
}
if (key=='#')
{
  Serial.println(key);
  Get_Snacks(user_address);// Calling Get_Snacks function to get snacks from selected slots
 
  
}
if(Serial1.available())
{
  Refill_slots();// Calling Refill_slots function to refill quantity from web UI 
}

  }
  void Refill_slots()
{
  
   String buffer=Serial1.readString(); // reading Quantity of Kitkat & Lays from MPU via serial communication 
 int sub_buffer=buffer.indexOf('&');// Identifying '&' to differentiate quantity of KitiKat  read serially 
  KitKat =buffer.substring(0,sub_buffer).toInt(); //Extracting value  before '&' i.e Quantity of KitKat
  //KitKat = Serial1.readString().toInt();
  Oreo =buffer.substring(sub_buffer+1).toInt();//Extracting value  after  '&' i.e Quantity of Oreo
 lcd.clear();
  lcd.home ();
  lcd.print("KitKat=");
   lcd.print(KitKat);
 Serial.print("Number of KitKat =");
  Serial.println(KitKat);
 /*/ delay(2000);
  Serial1.flush();
  Oreo = Serial1.readString().toInt();
  Serial1.flush();*/
    lcd.setCursor (0,1);
  Serial.print("Number of Oreo =");
 Serial.println(Oreo);
 lcd.print("Oreo=");
   lcd.print(Oreo);
}

  void User_check(int addr)
  {
    lcd.home ();

 
  // int amount_read = EEPROM.read(addr);
    String content= ""; // Empty string initialization which is used to concat 
  byte letter;
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
        for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = mfrc522.uid.uidByte[i];
    }
    
   for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  
  }
  content.toUpperCase();
  content.substring(1);
  Serial.println(content.substring(1));
if(Array==content.substring(1))
{
  Serial.println("Authorized Person");
  lcd.clear();
  lcd.home ();
  lcd.print("Authorized ");
   
 
  

//Serial.println("Your Balamce Amount is ");
  //Serial.println(amount_read);
  Balance(addr);
   mfrc522.PICC_HaltA();
       mfrc522.PCD_StopCrypto1();
   lcd.clear();  
     lcd.print("Enter * to Topup");
     
      lcd.print("Enter * to Topup");
      lcd.setCursor (0,1);
       lcd.print("Enter # to Snacks");
 Serial.println("Enter  to * to Top up your RFID");
 Serial.println("Enter  to # to get snacks");
 }
 else
 {
  lcd.clear();
 Serial.println("Un-Authorized Person"); 
  lcd.home ();
  lcd.print("Un-Authorized ");
  delay(2000);
  setup();
  
  

  }
  }
 void Topup(int addr)
 {
  int amount_check=1;
  
  Serial.println("Enter the amount to Topup or press '#' to exit");
 lcd.home ();
 lcd.clear();
  lcd.print("Entered amount ");
   lcd.setCursor (0,1);
   
  while(amount_check==1){
     if(Serial1.available())
     {int temp_amount =Serial1.readString().toInt();
     Total_amount=Total_amount+temp_amount; 
      lcd.print(Total_amount);
  
 amount_check=0;
 }
 else if (kpd.getKey()=='#')
 {
  amount_check=0;
 }
   
  }
  
  Serial.println("Total amount is ");
  Serial.print(Total_amount);
  EEPROM.write(addr, Total_amount);
  
 }
 void Get_Snacks(int addr)
 {
  
  int snacks_check=1;
 //  int temp_amount=EEPROM.read(addr);
lcd.clear();
lcd.home ();
lcd.print("Enter 1-->KitKat");
lcd.setCursor (0,1);
lcd.print("Enter 2-->oreo");

Serial.println("Enter 1-->KitKat");
  Serial.println("Enter 2-->oreo");

  while(snacks_check==1)
 { 
 
    char slot_number = kpd.getKey();
    switch (slot_number) {
    case '1':
    lcd.clear();
    lcd.home ();
    lcd.print("KitKat Selected");
     Serial.println(slot_number);
   
    Total_amount=Total_amount-slot_one_price;
     Serial.println(Total_amount);
     Serial1.write("KitKat"); // Serial write to MediaTek_DRS.js to decrement value by 1
    
    customStepRev(4096,1);//Passing parameter is complete one revolution of stepper motor
    snacks_check=0;
    if(Total_amount>0)
    {
    EEPROM.write(addr,Total_amount);
    Balance(addr);
    }
    else
 {   Serial.println("You have insufficient Balance");
    lcd.clear();
    lcd.home ();
    lcd.print("insuffiecient Balance");
 }
      //do something when var equals 1
      break;
    case '2':
    Serial.println(slot_number);
        lcd.clear();
    lcd.home ();
    lcd.print("Oreo Selected");
     Serial1.print("Oreo");
     customStepRev(4096,2);
   Total_amount=Total_amount-slot_two_price;
   
     snacks_check=0;
        if(Total_amount>0)
    {
    EEPROM.write(addr,Total_amount);
    Balance(addr);}
    else
 {    Serial.print("Amount is ");
 
     Serial.println(Total_amount);
    Serial.println("You have insuffiecient Balance");
    lcd.clear();
    lcd.home ();
    lcd.print("insufficient Balance");
 }
    break;
      
 /* if (slot_number=='1')
  {
   Serial.println(slot_number);
   
    temp_amount=temp_amount-slot_one_price;
    
    snacks_check=0;
    EEPROM.write(addr,temp_amount);
    Balance(addr);
  }
  else if (slot_number=='2')
  {
    Serial.println(slot_number);
  
    temp_amount=temp_amount-slot_two_price;
   
     snacks_check=0;
     Serial.println(temp_amount);
     EEPROM.write(addr,temp_amount);
      Balance(addr);
  }
  */
    }
    
  
 }
 }
 void Balance(int addr)
 {
  
    Total_amount = EEPROM.read(addr);
   lcd.setCursor (0,1);
   Serial.println(" Balamce  is ");
   lcd.print("Balance is ");
    
  Serial.println(Total_amount);
  lcd.print(Total_amount);
  delay(4000);
 }

  

