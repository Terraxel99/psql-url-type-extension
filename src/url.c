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

PG_FUNCTION_INFO_V1(url_authority); //host + port
Datum url_authority(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    char *c;
    c = psprintf("%s:%d", url->host,url->port);

    PG_RETURN_CSTRING(c);   
}

PG_FUNCTION_INFO_V1(url_host);
Datum url_host(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    char *c;
    c = psprintf("%s", url->host);

    PG_RETURN_CSTRING(c);   
}

PG_FUNCTION_INFO_V1(url_path);
Datum url_path(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);
    char *c;
    c = psprintf("%s", url->path);
    PG_RETURN_CSTRING(c);   
}


PG_FUNCTION_INFO_V1(url_file); //path + query
Datum url_file(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);
    char *c;
    c = psprintf("%s%s", url->path,url->query);
    PG_RETURN_CSTRING(c);   
}


PG_FUNCTION_INFO_V1(url_port);
Datum url_port(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);
    int port = url->port;
    PG_RETURN_INT32(port);   
}


PG_FUNCTION_INFO_V1(url_protocol);
Datum url_protocol(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);
    char *c;
    c = url->scheme;
    PG_RETURN_CSTRING(c);   
}



PG_FUNCTION_INFO_V1(url_query);
Datum url_query(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);
    char *c;
    c = url->query;
    PG_RETURN_CSTRING(c);   
}


PG_FUNCTION_INFO_V1(url_ref);
Datum url_ref(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);
    char *c;
    c = url->fragment;
    PG_RETURN_CSTRING(c);   
}

PG_FUNCTION_INFO_V1(url_equals);
Datum url_equals(PG_FUNCTION_ARGS) {
    UrlType *url1 = (UrlType *) PG_GETARG_POINTER(0);
    UrlType *url2 = (UrlType *) PG_GETARG_POINTER(1);
    if(strcmp(url1->scheme,url2->scheme)!=0){
        PG_RETURN_BOOL(false);
    }
    if(url1->port!=url2->port){   
        PG_RETURN_BOOL(false);
    }
    if(strcmp(url1->host,url2->host)!=0){
        PG_RETURN_BOOL(false);
    }
    if(strcmp(url1->path,url2->path)!=0){
        PG_RETURN_BOOL(false);
    }
    if(strcmp(url1->scheme,url2->scheme)!=0){
        PG_RETURN_BOOL(false);
    }
    if(strcmp(url1->fragment,url2->fragment)!=0){
        PG_RETURN_BOOL(false);
    }
    PG_RETURN_BOOL(true);
}


PG_FUNCTION_INFO_V1(url_same_file);
Datum url_same_file(PG_FUNCTION_ARGS) {
    UrlType *url1 = (UrlType *) PG_GETARG_POINTER(0);
    UrlType *url2 = (UrlType *) PG_GETARG_POINTER(1);
    if(strcmp(url1->scheme,url2->scheme)!=0){
        PG_RETURN_BOOL(false);
    }
    if(url1->port!=url2->port){   
        PG_RETURN_BOOL(false);
    }
    if(strcmp(url1->host,url2->host)!=0){
        PG_RETURN_BOOL(false);
    }
    if(strcmp(url1->path,url2->path)!=0){
        PG_RETURN_BOOL(false);
    }
    if(strcmp(url1->scheme,url2->scheme)!=0){
        PG_RETURN_BOOL(false);
    }
    PG_RETURN_BOOL(true);
}

PG_FUNCTION_INFO_V1(url_same_host);
Datum url_same_host(PG_FUNCTION_ARGS) {
    UrlType *url1 = (UrlType *) PG_GETARG_POINTER(0);
    UrlType *url2 = (UrlType *) PG_GETARG_POINTER(1);
    if(strcmp(url1->host,url2->host)!=0){
        PG_RETURN_BOOL(false);
    }
    PG_RETURN_BOOL(true);
}
/*
PG_FUNCTION_INFO_V1(url_same_host);
Datum url_default_port(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);
    if(strcmp(url->host,"http://")!=0){
        PG_RETURN_BOOL(false);
    }
    PG_RETURN_BOOL(true);
}
*/
   




