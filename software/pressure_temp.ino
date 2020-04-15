#include <Wire.h>

const int OUT_MAX = 14745.0;
const int OUT_MIN = 1638.0;
const int P_MAX = 1.0;
const int P_MIN = -1.0;

//previous,current,average,average,all of, until
 
int lut[128]= {-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-69,-67,-66,
               -65,-63,-62,-61,-59,-58,-56,-55,-54,-52,-51,-50,-48,-47,-45,-44,
               -43,-41,-40,-39,-37,-36,-35,-33,-32,-30,-29,-28,-26,-25,-24,-22,
               -21,-19,-18,-17,-15,-14,-13,-11,-10, -8, -7, -6, -4, -3, -2,  0,
                 0,  2,  3,  4,  6,  7,  8, 10, 11, 13, 14, 15, 17, 18, 19, 21,
                22, 24, 25, 26, 28, 29, 30, 32, 33, 35, 36, 37, 39, 40, 41, 43,
                44, 46, 47, 48, 50, 51, 52, 54, 55, 56, 58, 59, 61, 62, 63, 65,
                66, 67, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70};

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  int pt; //pressure and temp pointer/return value
  Wire.requestFrom(0x28, 4);    // request 6 bytes from slave device #2

  //get temp and pressure
  bool ret = getPressureTemp(&pt);
  if (!ret){
    Serial.println("sensor fail");}

  String str1 = String((byte)(pt >> 8), DEC);
  Serial.println(str1);
  delay(2000);
}
char hex2char(int v)
{
  if(v < 10){
    v = v | 0x30;
  }
  else {
    v = v + 55;
  }
  return char(v);
}
bool getPressureTemp(int * pressure_temp)
{
  int pt[4];
  int i = 0;

  //read sensor and get the pressure and temperature
  while(Wire.available())    // slave may send less than requested
  { 
    pt[i] = Wire.read();    // receive a byte as character
    i++;
  }
  if (i != 4)
    return false;

  int sensor_status = (pt[0] >> 6) & 0x03;
  if (sensor_status != 0)
    return false;
    
  int p_count = ((pt[0] << 8) | pt[1]) & 0x3fff;
  int t_count   = (pt[2] << 3) | (pt[3] >> 5);

  double pressure = (((double)p_count-OUT_MIN)*(P_MAX-P_MIN)/(OUT_MAX-OUT_MIN))+P_MIN; // psi
  pressure = pressure / 0.0142233; // cmH2O
  double temp = (((double)t_count*200.0)/2047.0)-50.0; //celsius
  
  *pressure_temp = ((int)temp << 8) | (int)pressure;
  
  return true;
}
