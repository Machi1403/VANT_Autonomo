//ReceptorDron.ino
#include <TinyGPS.h>
TinyGPS gps;
#include <sha1.h>
uint8_t *hash;
#include <Servo.h>

#include <Wire.h> 
#include <HMC5883L.h> 
HMC5883L compass; 
/*****************************DECLARAR VARIABLES A USAR*****************************/
#define inputRoll A0
#define inputPitch A1
#define inputThrottle A2
#define inputYaw A3
#define inputControlMode A4
#define inputAcc0 A5


Servo picht;
Servo roll;
Servo yaw;
Servo flight;
Servo accesorio;
Servo throttle; 

float flat, flon, falt;

float latitudInicial,longitudInicial;

bool newData; 
bool controlArduino;

float arrayLon[10];
float arrayLat[10];
int cantidadCoordenadas;
/*****************************INICIALIZACIÓN DE VALORES ÓPTIMOS*****************************/   
int aux=0;
int lectura=0;
int outputValue_throttle=43;
int outputValue_picht=89;
int outputValue_roll=90;
int outputValue_yaw=91;
int outputValue_flight=980;
int outputValue_accesorio=42;

int timeH;

char men[40];
String st="";

String val_a="86f7e437faa5a7fce15d1ddcb9eaeaea377667b8";
String val_q="22ea1c649c82946aa6e479e1ffd321e4a318b1b0";

String val_e="58e6b3a414a1e090dfc6029add0f3555ccba127f";
String val_d="3c363836cf4e16666669a25da280a1865c2d2874";

String val_s="a0f1490a20d0211c997b44bc357e1972deab8ae3";
String val_f="4a0a19218e082a343a1b17e5333409af9d98f0f5";

String val_i="042dc4512fa3d391c5170cf3aa61e6a638f84342";
String val_k="13fbd79c3d390e5d6585a21e11ff5ec1970cff0c";

String val_j="5c2dd944dde9e08881bef0894fe7b22a5c9c4b06";
String val_l="07c342be6e560e7f43842e2e21b774e61d85f047";

/*****************************CONFIGURACIÓN INICIAL*****************************/
void setup() 
{ 
/********************DEFINICIÓN DE PINES**********************/
  roll.attach(8);
  picht.attach(9);
  throttle.attach(10);  
  yaw.attach(11);
  flight.attach(12);
  accesorio.attach(13);

  pinMode(inputRoll, INPUT);
  pinMode(inputPitch, INPUT);
  pinMode(inputThrottle, INPUT);
  pinMode(inputYaw, INPUT);
  pinMode(inputControlMode, INPUT);
  pinMode(inputAcc0, INPUT);
  /******************COMUNICACIÓN SERIAL**********************/
  Serial.begin(9600);
  Serial.println("conectado");
  Serial1.begin(9600);
  Serial1.setTimeout(200);
  Serial2.begin(9600); 
  /*****************************ENVIO DE PARAMETROS INICIALES*****************************/
  throttle.write(outputValue_throttle);
  picht.write(outputValue_picht);
  roll.write(outputValue_roll);
  yaw.write(outputValue_yaw);
  flight.writeMicroseconds(outputValue_flight);
  accesorio.write(outputValue_accesorio);

  controlArduino=true;
  /*****************************ENVIO DE PARAMETROS INICIALES sha*****************************/


  Wire.begin(); 
  compass = HMC5883L(); 
  compass.SetScale(1.3); 
  compass.SetMeasurementMode(Measurement_Continuous); 
}

int posGPS(float flat, float flon, float falt)
{
  newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial2.available())
    {
      char c = Serial2.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
  if (newData)
  {
    //float flat, flon, falt;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &falt, &age);
    Serial.print("Coordenadas;");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(";");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(";");
    Serial.println(falt);
    return 1;
  }
  gps.stats(&chars, &sentences, &failed);
  if (chars == 0)
  {
    Serial.println("Error;GPS1");
  }
}

void armar()
{
  while(posGPS(flat, flon, falt)==0)
  {
    Serial.println("Error;GPS2");
  }
  posicionInicial();
  for(int i = 42; i<= 138; i++)
  {
    accesorio.write(i);
    delay(5);
  } 
  outputValue_accesorio=139;
  accesorio.write(outputValue_accesorio);
  Serial.println("E;Ensamblando");
  delay(500);
  for(int j=0;j<4;j++)
  {
    verificar_throttle();
    delay(500);
  }
  Serial.println("E;Armado");
}
void desarmar()
{
  Serial.println("E;Desensamblando");
  for(int i = 138; i>= 45; i--)
  {
    accesorio.write(i);
  } 
  optimos();
  accesorio.write(outputValue_accesorio);
  throttle.write(outputValue_throttle);
  Serial.println("E;Desarmado");
}
void verificar_throttle()
{
  for(int i=outputValue_throttle;i<=outputValue_throttle+30;i++)
  {
    throttle.write(i);
    delay(5);
  }
  for(int j=outputValue_throttle+30;j>=outputValue_throttle;j--)
  {
    throttle.write(j);
    delay(5);
  }
}
void optimos()
{
  outputValue_throttle=43;
  outputValue_picht=89;
  outputValue_roll=90;
  outputValue_yaw=91;
  outputValue_flight=980;
  outputValue_accesorio=42;
}
char validar(String mensaje)
{
  if(mensaje==val_a)
  {
    return ('a');
  }
  if(mensaje==val_q)
  {
    return ('q');
  }

  if(mensaje==val_e)
  {
    return ('e');
  }
  if(mensaje==val_d)
  {
    return ('d');
  }

  if(mensaje==val_s)
  {
    return ('s');
  }
  if(mensaje==val_f)
  {
    return ('f');
  }

  if(mensaje==val_i)
  {
    return ('i');
  }
  if(mensaje==val_k)
  {
    return ('k');
  }

  if(mensaje==val_j)
  {
    return ('j');
  }
  if(mensaje==val_l)
  {
    return ('l');
  }
  else
  {
    return('c');
  }

}
bool alertaDistacia(float lat1, float lon1)
{
  posGPS(flat,flon,falt);
  //Se calcula la distancia entre el punto de partida y el actual
  float distancia=gps.distance_between(lat1,lon1,flat,flon);
  //Si la distancia es mayor a 700 mts el VANT se acerca al punto de partida
  if(distancia>700)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool metodoDeControl()
{
  //True para control
  //False para arduino
  if(controlArduino==true && pulseIn(inputControlMode, HIGH)>940 && pulseIn(inputControlMode, HIGH)<1500 && pulseIn(inputThrottle,HIGH)>1500 && pulseIn(inputAcc0, HIGH)> 1600)
  {
    controlArduino=false;
    Serial.println("M;RadioControl");
    return true;
  }
  if(pulseIn(inputControlMode, HIGH)<1600 && controlArduino==false)
  {
    controlArduino=true;
    Serial.println("M;Arduino");
    return false;
  }
}
void vueloAutonomo(float lat1,float lon1,float lat2,float lon2)
{
  dirigir(lat2,lon2);
  volarHacia(lat2,lon2);
}
void acercarHacia(float lat2, float lon2)
{
  dirigir(lat2,lon2);
  posGPS(flat,flon,falt);
  /*Una vez alcanzado el ángulo deseado se procede a 
  avanzar hacia el punto de origen hasta que la distancia
  actual con el punto de origen sea de 600 metros*/
  while(gps.distance_between(flat,flon,lat2,lon2)<=600)
  {
    throttle.writeMicroseconds(1550);
    picht.writeMicroseconds(1600);
    
  }
}
void volarHacia(float lat2, float lon2)
{ 
  posGPS(flat,flon,falt);
  float auxlat=falt,auxlon=flon;
  while(gps.distance_between(flat,flon,lat2,lon2)>5.0 && !alertaDistacia(latitudInicial,longitudInicial))
  {
    throttle.writeMicroseconds(1550);
    picht.writeMicroseconds(1600);
    posGPS(flat,flon,falt);
    if(gps.distance_between(flat,flon,auxlat,auxlon)>10)
    {
      auxlat=flat;
      auxlon=flon;
      dirigir(lat2,lon2);
    }
  }
  if(alertaDistacia(latitudInicial,longitudInicial))
  {
    acercarHacia(latitudInicial,longitudInicial);
  }
}
void dirigir(float lat2, float lon2)
{
  /*En este proceso primero se debe fijar el ángulo al que 
  se debe apuntar respecto al norte para dirigirse al punto
  de origen.*/
  posGPS(flat,flon,falt);
  float angulo=gps.course_to (flat, flon, lat2, lon2);
  /*Ahora se verifica a que ángulo se apunta actualmente*/
  float anguloActual=brujula();
  /*Se apunta al ángulo del punto de origen por el lado más
  conveniente (giro más corto).
  yaw.writeMicroseconds(X) gira el VANT, sea hacia la izquierda
  o hacia la derecha según convenga*/
  if(angulo-anguloActual>0)
  {
    while(brujula()!=angulo+5.0||brujula()!=angulo-5.0)
    {
      yaw.writeMicroseconds(1280);
      throttle.writeMicroseconds(1550);
    }  
  }
  else
  {
    while(brujula()!=angulo+5.0||brujula()!=angulo-5.0)
    {
      yaw.writeMicroseconds(1620);
      throttle.writeMicroseconds(1550);
    } 
  }
}
float brujula()
{
  MagnetometerRaw raw = compass.ReadRawAxis(); 
  MagnetometerScaled scaled = compass.ReadScaledAxis(); 
  float xHeading = atan2(scaled.YAxis, scaled.XAxis); 
  float yHeading = atan2(scaled.ZAxis, scaled.XAxis); 
  float zHeading = atan2(scaled.ZAxis, scaled.YAxis); 
  if(xHeading < 0) xHeading += 2*PI; 
  if(xHeading > 2*PI) xHeading-= 2*PI; 
  if(yHeading < 0) yHeading += 2*PI; 
  if(yHeading > 2*PI) yHeading-= 2*PI; 
  if(zHeading < 0) zHeading += 2*PI; 
  if(zHeading > 2*PI) zHeading-= 2*PI; 
  float xDegrees = xHeading * 180/M_PI; 
  float yDegrees = yHeading * 180/M_PI; 
  float zDegrees = zHeading * 180/M_PI; 
  Serial.print("Brujula;");
  Serial.println(xDegrees);
  return xDegrees;
  /*Serial.print(xDegrees); 
  Serial.print(","); 
  Serial.print(yDegrees); 
  Serial.print(","); 
  Serial.print(zDegrees); 
  Serial.println(";");*/
}
void posicionInicial()
{
  posGPS(flat,flon,falt);
  longitudInicial=flon;
  latitudInicial=flat;
}
int separarCoordenadas()
{
  cantidadCoordenadas=0;
  int cantidadCaracteres;
  cantidadCaracteres=st.length();
  String auxCoordenadas=" ";
  for(int i=0;i>=cantidadCaracteres;i=i+20)
  {
    cantidadCoordenadas++;
    auxCoordenadas=st.substring(i,i+10);
    arrayLat[i/10]=auxCoordenadas.toFloat();
    auxCoordenadas=st.substring(i+10,i+20);
    arrayLon[i/10]=auxCoordenadas.toFloat();
  }
  return cantidadCoordenadas;
}
void coordenadas()
{
  int CantCoordenadas=separarCoordenadas();
  //posicionInicial();
  for(int i=0;i<=CantCoordenadas;i++)
  {
    posGPS(flat,flon,falt);
    vueloAutonomo(flat,flon,arrayLat[i],arrayLon[i]);
  }
}
/*****************************CICLO REPETITIVO*****************************/
void loop() 
{
  posGPS(flat, flon,falt);
  if(metodoDeControl())
  {
    roll.writeMicroseconds(pulseIn(inputRoll,HIGH));
    picht.writeMicroseconds(pulseIn(inputPitch,HIGH));
    throttle.writeMicroseconds(pulseIn(inputThrottle,HIGH));
    yaw.writeMicroseconds(pulseIn(inputYaw,HIGH));
    flight.writeMicroseconds(outputValue_flight);
    accesorio.writeMicroseconds(pulseIn(inputAcc0,HIGH));

    if(pulseIn(inputAcc0, HIGH)<1600)
    {
        Serial.println("E;Desarmado");
    }
  }
  else
  {
    lectura=0;
    int i=43;
    if(Serial1.available()>0)
    {
      st=Serial1.readString();
      lectura=validar(st);
    }  
    switch (lectura)
    {
      int salida;
      case 'e':
        for(i=outputValue_throttle;i<=(outputValue_throttle+10);i++)
        {
          throttle.write(i);
          delay(10);
        }
        outputValue_throttle=i;
        break;
      case 'd':
        for(i=outputValue_throttle;i>=(outputValue_throttle-10);i--)
        {
          throttle.write(i);
          delay(10);
        }
        outputValue_throttle=i;
        break;

      case 'f':
        for(int j=outputValue_yaw;j<=115;j++)
        {
          yaw.write(j);
          delay(50);
        }
        break;
      case 's':
        //salida = int(map(10, 0, 100,43,outputValue_yaw));
        for(int j=outputValue_yaw;j>=67;j--)
        {
          yaw.write(j);
          delay(50);
        }
        break;

      case 'i':
        for(int j=outputValue_picht;j<=114;j++)
        {
          picht.write(j);
          delay(50);
        }    
        break;
      case 'k':
        for(int j=outputValue_picht;j>=64;j--)
        {
          picht.write(j);
          delay(50);
        }
        break;

      case 'j':
        for(int j=outputValue_roll;j>=65;j--)
        {
          roll.write(j);
          delay(50);
        } 
        break;
      case 'l':
        for(int j=outputValue_roll;j<=115;j++)
        {
          roll.write(j);
          delay(50);
        }  
        break;


      case 'a':
        Serial.println("ARMANDO...");
        armar();
        break;
      case 'q':
        Serial.println("DESARMANDO...");
        desarmar();
        break;

      case 'c':
        //float arrayLat[10];
        //float arrayLong[10];
        coordenadas();
        break;
      default:
        throttle.write(outputValue_throttle);
        picht.write(outputValue_picht);
        roll.write(outputValue_roll);
        yaw.write(outputValue_yaw);
        flight.writeMicroseconds(outputValue_flight);
        accesorio.write(outputValue_accesorio);
        break;
    }
















  }   
} 
