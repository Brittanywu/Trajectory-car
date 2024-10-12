// #include "pinouts.h"

// int frequencyR = 0;
// int frequencyG = 0;
// int frequencyB = 0;

// int ChangeF(int frequency){
//   if (frequency < 0)
//     frequency = 0;
//   if (frequency > 255)
//     frequency = 255;
//   return frequency;
// }


//  int readFrequencyR(){
//   // Setting red filtered photodides to be read
//   digitalWrite(s2,LOW);
//   digitalWrite(s3,LOW);
//   // Reading the output frequency
//   frequencyR = pulseIn(sensorOut,LOW);
//   frequencyR = map(frequencyR,40,69,255,0);
//   frequencyR=ChangeF(frequencyR);
//   return frequencyR;
//  }
 
//  int readFrequencyG(){
//   //Setting green filtered photodiodes to be read
//   digitalWrite(s2,HIGH);
//   digitalWrite(s3,HIGH);
//   // Reading the output frequency
//   frequencyG = pulseIn(sensorOut,LOW);
//   frequencyG = map(frequencyG,72,94,255,0);
//   frequencyG=ChangeF(frequencyG);
//   return frequencyG;
//  }
 
//  int readFrequencyB(){  
//   //Setting blue filtered photodiodes to be read
//   digitalWrite(s2,LOW);
//   digitalWrite(s3,HIGH);
//   // Reading the output frequency
//   frequencyB = pulseIn(sensorOut,LOW);
//   frequencyB = map(frequencyB,53,91,255,0);
//   frequencyB=ChangeF(frequencyB);
//   return frequencyB;
//  }
 
//  int Color_Read(int frequencyR,int frequencyG,int frequencyB){
//   if(frequencyR>=100 && frequencyG<=100 && frequencyB<=100)//红色返回1
//   {
//     return 1;
//   }
//   else if(frequencyR<=100 && frequencyG>=100 && frequencyB<=100)//绿色返回2
//   {
//     return 2;
//   }
//   else if(frequencyR<=100 && frequencyG<=100 && frequencyB>=100)//蓝色返回3
//   {
//     return 3;
//   }
//   else if(frequencyR>=220 && frequencyG>=220 && frequencyB<220)//黄色返回4
//   {
//     return 4;
//   }
//   else if(frequencyR>=220 && frequencyG>=100 && frequencyB>=100)//橙色返回5
//   {
//      return 5;
//   }
//   else//没有返回0
//   {
//     return 0;
//   }
//  }