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
    url = (UrlType *) palloc(VARHDRSZ + ((totalLength  + 5) * sizeof(char)) + sizeof(UrlType));
    str_to_url(url, input);

    SET_VARSIZE(url, VARHDRSZ + ((totalLength + 5) * sizeof(char)) + sizeof(UrlType));

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_out);
Datum url_out(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    int totalLength = url->schemeLength + url->hostLength + url->pathLength + url->queryLength + url->fragmentLength + 1;
    char* c = palloc(totalLength * sizeof(char));

    strcpy(c, url->scheme);
    strcat(c, url->host);
    strcat(c, url->path);
    strcat(c, url->query);
    strcat(c, url->fragment);

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



