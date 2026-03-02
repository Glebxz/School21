WITH gender_list AS (SELECT menu.pizzeria_id, SUM(CASE WHEN person.gender = 'male' THEN 1 ELSE 0 END) AS male_count, SUM(CASE WHEN person.gender = 'female' THEN 1 ELSE 0 END) AS female_count
FROM person_order
INNER JOIN person ON person.id = person_order.person_id
INNER JOIN menu ON menu.id = person_order.menu_id
GROUP BY menu.pizzeria_id)
SELECT pizzeria.name
FROM gender_list
INNER JOIN pizzeria ON pizzeria.id = gender_list.pizzeria_id
WHERE (male_count = 0 AND female_count > 0) OR (male_count > 0 AND female_count = 0)
ORDER BY 1;