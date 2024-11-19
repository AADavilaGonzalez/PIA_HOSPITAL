#pragma once
#include <stdio.h>
#include "dstring.h"
#include "misc.h"

#define ARCHIVO_PACIENTES "pacientes.txt"
#define ARCHIVO_TMP ".tmp_pacientes.txt"
#define ANCHO_IMPRESION 60

#define L_NOMBRE 100
#define L_DESCRIPCION 1000
#define L_CALLE 50
#define L_COLONIA 50
#define L_MUNICIPIO 50

typedef enum {
    CONSULTA_EXTERNA,
    EMERGENCIA
} Servicio;

typedef enum {
    HOMBRE,
    MUJER,
} Genero;

typedef struct {
    Dstring calle;
    Dstring colonia;
    Dstring municipio;
    unsigned int numero;
    unsigned int cp;
} Direccion;

typedef struct {
    unsigned int no_registro;
    unsigned int consultorio;
    unsigned int edad;
    Dstring nombre;
    Dstring sintomas;
    Servicio servicio;
    Genero genero;
    Direccion direccion;
} Paciente;

void init_buffer_paciente(Paciente* buffer);
void alta_paciente(FILE* archivo, Paciente* buffer);
void busqueda_edicion_paciente(FILE** ptr_archivo, Paciente* buffer);
void listado_pacientes(FILE* archivo, Paciente* buffer);
void baja_paciente(FILE** ptr_archivo, Paciente* buffer);
void liberar_recursos(FILE* archivo, Paciente* buffer);