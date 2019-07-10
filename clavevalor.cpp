#include "clavevalor.h"
#include "checkML.h"

using namespace std;


void inicializa(tIndicePalabras &tabla)			//Inicializa la tabla
{

	tabla.pClaves = new tClaveValor[1];
	tabla.cap = 1;
	tabla.tamVariable = 0;

}//void inicializa

void aumentaCapacidad(tIndicePalabras &l)
{
	punterClaver newDatos = new tClaveValor[(l.cap * 3) / 2 + 1];
	
	for (int i = 0; i < l.cap - 1; i++)
	{
		newDatos[i] = l.pClaves[i];
	}

	punterClaver oldDatos = l.pClaves;
	l.pClaves = newDatos;

	delete[] oldDatos;
	l.cap = (l.cap * 3) / 2 + 1;

} // aumentaCapacidad

int getTamanno(const tIndicePalabras &l) //Devuelve el tamanno de la tabla
{
	int resultado;
	resultado = l.tamVariable;
	return resultado;
}// int getTamanno

//SE DA POR SENTADO QUE LA POSICION ENTREGADA ES MENOR QUE EL TAMAÑO DE LA LISTA
tClaveValor getRegistro(const tIndicePalabras & l, int pos) //Devuelve el registro de una posicion concreta
{
	tClaveValor registro;
	registro = l.pClaves[pos];
	return registro;
}// tClaveValor getRegistro

bool buscar(const tIndicePalabras &l, const string &s, int ini, int fin) //Busca una palabra en la tabla
{
	bool salida = false;
	if (ini <= fin) {
		int mitad = (ini + fin) / 2;
		if (s == l.pClaves[mitad].clave) {
			salida = true;
		}
		else if (s < l.pClaves[mitad].clave) {
			salida = buscar(l, s, ini, mitad - 1);
		}
		else {
			salida = buscar(l, s, mitad + 1, fin);
		}
	}
	return salida;

}//  bool buscar

int getPosicion(const tIndicePalabras &l, const string &s, int ini, int fin)  //Obtiene la posición de la clave s, 
															//si no existe, -1
{
	int pos = -1;
	if (ini <= fin) {
		int mitad = (ini + fin) / 2;
		if (s == l.pClaves[mitad].clave) {
			pos = mitad;
		}
		else if (s < l.pClaves[mitad].clave) {
			pos = buscar(l, s, ini, mitad - 1);
		}
		else {
			pos = buscar(l, s, mitad + 1, fin);
		}
	}
	return pos;
}//int getPosicion

void insertar(tIndicePalabras &idx, const string &palabra, const string &nombreArchivo)
		//Inserta las claves y los valores de cada una de las anteriores en una tabla 'idx'
{

	int pos = getPosicion(idx, palabra, 0, idx.tamVariable), i = 0;

	if (pos == -1)		//La palabra no esta en 'idx'
	{
		++idx.tamVariable;

		if (idx.pClaves[0].valor.datos == NULL)
		{
			inicializa(idx);
		}

		if (idx.cap == idx.tamVariable)
		{
			aumentaCapacidad(idx);
		}

		while ((i < idx.tamVariable) && (idx.pClaves[i].clave < palabra))
			++i;
		if(i == idx.tamVariable)
		{
			idx.pClaves[idx.tamVariable - 1].clave = palabra;
			insertar(idx.pClaves[idx.tamVariable - 1].valor, nombreArchivo);
		}//if
		else
		{
			for (int j = idx.tamVariable; j > i; --j)
			{
				idx.pClaves[j] = idx.pClaves[j - 1];
				idx.pClaves[j - 1].valor.tamVariable = 0;
			}//for
			idx.pClaves[i].clave = palabra;
			insertar(idx.pClaves[i].valor, nombreArchivo);
		}//else

		

	}//if
	else
	{
		insertar(idx.pClaves[pos].valor, nombreArchivo);
	}//else
	
	

}//void insertar

void imprimir(const tIndicePalabras &idx) //Muestra en pantalla una tabla 'idx'
{
	for (int i = 0; i < idx.tamVariable; ++i)
	{
		cout << "CLAVE: " << idx.pClaves[i].clave << "			VALORES ASOCIADOS: ";
		imprimir(idx.pClaves[i].valor);
		cout << "\n";
	}//for
}//void imprimir