# SQL Injection
## Walk-Through
- Suppling a malicious SQL code in user‐input fields, causing the application to run unintended database queries.

- Getting table names in database using `1 OR 1=1 UNION SELECT table_name, column_name FROM information_schema.COLUMNS`.

- Retrieving comments column from list_images table using using `1 OR 1=1 UNION SELECT Commentaire, countersign from users`.

- Decoding the code from one of the members surnames.

## Prevention
- Validating or whitelisting any fields that must follow a specific format (e.g. numeric IDs), rejecting anything with SQL metacharacters.