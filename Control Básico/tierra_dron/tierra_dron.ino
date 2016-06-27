#include <sha1.h>
//tierra_dron.ino

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
	//Serial1.write('Z');
}

void setup() 
{
	Serial.begin(9600);
	Serial.println("Conexion serial iniciada");
	Serial1.begin(9600);
        //Serial1.write("Conexion serial iniciada");
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
		    case 'd':
		    	Serial.println("Enviando comando de desarmado");
		      break;
		    case 't':
		    	Serial.println("Enviando comando de elevacion");
		      break;
		    case 'y':
		    	Serial.println("Enviando comando de inclinacion");
		      break;
		    case 'p':
		    	Serial.println("Enviando comando de desplazamiento");
		      break;
		    case 'r':
		    	Serial.println("Enviando comando de giro");
		      break;
		}
	}
}
