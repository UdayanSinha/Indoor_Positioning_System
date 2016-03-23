//calibration values
#define thres_low  35
#define thres_high 65
#define limit 87

int sense[3];    //distance values from the sensors

//sensor IO
unsigned char echoPin[3]={3, 7, 10};
unsigned char trigPin[3]={2, 6, 9};

int dist_calc(unsigned char sensor_select);

void setup() 
{
  Serial.begin (9600);         //start UART
  
  //pin definitions & iniializations
  for(unsigned char i=0; i<3; i++)
  {
    pinMode(trigPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
    digitalWrite(trigPin[i], LOW);
  }
}

void loop() 
{
  //get sensor data
  for(unsigned char i=0; i<3; i++)
  {
    sense[i]=dist_calc(i);           
    delay(200);    //to prevent interference among sensors
  }
  
  //infer location
  if((sense[0]<thres_high) && (sense[1]<thres_high) && (sense[2]<thres_high) && (sense[0]>thres_low) && (sense[1]>thres_low) && (sense[2]>thres_low))
  {
    Serial.println("REGION-7 --> CENTRAL REGION");
  }
  else if((sense[0]<thres_low) && (sense[1]>thres_low) && (sense[2]>thres_low))
  {
    Serial.println("REGION-1 --> CLOSE TO SENSOR-0"); 
  }
  else if((sense[1]<thres_low) && (sense[0]>thres_low) && (sense[2]>thres_low))
  {
    Serial.println("REGION-3 --> CLOSE TO SENSOR-1"); 
  }
  else if((sense[2]<thres_low)  && (sense[0]>thres_low) && (sense[1]>thres_low))
  {
    Serial.println("REGION-5 --> CLOSE TO SENSOR-2"); 
  }
  else if((sense[0]>thres_high) && (sense[0]<limit) && (sense[1]>limit) && (sense[2]>limit))
  {
    Serial.println("REGION-4 --> FAR FROM SENSOR-0"); 
  }
  else if((sense[1]>thres_high) && (sense[1]<limit) && (sense[0]>limit) && (sense[2]>limit))
  {
    Serial.println("REGION-6 --> FAR FROM SENSOR-1"); 
  }
  else if((sense[2]>thres_high) && (sense[2]<limit) && (sense[0]>limit) && (sense[1]>limit))
  {
    Serial.println("REGION-2 --> FAR FROM SENSOR-2"); 
  }
  else
  {
    Serial.println("OUT OF RANGE/BLIND SPOT"); 
  }
  
  //***********************FOR DEBUGGING********************************
  Serial.print("\n\n\n");
  Serial.println("DEBUG OUTPUT ===>");
  Serial.print("Sensor 0: ");
  Serial.println(sense[0]);
  Serial.print("Sensor 1: ");
  Serial.println(sense[1]);
  Serial.print("Sensor 2: ");
  Serial.println(sense[2]);
  //********************************************************************
  
  Serial.print("\n\n\n\n\n\n");
  delay(500);
}

//distance calculator
int dist_calc(unsigned char sensor_sel)
{
  digitalWrite(trigPin[sensor_sel], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[sensor_sel], LOW);
  return (pulseIn(echoPin[sensor_sel], HIGH))/58;
}
