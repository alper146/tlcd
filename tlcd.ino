#include <UTFT.h>
#include <UTouch.h>
UTFT myGLCD(ITDB24,A5,A4,A3,A2);
UTouch myTouch(A1,10,A0,8,9);
extern uint8_t BigFont[];
int x, y;
char a=1;
char stCurrent[20]="";
int stCurrentLen=0;
char stLast[20]="";
void setup(){
   myGLCD.InitLCD(PORTRAIT);
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  myGLCD.setFont(BigFont);
 draw_menu();
}
void loop(){
  while(true){
    if(myTouch.dataAvailable())
     {
      myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
    if(x<110){
     settings_menu();
   //          myGLCD.fillScr(255,255,0);
   }  
     else if((110<x)&&(x<220)){
     calibration_menu();
//myGLCD.fillScr(0,255,0);
     }
     else{
     read_menu();
//      myGLCD.fillScr(0,0,0);
     }
       }
  }

}
void draw_menu(void){
  
 myGLCD.print("Read", CENTER, 55);
 myGLCD.drawLine(0, 110, 239, 110);
 myGLCD.print("Calibration", CENTER, 165);
 myGLCD.drawLine(0, 220, 239, 220);
 myGLCD.print("Settings", CENTER, 275);
}
long val=1000001;

void read_menu(void){
myGLCD.clrScr();
myGLCD.print(" Return",CENTER,165);
myGLCD.print(" Reading",CENTER,275);
/*if(val>900000){
myGLCD.printNumI(val%1000000,10,55);
myGLCD.print(".",25,60);
myGLCD.printNumI((val/10)%100000,30,55);
myGLCD.printNumI((val/100)%10000,45,55);
myGLCD.printNumI((val/1000)%1000,60,55);
myGLCD.print(".",75,60);
myGLCD.printNumI((val/10000)%100,90,55);
myGLCD.printNumI((val/100000)%10,105,55);
myGLCD.printNumI(val/1000000,120,55);
//myGLCD.print(" mg",100,55); */
a=1;
myGLCD.drawLine(0, 110, 239, 110);
 myGLCD.drawLine(0, 220, 239, 220);
while(a==1){
 
  if(myTouch.dataAvailable())
     {
      myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
         if((x<220)&&(x>110)){
         myGLCD.clrScr();
         draw_menu();
         a=0;
        
         }
   else if((x<220)){
       
     myGLCD.print(" Processing",CENTER,275);
         
         a=1;
         }
     }
}

}
void calibration_menu(void){
myGLCD.clrScr();
set_standart(1);
set_standart(2);
draw_menu();
             
}
void set_standart(byte r){
myGLCD.print("Set Standart ",CENTER,55);
myGLCD.printNumI(r,200,55);
myGLCD.setColor(255,255,255);
myGLCD.setBackColor(0,0,255);
myGLCD.print("1 mg",CENTER,80);
myGLCD.drawRoundRect(10, 130, 40, 170);
myGLCD.drawRoundRect(10, 180, 40, 220);
//aşağı yönlü ok
myGLCD.drawLine(15,190,35,190);
myGLCD.drawLine(15,190,25,210);
myGLCD.drawLine(35,190,25,210);
// yukarı yönlü ok
myGLCD.drawLine(15,160,35,160);
myGLCD.drawLine(15,160,25,140);
myGLCD.drawLine(35,160,25,140);
myGLCD.drawRoundRect(80, 140,  160 , 190);
myGLCD.print("Set",CENTER,160);
char set=1;
char swtch=1;
while(set==1){

  if(myTouch.dataAvailable())
     {
       myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
     if((y<40)&&(10<y)){
             if((x<170)&&(130<x)){
               if(swtch==0){
               swtch=6;}
               else{swtch--;}
             }
              if((x<220)&&(180<x)){
               if(swtch==6){
               swtch=0;}
               else{swtch++;}
             }
              myGLCD.print("        ",CENTER,80);
               switch (swtch)
               {case 0: 
               myGLCD.print("1 mg",CENTER,80);
                break; 
              case 1: 
               myGLCD.print("10 mg",CENTER,80);
                break;
            case 2: 
               myGLCD.print("20 mg",CENTER,80);
               break;  
               case 3: 
               myGLCD.print("50 mg",CENTER,80);
                break;  
               case 4: 
               myGLCD.print("100 mg",CENTER,80);
                break;  
               case 5: 
               myGLCD.print("500 mg",CENTER,80);
                break;  
               case 6: 
               myGLCD.print("1000 mg",CENTER,80);
                break;  
               
                  
                         }
                         delay(50);
             }
 
 if((y<160)&&(80<y)){
       if((x<190)&&(140<x)){set=2;myGLCD.print("Done",CENTER,160); }
             }
     }
}
myGLCD.clrScr();
myGLCD.print(" Place Standart ",CENTER,60);
myGLCD.print("Here is same instructions: ....",CENTER,100);
myGLCD.drawRoundRect(80, 220,  160 , 280);
myGLCD.print("Ready",CENTER,250);
 while(set==2){
 if(myTouch.dataAvailable())
     { myTouch.read();
    y=myTouch.getX();
    x=myTouch.getY();
 if((y<100)&&(40<y)){
       if((x<160)&&(80<x)){set=1;myGLCD.print("     ",CENTER,250); myGLCD.print("OK",CENTER,250);  }
             }}}
             delay(50);
              while(set==1){
 if(myTouch.dataAvailable())
     { myTouch.read();
    y=myTouch.getX();
    x=myTouch.getY();
 if((y<100)&&(40<y)){
       if((x<160)&&(80<x)){set=2; myGLCD.clrScr(); }
             }}}
             
}

void settings_menu(void){
myGLCD.clrScr();
byte r=1;
myGLCD.print("Number of Readings ",CENTER,55);
myGLCD.printNumI(r,CENTER,70);
myGLCD.drawRoundRect(10, 130, 40, 170);
myGLCD.drawRoundRect(10, 180, 40, 220);
//aşağı yönlü ok
myGLCD.drawLine(15,190,35,190);
myGLCD.drawLine(15,190,25,210);
myGLCD.drawLine(35,190,25,210);
// yukarı yönlü ok
myGLCD.drawLine(15,160,35,160);
myGLCD.drawLine(15,160,25,140);
myGLCD.drawLine(35,160,25,140);
myGLCD.drawRoundRect(80, 140,  160 , 190);
myGLCD.print("Set",CENTER,160);
char set=1;

while(set==1){

  if(myTouch.dataAvailable())
     {
       myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
     if((y<40)&&(10<y)){
             if((x<170)&&(130<x)){
               if(r==0){
               r=256;}
               else{r--;}
             }
              if((x<220)&&(180<x)){
               if(r==256){
               r=0;}
               else{r++;}
             }  myGLCD.print("        ",CENTER,70);
            myGLCD.printNumI(r,CENTER,70);}
             
if((y<160)&&(80<y)){
       if((x<190)&&(140<x)){set=2;myGLCD.print("Done",CENTER,160); }
           
          myGLCD.clrScr();
             draw_menu();
           break;  }
           
}}}
