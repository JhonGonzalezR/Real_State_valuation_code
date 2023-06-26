/* 
This script represents a Neural Network which was previusly designed and tested in Google Collab using Tensorflow.

The objective is to create a neural network capable of predicting the house price of unit area in Sindian Dist., New Taipei City, Taiwan.
Followed by this, the model was implemented in the Atmega2560 Microcontroller.

Authors: Jhon Edward Gonzalez, Andrés Felipe Cotrino, Cesar Ramirez, Juan Sebastián Burbano.
Date: 02/2023       
*/

// Variables de entrada

float transactionDate = 0.0;
float houseAge = 0;
float distanceToMRT = 0.0;
int numStores = 0;
float latitude = 0.0;
float longitud = 0.0;
float housePriceOfUnitArea;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // Leer variable 1
  Serial.println("Ingrese la fecha de la transacción de la forma (2012.XXX), valores desde 2012.666667 hasta 2013.583333: ");
  while (transactionDate == 0){
    transactionDate = Serial.parseFloat();
    if (2012.666667<=transactionDate && transactionDate<=2013.58333){
        break;
    }else{
      transactionDate = 0;
    }
  }

  // Leer variable 2
  Serial.println("Ingrese la cantidad de años que tiene la vivienda: ");
  while (houseAge == 0){
    houseAge = Serial.parseFloat();
    if (0<houseAge && houseAge<=43.8){
        break;
    }else{
      houseAge = 0;
    }
  }
  // Leer variable 3
  Serial.println("Ingrese la fecha de la distancia desde la vivienda hasta la estación de MRT más cercana: ");
  while (distanceToMRT == 0){
    distanceToMRT = Serial.parseFloat();
    if (23.3828<=distanceToMRT && distanceToMRT<=6488.021){
        break;
    }else{
      distanceToMRT = 0;
    }
  }
  // Leer variable 4
  Serial.println("Ingrese la cantidad de tiendas cercanas a la vivienda: ");
  while (numStores == 0){
    numStores = Serial.parseInt();
    if (0<numStores && numStores<=10){
        break;
    }else{
      numStores = 0;
    }
    
  }
  
  // Leer variable 4
  Serial.println("Ingrese la latitud de la vivienda: ");
  while (latitude == 0){
    latitude = Serial.parseFloat();
    if (24.932070<=latitude && latitude<=25.014590){
        break;
    }else{
      latitude = 0;
  }
  }
  
  // Leer variable 5
  Serial.println("Ingrese la longitud de la vivienda: ");
  while (longitud == 0){
    longitud = Serial.parseFloat();
    if (121.473530<=longitud && longitud<=121.566270){
        break;
    }else{
      longitud = 0;
  }
  }

  // Se muestran lo ingresado por el usuario con el objetivo de que se pueda corroborar los datos
  Serial.println();
  Serial.println(transactionDate);
  Serial.println(houseAge);
  Serial.println(distanceToMRT);
  Serial.println(numStores);
  Serial.println(latitude);
  Serial.println(longitud);
  Serial.println();


  // Se envían las variables a la funcion de la red neural
  housePriceOfUnitArea = redNeuronal(transactionDate,houseAge,distanceToMRT,numStores,latitude,longitud);

  // Se deja ver el resultado de la red neural sin normalizar, tal cual sale de la red
  Serial.println("El precio de la vivienda por unidad de área sin normalizar es: ");
  Serial.println(housePriceOfUnitArea);

  // Se muestra el resultado una vez normalizado, este es la predicción correcta
  Serial.println("El precio de la vivienda por unidad de área normalizado es: ");
  Serial.println(inputNorm(housePriceOfUnitArea,1,-1,117.5,7.6));
  Serial.println();

  // Se limpian las variables para una próxima estimación.
  transactionDate = 0.0;
  houseAge = 0;
  distanceToMRT =  0.0;
  numStores = 0;
  latitude  = 0.0;
  longitud  = 0.0;
    
   //
 
 
  
}

// Función encargada de Normalizar variables
double inputNorm(double variable, double xmax, double xmin, double ymax, double ymin)
{
  double m = (ymax-ymin)/(xmax-xmin);
  double b = ymin - m*xmin;
  double y = m*variable+b;
  return y;
};


// Funciones de activación
double tanh(float p){
  return (2/(1+exp(-2*p)))-1;
};

double linear(double n){
  return n;
};


// Representación del diseño de la red neuronal en el microprocesador.
double redNeuronal(float X1, float X2, float X3, int X4, float X5, float X6){

// Se normalizan todas las variables de entrada respecto a su límites superior e inferior y se establecen de 1 a -1.
double mEntradas[6][1]{
{inputNorm(X1,2013.583333,2012.666667,1,-1)},
{inputNorm(X2,43.8,0,1,-1)},
{inputNorm(X3,6488.021,23.382840,1,-1)},
{inputNorm(X4,10,0,1,-1)},
{inputNorm(X5,25.014590,24.932070,1,-1)},
{inputNorm(X6,121.566270,121.473530,1,-1)}
};
// primera capa oculta

// Se crea a matriz resultante de la primera capa oculta
double a1[8][1];

// Pesos de la primera capa oculta
double Wco1[8][6] ={
  {0.6584713,-0.5038365,-0.665625,0.5290169,-0.59554756,-1.1085714},
{-0.23294099,-0.43767056,-0.80866188,1.1765734,-2.2756076,0.7308571},
{0.679437,-1.5046037,-0.02400195,-0.38565263,0.04365174,0.473935131},
{2.0966208,0.987552,-0.45369714,-0.07791814,-2.2418337,-1.9064659},
{0.67720294,-0.53510326,1.4925623,-0.03754785,-3.474614,0.12664165},
{-1.0548092,-1.2417803,-0.47506234,-1.558864,2.576958,1.9489783},
{-0.3674069,0.18911843,-1.5013474,-0.6645806,0.30375588,-0.15562648},
{0.4532645,-0.26774153,-1.4170946,0.14570005,-0.1274534,-1.8289468}
};

// Bias de la primera capa oculta.
double Bco1[8][1]={
  {-1.10987270},
  {-5.53905249E-01},
  {-1.09508085},
  {-8.98277387E-04},
  {6.59829140E-01},
  {1.67948937},
  {-1.04357585E-01},
  {-5.11825800E-01}
};
// Segunda capa oculta

// Se crea la matriz resultante de la segunda capa oculta.
double a2[3][1];

// Pesos de la segunda capa oculta.
double Wco2[3][8] = {
{0.75332814,-0.52393043,-0.22858498,-0.00435822,-1.4820213,-0.34681112,-1.6988596,0.8420838},
{-0.24979046,-0.6505003,0.18033394,0.51112425,-0.13939495,1.0426446,-0.09179696,-0.6344435},
{0.8108582,0.08285585,1.071121,0.7100273,-1.730596,-0.321918,0.8307133,-0.3544342}
};

// Bias de la segunda capa oculta
double Bco2[3][1] = {
{0.22911277},
{0.37733302},
{0.07681931}
};

// Capa de salida

// Se crea la matriz resultante de la capa de salida.
double a3[1][1];

// Pesos de la capa de salida.
double Wcs[1][3] = {
{-0.29535988,-0.67809945,0.3799114}
};

// Bias de la capa de salida
double Bcs[1][1]={-0.07558525};

// Multiplicación de matrices

float aux = 0.0;
for (int i=0; i<sizeof(Wco1)/sizeof(Wco1[0]); i++)
{
  for (int j=0; j<sizeof(mEntradas[0])/4; j++)
  { 
    for (int h=0; h<sizeof(Wco1[0])/4; h++)
    {
      aux = aux+Wco1[i][h]*mEntradas[h][j];        
    }
    // Se llena la matriz resultante de la primera capa oculta aplicanda la funcion de activación.
    a1[i][j] = tanh(aux+Bco1[i][0]);
    

    aux = 0.0;    
  }
  
}


for (int i=0; i<sizeof(Wco2)/sizeof(Wco2[0]); i++)
{
  for (int j=0; j<sizeof(a1[0])/4; j++)
  {
    for (int h=0; h<sizeof(Wco2[0])/4; h++)
    {
      aux = aux+Wco2[i][h]*a1[h][j];
    }
    // Se llena la matriz resultante de la segunda capa oculta aplicanda la funcion de activación.
    a2[i][j] = tanh(aux+Bco2[i][0]);
    aux = 0.0;
        
  }
  
}

for (int i=0; i<sizeof(Wcs)/sizeof(Wcs[0]); i++)
{
  for (int j=0; j<sizeof(a2[0])/4; j++)
  {
    for (int h=0; h<sizeof(Wcs[0])/4; h++)
    {
      aux = aux+Wcs[i][h]*a2[h][j];
      
    }
    // Se llena la matriz resultante de la capa de salida aplicanda la funcion de activación.
    a3[i][j] = linear(aux+Bcs[0][0]);

        aux = 0.0;
        // Resultado de la red Neuronal
        return a3[0][0];
  }

}
};
///