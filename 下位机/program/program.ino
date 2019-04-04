/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
           佛祖保佑       永无BUG
*/
#include <string.h>
#include <math.h>

#define masterArmDir 23                                                              //机械大臂控制器方向接线
#define masterArmPul 22                                                              //机械大臂控制器脉冲接线
#define slaveArmDir 24                                                               //机械小臂控制器方向接线
#define slaveArmPul 25                                                               //机械小臂控制器脉冲接线
#define zMotorDir 6                                                                 //Z轴控制器方向接线
#define zMotorPul 7                                                                 //Z轴控制器脉冲接线
#define zMotorEna 2
#define zMotorM0 3
#define zMotorM1 4
#define zMotorM2 5 

const float masterArmDiv=0.028125;                                                //机械大臂单步角位移
const float slaveArmDiv=0.028125;                                                 //机械小臂单步角位移
const float zMotorDiv=0.0125;                                                      //Z轴电机单步位移
const int signalWidth=1;                                                            //脉冲方波宽度，毫秒

String sbuffer="";
char operate;                                                                       //指令操作符
float masterArmCmd;                                                                 //指令中的三个参数
float slaveArmCmd;
float zMotorCmd;
float masterArmPos=90.0;                                                            //机械臂的位置
float slaveArmPos=0;
float zMotorPos=0;
int masterArmGo=1;                                                                  //机械臂运行方向
int slaveArmGo=1;
int zMotorGo=1;

void setup() {
  pinMode(masterArmDir,OUTPUT);
  pinMode(masterArmPul,OUTPUT);
  pinMode(slaveArmDir,OUTPUT);
  pinMode(slaveArmPul,OUTPUT);
  pinMode(zMotorDir,OUTPUT);
  pinMode(zMotorPul,OUTPUT);
  pinMode(zMotorEna,OUTPUT);
  pinMode(zMotorM0,OUTPUT);
  pinMode(zMotorM1,OUTPUT);
  pinMode(zMotorM2,OUTPUT);
  digitalWrite(zMotorEna,LOW);
  digitalWrite(zMotorM0,HIGH);                                                    //设定细分
  digitalWrite(zMotorM1,LOW);
  digitalWrite(zMotorM2,LOW);
  Serial.begin(115200);
  Serial.flush();
  digitalWrite(masterArmPul,LOW);
  digitalWrite(slaveArmPul,LOW);
  digitalWrite(zMotorPul,LOW);
  Serial.println("Reseted!");
}

void loop() {
 if(Serial.available()>0){
  //解析串口指令
  delay(50);
  operate=char(Serial.read());
  masterArmCmd=Serial.parseFloat();
  slaveArmCmd=Serial.parseFloat();
  zMotorCmd=Serial.parseFloat();
  if(operate=='R'){
    //复位指令
    int masterArmStep=round(abs(masterArmCmd/masterArmDiv));
    int slaveArmStep=round(abs(slaveArmCmd/slaveArmDiv));
    int zMotorStep=round(abs(zMotorCmd/zMotorDiv));
    if(masterArmCmd>=0){
      digitalWrite(masterArmDir,HIGH);
      masterArmGo=1;
    }else{
      digitalWrite(masterArmDir,LOW);
      masterArmGo=-1;
    }
    if(slaveArmCmd>=0){
      digitalWrite(slaveArmDir,HIGH);
      slaveArmGo=1;
    }else{
      digitalWrite(slaveArmDir,LOW);
      slaveArmGo=-1;
    }
    if(zMotorCmd>=0){
      digitalWrite(zMotorDir,HIGH);
      zMotorGo=1;
    }else{
      digitalWrite(zMotorDir,LOW);
      zMotorGo=-1;
    }
    for(int i=0;i<masterArmStep;i++){
      digitalWrite(masterArmPul,HIGH);
      delay(signalWidth);
      digitalWrite(masterArmPul,LOW);
      delay(signalWidth);
    }
    masterArmPos=90.0;
    for(int i=0;i<slaveArmStep;i++){
      digitalWrite(slaveArmPul,HIGH);
      delay(signalWidth);
      digitalWrite(slaveArmPul,LOW);
      delay(signalWidth);
    }
    slaveArmPos=0;
    for(int i=0;i<zMotorStep;i++){
      digitalWrite(zMotorPul,HIGH);
      delay(signalWidth);
      digitalWrite(zMotorPul,LOW);
      delay(signalWidth);
    }
    zMotorPos=0;
    
    Serial.println("90.00 0.00 0.0");
    
    
  }else if(operate=='W'){
    //工作指令
    int masterArmStep=round(abs((masterArmCmd-masterArmPos)/masterArmDiv));                   //机械臂预期运行步数
    int slaveArmStep=round(abs((slaveArmCmd-slaveArmPos)/slaveArmDiv));
    int zMotorStep=round(abs((zMotorCmd-zMotorPos)/zMotorDiv));

    if(masterArmCmd>=masterArmPos){
      digitalWrite(masterArmDir,HIGH);
      masterArmGo=1;
    }else{
      digitalWrite(masterArmDir,LOW);
      masterArmGo=-1;
    }
    if(slaveArmCmd>=slaveArmPos){
      digitalWrite(slaveArmDir,HIGH);
      slaveArmGo=1;
    }else{
      digitalWrite(slaveArmDir,LOW);
      slaveArmGo=-1;
    }
    if(zMotorCmd>=zMotorPos){
      digitalWrite(zMotorDir,HIGH);
      zMotorGo=1;
    }else{
      digitalWrite(zMotorDir,LOW);
      zMotorGo=-1;
    }
    for(int i=0;i<masterArmStep;i++){
        digitalWrite(masterArmPul,HIGH);
        delay(signalWidth);
        digitalWrite(masterArmPul,LOW);
        if(masterArmGo>=0){
           masterArmPos+=masterArmDiv;
         }else{
           masterArmPos-=masterArmDiv;
         }
         delay(signalWidth);
      }
      for(int i=0;i<slaveArmStep;i++){
        digitalWrite(slaveArmPul,HIGH);
        delay(signalWidth);
        digitalWrite(slaveArmPul,LOW);
        if(slaveArmGo>=0){
           slaveArmPos+=slaveArmDiv;
         }else{
           slaveArmPos-=slaveArmDiv;
         }
         delay(signalWidth);
      }
      for(int i=0;i<zMotorStep;i++){
        digitalWrite(zMotorPul,HIGH);
        delay(signalWidth);
        digitalWrite(zMotorPul,LOW);
        if(zMotorGo>=0){
           zMotorPos+=zMotorDiv;
         }else{
           zMotorPos-=zMotorDiv;
         }
         delay(signalWidth);
      }
      Serial.print(masterArmPos,2);
      Serial.print(" ");
      Serial.print(slaveArmPos,2);
      Serial.print(" ");
      Serial.println(zMotorPos,1);
  }else{
    Serial.print("Undefined command:");
    Serial.println(operate);
    Serial.flush();
  }
  Serial.flush();
 }
}
