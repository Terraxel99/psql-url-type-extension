#include <stdio.h>

#include "postgres.h"
#include "fmgr.h"
#include "urlType.h"

PG_MODULE_MAGIC;

/* ================ URL EXTENSION CODE ================ */

PG_FUNCTION_INFO_V1(url_in);
Datum url_in(PG_FUNCTION_ARGS) {
    char* input = PG_GETARG_CSTRING(0); 
    UrlType* url = NULL;

    int totalLength = strlen(input);
    url = (UrlType *) palloc(VARHDRSZ + ((totalLength  + 9) * sizeof(char)) + (6 * sizeof(int)));
    str_to_url(url, input);

    SET_VARSIZE(url, VARHDRSZ + ((totalLength + 9) * sizeof(char)) + (6 * sizeof(int)));

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_out);
Datum url_out(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    char *c;
    //c = psprintf("%s/*%s:%d%s%s%s", url->scheme, url->host, url->port, url->path, url->query, url->fragment);
    c = psprintf("%s%s:%d%s%s%s", url->scheme, url->host, url->port, url->path, url->query, url->fragment);

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



