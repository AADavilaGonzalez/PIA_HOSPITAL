#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    false,
    true,
} bool;

#ifdef _WIN32
#define clear() system("cls")
#endif

#ifdef __unix__
#define clear() system("clear")
#endif

#ifdef __APPLE__
#define clear() system("clear")
#endif

#define es_par(num) (num%2==0)

void flush(void);
void stop(void);
int validar_entero(int min, int max);
int menu(const char* msg, int min, int max);
FILE* abrir_archivo(char* nombre_archivo);
int leer_hasta(char caracter, FILE* entrada);
int es_archivo_vacio(FILE* archivo);