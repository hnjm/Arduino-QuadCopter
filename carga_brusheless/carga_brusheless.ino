#include <Servo.h> 
#define PINMOTOR1 1      //pin conectado al ESC, en este caso CH_5 en ARDUPILOT corresponde al pin 8
#define PINMOTOR2 2      //pin conectado al ESC, en este caso CH_5 en ARDUPILOT corresponde al pin 8
#define PINMOTOR3 3      //pin conectado al ESC, en este caso CH_5 en ARDUPILOT corresponde al pin 8
#define PINMOTOR4 4      //pin conectado al ESC, en este caso CH_5 en ARDUPILOT corresponde al pin 8

#define MAXIMOPWM 300   // Son grados Podia llegar hasta 180,paramas seguridad lo dejo bajo
#define MINIMOPWM 10   //   por si acaso empezar con un valor inferior, mi motor no arranca hasta 65
#define  PASO 1    // Incrementos del teclado
#define  BAUD 9600   //velocidad puerto serial   funciona hasta 38400

int pulsoMotor;
int ordenTeclado=0;
Servo myservo1;  // creamos el motor como elemento en la libreria          
Servo myservo2;  // creamos el motor como elemento en la libreria          
Servo myservo3;  // creamos el motor como elemento en la libreria          
Servo myservo4;  // creamos el motor como elemento en la libreria          
byte recibiendoByte ;
int recibiendoByteCalibrar=0;
boolean iniciado = false;
void setup() 
{ 

  Serial.begin(BAUD);
  myservo1.attach(PINMOTOR1);  // inicializo el ESC en el pin determinado
  myservo2.attach(PINMOTOR2);  // inicializo el ESC en el pin determinado
  myservo3.attach(PINMOTOR3);  // inicializo el ESC en el pin determinado
  myservo4.attach(PINMOTOR4);  // inicializo el ESC en el pin determinado
  Serial.println(" Comienzo del test");  //
  Serial.println (" Pulsar 'A' para arrancar \n Cuando escuche el pitido de confirmacion");
  while ( iniciado==false ){
    myservo1.write(0);   // Aramado
    myservo2.write(0);   // Aramado
    myservo3.write(0);   // Aramado
    myservo4.write(0);   // Aramado
    recibiendoByte = Serial.read(); // Leemos el Byte recibido
    if (recibiendoByte == 65 || recibiendoByte ==97) {    // A o a  Mayusculas o minusculas
      iniciado=true;
      Serial.println("inicio del loop principal arranque  \n Para subir controlar velocidad pulse \n    'A' para subir \n    'Z' para bajar \n    'S' para terminar Stop \n");
    }
  }
  
}
void loop(){
  ordenTeclado =OrdenSubirBajar ();
  if (ordenTeclado != 0) {       // Distinto de Cero
    pulsoMotor = pulsoMotor + ordenTeclado;
    pulsoMotor= constrain( pulsoMotor , MINIMOPWM, MAXIMOPWM); //
    myservo1.write(pulsoMotor); //Mientras no hay cambios,automaticamente  se siguen enviando los mismos pulsos
    myservo2.write(pulsoMotor); //Mientras no hay cambios,automaticamente  se siguen enviando los mismos pulsos
    myservo3.write(pulsoMotor); //Mientras no hay cambios,automaticamente  se siguen enviando los mismos pulsos
    myservo4.write(pulsoMotor); //Mientras no hay cambios,automaticamente  se siguen enviando los mismos pulsos
    Serial.print("Velocidad del pulso-->  ");
    Serial.println (pulsoMotor);
  }

  delay (200);   //delay para no colapsar
} 

int OrdenSubirBajar (){
  int  orden=0;
    if (Serial.available() > 0) {
      recibiendoByte = Serial.read(); // Leemos el Byte recibido
      if (recibiendoByte == 65 || recibiendoByte ==97) {    // A o A  Mayusculas o minusculas
        Serial.println( " SUBIR");
        orden = PASO;
      }
      if (recibiendoByte == 90 || recibiendoByte ==122) { // Z o z    Mayusculas o minisculas
        Serial.println( " BAJAR");
        orden = -PASO;
      }
      if (recibiendoByte == 83  || recibiendoByte == 115){ // t o T    Mayusculas o minisculas
        Serial.println( " Stop!!");
        orden = -(pulsoMotor- MINIMOPWM);   // Deja el pulso en MINIMOPWM
      }
    }
    return (orden);
}

