#include <string.h>
#include <stdlib.h>

#include "postgres.h"

typedef struct UrlType {
    char port[55];
    char scheme[55];
    char host[55];
    char path[55];
    char query[55];
    char fragment[55];
} UrlType;

// "http://www.test.com/test?query=5#anchor"
// "http://www.test.com/test?query=5"
// "http://www.test.com/test"
// "http://www.test.com/"
// "http://www.test.com"
// "ftp://192.28.10.1/dossier/sous-dossier/thomas"
void URL(UrlType* url, char* spec);
void str_to_url(char url_string[], UrlType* url);
void stringify(char* result, UrlType* url);