#include <stdio.h>
#include <string.h>
#include "hospital.h"
#include "misc.h"
#include "dstring.h"
#include "auxiliares.h"

void paciente_init(Paciente* paciente)
{
    paciente->no_registro=0;
    paciente->consultorio=0;
    paciente->edad=0;
    paciente->nombre=dstring_init(NULL, L_NOMBRE);
    paciente->sintomas=dstring_init(NULL, L_DESCRIPCION);
    paciente->servicio=2;
    paciente->genero=2;
    paciente->direccion.calle=dstring_init(NULL, L_CALLE);
    paciente->direccion.colonia=dstring_init(NULL, L_COLONIA);
    paciente->direccion.municipio=dstring_init(NULL, L_MUNICIPIO);
    paciente->direccion.numero=0;
    paciente->direccion.cp=0;
    return;
}

void paciente_destroy(Paciente* paciente)
{
    dstring_destroy(paciente->nombre);
    dstring_destroy(paciente->sintomas);
    dstring_destroy(paciente->direccion.calle);
    dstring_destroy(paciente->direccion.colonia);
    dstring_destroy(paciente->direccion.municipio);
    return;
}

#define N_SERVICIOS 2
static const char* strings_servicios[] = {"Consulta Externa", "Emergencia", "NULL"};
const char* get_string_servicio(Servicio servicio) {return strings_servicios[servicio];}

#define N_GENEROS 2
static const char* strings_genero[] = {"Masculino", "Femenino", "NULL"};
const char* get_string_genero(Genero genero) {return strings_genero[genero];}

int capturar_entero(int min, int max, const char* msg)
{
    int valor, scan_ok;
    printf(msg);
    while(true){
        scan_ok=scanf("%d", &valor);
        if(scan_ok && valor>=min && valor <=max) break;
        printf("Ingrese un valor entre %d y %d\n", min, max);
        if(!scan_ok) flush();
    } return valor;
}

void capturar_string(Dstring string, size_t longitud, const char* msg)
{
    static const char* texto_longitud_sobrepasada =
    "Se ha sobrepasado la longitud recomendada de %u caracteres para este dato\n"
    "Desea continuar con el dato capturado o desea volver a capturar el dato?\n"
    "1-Continuar\n"
    "2-Volver a Capturar\n";

    while(true) {
        printf(msg);
        dstring_fget(string, stdin, '\n');
        if(dstring_get_longitud(string) <= longitud) break;
        printf(texto_longitud_sobrepasada, longitud);
        if(validar_entero(1,2)==1) break;
        putchar('\n');
    } return;
}

void capturar_sintomas(Dstring sintomas)
{
    static const char* texto_instrucciones_sintomas=
    "*Introduzca 'FIN' en una sola linea para terminar la captura*'\n";

    printf(texto_instrucciones_sintomas);
    Dstring buffer_de_linea = dstring_init(NULL, 50);
    dstring_flush(sintomas);
    while(true) {
        dstring_fget(buffer_de_linea, stdin, '\n');
        if(strcmp(dstring_decay(buffer_de_linea), "FIN")==0) break;
        dstring_append(sintomas, dstring_decay(buffer_de_linea));
        dstring_append(sintomas, "\n");
    }
    dstring_destroy(buffer_de_linea);
    return;
}

void print_separador(const char* titulo, size_t ancho, char relleno, FILE* salida)
{
    int ancho_titulo = titulo==NULL ? 0 : strlen(titulo);
    int ancho_restante = (ancho-ancho_titulo);
    if(ancho_restante < 0) ancho_restante = 0;
    int medio_ancho = ancho_restante/2;
    if(!es_par(ancho_restante)) fputc(relleno, salida);
    for(int i=0; i<medio_ancho; i++) fputc(relleno, salida);
    if(titulo!=NULL) fputs(titulo, salida);
    for(int i=0; i<medio_ancho; i++) fputc(relleno, salida);
    fputc('\n', salida);
    return;
}

extern const char* titulo_datos_personales;
extern const char* titulo_datos_consulta;
extern const char* titulo_sintomas;
void print_paciente(Paciente* paciente, FILE* salida)
{
    fprintf(salida, "[PACIENTE NO. %d | %s]\n", paciente->no_registro, dstring_decay(paciente->nombre));
    print_separador(titulo_datos_personales, ANCHO_IMPRESION, '-', salida);
    fprintf(salida, "* Edad:  %u\n", paciente->edad);
    fprintf(salida, "* Genero: %s\n", get_string_genero(paciente->genero));
    fprintf(salida, "* Calle:  %s\n", dstring_decay(paciente->direccion.calle));
    fprintf(salida, "* Colonia:  %s\n", dstring_decay(paciente->direccion.colonia));
    fprintf(salida, "* Municipio: %s\n", dstring_decay(paciente->direccion.municipio));
    fprintf(salida, "* No. Exterior: %u\n", paciente->direccion.numero);
    fprintf(salida, "* Codigo Postal: %u\n", paciente->direccion.cp);
    print_separador(titulo_datos_consulta, ANCHO_IMPRESION, '-', salida);
    fprintf(salida, "* No. Consultorio: %u\n", paciente->consultorio);
    fprintf(salida, "* Tipo de Servicio: %s\n", get_string_servicio(paciente->servicio));
    print_separador(titulo_sintomas, ANCHO_IMPRESION, '-', salida);
    fprintf(salida, dstring_decay(paciente->sintomas));
    print_separador(NULL, ANCHO_IMPRESION, '*', salida);
    return;
}

int parsear_servicio(FILE* entrada)
{
    int i;
    Dstring string_servicio = dstring_init(NULL, 20);
    dstring_fget(string_servicio, entrada, '\n');
    for(i=0; i<N_SERVICIOS; i++) {
        if(strcmp(get_string_servicio(i),
            dstring_decay(string_servicio))==0
        ) break;
    }
    dstring_destroy(string_servicio);
    return i;
}

int parsear_genero(FILE* entrada)
{
    int i;
    Dstring string_genero = dstring_init(NULL, 20);
    dstring_fget(string_genero, entrada, '\n');
    for(i=0; i<N_GENEROS; i++) {
        if(strcmp(get_string_genero(i),
            dstring_decay(string_genero))==0
        ) break;
    }
    dstring_destroy(string_genero);
    return i;
}

int parsear_paciente(Paciente* paciente, FILE* entrada)
{
    int c;
    c = leer_hasta('[', entrada);
    if(c==EOF) return EOF;

    leer_hasta('.', entrada); fgetc(entrada);
    fscanf(entrada, "%u", &paciente->no_registro);
    leer_hasta('|', entrada); fgetc(entrada);
    dstring_fget(paciente->nombre, entrada, ']');

    leer_hasta(':', entrada); fgetc(entrada);
    fscanf(entrada, "%u", &paciente->edad);
    leer_hasta(':', entrada); fgetc(entrada);
    paciente->genero=parsear_genero(entrada);
    leer_hasta(':', entrada); fgetc(entrada);
    dstring_fget(paciente->direccion.calle, entrada, '\n');
    leer_hasta(':', entrada); fgetc(entrada);
    dstring_fget(paciente->direccion.colonia, entrada, '\n');
    leer_hasta(':', entrada); fgetc(entrada);
    dstring_fget(paciente->direccion.municipio, entrada, '\n');
    leer_hasta(':', entrada); fgetc(entrada);
    fscanf(entrada, "%u", &paciente->direccion.numero);
    leer_hasta(':', entrada); fgetc(entrada);
    fscanf(entrada, "%u", &paciente->direccion.cp);

    leer_hasta(':', entrada); fgetc(entrada);
    fscanf(entrada, "%u", &paciente->consultorio);
    leer_hasta(':', entrada); fgetc(entrada);
    paciente->servicio=parsear_servicio(entrada);

    leer_hasta('\n', entrada);
    dstring_fget(paciente->sintomas, entrada, '*');
    return 1;
}

unsigned int get_siguiente_no_registro(FILE * archivo, Paciente* buffer)
{
    if(es_archivo_vacio(archivo)) return 1;
    unsigned int no_registro;
    rewind(archivo);
    while(parsear_paciente(buffer, archivo)!=EOF) {
        no_registro=buffer->no_registro;
    }

    return no_registro+1;
}