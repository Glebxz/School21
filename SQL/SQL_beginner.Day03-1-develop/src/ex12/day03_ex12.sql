INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT generate_series((SELECT MAX(person_order.id) FROM person_order) + 1, (SELECT MAX(person_order.id) FROM person_order) + (SELECT MAX(person.id) FROM person), 1) AS id,
	   generate_series((SELECT MIN(person.id) FROM person), (SELECT MAX(person.id) FROM person), 1) AS person_id,
	   (SELECT menu.id FROM menu WHERE pizza_name = 'greek pizza') AS menu_id,
	   CAST('2022-02-25' AS DATE) AS order_date;