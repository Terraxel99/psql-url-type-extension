#include <stdio.h>

#include "postgres.h"
#include "fmgr.h"
#include "urlType.h"

PG_MODULE_MAGIC;

/* ================ URL EXTENSION CODE ================ */

PG_FUNCTION_INFO_V1(url_in);
Datum url_in(PG_FUNCTION_ARGS) {
    char* input = PG_GETARG_CSTRING(0); 

    UrlType *url = (UrlType *) palloc(VARHDRSZ + (73 * sizeof(char)));

    SET_VARSIZE(url, VARHDRSZ + (73 * sizeof(char)));

    url->scheme = (char *) malloc(7 * sizeof(char));
    url->host = (char *) malloc(15 * sizeof(char));
    url->path = (char *) malloc(18 * sizeof(char));
    url->query = (char *) malloc(25 * sizeof(char));
    url->fragment = (char *) malloc(8 * sizeof(char));

    memcpy(url->scheme, "https:", 7);
    memcpy(url->host, "//www.test.com", 15);
    memcpy(url->path, "/some/path/to/url", 18);
    memcpy(url->query, "?some=value&other=value2", 25);
    memcpy(url->fragment, "#anchor", 8);

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_out);
Datum url_out(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    char *c;
    c = psprintf("%s%s%s%s%s", url->scheme, url->host, url->path, url->query, url->fragment);

    PG_RETURN_CSTRING(c);
}

PG_FUNCTION_INFO_V1(url_scheme);
Datum url_scheme(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    char *c;
    c = psprintf("%s", url->scheme);

    PG_RETURN_CSTRING(c);   
}

PG_FUNCTION_INFO_V1(url_authority);
Datum url_authority(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    char *c;
    c = psprintf("%s", url->host);

    PG_RETURN_CSTRING(c);   
}



