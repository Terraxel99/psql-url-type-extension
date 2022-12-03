#include <stdio.h>
#include <string.h>
#include <urlType.h>

void str_to_url(char* url_string, UrlType* url){
    char* copy_url = (char *) malloc(sizeof(char) * (strlen(url_string) + 1));
    char* copy_url_pointer

    int port;
    char port_str[15];
    char scheme[150];
    char host[150];
    char path[150];
    char query[150];
    char fragment[150];

    token = strtok_r(copy_url, ":", &copy_url_pointer); //mendatory
    strcpy(url->scheme, token);

    token = strtok_r(copy_url, "/", &copy_url_pointer); //mendatory -> always the case
    
    
}
