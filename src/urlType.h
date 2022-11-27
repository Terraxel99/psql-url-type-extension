#include <string.h>
#include <stdlib.h>

#include "postgres.h"

typedef struct UrlType {
    int port;
    char scheme[150];
    char host[150];
    char path[150];
    char query[150];
    char fragment[150];
} UrlType;

// "http://www.test.com/test?query=5#anchor"
// "http://www.test.com/test?query=5"
// "http://www.test.com/test"
// "http://www.test.com/"
// "http://www.test.com"
// "ftp://192.28.10.1/dossier/sous-dossier/thomas"
void URL(UrlType* url, char* spec);
