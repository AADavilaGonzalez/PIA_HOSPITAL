#include <stdio.h>
#include <string.h>
#include "hospital.h"
#include "auxiliares.h"
#include "dstring.h"

const char* titulo_app = "Sistema de Gestion de Pacientes FCFM";
const char* titulo_datos_personales = "Datos-Personales";
const char* titulo_datos_consulta = "Datos-de-Consulta";
const char* titulo_sintomas = "Sintomas";

static const char* texto_captura_no_empleado=
    "Ingrese el numero de registro del paciente al cual modificar:\n";
static const char* texto_seleccion_genero=
    "Indique el genero del paciente:\n"
    "1-Masculino\n"
    "2-Femenino\n";
static const char* texto_seleccion_sevicio=
    "Indique el tipo de servicio que se le dio al paciente:\n"
    "1- Consulta Externa\n"
    "2- Emergencia Medica\n";

void alta_paciente(FILE* archivo, Paciente* buffer)
{
    buffer->no_registro=get_siguiente_no_registro(archivo, buffer);
    printf("Dando de alta un nuevo paciente:\n\n");

    print_separador(titulo_datos_personales, ANCHO_IMPRESION, '-', stdout);
    capturar_string(buffer->nombre, L_NOMBRE, "Nombre del paciente: ");
    buffer->edad=(unsigned int)capturar_entero(0, 150, "Edad: ");
    printf(texto_seleccion_genero); buffer->genero=(Genero)(validar_entero(1,2)-1);
    capturar_string(buffer->direccion.calle, L_CALLE, "Calle: ");
    capturar_string(buffer->direccion.colonia, L_COLONIA, "Colonia: ");
    capturar_string(buffer->direccion.municipio, L_MUNICIPIO, "Municipio: ");
    buffer->direccion.numero=(unsigned int)capturar_entero(10000, 99999, "No. Exterior: ");
    buffer->direccion.cp=(unsigned int)capturar_entero(0,999999, "Codigo Postal: ");

    print_separador(titulo_datos_consulta, ANCHO_IMPRESION, '-', stdout);
    buffer->consultorio=(unsigned int)capturar_entero(0, 999, "No. Consultorio: ");
    printf(texto_seleccion_sevicio); buffer->servicio=(Servicio)(validar_entero(1,2)-1);

    print_separador(titulo_sintomas, ANCHO_IMPRESION, '-', stdout);
    capturar_sintomas(buffer->sintomas);

    fseek(archivo, 0, SEEK_END);
    print_paciente(buffer, archivo);

    printf("El empleado ha sido dado de alta exitosamente\n");
    printf("*Regresando al menu principal*\n");
    return;
}

void busqueda_edicion_paciente(FILE** ptr_archivo, Paciente* buffer)
{

    static const char* texto_menu_de_modificacion=
    "Que desea hacer con la informacion del paciente?\n"
    "1- Modificar Nombre\n"
    "2- Modificar Edad\n"
    "3- Modificar Genero\n"
    "4- Modificar Calle\n"
    "5- Modificar Colonia\n"
    "6- Modificar Municipio\n"
    "7- Modificar No. Exterior\n"
    "8- Modificar Codigo Postal\n"
    "9- Modificar No. Consultorio\n"
    "10- Modificar Tipo de Servicio\n"
    "11- Modificar Descripcion de Sintomas\n"
    "12- Guardar Cambios\n";

    unsigned int no_registro=0;
    no_registro=(unsigned int)capturar_entero(1, 9999999, texto_captura_no_empleado);

    rewind(*ptr_archivo);
    while(parsear_paciente(buffer, *ptr_archivo)!=EOF) {
        if(buffer->no_registro==no_registro) break;
    }
    if(buffer->no_registro!=no_registro) {
        printf("No se encontro el paciente con el numero de registro proporcionado\n");
        printf("*Regresando al menu principal*");
        return;
    }

    int opc=0;
    while(opc!=12) {
        clear();
        printf("*Datos del paciente*\n");
        print_paciente(buffer, stdout); printf("\n");
        printf(texto_menu_de_modificacion);
        opc=validar_entero(1,12);
        switch(opc) {
        case 1: capturar_string(buffer->nombre,L_NOMBRE, "Nombre del paciente: "); break;
        case 2: buffer->edad=capturar_entero(0, 150, "Edad del paciente: "); break;
        case 3: buffer->genero=(Genero)capturar_entero(1,2,texto_seleccion_genero)-1; break;
        case 4: capturar_string(buffer->direccion.calle, L_CALLE, "Calle del Domicilio: "); break;
        case 5: capturar_string(buffer->direccion.colonia, L_CALLE, "Colonia del Domicilio: "); break;
        case 6: capturar_string(buffer->direccion.municipio, L_MUNICIPIO, "Municipio del Domicilio: "); break;
        case 7: buffer->direccion.numero=capturar_entero(1, 999999, "No. Exterior del Domicilio: "); break;
        case 8: buffer->direccion.cp=capturar_entero(11111, 999999, "Codigo postal del Domicilio: "); break;
        case 9: buffer->consultorio=capturar_entero(1, 999, "No. Consultorio del Paciente: "); break;
        case 10: buffer->servicio=(Servicio)capturar_entero(1,2,texto_seleccion_sevicio)-1; break;
        case 11: capturar_sintomas(buffer->sintomas); break;
        }
    }

    FILE* nuevo_archivo = fopen(ARCHIVO_TMP, "w");

    Paciente buffer_lectura_escritura;
    paciente_init(&buffer_lectura_escritura);

    rewind(*ptr_archivo);
    while(parsear_paciente(&buffer_lectura_escritura, *ptr_archivo)!=EOF) {
        if(buffer->no_registro==buffer_lectura_escritura.no_registro) {
            print_paciente(buffer, nuevo_archivo);
        } else {
            print_paciente(&buffer_lectura_escritura, nuevo_archivo);
        }
    }
    paciente_destroy(&buffer_lectura_escritura);

    fclose(nuevo_archivo);
    fclose(*ptr_archivo);
    remove(ARCHIVO_PACIENTES);
    rename(ARCHIVO_TMP, ARCHIVO_PACIENTES);
    *ptr_archivo = fopen(ARCHIVO_PACIENTES, "r+");

    printf("Paciente modificado exitosamente\n");
    printf("*Regresando al menu principal*\n");
    return;
}

void listado_pacientes(FILE* archivo, Paciente* buffer)
{
    printf("Listado de los pacientes en es sistema:\n\n");
    while(parsear_paciente(buffer, archivo)!=EOF) {
        print_paciente(buffer, stdout);
        printf("\n\n");
    }
    printf("Fin del listado\n");
    printf("*Regresando al menu principal*\n");
    return;
}

void baja_paciente(FILE** ptr_archivo, Paciente* buffer)
{
    static const char* texto_eliminar_paciente=
    "Realemente desea eliminar al paciente con los datos anteriores?\n"
    "1- Si\n"
    "2- No\n";

    unsigned int no_registro=0;
    no_registro=(unsigned int)capturar_entero(1, 9999999, texto_captura_no_empleado);

    rewind(*ptr_archivo);
    while(parsear_paciente(buffer, *ptr_archivo)!=EOF) {
        if(buffer->no_registro==no_registro) break;
    }
    if(buffer->no_registro!=no_registro) {
        printf("No se encontro el paciente con el numero de registro proporcionado\n");
        printf("*Regresando al menu principal*");
        return;
    }

    clear();
    printf("*Datos del paciente*\n");
    print_paciente(buffer, stdout); printf("\n");
    int opc=capturar_entero(1,2,texto_eliminar_paciente);
    if(opc==2) {
        printf("Abortando eliminacion del paciente\n");
        printf("*Regresando al menu principal*\n");
        return;
    }

    FILE* nuevo_archivo = fopen(ARCHIVO_TMP, "w");

    rewind(*ptr_archivo);
    while(parsear_paciente(buffer, *ptr_archivo)!=EOF) {
        if(buffer->no_registro!=no_registro)
            print_paciente(buffer, nuevo_archivo);
    }

    fclose(nuevo_archivo);
    fclose(*ptr_archivo);
    remove(ARCHIVO_PACIENTES);
    rename(ARCHIVO_TMP, ARCHIVO_PACIENTES);
    *ptr_archivo = fopen(ARCHIVO_PACIENTES, "r+");

    printf("Paciente eliminado exitosamente\n");
    printf("*Regresando al menu principal*\n");
    return;
}

void liberar_recursos(FILE* archivo, Paciente* buffer)
{
    paciente_destroy(buffer);
    fclose(archivo);
    return;
}