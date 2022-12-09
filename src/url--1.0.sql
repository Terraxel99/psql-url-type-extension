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

CREATE FUNCTION url_from_string(cstring) RETURNS url
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_from_phpf(cstring, cstring, integer, cstring) RETURNS url
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_from_phf(cstring, cstring, cstring) RETURNS url
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_in_context(url, cstring) RETURNS url
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

CREATE FUNCTION url_to_string(url) RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE C
    AS '$libdir/url';

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

CREATE FUNCTION url_userinfo(url) RETURNS cstring
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

CREATE OR REPLACE FUNCTION url_eq(url, url) 
RETURNS boolean LANGUAGE internal IMMUTABLE AS 'int8eq';

CREATE OR REPLACE FUNCTION url_ne(url, url) 
RETURNS boolean LANGUAGE internal IMMUTABLE AS 'int8ne';

CREATE OR REPLACE FUNCTION url_lt(url, url) 
RETURNS boolean LANGUAGE internal IMMUTABLE AS 'int8lt';

CREATE OR REPLACE FUNCTION url_le(url, url) 
RETURNS boolean LANGUAGE internal IMMUTABLE AS 'int8le';

CREATE OR REPLACE FUNCTION url_gt(url, url) 
RETURNS boolean LANGUAGE internal IMMUTABLE AS 'int8gt';

CREATE OR REPLACE FUNCTION url_ge(url, url) 
RETURNS boolean LANGUAGE internal IMMUTABLE AS 'int8ge';

CREATE OR REPLACE FUNCTION url_cmp(url, url) 
RETURNS integer LANGUAGE internal IMMUTABLE AS 'btint8cmp';

CREATE OPERATOR = (
	LEFTARG = url,
	RIGHTARG = url,
	PROCEDURE = url_eq,
	COMMUTATOR = '=',
	NEGATOR = '<>',
	RESTRICT = eqsel,
	JOIN = eqjoinsel
);
COMMENT ON OPERATOR =(url, url) IS 'equals?';

CREATE OPERATOR <> (
	LEFTARG = url,
	RIGHTARG = url,
	PROCEDURE = url_ne,
	COMMUTATOR = '<>',
	NEGATOR = '=',
	RESTRICT = neqsel,
	JOIN = neqjoinsel
);
COMMENT ON OPERATOR <>(url, url) IS 'not equals?';

CREATE OPERATOR < (
	LEFTARG = url,
	RIGHTARG = url,
	PROCEDURE = url_lt,
	COMMUTATOR = > , 
	NEGATOR = >= ,
   	RESTRICT = scalarltsel, 
	JOIN = scalarltjoinsel
);
COMMENT ON OPERATOR <(url, url) IS 'less-than';

CREATE OPERATOR <= (
	LEFTARG = url,
	RIGHTARG = url,
	PROCEDURE = url_le,
	COMMUTATOR = >= , 
	NEGATOR = > ,
   	RESTRICT = scalarltsel, 
	JOIN = scalarltjoinsel
);
COMMENT ON OPERATOR <=(url, url) IS 'less-than-or-equal';

CREATE OPERATOR > (
	LEFTARG = url,
	RIGHTARG = url,
	PROCEDURE = url_gt,
	COMMUTATOR = < , 
	NEGATOR = <= ,
   	RESTRICT = scalargtsel, 
	JOIN = scalargtjoinsel
);
COMMENT ON OPERATOR >(url, url) IS 'greater-than';

CREATE OPERATOR >= (
	LEFTARG = url,
	RIGHTARG = url,
	PROCEDURE = url_ge,
	COMMUTATOR = <= , 
	NEGATOR = < ,
   	RESTRICT = scalargtsel, 
	JOIN = scalargtjoinsel
);
COMMENT ON OPERATOR >=(url, url) IS 'greater-than-or-equal';

CREATE OPERATOR CLASS btree_url_ops
DEFAULT FOR TYPE url USING btree
AS
        OPERATOR        1       <  ,
        OPERATOR        2       <= ,
        OPERATOR        3       =  ,
        OPERATOR        4       >= ,
        OPERATOR        5       >  ,
        FUNCTION        1       url_cmp(url, url);


