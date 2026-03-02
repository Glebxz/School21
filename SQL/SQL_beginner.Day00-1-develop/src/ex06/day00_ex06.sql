SELECT
    (SELECT name FROM person WHERE id = person_id) AS NAME,  -- this is an internal query in a main SELECT clause
	(SELECT CASE WHEN person.name = 'Denis' THEN true ELSE false END FROM person WHERE id = person_id) AS check_name
FROM person_order
WHERE (menu_id = 13 OR menu_id = 14 OR menu_id = 18) AND order_date = '2022-01-07';