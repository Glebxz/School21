-- Session #1
BEGIN;
-- Session #2
BEGIN;
-- Session #1
UPDATE pizzeria SET rating = 1 WHERE name = 'Kazan Pizza';
-- Session #2
UPDATE pizzeria SET rating = 1 WHERE name = 'Kazan Pizza 2';
-- Session #1
UPDATE pizzeria SET rating = 2 WHERE name = 'Kazan Pizza 2';
-- Session #2
UPDATE pizzeria SET rating = 2 WHERE name = 'Kazan Pizza';
-- Session #1
COMMIT;
-- Session #2
COMMIT;