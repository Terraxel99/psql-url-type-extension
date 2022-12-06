#include "urlType.h"
#include <string.h>

void URL(UrlType* url, char *spec) {
    memcpy(url->scheme, "https:", 7);
    memcpy(url->host, "//www.test.com", 15);
    memcpy(url->path, "/test", 6);
    url->port = "80";
    memcpy(url->query, "?query=5", 9);
    memcpy(url->fragment, "#anchor", 8);
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
        memcpy(url->port,tmp_copy_tmp,strlen(tmp_copy_tmp)+1);
    }else{
        strcat(tmp_copy,"/");
    }
    memcpy(url->host,tmp_copy,strlen(tmp_copy)+1);
    strcpy(current_token,"");
    current_token = "";
    //check if there is a path
    tmp_pointer = current_pointer;
    current_token = strtok_r(NULL, "?", &tmp_pointer);
    if(current_token != ""){
        memcpy(url->path,tmp_copy,strlen(tmp_copy)+1);
        current_pointer = tmp_pointer;
        current_token = "";
    }
    //check if there is a query
    current_token = strtok_r(NULL, "#", &tmp_pointer);
    if(current_token != ""){
        strcpy(tmp_copy,"?");
        strcat(url->query,current_token);
        memcpy(url->query,tmp_copy,strlen(tmp_copy)+1);
        current_pointer = tmp_pointer;
        current_token = "";
    }

    if(tmp_pointer != ""){ //if it's the case it's necessarily the fragment
        memcpy(url->fragment,tmp_copy,strlen(tmp_copy)+1);
    }
}

void stringify(char* result, UrlType* url){
    snprintf(result,180,"%s%s%s%s%s%s\n",url->scheme,url->host,url->port,url->path,url->query,url->fragment);
}
