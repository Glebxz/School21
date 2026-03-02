CREATE FUNCTION fnc_fibonacci(IN pstop INTEGER = 10) RETURNS SETOF INTEGER AS $$
    WITH RECURSIVE fbc_line(prelast, last) AS (
            VALUES (0, 1)
        UNION ALL
            SELECT last, prelast + last FROM fbc_line WHERE last < pstop
    )
    SELECT prelast FROM fbc_line;
$$ LANGUAGE sql;
SELECT * FROM fnc_fibonacci(100);
SELECT * FROM fnc_fibonacci();