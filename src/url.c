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

    char* c = url_to_str(url);

    PG_RETURN_CSTRING(c);
}

PG_FUNCTION_INFO_V1(url_from_string);
Datum url_from_string(PG_FUNCTION_ARGS) {
    char* input = PG_GETARG_CSTRING(0); 
    UrlType* url = NULL;

    int totalLength = strlen(input);
    url = (UrlType *) palloc(VARHDRSZ + ((totalLength  + 5) * sizeof(char)) + sizeof(UrlType));
    str_to_url(url, input);

    SET_VARSIZE(url, VARHDRSZ + ((totalLength + 5) * sizeof(char)) + sizeof(UrlType));

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_from_phpf);
Datum url_from_phpf(PG_FUNCTION_ARGS) {
    char* inputProtocol = PG_GETARG_CSTRING(0);
    char* inputHost = PG_GETARG_CSTRING(1);
    int inputPort = PG_GETARG_INT32(2);
    char* inputPathQuery = PG_GETARG_CSTRING(3);

    UrlType* url = NULL;

    char* inputStr = psprintf("%s://%s:%d/%s", inputProtocol, inputHost, inputPort, inputPathQuery);
    int totalLength = strlen(inputStr);
    url = (UrlType *) palloc(VARHDRSZ + ((totalLength  + 5) * sizeof(char)) + sizeof(UrlType));

    SET_VARSIZE(url, VARHDRSZ + ((totalLength + 5) * sizeof(char)) + sizeof(UrlType));
    str_to_url(url, inputStr);

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_in_context);
Datum url_in_context(PG_FUNCTION_ARGS) {
    UrlType* url = (UrlType*) PG_GETARG_POINTER(0);
    char* spec = PG_GETARG_CSTRING(1); 
    
    UrlType* urlFromSpec = NULL;

    int specLength = strlen(spec);
    urlFromSpec = (UrlType *) palloc(VARHDRSZ + ((specLength  + 5) * sizeof(char)) + sizeof(UrlType));
    SET_VARSIZE(urlFromSpec, VARHDRSZ + ((specLength + 5) * sizeof(char)) + sizeof(UrlType));
    str_to_url(urlFromSpec, spec);

    if (urlFromSpec->schemeLength > 1 && urlFromSpec->hostLength > 1) {
        strcpy(url->scheme, urlFromSpec->scheme);
        strcpy(urlFromSpec->host, url->host);
    }

    url->port = urlFromSpec->port;

    strcpy(url->path, urlFromSpec->path);
    strcpy(url->query, urlFromSpec->query);
    strcpy(url->fragment, urlFromSpec->fragment);

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_from_phf);
Datum url_from_phf(PG_FUNCTION_ARGS) {
    char* inputProtocol = PG_GETARG_CSTRING(0);
    char* inputHost = PG_GETARG_CSTRING(1);
    char* inputPathQuery = PG_GETARG_CSTRING(2);

    UrlType* url = NULL;

    char* inputStr = psprintf("%s://%s/%s", inputProtocol, inputHost, inputPathQuery);
    int totalLength = strlen(inputStr);
    url = (UrlType *) palloc(VARHDRSZ + ((totalLength  + 5) * sizeof(char)) + sizeof(UrlType));

    SET_VARSIZE(url, VARHDRSZ + ((totalLength + 5) * sizeof(char)) + sizeof(UrlType));
    str_to_url(url, inputStr);

    PG_RETURN_POINTER(url);
}

PG_FUNCTION_INFO_V1(url_scheme);
Datum url_scheme(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    char *c;
    c = psprintf("%s", url->scheme);

    PG_RETURN_CSTRING(c);
}

PG_FUNCTION_INFO_V1(url_authority); // Host + port
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

PG_FUNCTION_INFO_V1(url_file); // Path + query
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

    if (port == 0) {
        PG_RETURN_NULL();
    } else {
        PG_RETURN_INT32(port);   
    }
}

PG_FUNCTION_INFO_V1(url_default_port);
Datum url_default_port(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType*) PG_GETARG_POINTER(0);

    int defaultPort = default_port_of(url->scheme);

    if (defaultPort == 0) {
        PG_RETURN_NULL();
    } else {
        PG_RETURN_INT32(defaultPort);
    }
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

PG_FUNCTION_INFO_V1(url_to_string);
Datum url_to_string(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);

    char* c = url_to_str(url);

    PG_RETURN_CSTRING(c);
}

PG_FUNCTION_INFO_V1(url_userinfo);
Datum url_userinfo(PG_FUNCTION_ARGS) {
    UrlType *url = (UrlType *) PG_GETARG_POINTER(0);
    
    char* host = palloc(url->hostLength * sizeof(char));
    char * splitted; 
    
    strcpy(host, url->host);
    splitted = strtok(host, "@");

    // If no @ was found, return NULL.
    if (strtok(NULL, "@") == NULL) {
        PG_RETURN_NULL();
    }

    // Removing "//" from host.
    PG_RETURN_CSTRING(splitted + (2 * sizeof(char)));
}

PG_FUNCTION_INFO_V1(url_equals);
Datum url_equals(PG_FUNCTION_ARGS) {
    UrlType *url1 = (UrlType *) PG_GETARG_POINTER(0);
    UrlType *url2 = (UrlType *) PG_GETARG_POINTER(1);
    
    if (strcmp(url1->scheme,url2->scheme)!=0){
        PG_RETURN_BOOL(false);
    }

    if (!are_port_equal(url1, url2)) {
        PG_RETURN_BOOL(false);
    }

    if (strcmp(url1->host,url2->host)!=0){
        PG_RETURN_BOOL(false);
    }
    
    if (strcmp(url1->path,url2->path)!=0){
        PG_RETURN_BOOL(false);
    }
    
    if (strcmp(url1->scheme,url2->scheme)!=0){
        PG_RETURN_BOOL(false);
    }
    
    if (strcmp(url1->fragment,url2->fragment)!=0){
        PG_RETURN_BOOL(false);
    }
    
    PG_RETURN_BOOL(true);
}

PG_FUNCTION_INFO_V1(url_same_file);
Datum url_same_file(PG_FUNCTION_ARGS) {
    UrlType *url1 = (UrlType *) PG_GETARG_POINTER(0);
    UrlType *url2 = (UrlType *) PG_GETARG_POINTER(1);
    
    if (strcmp(url1->scheme,url2->scheme)!=0){
        PG_RETURN_BOOL(false);
    }
    
    if (!are_port_equal(url1, url2)) {
        PG_RETURN_BOOL(false);
    }
    
    if (strcmp(url1->host,url2->host)!=0){
        PG_RETURN_BOOL(false);
    }
    
    if (strcmp(url1->path,url2->path)!=0){
        PG_RETURN_BOOL(false);
    }

    if (strcmp(url1->scheme,url2->scheme)!=0){
        PG_RETURN_BOOL(false);
    }

    PG_RETURN_BOOL(true);
}

PG_FUNCTION_INFO_V1(url_same_host);
Datum url_same_host(PG_FUNCTION_ARGS) {
    UrlType *url1 = (UrlType *) PG_GETARG_POINTER(0);
    UrlType *url2 = (UrlType *) PG_GETARG_POINTER(1);
    
    if (strcmp(url1->host,url2->host)!=0){
        PG_RETURN_BOOL(false);
    }

    PG_RETURN_BOOL(true);
}
