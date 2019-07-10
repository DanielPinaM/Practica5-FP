#include "listacadenas.h"		
#include "checkML.h"

#ifndef clavevalor_h
#define clavevalor_h

struct tClaveValor		
{
	string clave;
	tListaCadenas valor;

};// struct tClaveValor

typedef tClaveValor *punterClaver;

struct tIndicePalabras
{
	punterClaver pClaves;
	int tamVariable;
	int cap;

};// struct tIndicePalabras

//FUNCIONES:
int getTamanno(const tIndicePalabras &l);														//Devuelve el tamanno de la tabla
tClaveValor getRegistro(const tIndicePalabras & l, int pos);									//Devuelve el registro de una posicion concreta
bool buscar(const tIndicePalabras &l, const string &s, int ini, int fin);						//Busca una palabra en la tabla
int getPosicion(const tIndicePalabras &l, const string &s, int ini, int fin);										//Obtiene la posición de la clave s, Si no existe, -1
void insertar(tIndicePalabras &idx, const string &palabra, const string &nombreArchivo);		//Inserta una palabra en la tabla
void imprimir(const tIndicePalabras &idx);														//Muestra en pantalla una tabla 'idx'
void inicializa(tIndicePalabras &tabla);														//Inicializa los tIndicePalabras para asegurar el correcto funcionamiento
void aumentaCapacidad(tIndicePalabras &l);														//Aumenta l.cap


#endif // !clavevalor_h