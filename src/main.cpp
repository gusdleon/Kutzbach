#include <Arduino.h>
#include <Key.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


//variables
char expression ='A';
char oldexpression;
char variables[3] = {'n','j','g'};
char *nvariables[3];
char valor_n[3];
char valor_j[3];
char valor_g[3];
char tecla;
String msg;

int j=1;

const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinesFilas[FILAS] = {9,8,7,6};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {5,4,3,2}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto


//Declaraciones de Funciones
void displayMenu();
void displayTerminos();
void displayCalcular();
void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando");
  lcd.init();
  lcd.clear();			// limpia pantalla
  lcd.setCursor(2 , 4);
  lcd.print("INICIALIZANDO");
  lcd.setCursor(3 , 7);
  lcd.print("CARGANDO");
  delay(3000);
  lcd.clear();
}

void loop() {
  oldexpression = expression;
  delay(1);
  expression = teclado.getKey();
  if(oldexpression != expression) lcd.clear();


  if(expression)
    switch (expression)
  {
  case 'A': //Display Menu
      displayMenu();
    break;
  case 'B': //Display Terminos
      displayTerminos();
    break;
  case 'C': //Display Calcular
      displayCalcular();
    break;

  default:

    break;
  }
}

//Funciones
void displayMenu(){
  lcd.setCursor(0 ,6 );
  lcd.print("KUTZBACH!");
  lcd.setCursor(1,0);
  lcd.print("m=3(n-1)-2(j)-(g)");
  lcd.setCursor(2,0);
  lcd.print("Terminos  | Calcular");
  lcd.setCursor(3,0);
  lcd.print(" 'B'      |    'C'  ");
}
void displayTerminos(){
  lcd.setCursor(0 ,0 );
  lcd.print("m = Movilidad ");
  lcd.setCursor(1,0);
  lcd.print("n = eslabones,barras");
  lcd.setCursor(2,0);
  lcd.print("ji=Uniones 1° |Menu");
  lcd.setCursor(3,0);
  lcd.print("g =Uniones 2° |'A' ");
}

void displayCalcular(){
  lcd.setCursor(0,0);
  lcd.print("m=3(n-1)-2(j1)-(g)");


  for(int i = 0; i < 3; i++) //Preguntar por los valores de cada variable, y asignarlos a un array tipo char
  {
    msg = "INGRESA EL VALOR: " + variables[i];
    lcd.setCursor(1,0);
    lcd.print(msg);
    lcd.setCursor(4,10);
    lcd.print("OK-->#");
    lcd.setCursor(2,0);
    while(*nvariables[i] != 'a')
    {

      tecla = teclado.getKey();
      if(tecla){
        valor_n[j] = tecla;
        j++;
      }



    }
  }
  //Convertir el array tipo char a uno con valores int.


}
