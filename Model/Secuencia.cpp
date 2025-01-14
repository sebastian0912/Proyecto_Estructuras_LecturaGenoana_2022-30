
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <iomanip>

#include "Secuencia.h"
#include "Caracteres.cpp"
#include "Arbol/NodeHuffmanTree.cpp"
#include "Codificacion/Codificacion.cpp"

#define MAX_LENGHT 1000

using namespace std;

// Constructor
Secuencia::Secuencia() {}

Secuencia::~Secuencia() {}

unordered_map<char, string> huffmanCode;
vector<char> listaLetrasArchivo;

void guardar(list<Secuencia> &lista, string nombre_archivo)
{
    char *str = new char[800];
    string datos;
    ifstream fe(nombre_archivo);
    int cont = 0, aux = 0;
    // Comprobar si el archivo esta vacio y luego leeerlo
    if (fe.is_open())
    {
        string sec;
        while (!fe.eof())
        {
            fe.getline(str, MAX_LENGHT);
            if (str[0] == '>')
            {
                Secuencia secuencia;
                secuencia.setNombre_sec(datos);
                secuencia.setSecuencia(sec);

                secuencia.setTamano(cont);

                lista.push_back(secuencia);
                sec = "";
                datos = "";
                aux = 0;

                datos = str;
            }
            else
            {
                // copiar solo la primera secuencia
                if (aux == 0)
                {
                    sec = str;
                    cont = sec.size();
                    aux++;
                }
                else
                {
                    sec += str;
                }
            }
        }
        Secuencia secuencia;
        secuencia.setNombre_sec(datos);
        secuencia.setSecuencia(sec);
        secuencia.setTamano(cont);
        lista.push_back(secuencia);
        sec = "";
        aux = 0;
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    fe.close();
    lista.pop_front();
    cout << "Secuencias guardadas" << endl;
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        cout << "     " << it->getNombre_sec() << endl;
        cout << "Ancho: " << it->getTamano() << endl;
        cout << "     " << it->getSecuencia() << endl;
    }
    cout << "Tamaño de la lista: " << lista.size() << endl;
    fe.close();
}

void listarSecuenciaw(vector<char> cod, int &aux)
{
    int cont = 0, cont2 = 0;
    vector<char> codigos = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
    for (int i = 0; i < codigos.size(); i++)
    {
        vector<char>::iterator it = cod.begin();
        while (it != cod.end())
        {
            if (*it == codigos[i])
            {
                cont++;
            }
            if (*it == '-')
            {
                cont2++;
            }
            it++;
        }

        if (cont != 0 && cont2 != 0 && codigos[i] != '-')
        {
            aux -= cont;
            cout << codigos[i] << " Contiene: " << cont << " bases" << endl;
        }
        else if (cont != 0 && cont2 == 0 && codigos[i] != '-')
        {
            aux += cont;
            cout << codigos[i] << " Contiene: " << cont << " bases" << endl;
        }
        cont = 0;
        cont2 = 0;
    }
}

void listarSecuencias(list<Secuencia> lista)
{
    int cont = 0;
    // Cuantas veces cada codigo aparece en la secuencia por cada codigo genetico
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        vector<char> secuencias;
        for (int i = 0; i < it->getSecuencia().size(); i++)
        {
            secuencias.push_back(it->getSecuencia()[i]);
        }
        vector<char>::iterator it2 = secuencias.begin();

        // it2 vacio
        if (it2 == secuencias.end())
        {
            break;
        }
        else
        {
            cout << it->getNombre_sec() << endl;
            listarSecuenciaw(secuencias, cont);
            if (cont < 1)
            {
                cout << "Esta secuencia contiene al menos " << cont * -1 << " bases" << endl;
            }
            else
            {
                cout << "Esta secuencia contiene " << cont << " bases" << endl;
            }
            cont = 0;
        }
        /*for (int i = 0; i < secuencias.size(); i++)
        {
            cout << secuencias[i];
        }*/
        secuencias.clear();
        system("pause");
    }
}

void histograma(string nombre_secuencia, list<Secuencia> lista)
{
    int cont = 0;
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if (strstr(it->getNombre_sec().c_str(), nombre_secuencia.c_str()))
        {
            vector<char> secuencias;
            for (int i = 0; i < it->getSecuencia().size(); i++)
            {
                secuencias.push_back(it->getSecuencia()[i]);
            }
            vector<char>::iterator it2 = secuencias.begin();
            if (it == lista.end())
            {
                cout << "La secuencia " << nombre_secuencia << " esta invalidada, no se encuentra" << endl;
                break;
            }
            else
            {
                cout << it->getNombre_sec() << endl;
                listarSecuenciaw(secuencias, cont);
            }
        }
    }
}

void cuantos(string sub, vector<char> aux, int &cont2)
{
    char cadena[MAX_LENGHT];
    char subcadena[MAX_LENGHT];
    char *busqueda = NULL;
    strcpy(subcadena, sub.c_str());
    // cout<<subcadena<<endl;
    // copiar aux.secuencia a cadena
    for (int i = 0; i < aux.size(); i++)
    {
        cadena[i] = aux[i];
    } /*
     for (int i=0; i< sizeof(cadena); i++)
     {
         cout<<cadena[i];
     }    */
    busqueda = strstr(cadena, subcadena);
    if (busqueda == NULL)
    {
        cout << "La secuencia dada no existe." << endl;
    }
    while (busqueda != NULL)
    {
        cont2++;
        busqueda = strstr(busqueda + 1, subcadena);
    }
}

void sub_secuencia(string sub, list<Secuencia> lista)
{
    int cont = 0;
    // cout << sub << endl;

    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {

        // cout << "   " << it->nombre_sec << endl;
        vector<char> secuencias;
        secuencias.clear();
        for (int i = 0; i < it->getSecuencia().size(); i++)
        {
            secuencias.push_back(it->getSecuencia()[i]);
        }
        vector<char>::iterator it2 = secuencias.begin();
        cuantos(sub, secuencias, cont);
        secuencias.clear();
        // cout<<endl<<endl;
    }
    cout << endl
         << endl;
    cout << "La subsecuencia " << sub << " aparece " << cont << " veces" << endl;

    // es_subsecuencia CAACATCACCAATCA
}

void cambiarValorPorX(string sub, vector<char> &aux)
{
    // cout<<cadena<<endl;
    // cambiar valor por X donde este la secuencia completa
    int cont = sub.size();
    for (int i = 0; i < aux.size(); i++)
    {
        if (aux[i] == sub[0])
        {
            for (int j = 0; j < sub.size(); j++)
            {
                if (aux[i + j] == sub[j])
                {
                    cont--;
                }
            }
            if (cont == 0)
            {
                for (int j = 0; j < sub.size(); j++)
                {
                    aux[i + j] = 'X';
                }
            }
            cont = sub.size();
        }
    }
}

void enmascarar(string sub, list<Secuencia> &lista)
{
    vector<char> secuencias;
    string aux;
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        vector<char>::iterator it2 = secuencias.begin();
        for (int i = 0; i < it->getSecuencia().size(); i++)
        {
            secuencias.push_back(it->getSecuencia()[i]);
        }
        cambiarValorPorX(sub, secuencias);
        for (int i = 0; i < secuencias.size(); i++)
        {
            aux += secuencias[i];
        }
        it->setSecuencia(aux);

        secuencias.clear();
        aux.clear();
    }

    // listar secuencias
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        cout << it->getNombre_sec() << endl;
        cout << "Ancho: " << it->getTamano() << endl;
        cout << it->getSecuencia() << endl;
    }
}

void guardarEnArhivo(string nombreArchivo, list<Secuencia> &lista)
{
    int cont = 0;
    ofstream archivo;
    archivo.open(nombreArchivo);
    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    else
    {
        for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
        {
            archivo << it->getNombre_sec() << endl;
            for (int i = 0; i < it->getSecuencia().size(); i++)
            {
                if (cont == it->getTamano())
                {
                    archivo << endl;
                    cont = 0;
                }
                cont++;

                archivo << it->getSecuencia()[i];
            }
            cont = 0;
            archivo << endl;
        }
        archivo.close();
    }
}

bool operator>(Caracteres &s1, Caracteres &s2)
{
    return s1.getFrecuencia() > s2.getFrecuencia();
}

void sacarCaracteres(string nombreArchivo)
{
    ifstream archivo;
    archivo.open(nombreArchivo);
    // leer caracter por caracter
    char caracter;
    
    vector<char> caracteres;
    priority_queue<Caracteres> g;

    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    else
    {
        while (!archivo.eof())
        {
            archivo.get(caracter);
            if ((int)caracter >= 65 || (int)caracter <= 122 || (int)caracter == 10 || (int)caracter == 32 || (int)caracter == 13 || (int)caracter == 62)
            {
                // cout<<caracter<<endl;
                //  guardar caracteres en el vector caracteres sin repetirse
                if ((int)caracter == 10 || (int)caracter == 32 || (int)caracter == 13)
                {
                    caracter = '/';
                }
                listaLetrasArchivo.push_back(caracter);
            }
        }
        archivo.close();
    }
    /*for (int i = 0; i < listaLetrasArchivo.size(); i++)
    {
        cout<<listaLetrasArchivo[i];
    }*/
    // guardar caracteres en vector caracteres sin repetirse
    caracteres.push_back(listaLetrasArchivo[0]);
    for (int i = 0; i < listaLetrasArchivo.size(); i++)
    {
        for (int j = 0; j < caracteres.size(); j++)
        {
            if (listaLetrasArchivo[i] == caracteres[j])
            {
                break;
            }
            else if (j == caracteres.size() - 1)
            {
                caracteres.push_back(listaLetrasArchivo[i]);
            }
        }
    }

    // imprimir caracteres

    /*for (int i = 0; i < caracteres.size(); i++)
    {
        cout << caracteres[i]<<endl;
    }*/

    // contar cuantas veces aparece cada caracter y guardar lo en la cola de prioridad
    int cont = 0;
    Caracteres c = Caracteres();
    for (int i = 0; i < caracteres.size(); i++)
    {
        for (int j = 0; j < listaLetrasArchivo.size(); j++)
        {
            if (caracteres[i] == listaLetrasArchivo[j])
            {
                cont++;
            }
        }
        c.setCaracter(caracteres[i]);
        c.setFrecuencia(cont);
        g.push(c);
        cont = 0;
    }
    /*
    while (!g.empty())
    {
        Caracteres aux = g.top();
        cout << aux.getCaracter() << " " << aux.getFrecuencia() << endl;
        g.pop();
    }*/

    huffmanCode = buildHuffmanTree(g);
    cout <<endl<<endl<< "Codificacion de Huffman: " << endl
         << endl;
    for (auto pair : huffmanCode)
    {
        cout << setw(8) << pair.first << setw(20) << pair.second << endl;
    }
}

void cantidadBases(Codificacion &cod, list<Secuencia> &lista)
{
    int cont = 0, cont2 = 0;
    vector<char> codigos = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
    list<Secuencia>::iterator it = lista.begin();
    map<char, double> mapa;
    for (int i = 0; i < codigos.size(); i++)
    {
        for (it = lista.begin(); it != lista.end(); ++it)
        {

            for (int j = 0; j < it->getSecuencia().size(); j++)
            {
                if (codigos[i] == it->getSecuencia()[j])
                {
                    cont++;
                }
            }
        }

        mapa.insert({codigos[i], cont});

        cont = 0;
        cont2++;
    }
    cod.setBases(mapa);
}

void tamanoNombreSecuencia(Codificacion &cod, list<Secuencia> &lista)
{
    list<Secuencia>::iterator it = lista.begin();
    vector<int> tamNombre;
    int cont = 0;
    for (it = lista.begin(); it != lista.end(); ++it)
    {
        tamNombre.push_back(it->getNombre_sec().size());
    }
    cod.setTamanoNombresecuencia(tamNombre);
}

void ultimoCaracterDelNombre(Codificacion &cod, list<Secuencia> &lista)
{
    list<Secuencia>::iterator it = lista.begin();
    vector<char> ultimoCaracter;
    for (it = lista.begin(); it != lista.end(); ++it)
    {
        ultimoCaracter.push_back(it->getNombre_sec()[it->getNombre_sec().size() - 1]);
    }
    cod.setUltimoCaracterDelNombre(ultimoCaracter);
}

void tamanoSecuencia(Codificacion &cod, list<Secuencia> &lista)
{
    list<Secuencia>::iterator it = lista.begin();
    vector<double> tamSecuencia;
    for (it = lista.begin(); it != lista.end(); ++it)
    {
        tamSecuencia.push_back(it->getTamano());
    }
    cod.setLongitudSecuencia(tamSecuencia);
}

void generarCodifiacionArchivo(string nombreArchivo, unordered_map<char, string> &huffmanCode, Codificacion &cod, list<Secuencia> &lista)
{
    cantidadBases(cod, lista);
    cout << "Cantidad de bases: " << endl
         << endl;
    for (auto pair : cod.getBases())
    {
        cout << setw(8) << pair.first << setw(20) << pair.second << endl;
    }
}

string codificarSecuencia(vector<char> listaLetrasArchivo, unordered_map<char, string> &huffmanCode)
{
    string codificacion = "";
    for (int i=0; i < listaLetrasArchivo.size(); i++)
    {
        for (auto pair : huffmanCode)
        {
            if (listaLetrasArchivo[i] == pair.first)
            {
                codificacion += pair.second;
            }
        }
    }

    return codificacion;
}

void codificacion(string nombreArchivo, list<Secuencia> &lista)
{
    short acum;
    int tam=0; 
    Codificacion cod = Codificacion();
    generarCodifiacionArchivo(nombreArchivo, huffmanCode, cod, lista);
    for (auto pair : cod.getBases())
    {
        acum += pair.second;
    }
    cod.setCantidadBases(acum);
    cout << endl;

    cout << "Cantidad de bases: " << endl;
    cout << cod.getCantidadBases() << endl;
    cod.setCantidadSecuencias(lista.size());
    cout << endl;

    cout << "Cantidad de secuencias: " << endl;
    cout << cod.getCantidadSecuencias() << endl;
    tamanoNombreSecuencia(cod, lista);
    cout << endl;

    cout << "Tamano de nombre de secuencia: " << endl;
    for (int i = 0; i < cod.getTamanoNombresecuencia().size(); i++)
    {
        cout << cod.getTamanoNombresecuencia()[i] << endl;
    }

    ultimoCaracterDelNombre(cod, lista);
    cout << endl;
    cout << "Ultimo caracter del nombre: " << endl;
    for (int i = 0; i < cod.getUltimoCaracterDelNombre().size(); i++)
    {
        cout << cod.getUltimoCaracterDelNombre()[i] << endl;
    }

    tamanoSecuencia(cod, lista);
    cout << endl;
    cout << "Tamano de secuencia: " << endl;
    for (int i = 0; i < cod.getLongitudSecuencia().size(); i++)
    {
        cout << cod.getLongitudSecuencia()[i] << endl;
    }    

    cout << endl;
    cout << "Codificacion de Huffman: " << endl;
    cout << codificarSecuencia(listaLetrasArchivo, huffmanCode) << endl;
    string codificacion = codificarSecuencia(listaLetrasArchivo, huffmanCode);
    cout << codificacion << endl;
    cout << endl;
    vector <string > codificacionSecuencia;
    // subdividir en cadenas de 8 caracteres la codificacion y guardarla en el vector
    for (int i = 0; i < codificacion.size(); i += 8)
    {
        codificacionSecuencia.push_back(codificacion.substr(i, 8));
    }
    
    cout << "Codificacion de Huffman subdividida en 8 caracteres: " << endl;
    for (int i = 0; i < codificacionSecuencia.size(); i++)
    {
        cout << codificacionSecuencia[i] << endl;
    }
    cout << endl;
    cout << "------------------"    << endl;
    cout << codificacionSecuencia[codificacionSecuencia.size()-1] << endl;
    cout << "------------------"    << endl;
    if (codificacionSecuencia[codificacionSecuencia.size() - 1].size() < 8)
    {
        tam = 8 - codificacionSecuencia[codificacionSecuencia.size() - 1].size();
        cod.setCantidadCerosAgregados(tam);
        // rellenar con 0 hasta completar 8 caracteres a la derecha
        codificacionSecuencia[codificacionSecuencia.size() - 1].append(8 - codificacionSecuencia[codificacionSecuencia.size() - 1].size(), '0');
    }
    if (tam == 0)
    {
        cod.setCantidadCerosAgregados(0);
    }
    cout << endl;
    cout << "Cantidad de ceros agregados: " << endl;
    cout << cod.getCantidadCerosAgregados() << endl;

    

}
