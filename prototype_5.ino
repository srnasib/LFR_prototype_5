//Prototype 3

int v1,v2,v3,v4,v5;            //Values from sensor board
int dv1,dv2,dv3,dv4,dv5;       //Converted digital values from sensor board
#define trigPin 3
#define echoPin 5

void setup(){
  pinMode(2,OUTPUT);  //Left Motor Input A
  pinMode(4,OUTPUT);  //Left Motor Input B
  pinMode(7,OUTPUT);  //Right Motor Input A
  pinMode(8,OUTPUT);  //Right Motor Input B
  pinMode(6,OUTPUT);  //Left Motor PWM Output
  pinMode(11,OUTPUT);  //Right Motor PWM Output
  Serial.begin (9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);}

// In functions forward & backward, argument "a" indicates left 
// or right motor ------- a==1 indicates left motor & a==2 indicates
// right motor


void forward(int a, int b){
  if (a==1){
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
    analogWrite(6,b);
  }
  if (a==2){
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    analogWrite(11,b);
  }
  
}

void back(int a, int b){
  if (a==1){
    digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
    analogWrite(6,b);
  }
  if (a==2){
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    analogWrite(11,b);
  }
  
}

void loop(){
  v1 = analogRead(0);   // v of LDR1
  v2 = analogRead(1); // v of LDR2
  v3 = analogRead(2); // v of LDR3
  v4 = analogRead(3); // v of LDR4
  v5 = analogRead(4); // v of LDR5
  int duration,distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration/2) /29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(500);
  
  //A dv variable equal to zero implies black
  
  if ( v1 >= 1 && v1 <= 150 )
     dv1 = 0 ;
  else if ( v1 >= 151 && v1 <= 1000)
     dv1 = 1 ;
 
   
   if ( v2 >= 1 && v2 <= 150)
     dv2 = 0 ; 
   else if ( v2 >= 151 && v2 <= 1000)
     dv2 = 1 ;
   
   
   
   if ( v3 >= 1 && v3 <= 150)
     dv3 = 0 ; 
   else if ( v3 >= 151 && v3 <= 1000)
     dv3 = 1 ;

   
   
   if ( v4 >= 1 && v4 <= 150)
     dv4 = 0 ; 
   else if ( v4 >= 151 && v4 <=1000 )
     dv4 = 1 ;

   
   
   if ( v5 >= 1 && v5 <= 150)
     dv5 = 0 ;
   else if ( v5 >= 151 && v5 <= 1000)
     dv5 = 1 ;
     
 //-------- End of Conditions-------------
 
 
 //--------Start of Movement-------------
 
 if (distance==5)
 
      {
        forward(1,150);
        back(2,60);
        delay(1000);
        back(1,60);
        forward(2,150);
       }
 
 
 
  else if (dv1==1 && 
       dv2==1 &&
       dv3==0 &&      // Straight 
       dv4==1 &&
       dv5==1 )         //Combination 11011
       { 
         forward(1,200);
         forward(2,200);
        }
       
  else if (dv1==1 && 
           dv2==0 &&
           dv3==0 &&  //Bit Left turn
           dv4==1 &&
           dv5==1 ) // Combination 10011
       { 
         forward(1,60);
         forward(2,120);
        }
    
   else if (dv1==0 && 
            dv2==0 &&
            dv3==0 &&   //Sharp Left Turn
            dv4==1 &&
            dv5==1 )  //Combination 00011
       { 
         back(1,100);
         forward(2,120);
       }  
      
   else if (dv1==1 && 
            dv2==1 &&
            dv3==0 &&     //Bit Right turn
            dv4==0 &&
            dv5==1 ) //Combination 11001
       { 
         forward(1,120);
         forward(2,60);
       } 
 
  else if (dv1==1 && 
            dv2==1 &&
            dv3==0 &&
            dv4==0 &&  // Right SHARP TURN
            dv5==0 ) //Combination 11000       
       { 
         forward(1,120);
         back(2,100);
       } 

  else if ( dv1==1 && 
            dv2==0 && //Left TURN
            dv3==1 &&
            dv4==1 &&
            dv5==1 ) //Combination 10111
       { 
         back(1,60);
         forward(2,150);
       } 

  else if ( dv1==1 && 
            dv2==1 &&
            dv3==1 &&
            dv4==0 &&      //Right TURN
            dv5==1 ) //Combination 11101
       { 
         forward(1,150);
         back(2,60);
       }

else if ( dv1==1 && 
            dv2==1 &&  //Bit Right turn
            dv3==1 &&
            dv4==1 &&
            dv5==0 )  //Combination 11110
       { 
         forward(1,150);    
         back(2,80);
       }
       
       else if ( dv1==0 && 
            dv2==1 &&
            dv3==1 &&
            dv4==1 &&       //Bit Left turn
            dv5==1 )  //Combination 01111
       { 
         back(1,80);
         forward(2,150);
       }
       
       else if ( dv1==1 && 
            dv2==1 &&//Right Turn
            dv3==1 &&
            dv4==0 &&
            dv5==0 )   //Combination 11100
       { 
         forward(1,150);           
         back(2,100);
       }
       
       else if ( dv1==0 && 
            dv2==0 &&
            dv3==1 &&  //Left Turn
            dv4==1 &&
            dv5==1 )    //Combination 00111          
       { 
         back(1,100);
         forward(2,150);
       }
       
       else if ( dv1==1 && 
            dv2==1 &&
            dv3==1 &&             //Backward
            dv4==1 &&  
            dv5==1 )   //Combination 11111
       { 
         back(1,120);
         back(2,120);
       }
       
       else if ( dv1==0 && 
            dv2==0 &&
            dv3==0 &&  //Right Sharp Turn
            dv4==0 &&
            dv5==1 ) //Combination 00001
       { 
         back(1,60);
         forward(2,120);
       }
       
       else if ( dv1==1 && 
            dv2==0 &&
            dv3==0 && //Left Sharp Turn
            dv4==0 &&
            dv5==0 ) //Combination 10000
       { 
         forward(1,120);
         back(2,60);
       }
       
        else if ( dv1==0 &&
            dv2==0 && 
            dv3==0 && //Stop 
            dv4==0 &&
            dv5==0 ) //Combination 00000
       { 
         forward(1,120);
         forward(2,120);
       }

}
