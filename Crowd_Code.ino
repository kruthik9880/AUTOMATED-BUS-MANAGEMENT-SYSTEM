#include <TinyGPS.h>
#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
#include<Timer.h>
//SoftwareSerial gpsSerial(10,11);//rx,tx 
///* Create an object named gps of the class TinyGPSPlus */
//TinyGPS gps;   
#include<String.h>
Timer t;
float lat = -28.5458,lon = - 77.1703; // create variable for latitude and longitude object
const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial Rfid(8,9);  //rx,tx
String message="";
int sw=16;
int k,End_sw=17;
float Amount_2,travelMeters_2,Amount_3;
float lat_one,long_one,lat_two,long_two,travelMeters,Amount,BAL=30,BAL_ONE=6,DAILY_PASS=500,r_bal=500,e_bal=0,r_bal1=1100,e_bal1=0,MONTHLY_PASS=1100;
//char RFID[20];
char buff_Km_2[30],Amount_buff_2[20],sms_2[160],BAL_BUFF[20],SMS[100];
char time_buff[20],time_buff1[20];
int flag=0,flag1=0;
int days=1,M_days=2;
char textmessage[60];
char CARD_1[]="5900D497BBA1";
//String message="";
void RFID_CHECKING();
unsigned long temp=0;
float Startingtime=0;
int count=0;
int count2=0;
int ir1=6,ir2=7;

int in1=14,in2=15;

int vib=18;
float count1=0;
float count3=0;

//int flag=0;
void setup() 
{
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(sw,INPUT_PULLUP);
  pinMode(End_sw,INPUT_PULLUP);
  pinMode(vib,INPUT_PULLUP);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
 Serial.begin(9600); // connect serial 
//Serial.println("The GPS Received Signal:"); 
//gpsSerial.begin(9600); // connect gps sensor 
lcd.begin(16,2); 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Crowd Management");
delay(1000);
//GPS();
}
void loop()
{
//  Accident();
  Seat();

  
}
void Seat()
{
  while(1)
  {
    if(flag==0)
    {
      door_open();
      door_close();
      flag=1;
    }
  if((digitalRead(ir1)==LOW) &&(digitalRead(ir2)==HIGH)) 
  {
    lcd.clear();
lcd.setCursor(0,0);
lcd.print("Seat1 Occupied");
delay(1000);
    RFID_CHECKING();
  }
  if((digitalRead(ir2)==LOW) && (digitalRead(ir1)==HIGH))
  {
    lcd.clear();
lcd.setCursor(0,0);
lcd.print("Seat2 Occupied");
delay(1000);
    RFID_CHECKING();
//    break;
  }
  if((digitalRead(ir1)==LOW) && (digitalRead(ir2)==LOW))
  {
    lcd.clear();
lcd.setCursor(0,0);
lcd.print("Seats are Full");
delay(1000);
  }
  else if((digitalRead(ir1)==HIGH) && (digitalRead(ir2)==HIGH))
  {
    lcd.clear();
lcd.setCursor(0,0);
lcd.print("Seats are");
//lcd.clear();
lcd.setCursor(0,1);
lcd.print("       Available      ");
  delay(1000);
  }
  }
}
void RFID_CHECKING()
{ 
  Rfid.begin(9600);
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Scan the  ");
    lcd.setCursor(0,1);
    lcd.print("CARD......   ");
    Serial.print("Scan the card...");
    
 while(1)
 {
    if(Rfid.available()>0)
    {
//     GPS();
      message=Rfid.readString();
      int str_len = message.length() + 1;
      char textmessage[11];
      message.toCharArray(textmessage,str_len);
      Serial.println(textmessage);
      textmessage[12]='\0';
      if(!strcmp(textmessage,"5500B5EA5D57"))
      {
//          
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Name:XYZ");
            lcd.setCursor(0,1);
            lcd.print("C.No:");
            lcd.setCursor(0,1);
            lcd.print(CARD_1);
            Serial.println("$Name:XYZ");
            Serial.print("C.NO:");
            Serial.print(CARD_1);
            Serial.print("#");
            delay(2000);
//            temp=millis();
//            door_open();
//            door_close();
           
            while(1)
            {
               count1++;
               delay(1000);
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Distance:");
               lcd.setCursor(9,0);
               lcd.print(count1/2);
               Accident();
              if(k==0)
              {
                 lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Plz Start the  ");
              lcd.setCursor(0,1);
              lcd.print("Journey");
              delay(1000);
              if(digitalRead(sw)==LOW)
                {
              Accident();
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Your Journey ");
              lcd.setCursor(0,1);
              lcd.print("Starts Here");
              Serial.println("$Your Journey Starts Here#");
              delay(2000);
              count++; 
    
//              GPS();
              k=1; 
//            
            }
              }
           // count1++ ;
//              }
              else 
              {
                if(digitalRead(End_sw)==0)
              
              {
               Accident();
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Your Journey ");
              lcd.setCursor(0,1);
              lcd.print("Ends Here");
              Serial.println("$Your Journey Ends Here#");
              delay(2000);
              Serial.print("$Distance:"); 
              Serial.print(count1/2);
              Serial.println("#");
//              door_open();
//              door_close();
              flag=0;
              Destination1();
              k=0;
//              temp=millis();
              if(count>3)
              {
              Accident();
              days++;
              count=0;
//              Startingtime=0;
//setup();
              }
//               Amount_2 = travelMeters_2 * 50.0;
///Serial.print(count1);
               Amount_2 = count1/10 * 20.0;

               r_bal=r_bal - Amount_2;
               e_bal=DAILY_PASS-(60*days);
               if(r_bal<=e_bal)
              {
                 lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Converted to");
               lcd.setCursor(0,1);
               lcd.print("Daily Pass");
               Serial.println("$Convrted to Daily Pass#");
               delay(1000);
               Accident();
               r_bal=DAILY_PASS-(60*days);
               sprintf(time_buff,"DAY %d",days);
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("days:");
               lcd.setCursor(5,0);
               lcd.print(time_buff);
               delay(1000);
               sprintf(Amount_buff_2,"%f INR",Amount_2); 
//               lcd.clear();
//               lcd.print(String("Amount:")+Amount_2);
//               delay(1000);
                lcd.clear();
               lcd.print(String("Rem:")+r_bal);
               Serial.print("$");
               Serial.print(String("Rem:")+r_bal);
               Serial.println("INR#");
               delay(1000);
      //    sprintf(BAL_BUFF,"%f INR",BAL);
           sprintf(BAL_BUFF,"%f INR",r_bal);
//           lcd.clear();
//           lcd.setCursor(0,0);
//           lcd.print(BAL_BUFF);
           delay(1000);
           
           if(r_bal<100)
       {
           lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("LOW BALANCE");
           Serial.print("$INSUFFICIENT BALANCE PLEASE REACHARGE YOUR CARD#");
           delay(1000);
       }
       //loop();
              }
              else
              {
                Accident();
          lcd.clear();
          sprintf(time_buff,"DAY %d",days);     
          lcd.setCursor(0,0);
            lcd.print(time_buff);
            delay(2000);
            lcd.clear();
               lcd.print(String("Amount:")+Amount_2);
                Serial.print("$");
               Serial.print(String("Amount:")+Amount_2);
               Serial.println("INR#");
               delay(1000);

if(r_bal<100)
       {
           lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("LOW BALANCE");
           Serial.print("$INSUFFICIENT BALANCE PLEASE REACHARGE YOUR CARD#");
           delay(1000);
       }
        }
        break;
 
        }
       
        
              }
              
            }
}
//$U:H:56m#
//$U:T:78P#
//$U:M:56S#
else if(!strcmp(textmessage,"5500B5F2A4B6"))
      {
//          
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Name:ABC");
            lcd.setCursor(0,1);
            lcd.print("C.No:");
            lcd.setCursor(0,1);
            lcd.print(CARD_1);
            Serial.println("$Name:ABC");
            Serial.print("C.NO:");
            Serial.print(CARD_1);
            Serial.print("#");
            delay(2000);
//            door_open();
//              door_close();
//            temp=millis();
            
           
            while(1)
            {
               count3++;
               delay(1000);
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Distance:");
               lcd.setCursor(9,0);
               lcd.print((count3)/2);
               Accident();
               //delay(1000);
              if(k==0)
              {
                
                lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Plz Start the  ");
              lcd.setCursor(0,1);
              lcd.print("Journey");
              delay(1000);
              if(digitalRead(sw)==LOW)
                {
//              Accident();
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Your Journey ");
              lcd.setCursor(0,1);
              lcd.print("Starts Here");
              Serial.println("$Your Journey Starts Here#");
              delay(2000);
//              lcd.setCursor(0,0);
//               lcd.print("Distance:");
//               lcd.setCursor(9,0);
//               lcd.print(count3/5);
//               delay(1000);
              count2++; 
             
//              GPS();
              k=1; 
//             
            }
            }
         
           // count1++ ;
//              }
              else 
              {
                if(digitalRead(End_sw)==0)
              
              {
//               Accident();
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Your Journey ");
              lcd.setCursor(0,1);
              lcd.print("Ends Here");
              Serial.println("$Your Journey Ends Here#");
              delay(2000); 
              Serial.print("$Distance:"); 
              Serial.print((count3)/2);
              Serial.println("#");
//              door_open();
//              door_close();
              flag=0;
              Destination2();
              k=0;
//              temp=millis();
              if(count2>3)
              {
              Accident();
              M_days++;
              count2=0;
//              Startingtime=0;
//setup();
              }
//               Amount_2 = travelMeters_2 * 50.0;
//Serial.print(count3);
               Amount_3 = count3/10 * 20.0;
//             
               r_bal1=r_bal1 - Amount_3;
               e_bal1=MONTHLY_PASS-(60*M_days);
               if(r_bal1<=e_bal1)
              {
                lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Converted to");
               lcd.setCursor(0,1);
               lcd.print("Monthly Pass");
               Serial.print("$Converted to Monthly Pass#");
               delay(1000);
               Accident();
               r_bal1=MONTHLY_PASS-(60*M_days);
               sprintf(time_buff1,"DAY %d",M_days);
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("days:");
               lcd.setCursor(5,0);
               lcd.print(time_buff1);
               delay(1000);
               lcd.setCursor(0,0);
               lcd.print("Distance:");
               lcd.setCursor(10,0);
               lcd.print(count3/2);
               Serial.print("$Distance:");
               Serial.print((count3)/2);
               Serial.print("#");
               delay(1000);
               sprintf(Amount_buff_2,"%f INR",Amount_3); 
//               lcd.clear();
//               lcd.print(String("Amount:")+Amount_2);
//               delay(1000);
                lcd.clear();
               lcd.print(String("Rem:")+r_bal1);
               Serial.print("$");
               Serial.print(String("Rem:")+r_bal1);
                Serial.print("#");
               delay(1000);
      //    sprintf(BAL_BUFF,"%f INR",BAL);
           sprintf(BAL_BUFF,"%f INR",r_bal1);
//           lcd.clear();
//           lcd.setCursor(0,0);
//           lcd.print(BAL_BUFF);
           delay(1000);
           
           if(r_bal1<100)
       {
           lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("LOW BALANCE");
           Serial.print("$INSUFFICIENT BALANCE PLEASE REACHARGE YOUR CARD#");
           delay(1000);
       }
       //loop();
              }
              else
              {
                Accident();
          lcd.clear();
          sprintf(time_buff1,"DAY %d",M_days);
          lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("Distance:");
               lcd.setCursor(10,0);
               lcd.print(count3/2);
               Serial.print("$Distance:");
               Serial.print((count3)/2);
               Serial.print("#");
               delay(1000);    
               lcd.clear();
               lcd.print(String("Amount:")+Amount_3);
               Serial.print("$");
               Serial.print(String("Amount:")+Amount_3);
                Serial.print("#");
               delay(1000);

if(r_bal1<100)
       {
           lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("LOW BALANCE");
           Serial.print("$INSUFFICIENT BALANCE PLEASE REACHARGE YOUR CARD#");
           delay(1000);
       }
        }
        break;
  
        }
       
        
              }
              
            }
}
Seat();

    }
    count1=0;
    count3=0;
   
 }
 
 while(1)
 {
 Seat();
}
}
//}

void door_open()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  delay(2000);
   digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
}
void door_close()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  delay(2000);
   digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
}
void Destination1()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Destination1 ");
    lcd.setCursor(0,1);
    lcd.print("    Reached      ");
    Serial.print("$Destination1 is reached#");
    delay(1000);
}
void Destination2()
{
 lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Destination2 ");
    lcd.setCursor(0,1);
    lcd.print("    Reached      ");
    Serial.print("$Destination2 is reached#");
    delay(1000);
}
void Accident()
{
  flag=0;
  if(digitalRead(vib)==LOW)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Accident Occured");
    Serial.print("$Accident Occured#");
    delay(1000);
    String one = "PERSON LOCATION AT:https://www.google.com/maps/?q=";
    String two = "," ;   
    String message = one + 12.9357693 +two + 77.5359641;
    
    int str_len = message.length() + 1;
    char textmessage[str_len];
    message.toCharArray(textmessage,str_len);
    Serial.println(textmessage);
    delay(3000); // wait for 3 seconds
      Serial.println(textmessage);
        Serial.print("$");
        Serial.print(textmessage);
        Serial.println("#");
    while(1)
    {
    Seat();
    }
  }
}
//void GPS()
//{
//  
//  while(1)
//  {
//    gpsSerial.begin(9600);
//  while(gpsSerial.available()){ // check for gps data 
//  if(gps.encode(gpsSerial.read()))// encode gps data 
//  {  
//  gps.f_get_position(&lat,&lon); // get latitude and longitude 
//  // display position 
//  lcd.clear(); 
//  lcd.setCursor(1,0); 
//  lcd.print("GPS Signal"); 
//  //Serial.print("Position: "); 
//  //Serial.print("Latitude:"); 
//  //Serial.print(lat,6); 
//  //Serial.print(";"); 
//  //Serial.print("Longitude:"); 
//  //Serial.println(lon,6);  
//  lcd.setCursor(1,0); 
//  lcd.print("LAT:"); 
//  lcd.setCursor(5,0); 
//  lcd.print(lat); 
//  //Serial.print(lat); 
//  //Serial.print(" "); 
//  lcd.setCursor(0,1); 
//  lcd.print(",LON:"); 
//  lcd.setCursor(5,1); 
//  lcd.print(lon); 
// } 
//} 
//String latitude = String(lat,6); 
//  String longitude = String(lon,6); 
//Serial.println(latitude+";"+longitude); 
//delay(10); 
//if(lat>1 && lon >1)
//{
//loop();
//}
//} 
//}
