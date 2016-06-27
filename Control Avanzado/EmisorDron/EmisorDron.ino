//EmisorDron.ino
#include <sha1.h>
uint8_t *hash;
char lectura;
void printHash(uint8_t* hash) 
{
	int j=0;
	for (j=0; j<20; j++) 
	{
		Serial1.write("0123456789abcdef"[hash[j]>>4]);
		Serial1.write("0123456789abcdef"[hash[j]&0xf]);
	}
}
void setup() 
{
	Serial.begin(9600);
	Serial.println("Conexion serial iniciada");
	Serial1.begin(9600);
}
void loop() 
{
  lectura=0;
	if(Serial.available()>0)
	{
		lectura = Serial.read();
		Sha1.init();
		Sha1.print(lectura);
    	printHash(Sha1.result());
		switch (lectura) 
		{
		    case 'a':
		    	Serial.println("Enviando comando de armado");
		      break;
		    case 'q':
		    	Serial.println("Enviando comando de desarmado");
		      break;
		    case 'e':
		    	Serial.println("Enviando comando de elevacion");
		      break;
		    case 'd':
		    	Serial.println("Enviando comando de descenso");
		      break;
		    case 'f':
		    	Serial.println("Enviando comando de rotacion derecha");
		      break;
		    case 's':
		    	Serial.println("Enviando comando de rotacion izquierda");
		      break;
		    case 'i':
		    	Serial.println("Enviando comando de inclinacion adelante");
		      break;
		    case 'k':
		    	Serial.println("Enviando comando de inclinacion atras");
		      break;
		    case 'l':
		    	Serial.println("Enviando comando de desplazamiento derecha");
		      break;
		    case 'j':
		    	Serial.println("Enviando comando de desplazamiento izquierda");
		      break;
		}
	}
}