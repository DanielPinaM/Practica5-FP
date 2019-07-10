#include "listacadenas.h"
#include "checkML.h"

using namespace std;

void inicializa(tListaCadenas &lista)	//Inicializa la lista dejándola vacía
{
	lista.datos = new string[1];
	lista.cap = 1;
	lista.tamVariable = 0;

}//void inicializa

void aumentaCapacidad(tListaCadenas &l) {

	tArrayCadenas newDatos = new string[(l.cap * 3) / 2 + 1];

	for (int i = 0; i < l.cap - 1; i++)
	{
		newDatos[i] = l.datos[i];
	}

	tArrayCadenas oldDatos = l.datos;
	l.datos = newDatos;
	delete[] oldDatos;
	l.cap = (l.cap * 3) / 2 + 1;

}	//Aumenta capacidad

int getTamanno(const tListaCadenas &l) //Obtiene el tamanno de la lista
{
	int resultado;
	resultado = l.tamVariable;
	return resultado;
}//int getTamanno

string getCadena(const tListaCadenas &l, int pos) //Obtiene una cadena de la lista
{
	string resultado;
	resultado = l.datos[pos];
	return resultado;
}//string getCadena

int getPos(const tListaCadenas &l, const string &s)
{
	int resultado;
	int i = 0;
	while (i < getTamanno(l) && getCadena(l, i) != s)
		++i;
	if (i < getTamanno(l))
		resultado = i;
	else
		resultado = -1;
	return resultado;
}

void insertar(tListaCadenas &l, const string &s)//Inserta un elemento en el array
{
	if (!buscar(l, s))
	{
		
		++l.tamVariable; //Aumentamos en 1 el tamaño del array
		l.datos[l.tamVariable - 1] = s; //Guardamos el nuevo valor en el array

		if (l.tamVariable == l.cap)
		{
			aumentaCapacidad(l);
		}

	}//if
}//void insertar

bool buscar(const tListaCadenas &l, const string &s) //Busca un elemento del array
{
	bool resultado = false;
	int i = 0;
	while ((resultado == false) && (i < l.tamVariable))
	{
		if (l.datos[i] == s)
			resultado = true;
		++i;
	}//while
	return resultado;
}//bool buscar

void eliminar(tListaCadenas &l, int pos) //Elimina un valor concreto de la lista
{
	for (int i = pos; i < l.tamVariable; ++i) //El array lo movemos hacia la izquierda desde 'pos + 1'
		l.datos[i] = l.datos[i + 1];
	--l.tamVariable;
}//void eliminar

void imprimir(const tListaCadenas &l) //Muestra en pantalla la lista
{
	for (int i = 0; i < l.tamVariable; ++i)
	{
		cout << l.datos[i] << ", ";
	}//for
}//void imprimir