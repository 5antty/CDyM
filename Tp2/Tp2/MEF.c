/*
 * MEF.c
 *
 * Created: 5/6/2025 5:38:31 PM
 *  Author: González Villagra, Santiago y Troitiño, Arian
 */
#include "MEF.h"
// Estados MEF

typedef enum{ini,number1,number2,number3,numeral,vic,der}state;
/*
ini = Inicio del juego
number1 = ingreso del primer numero del caracter ASCII
number2 = ingreso del segundo numero del caracter ASCII
number3 = ingreso del tercer numero del caracter ASCII
numeral = ingreso del numeral para finalizar la lectura del codigo del caracter ASCII	
vic = Victoria del jugador
der = Derrota del jugador
*/

//Declaracion del varaibles globales de la MEF (contra y clocks)
char *contra;
static uint8_t clk;//Esta variable es el clk de la MEF, tiene un pulso cada 100ms debido a la interrupcion definida en timer.c
static uint8_t clkS0;
static uint8_t clkVic;
static uint8_t clkDer;
static state estado;

//Declaracion de variables que usamos como contadores y "listo" como si fuera un boolean
static int listo;
static int errores;
static int correctas;

void IniciarMEF(void)
{
	LCD_Init();
	estado = ini;
	cargaRegsTimer();
}

int inicio(void)
{
	//Inicializacion de contadores u clocks
	errores = 0;
	correctas = 0;
	clkDer = 0;
	clkVic = 0;
	uint8_t car = 0;
	
	srand(clk);
	//Compruebo si se presiono una tecla en el teclado, y si esa tecla es el *
	if ((KEYPAD_Scan(&car) == 1) && (car == 42))
	{
		//Guardo en la variable contra una contraseña elegida de manera pseudoaleatoria con una funcion del archivo diccionario.c
		contra = getContra();
		LCDstring((uint8_t *)contra, 5);
		clkS0 = 0;
		return 1;
	}
	return 0;
}

int caracter(uint8_t *car)
{
	if ((KEYPAD_Scan(car)) == 1)
	{
		//Si el caracter es un numero, lo imprimo y retorno 1 para decir que el caracter ingresado es efectivamente un num.
		if ((*car >= 48) && (*car <= 57))
		{
			LCDsendChar(*car);
			return 1;
		}
	}
	return 0;
}

void compCAR(char num1, char num2, char num3)
{
	char car;
	//Guardo en la variable car el caracter que represantan los digitos ingresados por teclado.
	car = (num1 - 48) * 100 + (num2 - 48) * 10 + num3 - 48;
	if (car == contra[correctas])
	{
		LCDGotoXY(correctas, 0);
		LCDsendChar(car);
		correctas++;
	}
	else
	{
		errores++;
	}
	// Borrar linea inferior
	LCDGotoXY(0, 1);
	LCDstring((uint8_t *)"                ", 16);
}

void derrota(void)
{
	//Pantalla de derrota mostrada en el LCD
	LCDclr();
	LCDGotoXY(5, 0);
	LCDstring((uint8_t *)"DERROTA", 7);
}

void victoria(void)
{
	//Pantalla de victoria mostrada en el LCD
	char *msj = "";
	int min = 0, seg = clk / 10;
	LCDclr();
	LCDGotoXY(0, 0);
	if (seg > 60)
	{
		min = seg / 60;
		seg = seg % 60;
	}
	//Guardo en la variable msj el string de victoria mas la cantidad de tiempo empleado para ganar el juego.
	sprintf(msj, "VICTORIA %d:%d", min, seg);
	LCDstring((uint8_t *)msj, 13);
}

void ActualizarMEF(void)
{
	//Declaro las variables locales que almacenan los numeros leidos del teclado
	static uint8_t num1;
	static uint8_t num2;
	static uint8_t num3;
	//Entrada del teclado que permite saber si ya se ingreso el # para comparar el caracter con la contraseña
	static uint8_t finCAR;
	
	switch (estado)
	{
	case ini:
		if (inicio())
		{
			listo = 1;
		}
		//Luego de haber pasado 20*100ms=2s 
		if ((listo) && (++clkS0 == 20))
		{
			LCDclr();
			clk = 0;
			estado = number1;
		}
		clk++;
		break;

	case number1:
		listo = 0;
		LCDGotoXY(0, 1);
		// caracter(&num1); Devuelve si se pulso un caracter numerico
		if (caracter(&num1))
		{
			estado = number2;
		}
		clk++;
		break;
	case number2:
		// caracter(&num2); Devuelve si se pulso un caracter numerico
		if (caracter(&num2))
		{
			estado = number3;
		}
		clk++;
		break;
	case number3:
		// caracter(&num3); Devuelve si se pulso un caracter numerico
		if (caracter(&num3))
		{
			estado = numeral;
		}
		clk++;
		break;

	case numeral:
		//Verifico si se presiono una tecla en el teclado, y si esa tecla es el #
		if ((KEYPAD_Scan(&finCAR) == 1) && (finCAR == 35))
		{
			//Comparo el caracter formado por las teclas presionadas con un caracter de la contraseña.
			compCAR(num1, num2, num3);
			if (correctas == 5)
			{
				estado = vic;
			}
			else if (errores > 2)
			{
				estado = der;
			}
			else
			{
				estado = number1;
			}
		}
		clk++;
		break;
	case der:
		if (!listo)
		{
			listo = 1;
			derrota();
		}
		//Luego de haber pasado 30*100ms=3s
		if ((listo) && (++clkDer == 30))
		{
			LCDclr();
			estado = ini;
			listo = 0;
		}
		clk++;
		break;

	case vic:
		if (!listo)
		{
			listo = 1;
			victoria();
		}
		//Luego de haber pasado 50*100ms=5s
		if ((listo) && (++clkVic == 50))
		{
			LCDclr();
			estado = ini;
			listo = 0;
			clk = 0;
		}
		else
			clk++;
		break;
	}
}