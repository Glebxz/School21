WITH women_list AS (SELECT * FROM person WHERE gender = 'female')
SELECT women_list.name
FROM women_list
LEFT JOIN person_order ON women_list.id = person_order.person_id
LEFT JOIN menu ON person_order.menu_id = menu.id
WHERE menu.pizza_name = 'pepperoni pizza'
INTERSECT
SELECT women_list.name
FROM women_list
LEFT JOIN person_order ON women_list.id = person_order.person_id
LEFT JOIN menu ON person_order.menu_id = menu.id
WHERE menu.pizza_name = 'cheese pizza'
ORDER BY name;