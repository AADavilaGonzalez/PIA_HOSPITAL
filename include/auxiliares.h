#pragma once
#include "hospital.h"

void paciente_init(Paciente* paciente);
void paciente_destroy(Paciente* paciente);
const char* get_string_servicio(Servicio servicio);
const char* get_string_genero(Genero genero);
int capturar_entero(int min, int max, const char* msg);
void capturar_string(Dstring string, size_t longitud, const char* msg);
void capturar_sintomas(Dstring sintomas);
void print_separador(const char* titulo, size_t ancho, char relleno, FILE* archivo);
void print_paciente(Paciente* paciente, FILE* archivo);
int parsear_paciente(Paciente* paciente, FILE* entrada);
unsigned int get_siguiente_no_registro(FILE * archivo, Paciente* buffer);
