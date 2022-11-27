\echo Use "CREATE EXTENSION url;" to load. \quit

CREATE FUNCTION url_in(cstring) RETURNS url
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/uri';

CREATE FUNCTION url_out(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/uri';

CREATE TYPE url {
    INPUT = url_in,
    OUTPUT = url_out
};
COMMENT ON TYPE url IS 'URL written as a string';