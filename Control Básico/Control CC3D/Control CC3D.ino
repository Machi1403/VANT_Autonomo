#include <sha1.h>
uint8_t *hash;
#include <Servo.h>
/*****************************DECLARAR VARIABLES A USAR*****************************/
Servo picht;
Servo roll;
Servo yaw;
Servo flight;
Servo accesorio;
Servo throttle; 
/*****************************INICIALIZACIÓN DE VALORES ÓPTIMOS*****************************/   
int aux=0;
int lectura=0;
int outputValue_throttle=43;
int outputValue_picht=89;
int outputValue_roll=90;
int outputValue_yaw=91;
int outputValue_flight=45;
int outputValue_accesorio=42;


char men[40];
String st="";
String val_a="86f7e437faa5a7fce15d1ddcb9eaeaea377667b8";
String val_d="3c363836cf4e16666669a25da280a1865c2d2874";
String val_t="8efd86fb78a56a5145ed7739dcb00c78581c5375";
String val_p="516b9783fca517eecbd1d064da2d165310b19759";
String val_r="4dc7c9ec434ed06502767136789763ec11d2c4b7";
String val_y="95cb0bfd2977c761298d9624e4b4d4c72a39974a";

//char ay[40];
/*String vala
String vald
String valt
String valp
String valr
String valy*/
/*****************************CONFIGURACIÓN INICIAL*****************************/
void setup() 
{ 
  //codificar();
  //m="86f7e437faa5a7fce15d1ddcb9eaeaea377667b8";
/*****************************DEFINICIÓN DE PINES*****************************/
  roll.attach(8);
  picht.attach(9);
  throttle.attach(10);  
  yaw.attach(11);
  flight.attach(12);
  accesorio.attach(13);
  /*****************************COMUNICACIÓN SERIAL*****************************/
  Serial.begin(9600);
  Serial.println("conectado");
  Serial1.begin(9600);
  //men.reserve(40);
  /*****************************ENVIO DE PARAMETROS INICIALES*****************************/
  throttle.write(outputValue_throttle);
  picht.write(outputValue_picht);
  roll.write(outputValue_roll);
  yaw.write(outputValue_yaw);
  flight.write(outputValue_flight);
  accesorio.write(outputValue_accesorio);
  /*****************************ENVIO DE PARAMETROS INICIALES sha*****************************/
}


char validar(String mensaje)
{
  if(mensaje==val_a)
  {
    return ('a');
  }
  if(mensaje==val_d)
  {
    return ('d');
  }
  if(mensaje==val_p)
  {
    return ('p');
  }
  if(mensaje==val_r)
  {
    return ('r');
  }
  if(mensaje==val_y)
  {
    return ('y');
  }
  if(mensaje==val_t)
  {
    return ('t');
  }
}

/*****************************CICLO REPETITIVO*****************************/
void loop() 
{ 
  if(Serial1.available()>0)
  {
    st=Serial1.readString();
    lectura=validar(st);
  }  
  switch (lectura)
  {
    case 't':
      lectura = Serial.parseInt();
      outputValue_throttle = map(lectura, 0, 100, 56, 130);
      throttle.write(outputValue_throttle);
      //Serial.print(outputValue_throttle);  
      break;
    case 'p':
      lectura = Serial.parseInt();
      outputValue_picht = map(lectura, 0, 100, 72, 119);
      picht.write(outputValue_picht);              
      break;
    case 'r':
      lectura = Serial.parseInt();
      outputValue_roll = map(lectura, 0, 100, 72, 119);
      roll.write(outputValue_roll);             
    case 'y':
       lectura = Serial.parseInt();
       outputValue_yaw = map(lectura, 0, 100, 72, 119);
       yaw.write(outputValue_yaw);              
       break; 
    case 'a':
      Serial.println("ARMANDO...");
      armar();
      break;
    case 'd':
      Serial.println("DESARMANDO...");
      desarmar();
      break;
    default:
      Serial.println(lectura);
      break;
  }   
  lectura=0;
  throttle.write(outputValue_throttle);
  picht.write(outputValue_picht);
  roll.write(outputValue_roll);
  yaw.write(outputValue_yaw);
  flight.write(outputValue_flight);
  accesorio.write(outputValue_accesorio);
} 
void armar()
{
  for(int i = 42; i<= 138; i++)
  {
    accesorio.write(i);
    delay(5);
  } 
  outputValue_accesorio=139;
  accesorio.write(outputValue_accesorio);
  Serial.println("ARMADO");
  delay(1000);
  for(int j=0;j<4;j++)
  {
    verificar_throttle();
    delay(500);
  }
}
void desarmar()
{
  for(int i = 138; i>= 43; i--)
  {
    accesorio.write(i);
    delay(5);
  } 
  optimos();
  accesorio.write(outputValue_accesorio);
  throttle.write(outputValue_throttle);
  Serial.println("DESARMADO");
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
  outputValue_flight=45;
  outputValue_accesorio=42;
}
/*
void codificar()
{
  vala.toCharArray(val_a,40);
  vald.toCharArray(val_d,40);
  valr.toCharArray(val_r,40);
  valp.toCharArray(val_p,40);
  valy.toCharArray(val_y,40);
  valt.toCharArray(val_t,40);
}*/
