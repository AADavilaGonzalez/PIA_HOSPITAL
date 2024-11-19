# Sistema de gestion de pacientes en C - PIA Laboratorio de programacion estructurada FCMF | UANL

Proyecto integrador de aprendizaje del laboratorio de la materia de
programacion estructurada. Consiste en implementar una pequeno sistema
de registros para un consultorio medico cualquiera utilizando los conceptos
de entradas y salidas del lenguaje C haciendo enfasis en los flujos secuenciales

# Integrantes
* Aldo Adrian Davila Gonzalez | 1994122
* Roberto Sanchez Santoyo | 2177547
* 

## Requesitos
* Algun compilador registrado en el PATH del sistema ej. gcc, clang
* Librerias y entorono de ejecucion estandar de C

# Proceso de Compilacion
El proceso de compilacion de este proyecto se realiza exclusivamente en la
terminal. Se necesita cambiar de direccion de trabajo a la direccion en donde se
haya descargado el proyecto. Una vez en localizado en la direccion correspondiente
se compilara el proyecto utilizando el script correspondiente a su entorno de trabajo.

Si su entorno es compatible con bash y su lenguaje de scripting,
ejecute el script compilar.sh. Si se encuentra en un entorno de Windowns,
ejecute el script compilar.bat.

Los dos script soportan la misma sintaxis de un solo argumento:

`./copilar.(sh/bat) <compilador>`

El argumento 'compilador' hace referencia al compilador que desea utilizar para
compilar el programa que debe estar previamente registrado como ejecutable
accesible mediante el PATH del sistema. El compilador debera ser compatible
con la sintaxis de argumentos del compilador GCC por lo que se recomienda usar
el compilador gcc o clang.