#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

void flush(void)
{
    int c;
    do c=getchar(); while(c!='\n' && c!=EOF);
    return;
}

void stop(void)
{
    scanf("%*c");
    flush();
    return;
}

int validar_entero(int min, int max)
{
    int valor, scan_ok;
    do {
        printf("... ");
        scan_ok=scanf("%d", &valor);
        if(!scan_ok) flush();
    } while(valor < min || valor > max);
    return valor;
}

extern const char* titulo_app;
int menu(const char* msg, int min, int max) {
    clear();
    printf("%s", titulo_app);
    printf("\n\n");
    printf("%s", msg);
    int opc=validar_entero(min, max);
    putchar('\n');
    return opc;
}

FILE* abrir_archivo(char* nombre_archivo)
{
    static const char* texto_archivo_no_encontrado =
    "No se encontro el archivo '%s' en la misma direccion que se ejecuto el programa.\n"
    "Desea crear un nuevo archivo sobreescribiendo el archivo en caso de que exista?\n"
    "1-Si\n"
    "2-No\n";

    static const char *texto_archivo_es_necesario =
    "Se necesita el archivo '%s' para proceder con la ejecucion de la aplicacion.\n"
    "*Terminano la ejecucion del programa*\n";

    static const char *texto_archivo_error_al_crear =
    "*Se ha producido un error al intentar crear el archivo '%s'*\n";

    int opc;
    FILE* archivo=fopen(nombre_archivo, "r+");
    if(!archivo) {
        printf(texto_archivo_no_encontrado, nombre_archivo);
        opc=validar_entero(1,2);
        if(opc==1) {
            archivo=fopen(nombre_archivo, "w+");
            if(!archivo) {
                printf(texto_archivo_error_al_crear, archivo);
                printf(texto_archivo_es_necesario, archivo);
                exit(EXIT_FAILURE);
            }
        }
        else {
            printf(texto_archivo_es_necesario, nombre_archivo);
            exit(EXIT_FAILURE);
        }
    }
    return archivo;
}

int leer_hasta(char caracter, FILE* entrada)
{
    int c; while((c=fgetc(entrada))!=caracter && c!=EOF);
    return c;
}

int es_archivo_vacio(FILE* archivo)
{
    long pos = ftell(archivo);
    rewind(archivo);
    if(fgetc(archivo)==EOF) return 1;
    fseek(archivo, pos, SEEK_SET);
    return 0;
}