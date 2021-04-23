#define SER 2	//PUERTO SERIAL
#define RCLK 3	//RELOJ DE REGISTRO DESPLAZAMIENTO
#define SRCLK 4  //RELOJ DE REGISTRO DE SALIDA
//int menuIn = 0;

void setup()
{
  //Inclizamos el serial para poder recibir datos por consola.
  Serial.begin(9600);
  //configuracion de puertos digitales
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  
  //Se inicializa el serial y los relojes en LOW.
  digitalWrite(SER, 0);
  digitalWrite(RCLK, 0);
  digitalWrite(SRCLK, 0);
}

//COMIENZO A AGREGAR LAS FUNCIONES PROPIAS

//Funcion que crea el doble puntero para la funcion imagen
int **CrearM(){
int **matrizCero;//Puntero doble que me recorre la matriz
  
matrizCero = new int*[8]; // Hice que el puntero tome un arreglo de 8 punteros(que serán las filas)
for (int f = 0; f < 8; f++)
  matrizCero[f] = new int[8]; // Los 8 elementos serán las filas
  return matrizCero;
}

//Esta el la funcion que recibe los datos de un patron y arma el doble puntero para la funcion Imagen
int **Imagen (int **matrizCero){
  //Le pido al usuario que me diga cuales led prender y cuales no
  for (int fila = 0; fila<8; fila++){
   
    Serial.print("\n");
    Serial.print("Fila: ");
    Serial.print(8-fila,DEC);
    Serial.print("\n");
    Serial.print("Ingrese 1 si el led debe prenderse y 0 si debe estar apagado (respectivamente por fila):  ");
    while(!Serial.available()>0);
      long long int dato = Serial.parseInt();
    for (int columna = 0; columna<7; columna++){
      int individual = dato%10;
      dato = dato/10;
      matrizCero[fila][columna]=individual;
    }
    matrizCero[fila][7]=dato;
    
} 
  return matrizCero;
}

//Esta es la funcion que manda los datos del doble puntero hacia los integrados
void EjecutarImagen(int ** matrizCero){
  
  for (int fila = 0; fila<8; fila++){
    for (int columna = 0; columna<8; columna++){
    
    int ingreso = *(*(matrizCero+fila)+columna) ;
    
    digitalWrite(SER, ingreso);//Se le da el valor al serial, que es el que va pasando los numeros.
  
    digitalWrite(RCLK, 0);
    digitalWrite(RCLK, 1);
    digitalWrite(RCLK, 0);
}
  digitalWrite(SRCLK, 0);
  digitalWrite(SRCLK, 1);
  digitalWrite(SRCLK, 0);
}
}



//Funcion de verificacion
void Verificacion(int num, int serial ,int dezpla,int salida)//Num lo que hace es recorrer la matriz de LEDS, la segunda variable es para mandar los datos al serial y las otras 2 ajustan los relojes.
{
  digitalWrite(serial, num);//Se le da el valor al serial, que es el que va pasando los numeros.
  
  digitalWrite(salida, 0);
  digitalWrite(salida, 1);
  digitalWrite(salida, 0);
  
  digitalWrite(dezpla, 0);
  digitalWrite(dezpla, 1);
  digitalWrite(dezpla, 0);
}


//Crea el triple puntero para la funcion Publik
int ***ArregloPublik( int patrones){
  int ***ArregloP = new int **[patrones];
  
  for(int p = 0; p<patrones ; p++){
  	ArregloP[p] = new int*[8];
    for(int f = 0; f<8 ; f++){
    	ArregloP[p][f] = new int[8];
    }
  }
  return ArregloP;
}

//Le pide al usuario los datos para armar el triple puntero de la funcion Publik
int ***MeterP (int ***ArregloP, int patrones){
  //Le pido al usuario que me diga cuales led prender y cuales no
  for(int patron = 0; patron<patrones ; patron++){ 
    for (int fila = 0; fila<8; fila++){
     
      Serial.print("\n");
      Serial.print("Numero de patron:");
      Serial.print(patron+1,DEC);
      Serial.print("\n");
      Serial.print("Fila: ");
      Serial.print(8-fila,DEC);
      Serial.print("\n");
      Serial.print("Ingrese 1 si el led debe prenderse y 0 si debe estar apagado (ocho numeros por fila):  ");
      while(!Serial.available()>0);
        long long int dato = Serial.parseInt();
      for (int columna = 0; columna<7; columna++){
        int individual = dato%10;
        dato = dato/10;
        ArregloP[patron][fila][columna]=individual;
      }
      ArregloP[patron][fila][7]=dato;
  } 
  }
  return ArregloP;
}

//Envia los datos del triple puntero a los integrados
void EjecutarPub(int *** MeterP, int patrones, int secpatron){
  
  for(int patron = 0; patron<patrones ; patron++){
    for (int fila = 0; fila<8; fila++){
      for (int columna = 0; columna<8; columna++){
      
      int ingreso = *(*(*(MeterP+patron)+fila)+columna) ;
      
      digitalWrite(SER, ingreso);//Se le da el valor al serial, que es el que va pasando los numeros.
    
      digitalWrite(RCLK, 0);
      digitalWrite(RCLK, 1);
      digitalWrite(RCLK, 0);
  }
    digitalWrite(SRCLK, 0);
    digitalWrite(SRCLK, 1);
    digitalWrite(SRCLK, 0);

}
int time = secpatron*1000;
delay(time);
}
}

//Funcion principal Publik
void Publik(){
  
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Ingrese la cantidad de patrones que desea imprimir: ");
  while(!Serial.available()>0);
  int patrones = Serial.parseInt();
  Serial.print("\n");
  Serial.print("Ingrese el tiempo (en segundos) entre cada impresion de patrones: ");
  while(!Serial.available()>0);
  int secpatron = Serial.parseInt();
  int ***InicialP = ArregloPublik(patrones);
  int ***MedioP = MeterP (InicialP,patrones);
  EjecutarPub(MedioP,patrones,secpatron);
}


void loop()
{  
 
  //Para que no se note el menu anterior en la consola
  for(int n=0;n<10;n++) Serial.print("\n");
  //Se imprime el menú para escoger ls fuciones
  Serial.print("                BIENVENIDO");
  Serial.print("\n");
  Serial.print("Escoja una de las opciones del menu");
  Serial.print("\n");
  Serial.print("0. Detener lo que se esta ejecutando");
  Serial.print("\n");
  Serial.print("1. Secuencia de VERIFICACION del estado de los LED");
  Serial.print("\n");
  Serial.print("2. Ingrese y visualice su propia IMAGEN");
  Serial.print("\n");
  Serial.print("3. Ingrese varios patrones a visualizar");
  Serial.print("\n");
  delay(3000);
  
  
  if (Serial.available()>0){
    Serial.flush();
    int caso = Serial.parseInt(); 
    
    switch(caso){
      
     
    
      case 0 :{
      Serial.print("\n\n\n\n");
      Serial.print("DETENIENDO LO QUE SE ESTA EJECUTANDO");
      Serial.print("\n");
     	for(int i = 1; i<=65; i++) {
      Verificacion(0,SER,RCLK,SRCLK);}
      Serial.print("\n");
      Serial.print("Para ejecutar otra opcion ingrese cualquier letra");
      Serial.print("\n");
      while(!Serial.available()>0);
        break;}
        
      case 1 :
      {
      //Para ejecutar la funcion de verificacion 
      Serial.print("\n\n\n\n");
      Serial.print("Ejecutando funcion de Verificacion");
      for(int i = 1; i<=65; i++) {
        Verificacion(i,SER,RCLK,SRCLK);}//Este for es el que permite recorrer los 64 LEDS. 
       // delay(8000);
      Serial.print("\n");
      Serial.print("Para ejecutar otra opcion ingrese cualquier letra");
      Serial.print("\n");
      while(!Serial.available()>0);
        break;}
       
       
      case 2 : 
      {
      //Para ejecutar la funcion de imagen 
      int **inicial = CrearM();
  	  int **final = Imagen(inicial);
  	  EjecutarImagen(final);
      Serial.print("\n");
      Serial.print("Para ejecutar otra opcion ingrese cualquier letra");
      Serial.print("\n");
      while(!Serial.available()>0);
      break;
      }
      
      case 3 :{
      Serial.print("\n");
      Serial.print("\n");
      Publik();
      Serial.print("\n");
      Serial.print("Para ejecutar otra opcion ingrese cualquier letra");
      Serial.print("\n");
      while(!Serial.available()>0);
        break;}
      
   
    }//Del switch
  }//Del if
}//Del loop
