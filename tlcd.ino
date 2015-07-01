#include <UTFT.h>
#include <UTouch.h>
UTFT myGLCD(ITDB24,A5,A4,A3,A2);
UTouch myTouch(A1,10,A0,8,9);
extern uint8_t BigFont[];
extern uint8_t SmallFont[];
int x, y;
char a=1;
void button(int x1,int y1,String st,byte prescx,byte prescy);
void button(int x1,int y1,String st);
void setup(){
   myGLCD.InitLCD(PORTRAIT);
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  myGLCD.setFont(BigFont);
// draw_menu();
 button(120,160,"Hello World!");
 while(!button_clicked(120,160,"Hello World!")){}
 myGLCD.clrScr();
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
  union{
		int32_t value;
		uint8_t aa[4];
	} c ;
void draw_menu(void){
  
 myGLCD.print("Read", CENTER, 55);
 myGLCD.drawLine(0, 110, 239, 110);
 myGLCD.print("Calibration", CENTER, 165);
 myGLCD.drawLine(0, 220, 239, 220);
 myGLCD.print("Settings", CENTER, 275);
}


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
         
       
  if(x>0 and (x<110)){
       
     myGLCD.print(" Processing",CENTER,275);
     Serial.begin(9600);
         Serial.write(10);
         
         delay(5);
         
          while(Serial.available()<3){}
          c.aa[0]=Serial.read();
          c.aa[1]=Serial.read();
          c.aa[2]=Serial.read();
         Serial.end();
          myGLCD.print("      ",CENTER,55);
          myGLCD.printNumI(c.value,CENTER,55);
          myGLCD.print("           ",CENTER,275);
          myGLCD.print(" Read",CENTER,275);
         a=1;
         }
       else  if((x<220)&&(x>110)){
         myGLCD.clrScr();
         draw_menu();
         a=0;
        
         }
 
     }
}

}
void calibration_menu(void){
myGLCD.clrScr();
Serial.begin(9600);
Serial.write(20);
Serial.end();
set_standart(1);
set_standart(2);
draw_menu();
             
}
void set_standart(byte r){
  myGLCD.clrScr();
myGLCD.print("Set Standart",CENTER,35);
myGLCD.printNumI(r,CENTER,55);
myGLCD.setColor(255,255,255);
myGLCD.setBackColor(0,0,255);
myGLCD.print("1 mg",CENTER,80);
myGLCD.drawRoundRect(10, 130, 70, 190);
myGLCD.drawRoundRect(10, 200, 70, 260);
//aşağı yönlü ok
myGLCD.drawLine(20,210,60,210);
myGLCD.drawLine(20,210,40,250);
myGLCD.drawLine(60,210,40,250);
// yukarı yönlü ok
myGLCD.drawLine(20,180,60,180);
myGLCD.drawLine(20,180,40,140);
myGLCD.drawLine(60,180,40,140);
//myGLCD.drawRoundRect(80, 140,  160 , 190);
button(120,165,"set");
char swtch=1;
byte set=1;
while(set==1){

  if(myTouch.dataAvailable())
     {
       myTouch.read();
    y=myTouch.getX();
    x=myTouch.getY();
     y=320-y;
     if((x<70)&&(10<x)){
             if((y<260)&&(200<y)){
               if(swtch==0){
               swtch=6;}
               else{swtch--;}
             }
              if((y<190)&&(130<y)){
               if(swtch==6){
               swtch=0;}
               else{swtch++;}
             }delay(80);
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
                         
             }
 
 if((y<180)&&(150<y)){
       if((x<150)&&(90<x)){set=2; button(120,165,"Done");
         myGLCD.clrScr();    
   Serial.begin(9600);  
   Serial.write(swtch);
Serial.end(); 
     }        }
     }
}
set=2;
myGLCD.print(" Place Standart ",CENTER,60);
myGLCD.print("Instructions:",LEFT,100);
//myGLCD.drawRoundRect(80, 220,  160 , 280);
//myGLCD.print("Ready",CENTER,250);
button(120,250,"Ready");
 while(set==2){
 if(myTouch.dataAvailable())
     { myTouch.read();
    y=myTouch.getX();
    x=myTouch.getY();
 if((y<100)&&(40<y)){
       if((x<160)&&(80<x)){set=1;myGLCD.setColor(0,0,0); myGLCD.fillRect(60,230,180,290);
     myGLCD.setColor(255,255,255);  button(120,250,"Waiting"); 
   Serial.begin(9600);  
     while(Serial.available()<3){}
          c.aa[0]=Serial.read();
          c.aa[1]=Serial.read();
          c.aa[2]=Serial.read();
          Serial.end();myGLCD.setColor(0,0,0);myGLCD.fillRect(40,230,200,290);
     myGLCD.setColor(255,255,255);  button(120,250,"OK");
       myGLCD.printNumI(c.value,CENTER,150);
       
     }
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
myGLCD.setFont(SmallFont);
myGLCD.drawRoundRect(10,10, 110, 80);
myGLCD.print("Number of",20,45);
myGLCD.print(" Readings",20,55);
myGLCD.drawRoundRect(10,90, 110, 160);
myGLCD.print("Brightness",20,125);

myGLCD.drawRoundRect(130,10, 230, 80);
myGLCD.print("somthng",140,55);
myGLCD.drawRoundRect(130,90, 230, 160);
myGLCD.print("somthng2",140,125);
byte set=1;
while(set==1){
if(myTouch.dataAvailable())
     {
       myTouch.read();
    y=myTouch.getX();
    x=myTouch.getY();
    y=320-y;
     if((x<110)&&(10<x)){
             if((y<80)&&(10<y)){set=2;
             }
     }}}
myGLCD.setFont(BigFont);
myGLCD.clrScr();
byte r=1;
myGLCD.print("Number of ",CENTER,35);
myGLCD.print("Readings ",CENTER,55);
myGLCD.printNumI(r,CENTER,80);
myGLCD.drawRoundRect(10, 130, 70, 190);
myGLCD.drawRoundRect(10, 200, 70, 260);
//aşağı yönlü ok
myGLCD.drawLine(20,210,60,210);
myGLCD.drawLine(20,210,40,250);
myGLCD.drawLine(60,210,40,250);
// yukarı yönlü ok
myGLCD.drawLine(20,180,60,180);
myGLCD.drawLine(20,180,40,140);
myGLCD.drawLine(60,180,40,140);
//myGLCD.drawRoundRect(80, 140,  160 , 190);
button(120,165,"set");
 set=1;
Serial.begin(9600);
Serial.write(30);
Serial.end();
while(set==1){
  

  if(myTouch.dataAvailable())
     {
        myTouch.read();
    y=myTouch.getX();
    x=myTouch.getY();
     y=320-y;
     if((x<70)&&(10<x)){
             if((y<260)&&(200<y)){
               if(r==0){
               r=255;}
               else{r--;}
             }
              if((y<190)&&(130<y)){
                if(r==255){
               r=0;}
               else{r++;}
             }delay(80);
 myGLCD.print("        ",CENTER,80);
            myGLCD.printNumI(r,CENTER,80);
         }
              if((y<180)&&(150<y)){
       if((x<150)&&(90<x)){set=2; button(120,165,"Done");
       myGLCD.clrScr();Serial.begin(9600); Serial.write(r); Serial.end(); 
             draw_menu();
           break; 
     }
           
           }
           
}}
}

void button(int x1,int y1,String st){

myGLCD.drawRoundRect(x1-2-(9*st.length()),y1-15,x1+2+(9*st.length()),y1+15);
myGLCD.print(st,x1-(8*st.length()),y1-10);

}
void button(int x1,int y1,String st,byte prescx=1,byte prescy=1){

myGLCD.drawRoundRect(x1-2-(prescx*7*st.length()),y1*prescy-15,x1+2+(prescx*7*st.length()),prescy*y1+15);
myGLCD.print(st,x1-(6*st.length()),y1-10);

}

boolean button_clicked(int x1,int y1,String st){
if(myTouch.dataAvailable())
     {
       myTouch.read();
    y=myTouch.getX();
    x=myTouch.getY();
   y=320-y;
   if((y<(y1+15))&&((y1-15)<y)){
               if((x<(x1+2+(9*st.length())))&&(x1-2-(9*st.length())<x)){return true;}
                     } 
   }
   return false;

}
