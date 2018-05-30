#define Gled 11
#define Rled 10
#define relay A0
const int seq[6] = {9, 6, 8, 6, 7, 8};

void setup() {
  //LedButton = 2 => 5
  //PushButton = 6 => 9
  //RedLed = 10
  //GreenLed = 11
  //Set LedButton Pins 
  for(int i = 2; i < 6; i++){
      pinMode(i, OUTPUT);
      digitalWrite(i, LOW);    
  }
  //Set PushButton Pins 
  for(int i = 6; i < 10; i ++){
    pinMode(i, INPUT_PULLUP);
  }
  //Set RedLed and GreenLEd Pins 
  pinMode(Rled, OUTPUT);
  digitalWrite(Rled, LOW);
  pinMode(Gled, OUTPUT);
  digitalWrite(Gled, LOW);

  //Set Relay Pin
  pinMode(relay, OUTPUT);
  analogWrite(relay, 0);
  
  //Serial.begin(9600);

}

int checkBtn(){
  bool btnPushed = false;
  int btnPin = 0;
  while (btnPushed != true){
    for (int btn = 6; btn < 10; btn++){
       
       if(digitalRead(btn) == 0){
          digitalWrite(btn - 4, 1);
          btnPin = btn; 
          delay(200);
          digitalWrite(btn - 4, 0);
          btnPushed = true; 
       }
     }  
  }
 return btnPin;
}

void loop() {
  bool state = false;
  digitalWrite(Rled, HIGH);
  for (int i = 0; i < 6; i++){
    //Serial.print("Cheking loop = ");
    //Serial.println(i);
    int btn = checkBtn();
    //Serial.print("Button pushed is = ");
    //Serial.println(btn);
    if (btn == seq[i]){
      state = true;
    }
    else{
      //Serial.println("break");
      state = false;
      break;
    }
    delay(200);
  }
  if(state){
    analogWrite(relay, 255);
    digitalWrite(Rled, LOW);
    digitalWrite(Gled, HIGH);
    delay(10000);
    analogWrite(relay, 0);
    digitalWrite(Gled, LOW);
    digitalWrite(Rled, HIGH);
  }
 delay(200);  
}
