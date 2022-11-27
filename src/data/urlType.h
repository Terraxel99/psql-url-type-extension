#include <string.h>

typedef struct UrlType {
    char *scheme;
    char *host;
    int port;
    char *path;
    char *query;
    char *fragment;
} UrlType;


// "http://www.test.com/test?query=5#anchor"
// "http://www.test.com/test?query=5"
// "http://www.test.com/test"
// "http://www.test.com/"
// "http://www.test.com"
// "ftp://192.28.10.1/dossier/sous-dossier/thomas"
UrlType URL(char *spec);
