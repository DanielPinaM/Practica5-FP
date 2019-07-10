#ifndef listacadenas_h
#define listacadenas_h
#include <iostream>		
#include <string>
#include "checkML.h"
using namespace std;

typedef string *tArrayCadenas;

struct tListaCadenas
{
	tArrayCadenas datos;
	int tamVariable;		
	int cap;				

};//struct tListaCadenas



//FUNCIONES 'listacadenas'
void aumentaCapacidad(tListaCadenas &l);				//Aumenta la capacidad de datos en listaCadenas dinamico
int getTamanno(const tListaCadenas &l);					//Obtiene el tamanno de la lista
string getCadena(const tListaCadenas &l, int pos);		//Obtiene una cadena de la lista
int getPos(const tListaCadenas &l, const string &s);	//Obtiene la posición de una palabra en una lista
void  insertar(tListaCadenas &l, const string & s);		//Inserta un elemento en el array
bool buscar(const tListaCadenas &l, const string &s);	//Busca un elemento del array
void eliminar(tListaCadenas &l, int pos);				//Elimina un valor concreto de la lista
void inicializa(tListaCadenas &tabla);					//Inicializa la lista dejándola vacía
void imprimir(const tListaCadenas &l);					//Muestra en pantalla la lista

#endif //!listacadenas_h