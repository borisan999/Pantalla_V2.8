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
  bool PANTALLA_MAESTRA=false;
  int VEL_LED=50;  

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
  boolean newData = false;
  int msnno=1;
  
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
  
  /*
  String mensaje1 = " En caso de emergencia recuerde que el Hospital Universitario Mayor tiene dos puntos de encuentro: Uno ubicado en la rotonda de la entrada principal y el otro en el parqueadero de ambulancias sobre la carrera 30.                   ";
  String mensaje2 = " En caso de emergencia no use el ascensor. Utilice las escaleras mas cercanas y circule por la derecha.                   ";
  String mensaje3 = " En caso de emergencia identifique al lider de evacuacion y brigadistas del area donde se encuentra y siga atentamente sus instrucciones.                   ";
  String mensaje4 = " En caso de cualquier emergencia que se presente en el Hospital Universitario Mayor, comuniquese desde cualquier telefono a la extension 4123. Identifiquese e informe el hecho que se presenta.                   ";
  String mensaje5 = " En Mederi manejamos los residuos de forma adecuada. Recuerde que en la caneca gris solo se deben depositar los residuos reciclables: papel seco, carton, periodico.                   ";
  String mensaje6 = " En Mederi manejamos los residuos de forma adecuada. Recuerde que en la caneca verde solo se deben depositar los residuos no reciclables, tales como toallas para el secado de manos, empaques de alimentos y restos de comida.                   ";
  String mensaje7 = " La higiene de manos en los hospitales ha salvado millones de vidas. En Mederi nos lavamos las manos.                   ";
  String mensaje8 = " El 80 porciento de las infecciones pueden ser evitadas por medio de una buena higiene de manos. En Mederi nos lavamos las manos.                   ";
  String mensaje9 = " Estimado empleado y colaborador recuerde y practique siempre los cinco momentos para la higiene de manos.                   ";
  String mensaje10 = " Estimado empleado y colaborador recuerde que en Mederi todos cuidamos de las instalaciones. Por favor informe oportunamente a mantenimiento los danos que se presenten en equipos e infraestructura.                   ";
  String mensaje11 = " En Mederi todos cuidamos de las instalaciones. Por favor cuide las zonas verdes y no arroje papeles en ellas.                   ";
  String mensaje12 = " En Mederi todos cuidamos de las instalaciones y los recursos disponibles. Por favor no se siente en las canecas y haga uso racional del agua y la luz.                   ";
  String mensaje13 = " Estimado empleado y colaborador recuerde que en Mederi todos cuidamos de las instalaciones. Por favor mantenga los puestos de trabajo en adecuadas condiciones de orden y aseo.                   ";
  String mensaje14 = " En Mederi todos cuidamos de las instalaciones. Recuerde que no esta permitido fumar en las instalaciones de los hospitales ni arrojar colillas de cigarrillo.                   ";
  String mensaje15 = " Estimado empleado y colaborador reduzca el riesgo de infecciones asociadas a la atencion en salud. Laveses las manos siempre.                   ";
  String mensaje16 = " El modelo de atencion de Mederi se centra en el paciente y la familia feliz, prestando una atencion oportuna, segura, sostenible y garantizando la mejora continua.                   ";
  String mensaje17 = " Estimado empleado y colaborador recuerde que una atencion limpia es una atencion segura. En Mederi nos lavamos las manos.                   ";
    */
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
      /*m.clear();*/
      //printString("                       ");
      m.setIntensity(2);  
      newData = false;   
      if(msnno==1)
      {
          //chunk = mensaje1.substring(mensaptr*10);
          //chunk.toCharArray(charBuf, 11);
        //mensaje1.toCharArray(charBuf2, 250);
        memcpy(charBuf2, mensaje1, sizeof(charBuf2));
          /*if((mensaptr*10)>=mensaje1.length())
          {
            reiniciomsn();
          }*/
      }else if(msnno==2){
          //chunk = mensaje2.substring(mensaptr*10);
          //chunk.toCharArray(charBuf, 11);
        //mensaje2.toCharArray(charBuf2, 250);
        memcpy(charBuf2, mensaje2, sizeof(charBuf2));
          }else if(msnno==3){
          //chunk = mensaje3.substring(mensaptr*10);
          //chunk.toCharArray(charBuf, 11);
          memcpy(charBuf2, mensaje3, sizeof(charBuf2));
        //mensaje3.toCharArray(charBuf2, 250);
      }/*else if(msnno==4){
        mensaje4.toCharArray(charBuf2, 250);
      }else if(msnno==5){
        mensaje5.toCharArray(charBuf2, 250);
      }else if(msnno==6){
        mensaje6.toCharArray(charBuf2, 250);
      }else if(msnno==7){
        mensaje7.toCharArray(charBuf2, 250);
      }else if(msnno==8){
        mensaje8.toCharArray(charBuf2, 250);
      }else if(msnno==9){
        mensaje9.toCharArray(charBuf2, 250);
      }else if(msnno==10){
        mensaje10.toCharArray(charBuf2, 250);
      }else if(msnno==11){
        mensaje11.toCharArray(charBuf2, 250);
      }else if(msnno==12){
        mensaje12.toCharArray(charBuf2, 250);
      }else if(msnno==13){
        mensaje13.toCharArray(charBuf2, 250);
      }else if(msnno==14){
        mensaje14.toCharArray(charBuf2, 250);
      }else if(msnno==15){
        mensaje15.toCharArray(charBuf2, 250);
      }else if(msnno==16){
        mensaje16.toCharArray(charBuf2, 250);
      }else if(msnno==17){
        mensaje17.toCharArray(charBuf2, 250);
      }*/
      printStringWithShift(charBuf2,VEL_LED); 
      msnno++;
      delay(100);
      if(msnno>=4)
      {
        msnno=1;
      }
      printString("                       ");
      //memset(charBuf2, 0, sizeof(charBuf2));
      //memset(receivedChars, 0, sizeof(receivedChars));
      //reiniciomsn();
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
    
  void printStringWithShift(char* s, int shift_speed)
  {        // Imprime cadena de caracteres de mensajes en este micro 
    while (*s != 0)
    {
      printCharWithShift(*s, shift_speed); 
      s++;
      if(Serial1.available() > 0)
      {
        //reiniciomsn();
        break;
      }
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

       
  void hora() // Imprime hora en pantalla
  { 
    DateTime now = RTC.now();
    char TimeNow[20] ;
    sprintf(TimeNow,"      %.2d:%.2d",now.hour(),now.minute());
    m.setIntensity(8);            
    printString(TimeNow);                     
    delay(50);
  }

  void reiniciomsn(){
    memset(receivedChars, 0, sizeof(receivedChars));
    delay(2000); 
    m.clear();
    msnno++;
    if(msnno>=18)
    {
      msnno=0;
    }
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
