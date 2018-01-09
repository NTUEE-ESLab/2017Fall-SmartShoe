// Address: A0:E6:F8:BA:20:04
#include <BLE.h>
#include <string.h>

/* +1 for null-terminator */
int numBytes = 0;
int ans_count = 1;
char serialData[BLE_SERIAL_BUFFER_SIZE + 1];

void setupPredict(){
  Serial.begin(115200);
  ble.setLogLevel(BLE_LOG_ERRORS);
  // Initalize I/O
  ble.begin();
  ble.serial();
  ble.setAdvertName("Energia Serial");
  ble.startAdvert(); 
}

void parseSerialString(String dataString)
{
  // Check if we found Adafruit app msg start char
  Serial.print("Do nothing:");
  Serial.println(dataString);
}

void loopPredict(){
  if(flag == 1){
    //Make the prediction using dot products
    Serial.println("Predict !!!");
    //Now Calculate the Dot Product of Data & ans
    for(int i = 0; i < ans_num; i++){
      float32_t multOutput[ans_len];
      float32_t local_sum = 0;
      arm_mult_f32(Data, ans[i], multOutput, ans_len);
      for(int j = 0; j < ans_len; j++){
        arm_add_f32(&local_sum, &multOutput[j], &local_sum, 1); 
      }
      Prediction[i] = local_sum;
    }
    int max_prob = 0;
    int index = 0;
    Serial.print("The Prediction Matrix Is: ");
    for(int i = 0; i < ans_num; i++){
        Serial.print(Prediction[i]);
        //Clear Data
        if(Prediction[i] > max_prob){
          max_prob = Prediction[i];
          index = i;
        }
        Prediction[i] = 0;
        Serial.print(" ");
    }
    Serial.println(""); 
    //Advertise through BLE
    ble.handleEvents();   
    serialData[0] = char(ans_count+1);
    ans_count = (ans_count+1)%9;
    serialData[1] = char(index+1);
  
    numBytes = 2;
    Serial.readBytes(serialData, numBytes);
    serialData[numBytes] = '\0';
    ble.print(serialData);    
    //Clear flag 
    flag = 0;
  }
}

