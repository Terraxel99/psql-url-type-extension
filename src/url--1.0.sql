\echo Use "CREATE EXTENSION url;" to load. \quit

CREATE FUNCTION url_in(cstring) RETURNS url
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_out(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE TYPE url (
    INPUT = url_in,
    OUTPUT = url_out
);
COMMENT ON TYPE url IS 'URL written as a string';

CREATE FUNCTION url_scheme(url) RETURNS cstring 
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_authority(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_host(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';


CREATE FUNCTION url_path(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_port(url) RETURNS integer
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_default_port(url) RETURNS integer
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_file(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_protocol(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_query(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_ref(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_equals(url,url) RETURNS boolean
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_same_file(url,url) RETURNS boolean
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_same_host(url,url) RETURNS boolean
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';
