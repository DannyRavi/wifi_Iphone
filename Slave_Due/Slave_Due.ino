
unsigned int data=0,data1=0,counter=0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.write("Start DUE");  
  //analogWriteResolution(12);
  }


//8-bit serial recieve
void loop() {



    if(Serial1.available()>0){
      data=Serial1.read();
     // Serial.println(data);
      //Serial.write(data);
      //Serial.write(13);
      //Serial.write(10);
      
      
      analogWrite(DAC1, data );
    }
}

