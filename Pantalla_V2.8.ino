/**
 * Codigo para pantalla de sistema de llamado de enfermeras ATENTO
 * Lee información enviada por serial dedse consola mediante protocolo propietario
 * Recibe letra h para imprimir hora enviada desde consola
 * Recibe letra a para imprimir caracteres estaticos con sondigo grave
 * Recibe letra v para imprimir caracteres moviles de arriba abajo con sondigo Agudo
 * Recibe letra m para imprimir mensajes pregrabados con prioridad en alertas 
 * 
 * Version:               2.8
 * Fecha de modificacion: 17/10/20
 * Creado por:            Fabian Garzon
 * Editado ultima vez:    Boris Urrea
 * Correo:                borisan999@gmail.com
**/
#include "RTClib.h"
#include <Wire.h>
#include <MaxMatrix.h> #include <avr/pgmspace.h>

  PROGMEM unsigned char const CH[] = {
  3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
  1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
  3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
  5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
  4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
  5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
  5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
  1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
  3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
  3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
  5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
  5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
  2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
  4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
  2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
  4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
  3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
  4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
  4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
  4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
  4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
  4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
  4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
  4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
  4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
  2, 8, B01001000, B00000000, B00000000, B00000000, B00000000, // :
  2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
  3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
  3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
  3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
  4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
  5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
  4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
  4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
  4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
  4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
  4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
  4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
  4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
  4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
  3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
  4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
  4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
  4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
  5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
  5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
  4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
  4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
  4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
  4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
  5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
  4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
  5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
  5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
  5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
  5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
  4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
  2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
  4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
  2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
  3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
  4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
  2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
  4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
  4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
  4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
  4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
  4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
  3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
  4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
  4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
  3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
  4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
  4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
  3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
  5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
  4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
  4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
  4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
  4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
  4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
  4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
  3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
  4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
  5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
  5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
  5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
  4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
  3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
  3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
  1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
  3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
  4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
  };
  int duracion=50; //Duracion del sonido
  bool DEBUG=true;
  bool PANTALLA_MAESTRA=true;
  int VEL_LED=600;  

  int duracion3=5; //Duracion del sonido
  int parlante =9;
  int lamparaazul=66;
  int data = 12;    // DIN pin del modulo MAX7219
  int load = 11;    // CS pin del modulo MAX7219
  int clock = 10;  // CLK pin del modulo MAX7219 
  int maxInUse = 9;    //el tamaño del display es de 9 cuadros 
  MaxMatrix m(data, load, clock, maxInUse); // Define el modulo
  byte buffer[10]; 
  RTC_DS1307 RTC;
  const byte numChars = 60;
  char receivedChars[numChars]; // an array to store the received data
  char charBuf2[250];
  char charBuf3[16];
  boolean newData = false;
  int msnno=1;
  String chunk;
  int mensaptr=0;
  int msnlen=0;
  char * item2;
  char * item;
  int combinedlen=0;
  int back=0;
  /*
  char mensaje1[] = " En caso de emergencia recuerde que el Hospital Universitario Mayor tiene dos puntos de encuentro: Uno ubicado en la rotonda de la entrada principal y el otro en el parqueadero de ambulancias sobre la carrera 30.";
  char mensaje2[] = " En caso de emergencia no use el ascensor. Utilice las escaleras mas cercanas y circule por la derecha.                   ";
  char mensaje3[] = " En caso de emergencia identifique al lider de evacuacion y brigadistas del area donde se encuentra y siga atentamente sus instrucciones.                   ";
  char mensaje4[] = " En caso de cualquier emergencia que se presente en el Hospital Universitario Mayor, comuniquese desde cualquier telefono a la extension 4123. Identifiquese e informe el hecho que se presenta.                   ";
  char mensaje5[] = " En Mederi manejamos los residuos de forma adecuada. Recuerde que en la caneca gris solo se deben depositar los residuos reciclables: papel seco, carton, periodico.                   ";
  char mensaje6[] = " En Mederi manejamos los residuos de forma adecuada. Recuerde que en la caneca verde solo se deben depositar los residuos no reciclables, tales como toallas para el secado de manos, empaques de alimentos y restos de comida.                   ";
  char mensaje7[] = " La higiene de manos en los hospitales ha salvado millones de vidas. En Mederi nos lavamos las manos.                   ";
  char mensaje8[] = " El 80 porciento de las infecciones pueden ser evitadas por medio de una buena higiene de manos. En Mederi nos lavamos las manos.                   ";
  char mensaje9[] = " Estimado empleado y colaborador recuerde y practique siempre los cinco momentos para la higiene de manos.                   ";
  char mensaje10[] = " Estimado empleado y colaborador recuerde que en Mederi todos cuidamos de las instalaciones. Por favor informe oportunamente a mantenimiento los danos que se presenten en equipos e infraestructura.                   ";
  char mensaje11[] = " En Mederi todos cuidamos de las instalaciones. Por favor cuide las zonas verdes y no arroje papeles en ellas.                   ";
  char mensaje12[] = " En Mederi todos cuidamos de las instalaciones y los recursos disponibles. Por favor no se siente en las canecas y haga uso racional del agua y la luz.                   ";
  char mensaje13[] = " Estimado empleado y colaborador recuerde que en Mederi todos cuidamos de las instalaciones. Por favor mantenga los puestos de trabajo en adecuadas condiciones de orden y aseo.                   ";
  char mensaje14[] = " En Mederi todos cuidamos de las instalaciones. Recuerde que no esta permitido fumar en las instalaciones de los hospitales ni arrojar colillas de cigarrillo.                   ";
  char mensaje15[] = " Estimado empleado y colaborador reduzca el riesgo de infecciones asociadas a la atencion en salud. Laveses las manos siempre.                   ";
  char mensaje16[] = " El modelo de atencion de Mederi se centra en el paciente y la familia feliz, prestando una atencion oportuna, segura, sostenible y garantizando la mejora continua.                   ";
  char mensaje17[] = " Estimado empleado y colaborador recuerde que una atencion limpia es una atencion segura. En Mederi nos lavamos las manos.                   ";
  */
  
  String mensaje1 = "En caso de emergencia recuerde que el Hospital Universitario Mayor tiene dos puntos de encuentro: Uno ubicado en la rotonda de la entrada principal y el otro en el parqueadero de ambulancias sobre la carrera 30.                    ";
  String mensaje2 = "En caso de emergencia no use el ascensor. Utilice las escaleras mas cercanas y circule por la derecha.                   ";
  String mensaje3 = "En caso de emergencia identifique al lider de evacuacion y brigadistas del area donde se encuentra y siga atentamente sus instrucciones.                   ";
  String mensaje4 = "En caso de cualquier emergencia que se presente en el Hospital Universitario Mayor, comuniquese desde cualquier telefono a la extension 4123. Identifiquese e informe el hecho que se presenta.                   ";
  String mensaje5 = "En Mederi manejamos los residuos de forma adecuada. Recuerde que en la caneca gris solo se deben depositar los residuos reciclables: papel seco, carton, periodico.                   ";
  String mensaje6 = "En Mederi manejamos los residuos de forma adecuada. Recuerde que en la caneca verde solo se deben depositar los residuos no reciclables, tales como toallas para el secado de manos, empaques de alimentos y restos de comida.                   ";
  String mensaje7 = "La higiene de manos en los hospitales ha salvado millones de vidas. En Mederi nos lavamos las manos.                   ";
  String mensaje8 = "El 80 porciento de las infecciones pueden ser evitadas por medio de una buena higiene de manos. En Mederi nos lavamos las manos.                   ";
  String mensaje9 = "Estimado empleado y colaborador recuerde y practique siempre los cinco momentos para la higiene de manos.                   ";
  String mensaje10 = "Estimado empleado y colaborador recuerde que en Mederi todos cuidamos de las instalaciones. Por favor informe oportunamente a mantenimiento los danos que se presenten en equipos e infraestructura.                   ";
  String mensaje11 = "En Mederi todos cuidamos de las instalaciones. Por favor cuide las zonas verdes y no arroje papeles en ellas.                   ";
  String mensaje12 = "En Mederi todos cuidamos de las instalaciones y los recursos disponibles. Por favor no se siente en las canecas y haga uso racional del agua y la luz.                   ";
  String mensaje13 = "Estimado empleado y colaborador recuerde que en Mederi todos cuidamos de las instalaciones. Por favor mantenga los puestos de trabajo en adecuadas condiciones de orden y aseo.                   ";
  String mensaje14 = "En Mederi todos cuidamos de las instalaciones. Recuerde que no esta permitido fumar en las instalaciones de los hospitales ni arrojar colillas de cigarrillo.                   ";
  String mensaje15 = "Estimado empleado y colaborador reduzca el riesgo de infecciones asociadas a la atencion en salud. Laveses las manos siempre.                   ";
  String mensaje16 = "El modelo de atencion de Mederi se centra en el paciente y la familia feliz, prestando una atencion oportuna, segura, sostenible y garantizando la mejora continua.                   ";
  String mensaje17 = "Estimado empleado y colaborador recuerde que una atencion limpia es una atencion segura. En Mederi nos lavamos las manos.                   ";
   
  void setup(){
    delay(3000);
    pinMode(parlante,LOW); 
    pinMode(lamparaazul,LOW); 
    pinMode(lamparaazul,OUTPUT);       //PARLANTE 
    pinMode(9,OUTPUT);       //PARLANTE 
    pinMode(12,OUTPUT);      //Conexion a DIN
    pinMode(11,OUTPUT);      //Conexion a CS
    pinMode(10,OUTPUT);      //Conexion a CLK
    m.init();                // inicializa el modulo
    Serial1.begin(9600);   
    Serial.begin(9600); 
    m.init();  m.setIntensity(5);
    Wire.begin(); 
    RTC.begin(); 
    Serial.begin(9600); 
  }
int speakerPin = 9;
int length = 15; // the number of notes

//twinkle twinkle little star
char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
  
  void codigoazul()
  { 
    delay(400);
    duracion3;   
    tone(9,340,240);
    duracion3;   
  }
  void codigoverde()
  {  
    duracion3;   
    tone(9,1540,240);
    duracion3; 
    /*for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }*/
    ////////////SECCION PARA LAMPARA //////////////////
    digitalWrite(lamparaazul, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);              // wait for a second
    digitalWrite(lamparaazul, LOW);    // turn the LED off by making the voltage LOW
    delay(100);       
  }
  void loop()
  {
    int cont=0;
    delay(100);
    while(Serial1.available() > 0) // Protocolo para lectura de datos
    {
      memset(receivedChars, 0, sizeof(receivedChars));
      cont++;
      mensaptr=0;
      if(DEBUG==true)
      {
        Serial.println("Recive 1");
        delay(10);
      }
       delay(10);
       recvWithEndMarker();
       if( ( receivedChars[0] == '1' ) && ( receivedChars[1] == '2' ) && ( receivedChars[2] == '3' ) )
       {
          memset(receivedChars, 0, sizeof(receivedChars));
          if(PANTALLA_MAESTRA==true)
          {
            writeString("456");
          }
          delay(11);
          while(true)
          {
            cont++;
            delay(50);
            newData = false;
            recvWithEndMarker();
            if(DEBUG==true)
            {
              Serial.println("Recive 2");
              delay(50);
            }
            if(newData == true)
            {
              break;
            }
            if(cont>5)
            {
              memset(receivedChars, 0, sizeof(receivedChars));
              newData = false;
              break;   
            }
          }
       }
       if(DEBUG == true)
       {
         Serial.println(receivedChars);
         delay(50);
       }
       if(cont>5)
       {
         memset(receivedChars, 0, sizeof(receivedChars));
         newData = false;
         break;   
       }
       
    }// FIN de Protocolo para lectura de datos
    if(receivedChars[0] == 'm')//codigo m, imprime mensajes
    {
      if(DEBUG == true)
       {
         Serial.println("enra en m");
         delay(50);
       }
      m.setIntensity(6);  
      newData = false;   
      if(msnno==1)
      {
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje1.length(); i++) {
          if (mensaje1.substring(i, i+1) == " ") {
            String palabra=mensaje1.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                //reiniciomsn();
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==2){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje2.length(); i++) {
          if (mensaje2.substring(i, i+1) == " ") {
            String palabra=mensaje2.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                //reiniciomsn();
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==3){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje3.length(); i++) {
          if (mensaje3.substring(i, i+1) == " ") {
            String palabra=mensaje3.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==4){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje4.length(); i++) {
          if (mensaje4.substring(i, i+1) == " ") {
            String palabra=mensaje4.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==5){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje5.length(); i++) {
          if (mensaje5.substring(i, i+1) == " ") {
            String palabra=mensaje5.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==6){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje6.length(); i++) {
          if (mensaje6.substring(i, i+1) == " ") {
            String palabra=mensaje6.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==7){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje7.length(); i++) {
          if (mensaje7.substring(i, i+1) == " ") {
            String palabra=mensaje7.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==8){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje8.length(); i++) {
          if (mensaje8.substring(i, i+1) == " ") {
            String palabra=mensaje8.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==9){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje9.length(); i++) {
          if (mensaje9.substring(i, i+1) == " ") {
            String palabra=mensaje9.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==10){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje10.length(); i++) {
          if (mensaje10.substring(i, i+1) == " ") {
            String palabra=mensaje10.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(1000);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==11){
        combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje11.length(); i++) {
          if (mensaje11.substring(i, i+1) == " ") {
            String palabra=mensaje11.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==12){
      combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje12.length(); i++) {
          if (mensaje12.substring(i, i+1) == " ") {
            String palabra=mensaje12.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==13){
      combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje13.length(); i++) {
          if (mensaje13.substring(i, i+1) == " ") {
            String palabra=mensaje13.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==14){
      combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje14.length(); i++) {
          if (mensaje14.substring(i, i+1) == " ") {
            String palabra=mensaje14.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==15){
      combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje15.length(); i++) {
          if (mensaje15.substring(i, i+1) == " ") {
            String palabra=mensaje15.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==16){
      combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje16.length(); i++) {
          if (mensaje16.substring(i, i+1) == " ") {
            String palabra=mensaje16.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }else if(msnno==17){
      combinedlen=0;
        int palabraant=0;
        String msnpant="";
        for (int i = 0; i < mensaje17.length(); i++) {
          if (mensaje17.substring(i, i+1) == " ") {
            String palabra=mensaje17.substring(palabraant, i);
            palabraant = i+1;
            combinedlen=combinedlen+palabra.length()+1;
            if(combinedlen>=15)
            {
              combinedlen=0;
              msnpant.toCharArray(charBuf3, 16);
              printString("                       ");
              printString(charBuf3);
              delay(VEL_LED);
              printString("                       ");
              memcpy(charBuf3, 0, sizeof(charBuf3));
              msnpant="";
              combinedlen=combinedlen+palabra.length()+1;
              if(Serial1.available() > 0)
              {
                break;
              }
            }
            msnpant.concat(palabra);
            msnpant.concat(" ");
          }
        }
        reiniciomsn(); 
      }
    }
    if(newData == true)// Imprime en pantalla segun el caso
    {
      if(receivedChars[0] == 'a')//codigo a, imprime lo que se recive estatico con generaciòn de sonido grave
      {
        printString("                       ");
        char* ptr = receivedChars + 1;
        printString( ptr);
        codigoazul();
        delay(3000);
        printString("                       ");
        memset(receivedChars, 0, sizeof(receivedChars));
        newData = false; 
      }else if(receivedChars[0] == 'v')//codigo v, imprime lo que recive con animacion de arriba a abajo, sonando dos veces un sonido agudo
      {
        printString("                       ");
        char* ptr = receivedChars + 1;
        printString( ptr);
        codigoverde();
        m.setIntensity(8);            
        printString(ptr ); 
        for (int i=0; i<8; i++)
        {
          delay(30);
          m.shiftDown(true); // rotate = true = rotate within 8 bit block 
        }
        m.setIntensity(15);
        codigoverde();
        delay(2000);
        printString("                       ");
        memset(receivedChars, 0, sizeof(receivedChars));
        newData = false; 
      }
      /*else if(receivedChars[0] == 'x')//codigo v, imprime lo que recive con animacion de arriba a abajo, sonando dos veces un sonido agudo
      {
        char* ptr = receivedChars + 1;
        delay(10);
        m.clear(); 
        memset(receivedChars, 0, sizeof(receivedChars));
        newData = false; 
      }*/
      else if(receivedChars[0] == 'h')//codigo h, imprime hora enviada desde la consola
      {
        char* ptr = receivedChars + 1;
        m.setIntensity(8);  
        printString(ptr);
        delay(1000); 
        memset(receivedChars, 0, sizeof(receivedChars));
        newData = false; 
      }
    }
  } //fin del loop 
  

    
  void printStringWithShift(char* s, int shift_speed)
  {        // Imprime cadena de caracteres de mensajes en este micro 
    while (*s != 0)
    {
      printCharWithShift(*s, shift_speed); 
      s++;
     
    }  
  }

  void printString(char* s)  // Imprime cadena de manera estatica
  {   
    int col = 0;  
    while (*s != 0)
    {
      if (*s < 32) continue;
      char c = *s - 32;  
      memcpy_P(buffer, CH + 7*c, 7);  
      m.writeSprite(col, 0, buffer);  
      m.setColumn(col + buffer[0], 0); 
      col += buffer[0] + 1; 
      s++;
    }
  }
  void printCharWithShift(char c, int shift_speed ){    // Imprime caracter con corrimiento
    if (c < 32) 
      return;  
    c -= 32;
    memcpy_P(buffer, CH + 7*c, 7); 
    m.writeSprite(maxInUse*8, 0, buffer);
    m.setColumn(maxInUse*8 + buffer[0], 0); /*tomar el espacio entre caracteres*/
    for (int i=0; i<buffer[0]+1; i++)  
    {  
      delay(shift_speed);  
      m.shiftLeft(false, false); 
    } 
  }

  /*     
  void hora() // Imprime hora en pantalla
  { 
    DateTime now = RTC.now();
    char TimeNow[20] ;
    sprintf(TimeNow,"      %.2d:%.2d",now.hour(),now.minute());
    m.setIntensity(8);            
    printString(TimeNow);                     
    delay(50);
  }*/

  void reiniciomsn(){
    printString("                       ");
    memset(receivedChars, 0, sizeof(receivedChars));
    delay(50); 
    msnno++;
    if(msnno>=18)
    {
      msnno=1;
    }
    return;
  }
  void recvWithEndMarker() {//recibe datos por serial
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial1.available() > 0 && newData == false) {
      rc = Serial1.read();
      
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        ndx = 0;
        newData = true;
      }
    }
  }
  
  void writeString(String stringData) { // Escribe datos por serial  
    for (int i = 0; i < stringData.length(); i++)
    {
      Serial1.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
    }
    Serial1.write('\n');
  }// end writeString
