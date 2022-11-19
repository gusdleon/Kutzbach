#include <Arduino.h>
#include <Key.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Variables
char expression = '*';
char variables[3] = {'n', 'j', 'g'};
char tecla;
int valor_m;
int valor;
int valores_variables[3]; // Continen los valores decimales de cada variable de la ecuación

int IN1 = 10; // Se definen pines de salida al puente H
int IN2 = 11;
int ENA = 12;

int j = 1;

const byte FILAS = 4;		   // Define numero de filas
const byte COLUMNAS = 4;	   // Define numero de columnas
char keys[FILAS][COLUMNAS] = { // Define la distribucion de teclas
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {9, 8, 7, 6};		 // Pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2}; // Pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS); // Crea objeto

// Declaraciones de Funciones
void displayMenu();
void displayTerminos();
void displayCalcular();
int obtenerValor();
void mIzq();
void mDer();

void setup(){
	lcd.setContrast(HIGH);
	lcd.setBacklight(HIGH);
	Serial.begin(9600);
	lcd.init();
	lcd.clear(); // Limpia pantalla
	lcd.setCursor(2, 0);
	lcd.print("INICIALIZANDO");
	lcd.setCursor(4, 3);
	lcd.print("CARGANDO");
	delay(3000);
	lcd.clear();
	pinMode(IN1, OUTPUT); // Salida de pines a puente H
	pinMode(IN2, OUTPUT);
	pinMode(ENA, OUTPUT);
}

void loop(){
	digitalWrite(IN1, LOW);//Se gira
	digitalWrite(IN2, HIGH);
	tecla = teclado.getKey();
	if (tecla){ // Condicional detecta un cambio de tecla para borrar la pantalla
		expression = tecla;
		lcd.clear();
	}
	delay(100); // Delay de chill
	switch (expression){
		case 'B': // Display Menu
			displayMenu();
			expression = ' ';
			break;
		case 'C': // Display Terminos
			displayTerminos();
			expression = ' ';
			break;
		case 'A': // Display Calcular
			displayCalcular();
			expression = ' ';
			break;
		case '*': // Grio izquierda
			displayMenu();
			mIzq();
			expression = ' ';
			break;
		case '#': // Giro derecha
			displayMenu();
			mDer();
			expression = ' ';
		default:
			break;
	}
}

// Funciones
void mIzq(){
	digitalWrite(ENA, LOW); // Se apaga motor
}

void mDer(){
	digitalWrite(ENA, HIGH); //Se apaga motor
}

void displayMenu(){ // Imprime el menu inicial
	lcd.setCursor(6, 0);
	lcd.print("KUTZBACH!");
	lcd.setCursor(0, 1);
	lcd.print("m=3(n-1)-2(j)-(g)");
	lcd.setCursor(0, 2);
	lcd.print("Terminos  | Calcular");
	lcd.setCursor(0, 3);
	lcd.print(" 'info'   |   'A'   ");
}

void displayTerminos(){ // Imprime pequeña info sobre cada variable de la ecuacion
	lcd.setCursor(0, 0);
	lcd.print("m = Movilidad ");
	lcd.setCursor(0, 1);
	lcd.print("n = eslabones,barras");
	lcd.setCursor(0, 2);
	lcd.print("j=Uniones 1 grado ");
	lcd.setCursor(0, 3);
	lcd.print("g=Uniones 2 grados ");
}

void displayCalcular(){

	for (int i = 0; i < 3; i++){ // Preguntar por los valores de cada variable, y asignarlos a un array tipo char
		lcd.setCursor(0, 0);
		lcd.print("m=3(n-1)-2(j)-(g)");
		lcd.setCursor(13, 3);
		lcd.print("OK-->D");
		lcd.setCursor(0, 1);
		lcd.print("Ingresa el valor: ");
		lcd.print(variables[i]);
		lcd.setCursor(0, 2);
		valores_variables[i] = obtenerValor(); // Asignar a un array el valor de cada variable de la ecuacion.
		valor = 0;
		if (i < 2)
			lcd.clear();
	}
	valor_m = (3 * (valores_variables[0] - 1)) - (2 * valores_variables[1]) - (valores_variables[2]); // Asignar valor total utilizando los valores
	lcd.setCursor(0, 3);																			  // del array "valores_variables"
	lcd.print("m = ");
	lcd.print(valor_m);
	lcd.setCursor(9, 3);
	lcd.print("Menu->Back");
}

int obtenerValor(){ // Algoritmo para obtener el valor decimal de un tipo caracter de entrada '0...9'

	while (1){
		tecla = teclado.getKey();
		if (tecla >= '0' && tecla <= '9'){
			valor = valor * 10 + (tecla - '0');
			lcd.setCursor(0, 2);
			lcd.print(valor);
			Serial.println(valor);
		}

		if (tecla == 'D')
			break; // Enter para salir del while
	}
	return valor;
}
