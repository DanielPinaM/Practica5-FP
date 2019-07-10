#include <iostream>					//Mostrar en pantalla informacion
#include <fstream>					//Abrir archivos de texto
#include <string>					//Trabajar con variables 'string'
#include <algorithm>				//Para transformar las mayúsculas a minúsculas
#include <cctype>					//Para la función 'tolower()'
#include <math.h>
#include "clavevalor.h"				//Trabajar con cadenas de clave-valor

#ifndef matrices_h
#define matrices_h

using namespace std;

const int MAX_TAM = 60;

struct tMatriz {
	double arrayMatriz[MAX_TAM][MAX_TAM];
	int dimensionMatriz;
};

struct  tVector {
	double datos[MAX_TAM];
	int tam;
};

void inicializaM(tMatriz &m, const int &dimension, const double &e);		//Inicializa una matriz 'm'
void incrementaTam(tMatriz &m);												//Aumenta el tamaño de la matriz
void annadir(tVector &v, const double &e);									//Agrega un valor al final de un vector
tMatriz matrizConstante(double x, int n);									//Crea una matriz de 'n' ∙ 'n', en la que todos los valores iniciales son 'x'.
tVector operator*(const tMatriz & m, const tVector & v);					//Multiplica una matriz por un vector.
tMatriz operator*(double x, const tMatriz & m);								//Obtiene la matriz que se obtiene multiplicando cada elemento de 'm' por 'x'.
tMatriz operator+(const tMatriz & m1, const tMatriz & m2);					//Suma dos matrices.
tMatriz desdeEnlacesAMatriz(const tMatriz & L);								//Devuelve la matriz M obtenida de L como en la introducción de la sección 4.
tVector vectorUnos(const int &dimensionMatriz);								//Dada una dimensión de una matriz, obtenemos un vector de 'unos' de esa dimensión
tVector normaliza(const tVector &v1);										//Divide la matriz por su primer componente
bool proximos(const tVector &v1, const tVector &v2, double epsilon);		//Comprueba si dos vectores son próximos
tVector vectorX(tMatriz &M);												//Crea el vector con los valores de relevancia


#endif // !matrices_h