#define fsr_pin A3
#define ans_num 4
#define ans_len 300
#define delay_interval 10
#define height 1024
#define input_buffer 700
#define threshold 200
#define end_thres 100

//int buf = 400;
//int ans_len = 300;

#include <math.h>
#include <arm_math.h>

float32_t ans[ans_num][ans_len];      //Predefined Input
float32_t Prediction[ans_num];        //Prediction Matrix
float32_t Input[input_buffer];   //Raw input
float32_t Data[ans_len];            //Data extracted from input

const int ledPin = GREEN_LED;

int State = 0;
int counter = 0;              //count for InputAdd
int count_zero = 0;           //count for consecutive input less the threshold
int flag = 0;                 //flag for Prediction
//int end_index = 0;            //index for the end of signal

int init_num = -1;
int prev_init_num = -1;
int init_state = 0;
int initializing = 0;


void Init(int num);
void PrintByCommand(char a);
void InputAdd(float32_t temp);
void Rotate(float32_t temp);


void setup() {
  // put your setup code here, to run once:
  //Init(init_num);
  pinMode(fsr_pin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly: 
  if (Serial.available() > 0) {
    char a = Serial.read();
    PrintByCommand(a);
  }
  if(init_state == 0){
      if ((init_num != prev_init_num)&&(init_num < ans_num)){
        Init(init_num);
        prev_init_num = init_num;
        if(init_num >= ans_num-1){
          Serial.println("Collected All Data!!");
          init_state = 1;
        }
      }    
  }else{
      float32_t temp = analogRead(fsr_pin);
      if((temp > threshold)&&(State == 0)){
        State = 1;
      }
      if(State == 1){
        InputAdd(temp);
        if(temp < threshold){
          count_zero += 1;
        }else{
          count_zero = 0;
        }
      }
      if(count_zero > end_thres){
        int end_point = counter - end_thres;
        if(end_point <= ans_len){
          int start = (ans_len - end_point)/2;
          for (int i = 0; i < end_point; i++){
            Data[start+i] = Input[i];
          }
        }else{
          int start = (end_point - ans_len)/2;     
          for (int i = 0; i < ans_len; i++){
            Data[i] = Input[start+i];
          }
        }
        flag = 1;
        for (int i = 0; i < input_buffer; i++){
          Input[i] = 0;
        }
        State = 0;
        counter = 0;
        count_zero = 0;    
      }
  }
  delay(delay_interval);
}

void Init(int num){
  Serial.print("Initialzing: ");
  Serial.println(num);
  digitalWrite(ledPin, HIGH);
  initializing = 1;
  float32_t sum = 0;
  while(1){
    float32_t temp = analogRead(fsr_pin);
    if((temp > threshold)&&(State == 0)){
      State = 1;
    }
    if(State == 1){
      InputAdd(temp);
      if(temp < threshold){
          count_zero += 1;
      }else{
          count_zero = 0;
          sum += 1;
      }
    }
    if(count_zero > end_thres){
      int end_point = counter - end_thres;
      if(end_point <= ans_len){
          int start = (ans_len - end_point)/2;
          for (int i = 0; i < end_point; i++){
              ans[num][start+i] = Input[i];
          }
      }else{
          int start = (end_point - ans_len)/2;     
          for (int i = 0; i < ans_len; i++){
              ans[num][i] = Input[start+i];
          }
      }
      for (int i = 0; i < input_buffer; i++){
          Input[i] = 0;
      }
      State = 0;
      counter = 0;
      count_zero = 0; 
      break;   
    }
    delay(delay_interval);
  }
  digitalWrite(ledPin, LOW);
  if(sum != 0){
    for(int i = 0; i < ans_len; i++){
      ans[num][i] /= sum;
    }
  } 
  Serial.println("Done Initializing");
  initializing = 0;
}


void Rotate(float32_t temp){
  for(int i = 1; i < ans_len; i++){
    Input[i-1] = Input[i];
  }
  Input[ans_len-1] = temp;
}

void InputAdd(float32_t temp){
      if(counter < input_buffer){
        Input[counter] = temp;
        counter += 1;
      }else{
        Rotate(temp);
      }  
}

void PrintByCommand(char a){
    if(a=='a'){
      Serial.println("The pattern of A is: ");
      for(int i = 0; i < ans_len; i++){
        Serial.print(ans[0][i]);
        if((i+1)%20 == 0){
          Serial.println(' ');
        }else{
          Serial.print(" ");
        }
      }
    }
    if(a=='b'){
      Serial.println("The pattern of B is: ");      
      for(int i = 0; i < ans_len; i++){
        Serial.print(ans[1][i]);
        if((i+1)%20 == 0){
          Serial.println(' ');
        }else{
          Serial.print(" ");
        }
      }
    }
    if(a=='c'){
      Serial.println("The pattern of C is: ");      
      for(int i = 0; i < ans_len; i++){
        Serial.print(ans[2][i]);
        if((i+1)%20 == 0){
          Serial.println(' ');
        }else{
          Serial.print(" ");
        }
      }
    }
    if(a=='d'){
      Serial.println("The pattern of D is: ");      
      for(int i = 0; i < ans_len; i++){
        Serial.print(ans[3][i]);
        if((i+1)%20 == 0){
          Serial.println(' ');
        }else{
          Serial.print(" ");
        }
      }
    } 
    if(a=='i'){
      Serial.println("The Input is: ");      
      for(int i = 0; i < ans_len; i++){
        Serial.print(Input[i]);
        if((i+1)%20 == 0){
          Serial.println(' ');
        }else{
          Serial.print(" ");
        }
      }
    }
    if(a=='f'){
      Serial.print("The flag is: ");
      Serial.println(flag); 
    }
}

