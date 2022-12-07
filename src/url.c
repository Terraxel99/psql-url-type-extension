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
   // str_to_url(input,url);
    strcpy(url->host,"haha");
    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_out);
Datum url_out(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType*) PG_GETARG_POINTER(0);
    char* result = (char *) palloc(280);
    stringify(result,url);
	PG_RETURN_CSTRING(result);
}

