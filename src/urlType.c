#include "urlType.h"

void URL(UrlType* url, char *spec) {
    memcpy(url->scheme, "https:", 7);
    memcpy(url->host, "//www.test.com", 15);
    memcpy(url->path, "/test", 6);
    url->port = 80;
    memcpy(url->query, "?query=5", 9);
    memcpy(url->fragment, "#anchor", 8);
}