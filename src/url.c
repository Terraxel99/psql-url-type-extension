#include <stdio.h>

#include "postgres.h"
#include "fmgr.h"
#include "data/urlType.h"

PG_MODULE_MAGIC;

/* ================ URL EXTENSION CODE ================ */


PG_FUNCTION_INFO_V1(url_in);
Datum url_in(PG_FUNCTION_ARGS) {
    char *urlStr = PG_GETARG_CSTRING(0);
    PG_RETURN_POINTER(URL(urlStr));
}

PG_FUNCTION_INFO_V1(url_out);
Datum url_out(PG_FUNCTION_ARGS) {
    Datum input = PG_GETARG_DATUM(0);
    PG_RETURN_CSTRING("http://www.test.com:80/path/to/page?query=5#anchor");
}
