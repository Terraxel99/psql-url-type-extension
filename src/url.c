#include <stdio.h>

#include "postgres.h"
#include "fmgr.h"
#include "urlType.h"

PG_MODULE_MAGIC;

/* ================ URL EXTENSION CODE ================ */

PG_FUNCTION_INFO_V1(url_in);
Datum url_in(PG_FUNCTION_ARGS) {
    char* input = PG_GETARG_CSTRING(0); 

    UrlType *url = (UrlType *) palloc(sizeof(UrlType));
    //SET_VARSIZE(url, sizeof);

    memcpy(url->scheme, "https:", 7);
    memcpy(url->host, "//www.test.com", 15);
    memcpy(url->path, "/test", 6);
    memcpy(url->query, "?query=5", 9);
    memcpy(url->fragment, "#anchor", 8);
    url->port = 80;

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_out);
Datum url_out(PG_FUNCTION_ARGS) {
    // Datum input = PG_GETARG_DATUM(0);
    PG_RETURN_CSTRING("http://www.test.com:80/path/to/page?query=5#anchor");
}
