#include <iostream>					//Mostrar en pantalla informacion
#include <fstream>					//Abrir archivos de texto
#include <string>					//Trabajar con variables 'string'
#include <algorithm>				//Para transformar las mayúsculas a minúsculas
#include <cctype>					//Para la función 'tolower()'
#include "matrices.h"				//Tabrajar con cadenas de clave-valor


//FUNCIONES:
void completarArchivoActual(tIndicePalabras &tabla, const string &nombreArchivoActual, tListaCadenas &enlaces, tListaCadenas &totales, tMatriz &L, const int &j);
void crearTabla(tIndicePalabras &tabla, const string &archivoInicial, tListaCadenas & totales, tMatriz &L);		//Rellenamos la tabla a partir de archivoInicial