#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <list>

#include "librerias.h"
// Hecho por Sebastian Guarnizo Campos, Maikol Alexander Vergara y Santiago Vides Salcedo
using namespace std;

int main(int argc, char const *argv[])
{
    char opcion[50], delimitador[] = " ";
    vector<string> comandos;    
    vector<CodigosGeneticos> lista;    
    int it = 0, cont = 0;
    bool bandera=false;
    bool centinela;
    do
    {
        cout << "$ ";
        cin.getline(opcion, 50);
        char *token = strtok(opcion, delimitador);
        if (token != NULL)
        {
            while (token != NULL)
            {
                comandos.push_back(token);                
                token = strtok(NULL, delimitador);                
            }
        }
        

        if (comandos[0] == "cargar")
        {
            if (comandos.size() == 1)
            {
                cout << "   cargar argumento no valido" << endl;
                cout << "   cargar nombre_comandos" << endl;
            }
            else if (strstr(comandos[1].c_str(), ".fa") == NULL)
            {
                cout << "   archivo no valido deje ser un .fa" << endl;
            }
            else
            {                   
                // Leer archivo cargar AligSeq85678-lin.fa
                comandos[1] = "archivosFASTA/" + comandos[1];
                lista.clear();
                guardar(lista, comandos[1]);    
                centinela = true;            
                
            }
        }

        else if (comandos[0] == "conteo")
        {            
            if (comandos.size() > 1)
            {
                cout << "   conteo argumento no valido" << endl;
                cout << "   conteo " << endl;
            }
            else
            {                
                if (centinela == true){
                    cout<<lista.size()<<" secuencias cargadas en memoria"<<endl;
                }
            }
        }
        else if (comandos[0] == "listar_secuencias")
        {
            if (comandos.size() > 1)
            {
                cout << "listar_secuencias argumento no valido" << endl;
                cout << "listar_secuencias " << endl;
            }
            else if (comandos.size() == 1)
            {
                cout << "Lista de secuencias" << endl;
            }
        }
        else if (comandos[0] == "histograma")
        {
            if (comandos.size() > 2)
            {
                cout << "histograma argumento no valido" << endl;
                cout << "histograma descripcion_secuencia" << endl;
            }
            else if (comandos.size() == 2)
            {
                cout << "Histograma realizado" << endl;
            }
        }
        else if (comandos[0] == "es_subsecuencia")
        {
            if (comandos.size() == 1)
            {
                cout << "es_subsecuencia argumento no valido" << endl;
                cout << "es_subsecuencia secuencia" << endl;
            }
            else if (comandos.size() == 2)
            {
                cout << "Subsecuencia realizado" << endl;
            }
        }
        else if (comandos[0] == "enmascarar")
        {
            if (comandos.size() == 1)
            {
                cout << "enmascarar argumento no valido" << endl;
                cout << "enmascarar secuencia" << endl;
            }
            else if (comandos.size() == 2)
            {
                cout << "Enmascarado realizado" << endl;
            }
        }
        else if (comandos[0] == "guardar")
        {
            if (comandos.size() == 1)
            {
                cout << "guardar argumento no valido" << endl;
                cout << "guardar nombre_archivo" << endl;
            }
            else if (comandos.size() == 2)
            {
                cout << "Guardado realizado" << endl;
            }
        }
        else if (comandos[0] == "codificar")
        {
            if (comandos.size() == 1)
            {
                cout << "codificar argumento no valido" << endl;
                cout << "codificar nombre_archivo.fabin" << endl;
            }
            else if (comandos.size() == 2)
            {
                cout << "Codificado realizado" << endl;
            }
        }
        else if (comandos[0] == "decodificar")
        {
            if (comandos.size() == 1)
            {
                cout << "decodificar argumento no valido" << endl;
                cout << "decodificar nombre_archivo.fabin" << endl;
            }
            else if (comandos.size() == 2)
            {
                cout << "Decodificado realizado" << endl;
            }
        }
        else if (comandos[0] == "ruta_mas_corta")
        {
            if (comandos.size() < 6)
            {
                cout << "ruta_mas_corta argumento no valido" << endl;
                cout << "ruta_mas_corta descripcion_secuencia i j x y" << endl;
            }
            else if (comandos.size() == 6)
            {
                cout << "Ruta mas corta realizado" << endl;
            }
        }
        else if (comandos[0] == "base_remota")
        {
            if (comandos.size() < 4)
            {
                cout << "base_remota argumento no valido" << endl;
                cout << "base_remota descripcion_secuencia i j" << endl;
            }
            else if (comandos.size() == 4)
            {
                cout << "Base remota realizado" << endl;
            }
        }
        else if (comandos[0] == "salir")
        {
            exit(0);
        }

        cout << endl;

        system("Pause");
        system("CLS");
        if (comandos[0] == "Ayuda" || comandos[0] == "ayuda")
        {
            cout << endl
                 << "  Lista de comanados" << endl;
            cout << "     1 -> cargar nombre_archivo" << endl;
            cout << "     2 -> conteo" << endl;
            cout << "     3 -> listar_secuencias" << endl;
            cout << "     4 -> histograma descripcion_secuencia" << endl;
            cout << "     5 -> es_subsecuencia secuencia" << endl;
            cout << "     6 -> enmascarar secuencia" << endl;
            cout << "     7 -> guardar nombre_archivo" << endl;
            cout << "     8 -> codificar nombre_archivo.fabin" << endl;
            cout << "     9 -> decodificar nombre_archivo.fabin" << endl;
            cout << "     10 -> ruta_mas_corta descripcion_secuencia i j x y" << endl;
            cout << "     11 -> base_remota descripcion_secuencia i j" << endl;
            cout << "     12 ->salir" << endl;
        }
        comandos.clear();
    } while (bandera == false);

    exit(0);
}