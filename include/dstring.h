//Libreria de tipo de dato string dinamic 'Dstring'
#pragma once

typedef struct dstring_s* Dstring;

Dstring dstring_init(const char* datos, size_t capacidad);
void dstring_resize(Dstring string, size_t capacidad);
void dstring_get(Dstring string, const char* origen);
void dstring_fill(Dstring string, const char* origen);
void dstring_append(Dstring string, const char* origen);
int dstring_fget(Dstring string, FILE* entrada, char delimitador);
int dstring_ffill(Dstring string, FILE* entrada, char delimitador);
int dstring_fread(Dstring string, FILE* entrada, size_t n);
void dstring_flush(Dstring string);
int dstring_fappend(Dstring string, FILE* entrada, char delimitador);
const char* dstring_decay(Dstring string);
size_t dstring_get_longitud(Dstring string);
int dstring_isfull(Dstring string);
void dstring_destroy(Dstring string);