#include "indices.h"
#include "checkML.h"

void  completarArchivoActual(tIndicePalabras &tabla, const string &nombreArchivoActual, tListaCadenas &enlaces, tListaCadenas &totales, tMatriz &L, const int &j)
{
	/*Dado un archivo no visitado, se guarda en la tabla los valores de ese archivo.
	  Si encontramos un enlace, lo guardamos en 'enlaces', en 'totales' y modificamos 'L'.
	  'j' está para comprobar si un nuevo enlace se encontraba en una posición concreta de 'totales',
	  para modificar correctamente la matriz 'L'*/

	//******************************************************************************************************
	ifstream archivo;
	archivo.open(nombreArchivoActual);

	if (archivo.is_open())						//Si el archivo existe****************************************************
	{
		string palabra;
		archivo >> palabra;
		cout << palabra;
		while (!archivo.eof())		//Mientras el archivo no esté terminado, seguimos leyendo		******************************
		{

			cout << ispunct(palabra[palabra.size() - 1]);

			if (ispunct(palabra[palabra.size() - 1]))
			{
				palabra.erase(palabra.size() - 1, 1);
			}//es puntuacion?

			transform(palabra.begin(), palabra.end(), palabra.begin(), tolower);  //Ponemos todo en minúsculas

			cout << palabra;

			//ES ENLACE?


			if (palabra[0] == '<' &&   palabra[palabra.length() - 1] == '>')
			{
				cout << palabra;
				palabra.erase(0, 1);
				palabra.erase(palabra.length() - 1, 1);


				if (totales.datos[j] == palabra)	//Si el archivo nuevo se encontraba en 'posI' de 'totales'
				{
					L.arrayMatriz[j][L.dimensionMatriz - 1] = 1.0;	//L(i,j) = 1.0
				}//if
				else
				{
					if (buscar(totales, palabra))
					{
						int i = getPos(totales, palabra);
						L.arrayMatriz[i][j] = 1.0;
					}//if
					else
					{
						insertar(totales, palabra);			//Todos los enlaces deben estar en 'totales'
						insertar(enlaces, palabra);			//Declaramos en el programa que hay un nuevo enlace
						incrementaTam(L);					//Incrementamos el tamaño de la matriz
						L.arrayMatriz[L.dimensionMatriz - 1][j] = 1.0;		//L(t-1,j) = 1.0
					}
				}
			}
			else	//La palabra leída no es un enlace, es una palabra que hay que guardar en el registro
			{
				insertar(tabla, palabra, nombreArchivoActual);
			}//else

			archivo >> palabra;					/*****************************************************************************/

		}//archivo abierto (while)
		archivo.close();					/************************************************************************************/
	}
	else
	{
		cout << "No se ha podido abrir el archivo\n";
	}
}
			

void crearTabla(tIndicePalabras &tabla, const string &archivoInicial, tListaCadenas &totales, tMatriz &L)
//Rellenamos la tabla a partir de archivoInicial
{
	tListaCadenas visitados;		//'visitados' es la lista de enlaces ya visitados
	tListaCadenas noVisitados;		//'noVisitados' es la lista de enlaces pendientes por revisar
	string nombreArchivoActual;		//'nombreArchivoActual' nos indica el archivo que vamos a abrir
	inicializa(noVisitados);
	inicializa(visitados);
	inicializa(totales);
	insertar(noVisitados, archivoInicial);
	insertar(totales, archivoInicial);
	inicializaM(L, 1, 0.0);

	cout << "\n \n CREANDO LA TABLA CON EL ARCHIVO INICIAL ... ";

	//Lo que haremos a continuación es leer el archivo inicial aplicando lo siguiente:
		//1.- Guardaremos en el registro las palabras del archivo de texto.
		//2.- Si nos encontramos un enlace:
					//Si no está en totales añadirlo a totales y no-visitados,
					//ampliar el tamaño de L en 1 (de forma que las nuevas entradas sean nulas) y poner l(t−1,j) a 1.0 siendo t el nuevo tamaño.

					//Si está en totales en la posición i poner l(i,j) a 1.0
	int j;
	while (noVisitados.tamVariable > 0)	//Comprobamos que todos los enlaces se han revisado
	{
		if (!buscar(visitados, noVisitados.datos[0]))		//Si el enlace no se ha revisado, se revisa.
		{
			insertar(visitados, noVisitados.datos[0]);		//a)
			nombreArchivoActual = noVisitados.datos[0];
			eliminar(noVisitados, 0);

			j = getPos(totales, nombreArchivoActual);
			completarArchivoActual(tabla, nombreArchivoActual, noVisitados, totales, L, j);
		}//if
	}//for

	cout << "(TERMINADA)\n";

}//void crearTabla