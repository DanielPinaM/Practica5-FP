//Daniel Piña Miguelsanz & Artur Amon

#include "indices.h"			
#include "checkML.h"

using namespace std;


bool comprobarArchivoInicial(string archivo)	//Comprueba si el archivo se puede abrir
{
	bool resultado = false;
	ifstream fich;
	fich.open(archivo);
	if (fich.is_open())		//Si el archivo se abre, entonces podemos trabajar con él
	{
		resultado = true;
		fich.close();
	}//if
	return resultado;
}//bool comprobarArchivoInicial

tListaCadenas getValor(const tIndicePalabras &tabla, const string &clave)
{
	tListaCadenas resultado;
	int pos = getPosicion(tabla, clave, 0, tabla.tamVariable);
	
	if (pos == -1)				// Devolvemos una variable vacía
		resultado.tamVariable = 0;
	else						// Devolvemos los valores de la clave
		resultado = tabla.pClaves[pos].valor;
	return resultado;
}//tListaCadenas getValor

tVector valoresSubLista(const tListaCadenas &archivos, const tListaCadenas &totales, const tVector &v)
{
	tVector resultado = vectorUnos(0);
	int pos;
	for (int i = 0; i < getTamanno(archivos); ++i)
	{
		string archivo = getCadena(archivos, i);
		pos = getPos(totales, archivo);
		annadir(resultado, v.datos[pos]);
	}//for
	return resultado;
}//tVector valoresSubLista

void ordenarValores(tListaCadenas &archivos, tVector &v)
{
	double auxVector;
	string auxArchivos;
	for (int i = 0; i < v.tam - 1; ++i)
	{
		for (int j = v.tam - 1; j > i; --j)
		{
			if (v.datos[j] > v.datos[j - 1])
			{
				auxVector = v.datos[j];
				v.datos[j] = v.datos[j - 1];
				v.datos[j - 1] = auxVector;

				auxArchivos = archivos.datos[j];
				archivos.datos[j] = archivos.datos[j - 1];
				archivos.datos[j - 1] = auxArchivos;
			}
		}
	}
}//void ordenarValores

void mostrarRelevancia(const tListaCadenas &enlaces, const int &pos, const tVector v)
{
	for (int i = 0; i < enlaces.tamVariable; ++i)
	{
		cout << "Encontrada en " << enlaces.datos[i]
			<< " (relevancia " << v.datos[i] << " )\n";
	}//for
}//void mostrarRelevancia

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	tListaCadenas totales;						//El conjunto de enlaces de la versión 2
	tMatriz L;									//La matriz de version 2
												//PEDIR EL ARCHIVO RAIZ
	tIndicePalabras tabla;		//La tabla en la cual se encuentra las 'claves' y sus 'valores'
	inicializa(tabla);		//Inicializamos la tabla que vamos a utilizar
	inicializa(totales);	//Inicializamos la lista de enlaces totales
	inicializaM(L, 0, 0.0);
	string nombreIndice;						//El nombre del archivo
	string palabraBuscada = "a";				//La palabra que el usuario quiere buscar


	cout << "Introduzca el nombre del archivo:\n";
	cin >> nombreIndice;

	while (!comprobarArchivoInicial(nombreIndice))		//Comprobamos si el archivo existe
	{
		cout << "\n El archivo introducido no se ha podido abrir.\nIntroduzca el nombre del archivo:\n";
		cin >> nombreIndice;
	}//while

	//CREAR TABLA

	crearTabla(tabla, nombreIndice, totales, L);		//Creamos la tabla que vamos a utilizar
	tMatriz M = desdeEnlacesAMatriz(L);			// M = (1 - C) * Cn + C * Mprima;
	tVector vX = vectorX(M);

	imprimir(tabla);

	cout << "\n \n Escoja que palabra quiere que se busque en el registro('fin' para terminar): ";
	cin >> palabraBuscada;
	while (palabraBuscada != "fin")		//Si palabraBuscada == "fin" entonces cerramos el programa
	{
		if (buscar(tabla, palabraBuscada, 0, tabla.tamVariable))	//Si la palabra está en la tabla
		{	
			tListaCadenas enlaces = getValor(tabla, palabraBuscada);
			tVector vOrdenado = valoresSubLista(enlaces, totales, vX);
			ordenarValores(enlaces, vOrdenado);
			int pos = getPosicion(tabla, palabraBuscada, 0, tabla.tamVariable);
			mostrarRelevancia(enlaces, pos, vOrdenado);

		}//if
		else						//Si la palabra no está en la tabla
			cout << "\nLa palabra buscada no esta en la tabla.\n";

		cout << "\n \n Escoja que palabra quiere que se busque ('fin' para terminar): ";
		cin >> palabraBuscada;
	}//while
	cout << "\nGracias por usar este buscador.\n\n";
	
	delete[]tabla.pClaves;
	delete[]totales.datos;
	_CrtDumpMemoryLeaks();
	
	return 0;
} // main
