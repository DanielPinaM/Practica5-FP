const int MAX_DIM = 50;

typedef struct
{
    double datos[MAX_DIM];
    int tam;
} tVector;


int main()
{
    tIndicePalabras idx = nuevoIndice();
    tListaCadenas totales = nuevaListaCadenas();
    tMatriz L = inicMatriz(1, 0.0);	
    string nombreArchivo = pedirArchivo();
    crearTabla(nombreArchivo, idx, totales, L);
    tMatriz M = desdeEnlacesAMatriz(L, C); // M = (1 - C) * Cn + C * M´
    tVector v = vectorPropio(M, 0.000001);
    string palabra = pedirPalabra();
    while (palabra != "fin")
    {
        tListaCadenas archivos = getValor(idx, palabra);
        tVector valores = valoresSubLista(archivos, totales, v);
        ordenaValores(archivos, valores);
        muestraArchivos(archivos, valores);
        palabra = pedirPalabra();
    }//while
} // main


tVector normaliza(const tVector &v1)
{
    tVector result;
    result.tam = v1.tam;
    for (int k = 0; k < v1.tam; k++)
    {
        result.datos[k] = v1.datos[k] / v1.datos[0];
    }
    return result;     
} // normaliza


bool proximos(const tVector &v1, const tVector &v2, double epsilon)		//Para ver si dos vectores son proximos
{
    int i = 0;
    while (i < v1.tam && abs(1 - v1.datos[i] / v2.datos[i]) < epsilon)
    {
	   i++;	 
    }
    return i == v1.tam;
} // proximos


tVector vectorPropio(const tMatriz &M, double epsilon)
{
    tVector v = vectorUnos(M.columnas);
    tVector w = M * v;
    while (!proximos(v, w, epsilon))
    {
        v = w;
        w = M * v;
    }
    return normaliza(v);
} // vectorPropio


void annadir(tVector &v, double e)
{
    v.datos[v.tam] = e;
    v.tam++;
} // annadir


tVector valoresSubLista(const tListaCadenas &archivos, const tListaCadenas &enlaces, const tVector &v)
{
    tVector result = vectorUnos(0);
    int pos;
    for (int i = 0; i < getTamanno(archivos); i++)
    {
        string archivo = getCadena(archivos, i);
        pos = getPosicion(enlaces, archivo);
        annadir(result, v.datos[pos]);
    }
    return result;
} // valoresSubLista