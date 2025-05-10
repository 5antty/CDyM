/*
 * diccionario.c
 *
 * Created: 5/4/2025 4:55:16 PM
 *  Author: González Villagra, Santiago y Troitiño, Arian
 */ 

#include "diccionario.h"
//Declaro el arreglo de contrasenias como privado
static char contras[25][5]={"Arbol", "Boton", "CDyMC", "ClavE", "Facil", "Gafas", "Hojas", "LiBro", "Lanza", "Nieve", "PeRro", "PecES", "PiAno", "PrYKe", "RUEDa",
"SERIE", "SalUd", "Salud", "Silla", "Tecla", "Valor", "Verde", "YnHRz", "hARdD", "silla"};

//Funcion publica que devuelve una contraseña del arreglo de forma pseudoaleatoria.
char * getContra(void){
	int num = rand()%25;
	return contras[num];
}