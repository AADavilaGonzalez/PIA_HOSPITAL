#include <stdlib.h>
#include <stdio.h>
#include "hospital.h"
#include "auxiliares.h"
#include "misc.h"

static const char* texto_menu_principal =
    "Ingrese una de las siguientes opciones:\n"
    "1-Alta de Paciente\n"
    "2-Busqueda o Edicion de Paciente\n"
    "3-Listado de Pacientes\n"
    "4-Baja de Paciente\n"
    "5-Salir\n";

int main(void)
{
    int opc=0;
    Paciente buffer_paciente;
    paciente_init(&buffer_paciente);
    FILE* archivo = abrir_archivo(ARCHIVO_PACIENTES);
    while(opc!=5) {
        opc = menu(texto_menu_principal, 1, 5);
        clear();
        switch(opc) {
        case 1:
            alta_paciente(archivo, &buffer_paciente);
            stop();
            break;
        case 2:
            busqueda_edicion_paciente(&archivo, &buffer_paciente);
            stop();
            break;
        case 3:
            listado_pacientes(archivo, &buffer_paciente);
            stop();
            break;
        case 4:
            baja_paciente(&archivo, &buffer_paciente);
            stop();
            break;
        }
    }
    liberar_recursos(archivo, &buffer_paciente);
    exit(EXIT_SUCCESS);
}