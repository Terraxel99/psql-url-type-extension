#include "urlType.h"

UrlType URL(char *spec) {
    UrlType url = { .scheme = "http:", .host = "//www.test.com", .port = 80 , .path = "/path/to/page", .query = "?query=5", .fragment = "#anchor"  };
    return url;
}