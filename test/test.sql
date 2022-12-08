    DROP TABLE IF EXISTS test;
    DROP EXTENSION IF EXISTS url;

    CREATE EXTENSION url;

    CREATE TABLE test (
        Id INT PRIMARY KEY,
        Url url NOT NULL
    );

    INSERT INTO test (Id, Url)
    VALUES  (1 ,'http://www.postgresql.org:253/x?a#somefra'),
            (2 ,'http://www.perdu.com:45/aa?zz#somefra'),
            (3 ,'http://www.test.com:45?aaaa#somefra');

    SELECT * from test;

    SELECT Id, url_scheme(Url)
    FROM test;

    SELECT Id, url_authority(Url) -- host + port 
    FROM test;

    SELECT Id, url_host(Url)
    FROM test;

    SELECT Id, url_path(Url)
    FROM test;

    SELECT Id, url_port(Url)
    FROM test;

    SELECT Id, url_file(Url) --path+query
    FROM test;

    SELECT Id, url_protocol(Url) -- =scheme
    FROM test;

    SELECT Id, url_query(Url) 
    FROM test;

    SELECT Id, url_ref(Url) -- =fragment 
    FROM test;




    INSERT INTO test (Id, Url)
    VALUES  (1 ,'http://www.postgresql.org:253/x?a#somefra'),
            (2 ,'http://www.perdu.com:45/aa?zz#somefra'),
            (3 ,'http://www.test.com:45?aaaa#somefra'),
            --(4 ,'ftp://192.168.0.39/a');
            (5 ,'https://en.cppreference.com/w/c?a');
