#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dstring.h"

//Politica de crecimiento del espacio de memoria reservado
#define PC(capacidad) (capacidad*2+1)

struct dstring_s {
    size_t longitud;
    size_t capacidad;
    char* contenido;
};

/*Inicializar un string en el heap desde un arreglo de caractres o
vacio si datos==NULL*/
Dstring dstring_init(const char* datos, size_t capacidad)
{
    Dstring string = (Dstring)malloc(sizeof(struct dstring_s));
    if(!datos) {
        string->longitud=0;
        string->capacidad=capacidad;
        string->contenido=malloc(capacidad+1);
        string->contenido[0]='\0';
        return string;
    }
    string->longitud=strlen(datos);
    string->capacidad=string->longitud>capacidad ? string->longitud : capacidad;
    string->contenido=malloc(string->capacidad+1);
    strcpy(string->contenido, datos);
    return string;
}

/*Cambiar la capacidad de un string, redujiendo su longitud si es necesario*/
void dstring_resize(Dstring string, size_t capacidad)
{
    char* nuevo_contenido = realloc(string->contenido, capacidad+1);
    if(nuevo_contenido) {
        string->contenido = nuevo_contenido;
        if(string->longitud > capacidad) string->longitud=capacidad;
        string->capacidad = capacidad;
    }
    return;
}

/*Copia los contenidos de un arreglo de caracteres a el string*/
void dstring_get(Dstring string, const char* origen)
{
    int i;
    size_t longitud_origen = strlen(origen);
    if(longitud_origen>string->capacidad)
        dstring_resize(string, longitud_origen);
    for(i=0; i<longitud_origen; i++)
        string->contenido[i]=origen[i];
    string->contenido[i]='\0';
    string->longitud=longitud_origen;
    return;
}

/*Copia los contenidos de un arreglo de caracteres a el string hasta llenar la capacidad
del string o no tener mas caracteres por copiar*/
void dstring_fill(Dstring string, const char* origen)
{
    int i;
    size_t nueva_longitud = strlen(origen);
    if(nueva_longitud>string->capacidad)
        nueva_longitud=string->capacidad;
    for(i=0; i<nueva_longitud; i++)
        string->contenido[i]=origen[i];
    string->contenido[i]='\0';
    string->longitud=nueva_longitud;
    return;
}

/*Agrega los contenidos de un arreglo de caracteres al final del string*/
void dstring_append(Dstring string, const char* origen)
{
    int i;
    size_t longitud_origen = strlen(origen);
    size_t nueva_longitud = string->longitud + longitud_origen;
    if(nueva_longitud>string->capacidad)
        dstring_resize(string, PC(string->capacidad)+longitud_origen);
    char* punta = string->contenido + string->longitud;
    for(i=0; i<longitud_origen; i++)
        punta[i]=origen[i];
    punta[i]='\0';
    string->longitud=nueva_longitud;
    return;
}

/*Intenta copiar los contenidos de un archivo al string, avanzando el indicador de
posicion del archivo hasta topar con el caracter delimitador o EOF y devuelve
la cantidad de caracteres copiados exitosamente*/
int dstring_fget(Dstring string, FILE* entrada, char delimitador)
{
    int c, i=0;
    while(isspace(c=fgetc(entrada)));
    while(c!=delimitador && c!=EOF) {
        if(i>=string->capacidad)
            dstring_resize(string, PC(string->capacidad));
        string->contenido[i]=c;
        c=fgetc(entrada);
        i++;
    }
    string->contenido[i]='\0';
    string->longitud=i;
    return i;
}

/*Copia los contenidos de un archivo al string, avanzando el indicador de
posicion del archivo  hasta topar con el caracter delimitador, EOF
o llenar la capacidad del string, devuelve la cantidad de caracteres copiados*/
int dstring_ffill(Dstring string, FILE* entrada, char delimitador)
{
    int c, i=0;
    while(isspace(c=fgetc(entrada)));
    while(c!=delimitador && c!=EOF) {
        if(i>=string->capacidad) break;
        string->contenido[i]=c;
        c=fgetc(entrada);
        i++;
    }
    string->contenido[i]='\0';
    string->longitud=i;
    return i;
}

/*Agrega los contenidos de un archivo al final del string avanzando el indicador de
posicion del archivo hasta topar con el caracter delimitador o EOF y devuelve
la cantidad de caracteres agregados exitosamente*/
int dstring_fappend(Dstring string, FILE* entrada, char delimitador)
{
    int c, i=0;
    char* punta = string->contenido + string->longitud;
    while(isspace(c=fgetc(entrada)));
    while(c!=delimitador && c!=EOF) {
        if(string->longitud+i>=string->capacidad)
            dstring_resize(string, PC(string->capacidad));
        punta[i]=c;
        c=fgetc(entrada);
        i++;
    }
    punta[i]='\0';
    string->longitud+=i;

}

/*Intenta copiar los siguientes 'n' caracteres de un archivo al string devolviendo
la cantidad de caracteres copiados exitosamente*/
int dstring_fread(Dstring string, FILE* entrada, size_t n)
{
    int c, i=0;
    if(n>string->capacidad)
        dstring_resize(string, n);
    while(isspace(c=fgetc(entrada)));
    if(c==EOF) return i;
    string->contenido[i]=c;
    for(int i=1; i<n; i++) {
        c=fgetc(entrada);
        if(c==EOF) break;
        string->contenido[i]=c;
    }
    string->contenido[i]='\0';
    string->longitud=i;
    return i;
}

/*Convierte al estring en un string vacio*/
void dstring_flush(Dstring string) {string->longitud=0; string->contenido[0]='\0'; return;}

/*Regresa una referencia constante para poder leer del string
directamente pero sin poder modificarlo*/
const char* dstring_decay(Dstring string) {return (const char*)string->contenido;}

/*Regresa la longitud del string*/
size_t dstring_get_longitud(Dstring string) {return string->longitud;}

/*Regresa si el estring esta lleno*/
int dstring_isfull(Dstring string) {return string->longitud==string->capacidad;}

//Libera el espacio de memoria dedicado al string
void dstring_destroy(Dstring string)
{
    free(string->contenido);
    free(string);
    return;
}