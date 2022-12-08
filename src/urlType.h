#include <string.h>
#include <stdlib.h>

#include "postgres.h"

typedef struct UrlType {
    int length;
    int port;
    int schemeLength;
    int hostLength;
    int pathLength;
    int queryLength;
    int fragmentLength;
    char* scheme;
    char* host;
    char* path;
    char* query;
    char* fragment;
} UrlType;

void str_to_url(UrlType* url, char* spec);
bool char_is_digit(char c);
void check_port(UrlType* url, char* spec, int startChar, char* offset, int totalLength);
void check_path(UrlType* url, char* spec, int startChar, char* offset, int totalLength);
void check_query(UrlType* url, char* spec, int startChar, char* offset, int totalLength);
void check_fragment(UrlType* url, char* spec, int startChar, char* offset, int totalLength);
