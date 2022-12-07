#include <string.h>
#include <stdlib.h>

#include "postgres.h"

typedef struct UrlType {
    int length;
    //int* port;
    char* scheme;
    char* host;
    char* path;
    char* query;
    char* fragment;
} UrlType;

// "http://www.test.com/test?query=5#anchor"
// "http://www.test.com/test?query=5"
// "http://www.test.com/test"
// "http://www.test.com/"
// "http://www.test.com"
// "ftp://192.28.10.1/dossier/sous-dossier/thomas"
void URL(UrlType* url, char* spec);
