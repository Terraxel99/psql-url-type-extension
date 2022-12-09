DROP TABLE IF EXISTS test;
DROP TABLE IF EXISTS test_equals;
    
DROP EXTENSION IF EXISTS url;
CREATE EXTENSION url;

-- ============================== Basic insertion test ==============================

CREATE TABLE test (
    Id INT PRIMARY KEY,
    Url url NOT NULL
);

INSERT INTO test (Id, Url)
VALUES  (1, 'https://www.perdu.com'),
    (2, 'https://www.perdu.com?someQuery=1'),
    (3, 'https://www.perdu.com#someAnchor'),
    (4, 'https://www.perdu.com?someQuery=1#someAnchor'),
    (5, 'https://www.perdu.com/path/to/page'),
    (6, 'https://www.perdu.com/path/to/page/'),
    (7, 'https://www.perdu.com/path/to/page?someQuery=1&someOtherQuery=2#someAnchorAgain'),
    (8, 'https://www.perdu.com/path/to/page#stillAnAnchor'),
    (9, 'https://www.perdu.com/path/to/page#stillAnAnchor'),
    (10, 'http://www.perdu.com/path/to/page#stillAnAnchor'),
    (11, 'http://192.168.0.93/'),
    (12, 'ftp://192.168.0.93/path/to/folder'),
    (13, 'someunknownprotocol://192.168.0.93/path/to/folder'),
    (14, 'ssh://192.168.0.93/'),
    (15, 'ssh://192.168.0.93'),
    (16, 'telnet://192.168.29.93/'),
    (17, 'nntp://172.39.29.12:2593/'),
    (18, 'ntp://128.102.39.1'),
    (19, 'ftps://192.168.1.19/path/to/folder?someArgument=test'),
    (20, 'tftp://192.168.0.93/path/to/folder'),
    (21, 'http://totojr@www.perdu.com/path/to/page#stillAnAnchor');

-- ============================= Basic Testing =============================

SELECT * from test;

SELECT Id, url_scheme(Url), url_default_port(Url), url_port(Url)
FROM test;

SELECT Id, url_scheme(Url)
FROM test;

SELECT Id, url_authority(Url) -- Host + port
FROM test;

SELECT Id, url_host(Url)
FROM test;

SELECT Id, url_path(Url)
FROM test;

SELECT Id, url_port(Url)
FROM test;

SELECT Id, url_file(Url) -- Path + query
FROM test;

SELECT Id, url_protocol(Url) -- Scheme
FROM test;

SELECT Id, url_query(Url) 
FROM test;

SELECT Id, url_ref(Url) -- Fragment 
FROM test;

SELECT Id, url_to_string(Url)
FROM test;

SELECT Id, Url, url_userinfo(Url)
FROM test;

SELECT Id, Url, (Url)

-- ============================== Testing equality ==============================

CREATE TABLE test_equals (
    Id INT PRIMARY KEY,
    Url1 url NOT NULL,
    Url2 url NOT NULL
);

INSERT INTO test_equals (Id, Url1, Url2)
VALUES  (1 ,'http://www.postgresql.org:253/x?a#somefra', 'http://www.perdu.com:45/aa?zz#somefra'),
        (2 ,'http://www.perdu.com:45/aa?zz#somefra', 'http://www.test.com:45?aaaa#somefra'),
        (3 ,'http://www.test.com:45?aaaa#somefra', 'http://www.test.com:45?aaaa#somefra');

INSERT INTO test_equals (Id, Url1, Url2)
VALUES  (4 ,'http://www.test.com:45/haha?aaaa#somefrsssa','http://www.test.com:45/haha?aaaa#somefra');

SELECT Id, url_equals(Url1,Url2) -- url equals 
FROM test_equals;

SELECT Id, url_same_file(Url1,Url2) -- =url equals 
FROM test_equals;

SELECT Id, url_same_host(Url1,Url2) -- =url equals 
FROM test_equals;

-- ================== Using constructors to test equality ==================

SELECT * FROM test 
WHERE url_equals(Url, 'https://www.perdu.com/path/to/page?someQuery=1');

SELECT * FROM test 
WHERE url_equals(Url, url_from_string('https://www.perdu.com/path/to/page?someQuery=1'));

SELECT * FROM test
WHERE url_equals(Url, url_from_phpf('https', 'www.perdu.com', 443,'path/to/page?someQuery=1'));

SELECT * FROM test
WHERE url_equals(Url, url_from_phf('https', 'www.perdu.com', 'path/to/page?someQuery=1'));

SELECT * FROM test 
WHERE url_equals(Url, 'https://www.perdu.com/path/to/page?someQuery=1');

-- Should return everything
SELECT * FROM test 
WHERE url_equals(Url, url_in_context(Url, 'https://www.perdu.com/path/to/page?someQuery=1'));