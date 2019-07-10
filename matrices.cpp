#include "matrices.h"
#include "checkML.h"


void inicializaM(tMatriz &m,const int &dimension, const double &e) {		//Inicializa una matriz 'm'

	m.dimensionMatriz = dimension;
	for (int i = 0; i < dimension; ++i)
		for (int j = 0; j < dimension; ++j)
			m.arrayMatriz[i][j] = e;
}//void inicializaM

void incrementaTam(tMatriz &m)
{
	++m.dimensionMatriz;
	for (int j = 0; j < m.dimensionMatriz; ++j)
	{
		m.arrayMatriz[m.dimensionMatriz - 1][j] = 0.0;		//Modificamos las columnas	(ultima fila)
		m.arrayMatriz[j][m.dimensionMatriz - 1] = 0.0;		//Modificamos las filas (ultima columna)
	}//for
}//void incrementaTam

void annadir(tVector &v, const double &e)
{
	v.datos[v.tam] = e;
	++v.tam;
}//void annadir

tMatriz matrizConstante(double x, int n) {			//Crea una matriz 'n' * 'n'  con los valores inicializados a 'x'
	tMatriz matrizN;
	matrizN.dimensionMatriz = n;							//Actualizo la dimension de la matriz (n)
	for (int i = 0; i < matrizN.dimensionMatriz; ++i) {
		for (int j = 0; j < matrizN.dimensionMatriz; ++j)
			matrizN.arrayMatriz[i][j] = x;						//Todos los elementos de la matriz seran = x
	}//for
	return matrizN;
}//tMatriz matrizConstante

tVector operator*(const tMatriz & m, const tVector & v) {		//Multiplica una matriz por un vector
	tVector vSalida;
	vSalida.tam = v.tam;
	int i;
	int j;
	double valorPos = 0;
	for (i = 0; i < m.dimensionMatriz; ++i) {
		valorPos = 0;
		for (j = 0; j < m.dimensionMatriz; ++j) {
			valorPos += m.arrayMatriz[i][j] * v.datos[j];			//Multiplica la pos del array (columna i) * pos i del vector
		}//for
		vSalida.datos[i] = valorPos;
	}//for
	return vSalida;
}//tVector operator*

tMatriz operator+(const tMatriz & m1, const tMatriz & m2) {		//Suma dos matrices.
	tMatriz mSalida;
	mSalida.dimensionMatriz = m1.dimensionMatriz;

	for (int j = 0; j < m1.dimensionMatriz; ++j) {
		for (int i = 0; i < m1.dimensionMatriz; ++i) {
			mSalida.arrayMatriz[i][j] = m1.arrayMatriz[i][j] + m2.arrayMatriz[i][j];
		}//for
	}//for
	return mSalida;
}//tMatriz opertator+

tMatriz operator*(double x, const tMatriz & m) {	//Obtiene la matriz que se obtiene multiplicando cada elemento de 'm' por 'x'
	tMatriz mSalida;
	mSalida.dimensionMatriz = m.dimensionMatriz;

	for (int j = 0; j < m.dimensionMatriz; ++j) {
		for (int i = 0; i < m.dimensionMatriz; ++i) {
			mSalida.arrayMatriz[i][j] = m.arrayMatriz[i][j] * x;
		}//for
	}//for
	return mSalida;
}//tMatriz operator*

tMatriz desdeEnlacesAMatriz(const tMatriz & L) {		//Obtiene M, a partir de L.	Obteniendo primero M' y Cn tal que M = (1 - c)Cn + cM'

	int i, j, k;
	int Nj = 0, N = L.dimensionMatriz;
	//N es el numero total de archivos
	tMatriz Mprima;
	inicializaM(Mprima, N, 0.0);
	tMatriz M;
	inicializaM(M, N, 0.0);
	tMatriz Cn;					//Cn es matriz con todos sus valores 1/N
	inicializaM(Cn, N, 1.0/N);

	for (j = 0; j < N; ++j) {
		Nj = 0;
		for (k = 0; k < N; ++k) {	//Consigo Nj, la cantidad de enlaces de Aj hacia otro archivo
			if (L.arrayMatriz[k][j] == 1.0)
				++Nj;
		}//for
		
		if (Nj != 0)	//Debemos a las pos donde este un '1' y poner 1/Nj
		{
			for (i = 0; i < N; ++i)
			{
				if (L.arrayMatriz[i][j] == 1.0)
					Mprima.arrayMatriz[i][j] = 1.0 / Nj;
			}//for
		}//if
		else		//Para todas las posiciones de i hay que poner 1/N
		{
			for (i = 0; i < N; ++i)
			{
				Mprima.arrayMatriz[i][j] = 1.0 / N;
			}//for
		}//else
	}//for Mprima										//Aquí ya tengo M' (Mprima)

	Cn = 0.15 * Cn;								//(1 - 0.85)Cn

	Mprima = 0.85 * Mprima;						//cM'

	M = Cn + Mprima;							//M = (1 - c)Cn + cM'
	return M;
}//tMatriz desdeEnlacesAMatriz

tVector vectorUnos(const int &dimensionVector) {
	//Dada una dimensión de una matriz, obtenemos un vector de 'unos' de esa dimensión
	tVector vectorUnos;
	vectorUnos.tam = dimensionVector;
	for (int i = 0; i < dimensionVector; ++i)
		vectorUnos.datos[i] = 1.0;
	return vectorUnos;
}//tVector vectorUnos

bool proximos(const tVector &v1, const tVector &v2, double epsilon)	//Comprueba si dos vectores son próximos
{
	int i = 0;
	while (i < v1.tam && abs(1 - v1.datos[i] / v2.datos[i]) < epsilon)
		i++;
	return i == v1.tam;
} // proximos

tVector normaliza(const tVector &v1)	//Normalizamos el vector (dividimos entre el primer componente)
{
	tVector resultado;
	resultado.tam = v1.tam;
	for (int i = 0; i < v1.tam; ++i)
		resultado.datos[i] = v1.datos[i] / v1.datos[0];
	return resultado;
}//tVector normaliza

tVector vectorX(tMatriz &M) {	//Dada una matriz 'M', obtenemos los valores de relevancia en un vector 'w1'
	tVector v = vectorUnos(M.dimensionMatriz);
	tVector w = M * v;
	while (!proximos(v, w, 0.00001)) {		//epsilon = 0.00001
		v = w;			//w igual al w1 ANTERIOR
		w = M * v;		//w1 sera nuestro w2 = w1 * 
	}//while
	return normaliza(v);
}//tVector vectorX