#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <SD.h>
#include <SPI.h>

File myFile;

int pinCS = 53; // Pin 10 on Arduino Uno

//Deklarasi LCD Display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Inisialisasi pin (CLK, DAT, RST)
virtuabotixRTC myRTC(3,4,5);

//Deklarasi karakter dan variable
char keypressed,keypressedx;
String Line = "Line09";

//Deklarasi Counter
int ir_pin = 2;
int counter = 0;
int hitObject = false;

void setup() {
  Serial.begin(9600);
  pinMode(ir_pin,INPUT);
  lcd.init();
  lcd.backlight ();


  pinMode(pinCS, OUTPUT);
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }  


//penulisan data pertama kali dan disarankan saat transfer
//ke-2 ini tidak digunakan dikarenakan akan menghapus data
//sebelumnya
//myRTC.setDS1302Time(00,52,22,06,04,04,2021);
//detik, menit, jam, hari dalam seminggu, tanggal, bulan, tahun
// 00:59:23 "Rabu" 7-September-2017
}

void loop() {
//memanggil fungsi untuk update data waktu
myRTC.updateTime(); 


int val = digitalRead(ir_pin);

if( (val == 0) && (hitObject == false) ){
        counter++;
        hitObject = true;

Serial.print(Line);
Serial.print(" ");
//penulisan data pada serial monitor komputer
//Serial.print("Current Date / Time: ");
//fungsi penulisan data untuk tanggal
if(myRTC.dayofmonth<10){
    Serial.print("0");
    Serial.print(myRTC.dayofmonth);
  }
  else{
    Serial.print(myRTC.dayofmonth);
  }
 
//penulisan data "/" sebagai separator
Serial.print("_");
 
//fungsi penulisan data untuk bulan
if(myRTC.month<10){
    Serial.print("0");
    Serial.print(myRTC.month);
  }
  else{
    Serial.print(myRTC.month);
  }
 
//penulisan data "/" sebagai separator
Serial.print("_");
 
//fungsi penulisan data untuk tahun
Serial.print(myRTC.year);

 
//penulisan data untuk jarak
Serial.print(" ");
 
//fungsi penulisan data untuk jam
if(myRTC.hours<10){
    Serial.print("0");
    Serial.print(myRTC.hours);
  }
  else{
    Serial.print(myRTC.hours);
  }
 
Serial.print(":");
 
//fungsi penulisan data untuk menit
if(myRTC.minutes<10){
    Serial.print("0");
    Serial.print(myRTC.minutes);
  }
  else{
    Serial.print(myRTC.minutes);
  }
 
Serial.print(":");
 
//fungsi penulisan data untuk detik
if(myRTC.seconds<10){
    Serial.print("0");
    Serial.print(myRTC.seconds);
  }
  else{
    Serial.print(myRTC.seconds);
  }
  
  Serial.print(" ");
  Serial.println(counter);


    //SD Card Module Code
  myFile = SD.open("Line09.txt", FILE_WRITE);
  if (myFile) {    
    myFile.print(Line);
    
    myFile.print(" ");
        
    if(myRTC.dayofmonth<10){
    myFile.print("0");
    myFile.print(myRTC.dayofmonth);
    }
    else{
    myFile.print(myRTC.dayofmonth);
    }
    myFile.print("_");
    if(myRTC.month<10){
    myFile.print("0");
    myFile.print(myRTC.month);
    }
    else{
    myFile.print(myRTC.month);
    }
    myFile.print("_");
    myFile.print(myRTC.year);
    
    myFile.print(" ");
    
    if(myRTC.hours<10){
    myFile.print("0");
    myFile.print(myRTC.hours);
    }
    else{
    myFile.print(myRTC.hours);
    }
    myFile.print(":");
    if(myRTC.minutes<10){
    myFile.print("0");
    myFile.print(myRTC.minutes);
    }
    else{
    myFile.print(myRTC.minutes);
    }
    myFile.print(":");
    if(myRTC.seconds<10){
    myFile.print("0");
    myFile.print(myRTC.seconds);
    }
    else{
    myFile.print(myRTC.seconds);
    }

    myFile.print(" ");

    myFile.println(counter);
    
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  
  
  }else if( (val == 1) && (hitObject == true) ) {
        hitObject = false;
  }
  
  //LCD Print Time
  lcd.setCursor(0,0);
  lcd.print(myRTC.dayofmonth);
  lcd.print("_");
  lcd.print(myRTC.month);
  lcd.print("_");
  lcd.print(myRTC.year);
  if(myRTC.hours<10){
    lcd.setCursor(11,0);
    lcd.print("0");
    lcd.print(myRTC.hours);
  }
  else{
    lcd.setCursor(11,0);
    lcd.print(myRTC.hours);
  }

  lcd.setCursor(13,0);
  lcd.print(":");
  
  if(myRTC.minutes<10){
    lcd.setCursor(14,0);
    lcd.print("0");
    lcd.print(myRTC.minutes);
  }
  else{
    lcd.setCursor(14,0);
    lcd.print(myRTC.minutes);
  }

  //LCD Print Counter
  lcd.setCursor(0,1);
  lcd.print(counter);
  lcd.print("ctn");

  //LCD Print Line
  lcd.setCursor(10, 1);
  lcd.print(Line);
 
}
