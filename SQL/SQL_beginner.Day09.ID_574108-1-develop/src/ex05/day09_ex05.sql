DROP FUNCTION fnc_persons_female();
DROP FUNCTION fnc_persons_male();
CREATE FUNCTION fnc_persons(IN pgender VARCHAR = 'female' ) RETURNS SETOF person AS $$
    SELECT * FROM person WHERE gender = pgender;
$$ LANGUAGE sql; 
SELECT *
FROM fnc_persons(pgender := 'male');
SELECT *
FROM fnc_persons();
