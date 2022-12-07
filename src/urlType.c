#include "urlType.h"
#include <string.h>

void URL(UrlType* url, char *spec) {
   
}

void scheme_check(char* token,char* path,char* pointer, UrlType* url){
    char* tmp;
    token = strtok_r(path, ":", &tmp);
    if(strlen(token) != 0){
        strcpy(pointer,tmp);
        strcpy(url->scheme,token);
    }else{
        printf("URL non valide\n");
    }
}


void host_check(char* token, char* pointer,UrlType* url){
    char* tmp_token;
    char* tmp_pointer;
    char* tmp_pointer_host;
    strcpy(tmp_pointer,pointer);
    token = strtok_r(NULL, "/", &tmp_pointer);
    if(strlen(token) != 0){
        tmp_pointer_host = token;
        tmp_token = strtok_r(NULL, ":", &tmp_pointer_host);
        if(strlen(tmp_token) != 0){
            strcpy(url->host,tmp_token);
            strcpy(url->port,tmp_pointer_host);
        }else{
            strcpy(url->host,token);
        }
        strcpy(pointer,tmp_pointer);
    }else{ 
        printf("URL non valide\n");
    }
}

char* generic_check(char* to_check,char* token, char* pointer,char* url_type){
    char* tmp_pointer;
    strcpy(tmp_pointer,pointer);
    token = strtok_r(NULL, to_check, &tmp_pointer);
    if(strlen(tmp_pointer) != 0){
        strcpy(url_type,token);
        strcpy(pointer,tmp_pointer);
        return to_check;
    }else{
        return "";
    }
}

void str_to_url(char url_string[], UrlType* url){
    char* path = (char *)malloc(strlen(url_string) + 1);
    char* pointer = (char *)malloc(strlen(url_string) + 1);
    char* token = (char *)malloc(strlen(url_string) + 1);
    strcpy(path,url_string);
    scheme_check(token,path,pointer,url);
    host_check(token,pointer,url);
    //path check
    char* delimiter_find;
    delimiter_find = generic_check("?",token,pointer,url->path); //check for query start
    if(delimiter_find == ""){
        delimiter_find = generic_check("#",token,pointer,url->path); //check for fragment start
        if(delimiter_find == ""){
            if(strlen(pointer) != 0){
                strcpy(url->path, pointer); //check for fragment
            }
        }
    }

    //query check
    if(delimiter_find == "?"){
        delimiter_find = "";
        delimiter_find = generic_check("#",token,pointer,url->query); //check for fragment start
        if(delimiter_find == ""){
            if(strlen(pointer) != 0){
                strcpy(url->query, pointer); //check for fragment
            }
        }
    }

    //fragment check
    if(delimiter_find == "#"){
        if(strlen(pointer) != 0){
            strcpy(url->fragment, pointer); //check for fragment
        }
    }
    



    generic_check("#",token,pointer,url->query); //check for query
    
    free(path);
    free(pointer);
    free(token);
}


void stringify(char* res,UrlType* url){
    snprintf(res,180,"%s%s%s%s%s%s\n",url->scheme,url->host,url->port,url->path,url->query,url->fragment);
}