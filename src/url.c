#include <stdio.h>

#include "postgres.h"
#include "fmgr.h"
#include "urlType.h"

PG_MODULE_MAGIC;

/* ================ URL EXTENSION CODE ================ */

PG_FUNCTION_INFO_V1(url_in);
Datum url_in(PG_FUNCTION_ARGS) {
    char* input = PG_GETARG_CSTRING(0); 

    UrlType *url = (UrlType *) palloc(sizeof(UrlType) + (45 * sizeof(char)));

    url->scheme = "https:";
    url->host = "//www.test.com";
    url->path = "/test";
    url->query = "?query=5";
    url->fragment = "#anchor";
    url->port = 80;

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_out);
Datum url_out(PG_FUNCTION_ARGS) {
    PG_RETURN_CSTRING("http://www.test.com:80/path/to/page?query=5#anchoR");
}
