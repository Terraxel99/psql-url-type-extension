#include "urlType.h"

void str_to_url(UrlType* url, char *spec) {
    int i = 0;
    char* offset = spec;
    int totalLength = strlen(spec);
    int hostSlashOccurence = 0;
    
    // Initializing every length at 1 for the null terminator (\0).
    url->schemeLength = 1;
    url->hostLength = 1;
    url->pathLength = 1;
    url->queryLength = 1;
    url->fragmentLength = 1;

    while (spec[i] != '/') {
        url->schemeLength++;
        i++;
    }
    
    url->scheme = (char *) malloc((url->schemeLength) * sizeof(char));
    memcpy(url->scheme, offset, url->schemeLength);
    url->scheme[url->schemeLength - 1] = '\0';
    offset += url->schemeLength - 1;

    while (i != totalLength && spec[i] != '?' && spec[i] != ':' && spec[i] != '#') {
        if (spec[i] == '/') {
            hostSlashOccurence++;
        }

        if (hostSlashOccurence == 3) {
            break;
        }

        url->hostLength++;
        i++;
    }

    url->host = (char *) malloc((url->hostLength) * sizeof(char));
    memcpy(url->host, offset, url->hostLength);
    url->host[url->hostLength - 1] = '\0';
    offset += url->hostLength - 1;

    check_port(url, spec, i, offset, totalLength);
    //check_path(url, spec, i, offset, totalLength);
}

void check_port(UrlType* url, char* spec, int startChar, char* offset, int totalLength) {
    url->port = 0;

    if (spec[startChar] == ':') {
        startChar++;
        offset++;

        while(char_is_digit(spec[startChar])) {
            url->port = url->port * 10 + (spec[startChar] - '0');
            startChar++;
            offset++;
        }
    } 
    
    if (url->port == 0) {
        url->port = default_port_of(url->scheme);
    }

    check_path(url, spec, startChar, offset, totalLength);
}

void check_path(UrlType* url, char* spec, int startChar, char* offset, int totalLength) {
    while (startChar != totalLength && spec[startChar] != '?' && spec[startChar] != '#') {
        url->pathLength++;
        startChar++;
    }

    url->path = (char *) malloc((url->pathLength) * sizeof(char));
    memcpy(url->path, offset, url->pathLength);
    url->path[url->pathLength - 1] = '\0';
    offset += url->pathLength - 1;

    check_query(url, spec, startChar, offset, totalLength);
}

void check_query(UrlType* url, char* spec, int startChar, char* offset, int totalLength) {
    while (startChar != totalLength && spec[startChar] != '#') {
        url->queryLength++;
        startChar++;
    }

    url->query = (char *) malloc((url->queryLength) * sizeof(char));
    memcpy(url->query, offset, url->queryLength);
    url->query[url->queryLength - 1] = '\0';
    offset += url->queryLength - 1;

    check_fragment(url, spec, startChar, offset, totalLength);
}

void check_fragment(UrlType* url, char* spec, int startChar, char* offset, int totalLength) {
    while (startChar != totalLength) {
        url->fragmentLength++;
        startChar++;
    }

    url->fragment = (char *) malloc((url->fragmentLength) * sizeof(char));

    if (url->fragmentLength == 1) {
        url->fragment[0] = '\0';
        return;
    }

    memcpy(url->fragment, offset, url->fragmentLength);
    url->fragment[url->fragmentLength - 1] = '\0';
}

bool char_is_digit(char c) {
    return c >= '0' && c <= '9';
}

int default_port_of(char* scheme) {
    if (strcmp(scheme, "ftp:") == 0) {
        return DEFAULT_PORT_FTP;
    }
    
    if (strcmp(scheme, "ssh:") == 0) {
        return DEFAULT_PORT_SSH;
    }
    
    if (strcmp(scheme, "telnet:") == 0) {
        return DEFAULT_PORT_TELNET;
    }
    
    if (strcmp(scheme, "http:") == 0) {
        return DEFAULT_PORT_HTTP;
    }
    
    if (strcmp(scheme, "https:") == 0) {
        return DEFAULT_PORT_HTTPS;
    }
    
    if (strcmp(scheme, "nntp:") == 0) {
        return DEFAULT_PORT_NNTP;
    }
    
    if (strcmp(scheme, "ntp:") == 0) {
        return DEFAULT_PORT_NTP;
    }
    
    if (strcmp(scheme, "ftps:") == 0) {
        return DEFAULT_PORT_FTPS;
    }
    
    if (strcmp(scheme, "tftp:") == 0) {
        return DEFAULT_PORT_TFTP;
    }
    
    return 0;
}

bool are_port_equal(UrlType* url1, UrlType* url2) {
    if (url1->port != 0 || url2->port != 0) {
        if (url1->port != url2->port) {
            return false;
        }
    }

    return true;
}

char* url_to_str(UrlType* url) {
    char *c;

    // If port is 0, then is wasn't given at construction AND,
    // No default port could be found
    if (url->port == 0) {
        c = psprintf("%s%s%s%s%s", url->scheme, url->host, url->path, url->query, url->fragment);
    } else {
        c = psprintf("%s%s:%d%s%s%s", url->scheme, url->host, url->port, url->path, url->query, url->fragment);
    }

    return c;
}
