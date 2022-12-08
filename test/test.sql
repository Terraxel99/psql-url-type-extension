DROP TABLE IF EXISTS test;
DROP EXTENSION IF EXISTS url;

CREATE EXTENSION url;

CREATE TABLE test (
    Id INT PRIMARY KEY,
    Url url NOT NULL
);

INSERT INTO test (Id, Url)
VALUES  (1 ,'https://www.perdu.com'),
        (2 ,'https://www.perdu.com?someQuery=1'),
        (3 ,'https://www.perdu.com#someAnchor'),
        (4 ,'https://www.perdu.com?someQuery=1#someAnchor'),
        (5 ,'https://www.perdu.com/path/to/page'),
        (6 ,'https://www.perdu.com/path/to/page/'),
        (7 ,'https://www.perdu.com/path/to/page?someQuery=1&someOtherQuery=2#someAnchorAgain'),
        (8 ,'https://www.perdu.com/path/to/page#stillAnAnchor'),
        (9 ,'http://192.168.0.93/'),
        (10 ,'ftp://192.168.0.93/path/to/folder');

SELECT * from test;

SELECT Id, url_scheme(Url)FROM test;

SELECT Id, url_authority(Url)
FROM test;
