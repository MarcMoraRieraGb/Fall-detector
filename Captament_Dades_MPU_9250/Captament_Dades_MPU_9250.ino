//
 //
 // Desarrolladores de este código:
 //
 // - Xavier Vilanova Barrio - 2022
 //
 // - Marc Mora Riera - 2022
 //
 //
 // Este programa utiliza de base el Programa Sensores de: JUAN PALOMARES MOYANO - 2019
 //
 // No se permite la distribución, la utilización o la venta de este código sin el permiso de los desarrolladores
 //
 //
 /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 /*~~~~~~~~~~LIBRERÍAS~~~~~~~~~~*/
 /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
 //Conexionados UART e I2C
 #include <Wire.h>
 #include "SoftwareSerial.h"
 #include "WiFi.h"
 #include "ESPAsyncWebServer.h"
 //IMU
 #include "MPU6050_6Axis_MotionApps20.h" //Mediante esta biblioteca se pueden obtener datos del DMP (Digital Motion Processor) de la IMU
 #include "I2Cdev.h" //Mediante esta biblioteca se pueden obtener datos del DMP de la 
IMU
 #include "helper_3dmath.h" //Mediante esta biblioteca se pueden realizar operaciones de cuaterniones
 #define MPU9250_ADDRESS 0x68 //Es la MPU6050 Pero definida amb un altre nom
 
 /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 /*~~~DEFINICIÓN DE VARIABLES~~~*/
 /*~~~~~~~Y CONSTANTES~~~~~~~~~~*/
 /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 const char* ssid = "ESP32-Access-Point";
 const char* password = "123456789";
 const float pi = 3.141592653;
 
 AsyncWebServer server(80);
 
 //IMU
 const int mpuAddress = 0x68; // Se define la dirección de la IMU, puede ser 0x68 o 0x69
 MPU6050 mpu(mpuAddress); //Se crea un objeto MPU6050 para poder extraer datos de la DMP
 int fifoCount = 0, packetSize; //Se crea un contador de 
valores en el FIFO de la MPU y el tamaño del paquete que obtendremos
 byte fifoBuffer[42]; //Se crea el buffer que se 
utilizará para obtener los datos roll, pitch y yaw.
 float roll, pitch, yaw, sqx, sqy, sqz, sqw, test; //Se crea tanto las variables de roll, pitch y yaw como las variables "float"
 bool inici = false; //Variable booleana que decidira quan enviem les dades
 int16_t ax, ay, az; //intermedias necesarias para obtenerlas
 long espera = 50; //Tiempo Espera de enviamientos de datos en ms
 Quaternion q; //Se crea el cuaternión necesario para obtener los valores de pitch, yaw y roll
 int mostrae = 0;
 int boto = 15; //Variable que sirve para definir el pin del boton
 int mostra;
 float ax_m_s2, ay_m_s2, az_m_s2;
 int16_t gx, gy, gz;
 
 

 
 /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~* /
 /*~~~~~~~~~~~~SETUP~~~~~~~~~~~~*/
 /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 //Función que se devuelve lo que queremos enviar
 String readAcc() {
 
 //Serial.println("enviament");
 return String((String(yaw) + "/t" + String(pitch) + "/t" + String(roll) + "/t" + String(q.x) + "/t" + String(q.y) + "/t" + String(q.z) + "/t" + String(q.w) + "/t" + String(ax) + "/t" + String(ay) + "/t"  String(az) + "/t" + String(gx) + "/t" + String(gy) + "/t" + String(gz) + "/t" + String(mostra)));
 }
 
 void setup()
 {
 //PUERTO SERIE
 Serial.begin(115200); //abrimos el puerto serie
 pinMode (boto, INPUT_PULLDOWN); //definimos el boton
 Wire.begin(); //Se inicializa la librería Wire.h
 
 //IMU
 mpu.initialize(); //Inicialización de la imu
 mpu.dmpInitialize(); //Inicialización del DMP
 mpu.setDMPEnabled(true); //Habilitación del DMP
 packetSize = mpu.dmpGetFIFOPacketSize(); //Se obtiene el tamaño del paquete que 
obtendremos del DMP (42)
 
 //Se introducen los offsets calculados mediante MPU6050_calibration
 mpu.setXAccelOffset(5444);
 mpu.setYAccelOffset(6328);
 mpu.setZAccelOffset(9715);
 mpu.setXGyroOffset(5);
 mpu.setYGyroOffset(-13);
 mpu.setZGyroOffset(37);
 
 //Se define el cuaternión inicial de actitud
 q.w = 1;
 q.x = 0;
 q.y = 0;
 q.z = 0;
 Serial.println("Debug");
 
 // Setting the ESP as an access point
 Serial.print("Setting AP (Access Point)…");
// Remove the password parameter, if you want the AP (Access Point) to be open
WiFi.softAP(ssid, password);
 
 IPAddress IP = WiFi.softAPIP();
 
 Serial.print("AP IP address: ");
 Serial.println(IP);
 
 server.on("/Acceleracio", HTTP_GET, [](AsyncWebServerRequest * request) {
 request->send_P(200, "text/plain", readAcc().c_str());
 });
 
 bool status;
 // Start server
 server.begin();
 
 }
 void loop()
 {
 IMU();
 }
