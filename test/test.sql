DROP TABLE IF EXISTS test CASCADE;
DROP EXTENSION IF EXISTS url CASCADE;

CREATE EXTENSION url;

CREATE TABLE test (
    Id INT PRIMARY KEY,
    Url url NOT NULL
);

INSERT INTO test (Id, Url)
VALUES  (1 ,'http://www.test.com/tesxxt?query=5#anchor'),
VALUES  (2 ,'http://www.test.com/tesxxt');

SELECT * FROM test;
    