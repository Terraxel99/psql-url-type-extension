CREATE TABLE test (
    Id INT PRIMARY KEY,
    Url url NOT NULL
);

INSERT INTO test (Id, Url)
VALUES  (1 ,'http://www.postgresql.org/'),
        (2 ,'http://www.perdu.com/'),
        (3 ,'http://www.test.com/'),
        (4 ,'ftp://192.168.0.39/'),
        (5 ,'https://en.cppreference.com/w/c');

SELECT * FROM test;
    