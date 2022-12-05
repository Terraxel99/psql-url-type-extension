#include "urlType.h"
#include <string.h>

void URL(UrlType* url, char *spec) {
    url->scheme = palloc(10*sizeof(char));
    url->host = palloc(40*sizeof(char));
    url->path = palloc(40*sizeof(char));
    url->query = palloc(40*sizeof(char));
    url->fragment = palloc(40*sizeof(char));
    url->port = palloc(8*sizeof(char));
}

void str_to_url(char url_string[], UrlType* url){
    char* current_token;
    char* tmp_token;
    char* current_pointer;
    char* tmp_pointer;
    char tmp_copy[100];
    char tmp_copy_tmp[100];

    //schema
    current_token = strtok_r(url_string, ":", &current_pointer);
    
    strcpy(tmp_copy,current_token);
    strcat(tmp_copy,":");
    strcpy(url->scheme,tmp_copy);

    current_token = strtok_r(NULL, "/", &current_pointer);
    tmp_token = strtok_r(current_token, ":", &tmp_pointer);
    strcpy(tmp_copy,"//");
    strcat(tmp_copy,tmp_token);
    if(tmp_pointer != ""){ //if pointer != NULL -> There is a port 
        strcpy(tmp_copy_tmp,":");
        strcat(tmp_copy_tmp,tmp_pointer);
        strcat(tmp_copy_tmp,"/");
        memcpy(url->port,tmp_copy_tmp,strlen(tmp_copy_tmp));
    }else{
        strcat(tmp_copy,"/");
    }
    memcpy(url->host,tmp_copy,strlen(tmp_copy));
    strcpy(current_token,"");
    current_token = "";
    //check if there is a path
    tmp_pointer = current_pointer;
    current_token = strtok_r(NULL, "?", &tmp_pointer);
    if(current_token != ""){
        memcpy(url->path,tmp_copy,strlen(tmp_copy));
        current_pointer = tmp_pointer;
        current_token = "";
    }
    //check if there is a query
    current_token = strtok_r(NULL, "#", &tmp_pointer);
    if(current_token != ""){
        strcpy(tmp_copy,"?");
        strcat(url->query,current_token);
        memcpy(url->query,tmp_copy,strlen(tmp_copy));
        current_pointer = tmp_pointer;
        current_token = "";
    }

    if(tmp_pointer != ""){ //if it's the case it's necessarily the fragment
        memcpy(url->fragment,tmp_copy,strlen(tmp_copy));
    }
}

void stringify(UrlType url){
    printf("%s%s%s%s%s%s\n",url.scheme,url.host,url.port,url.path,url.query,url.fragment);
}
