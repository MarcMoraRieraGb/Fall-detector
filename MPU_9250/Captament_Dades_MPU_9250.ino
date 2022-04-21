/*JUAN PALOMARES MOYANO - 2019*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~LIBRERÍAS~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Conexionados UART e I2C
#include <Wire.h>
#include "SoftwareSerial.h" 

//IMU
#include "MPU6050_6Axis_MotionApps20.h" //Mediante esta biblioteca se pueden obtener datos del DMP (Digital Motion Processor) de la IMU
#include "I2Cdev.h" //Mediante esta biblioteca se pueden obtener datos del DMP de la IMU
#include "helper_3dmath.h" //Mediante esta biblioteca se pueden realizar operaciones de cuaterniones

//GPS
#include "NMEAGPS.h"
#define    MPU9250_ADDRESS            0x68
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~DEFINICIÓN DE VARIABLES~~~*/
/*~~~~~~~Y CONSTANTES~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const float pi = 3.141592653;

//IMU
const int mpuAddress = 0x68;  // Se define la dirección de la IMU, puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress); //Se crea un objeto MPU6050 para poder extraer datos de la DMP
int fifoCount = 0, packetSize; //Se crea un contador de valores en el FIFO de la MPU y el tamaño del paquete que obtendremos
byte fifoBuffer[42]; //Se crea el buffer que se utilizará para obtener los datos roll, pitch y yaw.
float roll, pitch, yaw, sqx, sqy, sqz, sqw, test; //Se crea tanto las variables de roll, pitch y yaw como las variables "float"
                                                  //intermedias necesarias para obtenerlas
long espera=50;
Quaternion q; //Se crea el cuaternión necesario para obtener los valores de pitch, yaw y roll
int mostra=0;
bool inici=false;
const int boto = 15;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~SETUP~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void setup()
{
  Serial.begin(115200);
  //PUERTOS SERIE

  Wire.begin(); //Se inicializa la librería Wire.h
  
  //IMU
  mpu.initialize(); //Inicialización de la imu
  mpu.dmpInitialize(); //Inicialización del DMP
  mpu.setDMPEnabled(true); //Habilitación del DMP
  packetSize = mpu.dmpGetFIFOPacketSize(); //Se obtiene el tamaño del paquete que obtendremos del DMP (42)
  
  //Se introducen los offsets calculados mediante MPU6050_calibration
  mpu.setXAccelOffset(5566);
  mpu.setYAccelOffset(6324);
  mpu.setZAccelOffset(9765);
  mpu.setXGyroOffset(15);
  mpu.setYGyroOffset(-5);
  mpu.setZGyroOffset(-7);
  
  //Se define el cuaternión inicial de actitud
  q.w = 1;
  q.x = 0;
  q.y = 0;
  q.z = 0;

  //Configuració boto
  pinMode(boto, INPUT_PULLDOWN);
  
  delay(1000); //Se da un margen de tiempo para que todos los procesos se completen
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~LOOP~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void loop()
{
 // Serial.println("I2Cdev.h");
  IMU();

}
