#include <string.h>
#include <stdlib.h>

#include "postgres.h"

#define DEFAULT_PORT_FTP 21
#define DEFAULT_PORT_SSH 22
#define DEFAULT_PORT_TELNET 23
#define DEFAULT_PORT_HTTP 80
#define DEFAULT_PORT_NNTP 119
#define DEFAULT_PORT_NTP 123
#define DEFAULT_PORT_HTTPS 443
#define DEFAULT_PORT_FTPS 989
#define DEFAULT_PORT_TFTP 69

typedef struct UrlType {
    int length;
    int port;
    int schemeLength;
    int hostLength;
    int portLength;
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
int default_port_of(char* scheme);
void check_port(UrlType* url, char* spec, int startChar, char* offset, int totalLength);
void check_path(UrlType* url, char* spec, int startChar, char* offset, int totalLength);
void check_query(UrlType* url, char* spec, int startChar, char* offset, int totalLength);
void check_fragment(UrlType* url, char* spec, int startChar, char* offset, int totalLength);
