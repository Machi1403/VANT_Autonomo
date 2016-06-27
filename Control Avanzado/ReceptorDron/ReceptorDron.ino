//ReceptorDron.ino
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
  /******************COMUNICACIÓN SERIAL**********************/
  Serial.begin(9600);
  Serial.println("conectado");
  Serial1.begin(9600);
  Serial1.setTimeout(200); 
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

}

/*****************************CICLO REPETITIVO*****************************/
void loop() 
{
  lectura=0;
  if(Serial1.available()>0)
  {
    st=Serial1.readString();
    lectura=validar(st);
  }  
  switch (lectura)
  {
  	int salida;
    case 'e':
      outputValue_throttle = map(5, 0, 100, outputValue_throttle, 140);
      throttle.write(outputValue_throttle);
      break;
    case 'd':
      outputValue_throttle = map(5, 0, 100,43,outputValue_throttle);
      throttle.write(outputValue_throttle);
      break;

    case 's':
      salida = map(10, 0,100,outputValue_yaw,139);
      yaw.write(salida);
      break;
    case 'f':
      salida = map(10, 0, 100,43,outputValue_yaw);
      yaw.write(salida);
      break;

    case 'i':
      salida = map(10, 0, 100,outputValue_picht,160);
      picht.write(salida);
      break;
    case 'k':
      salida = map(10, 0, 100,42,outputValue_picht);
      picht.write(salida);
      break;

    case 'j':
      salida = map(10, 0, 100,outputValue_roll,160);
      roll.write(salida);
      break;
    case 'l':
      salida = map(5, 0, 100,43,outputValue_roll);
      roll.write(salida);
      break;


    case 'a':
      Serial.println("ARMANDO...");
      armar();
      break;
    case 'q':
      Serial.println("DESARMANDO...");
      desarmar();
      break;

    default:
      throttle.write(outputValue_throttle);
      picht.write(outputValue_picht);
      roll.write(outputValue_roll);
      yaw.write(outputValue_yaw);
      flight.write(outputValue_flight);
      accesorio.write(outputValue_accesorio);
      break;
  }   
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
  delay(500);
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