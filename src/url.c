#include <stdio.h>

#include "postgres.h"
#include "fmgr.h"
#include "urlType.h"





PG_MODULE_MAGIC;

/* ================ URL EXTENSION CODE ================ */

PG_FUNCTION_INFO_V1(url_in);
Datum url_in(PG_FUNCTION_ARGS) {
    char* input = PG_GETARG_CSTRING(0); 
    //UrlType *url = (UrlType *) palloc(sizeof(UrlType) + (180 * sizeof(char)));
    //str_to_url(input, url); //parse string -> url (utils)
    UrlType *url = (UrlType *) palloc(sizeof(UrlType) + (180 * sizeof(char)));
    url->scheme = palloc(10*sizeof(char));
    url->host = palloc(40*sizeof(char));
    url->path = palloc(40*sizeof(char));
    url->query = palloc(40*sizeof(char));
    url->fragment = palloc(40*sizeof(char));
    url->port = palloc(8*sizeof(char));
    str_to_url(input, url); //parse string -> url (utils)
    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_out);
Datum url_out(PG_FUNCTION_ARGS) {
    Datum arg = PG_GETARG_DATUM(0);
    char* ret_tmp = "http://www.test.com/test?query=5#anchor";
	PG_RETURN_CSTRING(ret_tmp);
}
