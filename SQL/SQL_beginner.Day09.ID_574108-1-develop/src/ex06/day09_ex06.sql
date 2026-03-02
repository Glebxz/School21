CREATE FUNCTION fnc_person_visits_and_eats_on_date(IN pperson VARCHAR = 'Dmitriy', IN pprice NUMERIC = 500, IN pdate DATE = '2022-01-08') RETURNS SETOF VARCHAR AS $$
    BEGIN
    RETURN QUERY
        SELECT DISTINCT pizzeria.name
        FROM pizzeria
        INNER JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id
        INNER JOIN person ON person.id = person_visits.person_id
        INNER JOIN menu ON menu.pizzeria_id = pizzeria.id
        WHERE person.name = pperson AND menu.price < pprice AND person_visits.visit_date = pdate;
    END;
$$ LANGUAGE plpgsql;
SELECT *
FROM fnc_person_visits_and_eats_on_date(pprice := 800);
SELECT *
FROM fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');