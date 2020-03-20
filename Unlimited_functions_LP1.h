/* 
 * File:   Unlimited_functions_LP1.h
 * Author: Jose Manuel Serrano Amaut
 * Codigo: 20122128
 * Created on 3 de mayo de 2018, 08:34 PM
 */

#ifndef UNLIMITED_FUNCTIONS_LP1_H
#define UNLIMITED_FUNCTIONS_LP1_H

#include <iostream>
using namespace std;
#define J J
#define INCREMENTO 0
/*****************MERGESORT Y BINARY SEARCH******************/
template <typename J>
void merge(J* A, int ini1, int fin1, int ini2, int fin2, int(*compara_registro)(J,J)) {
    //mezcla del mergesort
    int i = ini1, j = ini2, k = 0;
    int N=fin2-ini1+1;
    J *B=new J[N];
    while( i<=fin1 and j<=fin2 ) {
        if(compara_registro(A[i],A[j])<0){
            B[k]=A[i];
            i++;
        }else{
            B[k]=A[j];
            j++;
        }
        k++;
    }
    while(i<=fin1 and k<=N){
        B[k]=A[i];
        k++;
        i++;
    }
    while(j<=fin2  and k<=N){
        B[k]=A[j];
        k++;
        j++;
    }
    
    k=0;
    i=ini1;
    while(k<=N and i<=fin2){
        A[i]=B[k];
        k++;
        i++;
    }
    if(N>0) delete[]B;
}
template <typename J>
void merge_sort(J* A, int ini, int fin, int(*compara_registro)(J,J)) {
    //ordenamiento mergesort cualquier dato, pero recibe la funcion de comparacion
    int med = (fin + ini) / 2;
    if (fin > ini) {
        merge_sort(A, ini, med,compara_registro);
        merge_sort(A, med + 1, fin,compara_registro);
        merge(A, ini, med, med + 1, fin,compara_registro);
    }
    return;
}
template <typename J>
int binary_search(J* A, J dato, int ini, int fin, int(*compare)(J, J)) {
    int result = -1;
    int med = (ini + fin) / 2;
    if (ini <= fin) {
        if (compare(A[med] , dato)==0)
            return med;
        else if (compare(dato , A[med])==1)
            result = binary_search(A, dato, ini, med - 1,compare);
        else if (compare(dato , A[med]) ==-1)
            result = binary_search(A, dato, med + 1, fin,compare);
    }
    return result;
}
//*************** CHAR* cadena en memoria exacta*********************
char* get_cad_mem_exacta(char* ) ;

//*****************/ARREGLOS DINAMICOS/********************
template <typename J> void incrementar_lista(J*& lista,int &tam);
template <typename J> void insertar_en_lista_incrementos(J*& lista, J dato, int cant, int &tam);
template <typename J> J*get_lista_mem_exacta(J* lista, int numDat);

//**************** PUNTEROS VOID* ARBOLES**************************/
void insertar_arbol(void* &a, void * dato, int (*compara_registro)(const void*,const void*) ) ;
void imprimir_arbol(void *&a, void (*imprime_registro)(void*));
void* buscar_arbol(void* a, char * nombre_key, int (*compara_registro)(const void*,const void*));
/******************PUNTERO A FUNCION Y OBJETO STREAM EN PARAMETRO**************/
void imprimir_arbol(void *&a, ostream& out, void (*imprime_registro)( const void*,ostream&));
//lista enlazada
void insertar_en_lista(void* &l, void* registro, int(*compara_registro)(const void*, const void*));

/****************    USUARIOOOOO  SOLO PUNTERO A FUNCION  ***************/
void* lee_registro();
void imprime_registro(void* );
int compara_registro(const void*,const void*);   
/***************     PUNTERO A FUNCION CON OBJETO STREAM COMO PARAMETRO  ******/
void* lee_registro(istream&);
void imprime_registro(const void* , ostream&);
/******************     CLASES*  VOID     ***************/
int compara_registro_clase(const void* reg1,const void* reg2);
void imprime_registro_clase(const void* reg, ostream& out);
/****************ARCHIVOS***********************/
void validar_archivo(ifstream& arch, char *name);
void validar_archivo(ofstream& arch, char* name);


#endif /* UNLIMITED_FUNCTIONS_LP1_H */

