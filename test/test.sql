        DROP TABLE IF EXISTS test;
        DROP EXTENSION IF EXISTS url;

        CREATE EXTENSION url;

        CREATE TABLE test (
            Id INT PRIMARY KEY,
            Url url NOT NULL
        );

        INSERT INTO test (Id, Url)
        VALUES  (1 ,'http://www.postgresql.org/aa?'),
                (2 ,'http://www.perdu.com/a?test=2'),
                (3 ,'http://www.test.com/aa?test=2'),
                --(4 ,'ftp://192.168.0.39/a');
                (5 ,'https://en.cppreference.com/w/c?test=2');

        SELECT * from test;

        SELECT Id, url_scheme(Url)
        FROM test;

        SELECT Id, url_authority(Url)
        FROM test;
