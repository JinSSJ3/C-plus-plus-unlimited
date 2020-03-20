/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Unlimited_functions_LP1.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define INCREMENTO 0
#define J J
#define CODIGO 0
#define NOMBRE 1

/**************************************************************************/
/***********************      CADENAS     ********************************/
/**************************************************************************/
char* get_cad_mem_exacta(char* buffer) {
    //obtiene la cadena en tamaño exacto, el input es un arreglo estatico de char
    int tam = strlen(buffer)+1;
    char *cadena_mem_exacta = new char[tam + 1];
    strncpy(cadena_mem_exacta, buffer, tam);
    return cadena_mem_exacta;
}
/******************************************************************************/
/*******************      ARREGLOS MEM DINAMICA        ************************/
/******************************************************************************/
template <typename J>
void incrementar_lista(J*& lista,int &tam){
    int newtam= tam+INCREMENTO;
    J* lista_incrementada= new J[newtam];
    for(int i=0;i<tam;i++){
        lista_incrementada[i]= *(lista+i);
    }
    if(lista!=0) delete[]lista;
    lista=lista_incrementada;
    tam= newtam;
}
template void incrementar_lista(int *& lista,int &tam);
template void incrementar_lista(char **& lista,int &tam);
template void incrementar_lista(void **& lista,int &tam);

template <typename J>
void insertar_en_lista_incrementos(J*& lista, J dato, int cant, int &tam){
    if(cant==tam)
        incrementar_lista(lista,tam);
    lista[cant]=dato;
}
template void insertar_en_lista_incrementos(int*& lista, int dato, int cant, int &tam);
template void insertar_en_lista_incrementos(char**& lista, char* dato, int cant, int &tam);
template void insertar_en_lista_incrementos(void**& lista, void* dato, int cant, int &tam);

template <typename J>
J*get_lista_mem_exacta(J* lista, int numDat) {
    J* lista_nueva = new J[numDat+1];
    for(int i=0;  i<numDat ; i++)
        lista_nueva[i]=lista[i];
    lista_nueva[numDat]=0;//para terminar las impresines
    //if(lista!=NULL) delete[]lista;
    return lista_nueva;
}
template int*get_lista_mem_exacta(int* lista, int numDat);
template char**get_lista_mem_exacta(char** lista, int numDat);
template void**get_lista_mem_exacta(void** lista, int numDat);
/******************************************************************************/
/**********************     PUNTEROS VOID (ARBOLES, listas , colas) ***************************/
/******************************************************************************/
#define IZQ 0
#define DAT 1
#define DER 2
#define ABB 3
void insertar_arbol(void* &a, void * dato, int (*compara_registro)(const void*,const void*) ) {
    void** arbol = (void**) a;
    
    if(arbol == NULL){
        arbol = new void*[ABB];
        arbol[DAT] = dato;
        arbol[IZQ] = NULL;
        arbol[DER] = NULL;
        a = arbol;
        return;
    }
    //si no es NULL esntoces comparo IZQ o DER
    int comparacion = compara_registro(dato,arbol[DAT]);
    if(comparacion == 0 ){//igual que la raiz
        arbol[DAT] = dato;
        return;
    }else if(comparacion < 0 ){//menor a la raiz
        insertar_arbol(arbol[IZQ],dato,compara_registro);
    }else{
        insertar_arbol(arbol[DER],dato,compara_registro);
    }

}
void imprimir_arbol(void *&a, void (*imprime_registro)(void*)){
    if(a == NULL){
        return;
    }
    void** arbol = (void**) a;
    
    imprimir_arbol(arbol[IZQ],imprime_registro);
    imprime_registro(arbol[DAT]);
    imprimir_arbol(arbol[DER],imprime_registro);
}
void* buscar_arbol(void* a, char * nombre_key, int (*compara_registro)(const void*,const void*)) {
    if(a == NULL) return a;
    
    void** arbol = (void**) a;
    void* registro[2];
    registro[NOMBRE] =nombre_key;
    int comparacion = compara_registro(registro,arbol[DAT]) ;
    
    if(comparacion ==0){
        return arbol[DAT];
    }else if(comparacion < 0 ){//menor a la raiz
        buscar_arbol(arbol[IZQ],nombre_key,compara_registro);
    }else{
        buscar_arbol(arbol[DER],nombre_key,compara_registro);
    }
}
/************USANDO PUNTEROS A FUNCION CON OBJETO STREAM ***************/
void imprimir_arbol(void *&a, ostream& out, void (*imprime_registro)(const void*,ostream&)){
    if(a == NULL){
        return;
    }
    void** arbol = (void**) a;
    
    imprimir_arbol(arbol[IZQ],out,imprime_registro);
    imprime_registro(arbol[DAT],out);
    imprimir_arbol(arbol[DER],out,imprime_registro);
}

void insertar_en_lista(void* &l, void* registro, int(*compara_registro)(const void*, const void*)) {
    //la lista void* va por referencia porque en el caso base apuntara al primer elemento
    //recibo la funcion de comparacion como parametro
    void ** lista = (void**) l;
    void ** nuevo = new void*[2];
    nuevo[0] = registro;
    void**ant = 0;
    void**rec = lista;
    while (rec != 0) {
        if (compara_registro(registro, rec[0]) < 0) break;
        ant = rec;
        rec = (void**) (rec[1]);
    }
    if (ant == 0) lista = nuevo;
    else ant[1] = nuevo;
    nuevo[1] = rec;
    //////////
    l = lista;
}

/******************************************************************************/
/**********************       PUNTEROS A FUNCION      *************************/
/******************************************************************************/
void* lee_registro() {
    int *codigo = new int;
    char* nombre;
    char buffer[100];
    void** registro;

    cin >> *codigo;
    if (cin.eof() or cin.fail()) return NULL;
    cin >> ws;
    cin.getline(buffer, 100);
    nombre = get_cad_mem_exacta(buffer);
    
    registro = new void*[2];
    registro[CODIGO] = codigo;
    registro[NOMBRE] = nombre;
    
    return registro;
}
void imprime_registro(void* reg) {
    void** registro = (void**) reg;
    char* nombre = (char*) registro[NOMBRE];
    int * codigo = (int *) registro[CODIGO];
    cout << "Codigo: " << *codigo << setw(15)<<"Nombre :" <<  nombre << endl;
}
int compara_registro(const void* reg1,const void* reg2) {
    void** registro1 = (void**) reg1;
    void** registro2 = (void**) reg2;
    char* nomb1 = (char*) registro1[NOMBRE];
    char* nomb2 = (char*) registro2[NOMBRE];

    return strcmp(nomb1, nomb2);
}
/***************        ENVIANDO UN OBJETO STREAM        ***************/
void* lee_registro(istream& in) {
    int *codigo = new int;
    char* nombre;
    char buffer[100];
    void** registro;

    in >> *codigo;
    if (in.eof() or in.fail()) return NULL;
    in >> ws;
    in.getline(buffer, 100);
    nombre = get_cad_mem_exacta(buffer);
    
    registro = new void*[2];
    registro[CODIGO] = codigo;
    registro[NOMBRE] = nombre;
    //registro = get_registro("dds",codigo,nombre);
    return registro;
}
void imprime_registro(const void* reg, ostream& out) {
    void** registro = (void**) reg;
    char* nombre = (char*) registro[NOMBRE];
    int * codigo = (int *) registro[CODIGO];
    out << "Codigo: " << *codigo << setw(15)<<"Nombre :" <<  nombre << endl;
}
/****************************      CLASES VOID*      *************************/
int compara_registro_clase(const void* reg1,const void* reg2) {
//    Libro* lib1 = (Libro*) reg1;
//    Libro* lib2 = (Libro*) reg2;
//
//    return strcmp(lib1->GetCodigo_Libro(), lib2->GetCodigo_Libro());
}

void imprime_registro_clase(const void* reg, ostream& out) {
//    Libro* lib = (Libro*) reg;
//    lib->imprimir(out);
}

/******************************************************************************/
/*********************            ARCHIVOS                **********************/
/******************************************************************************/
void validar_archivo(ifstream& arch, char *name){
    if(!arch){
        cerr << "Error al abrir el archivo "  << name << endl;
        exit(1);
    }
}
void validar_archivo(ofstream& arch, char* name){
    if(!arch){
        cerr << "Error al abrir el archivo "  << name << endl;
        exit(1);
    }
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/