WITH men_list AS (SELECT * FROM person WHERE gender = 'male' AND (address = 'Moscow' OR address = 'Samara'))
SELECT DISTINCT men_list.name
FROM men_list
LEFT JOIN person_order ON men_list.id = person_order.person_id
LEFT JOIN menu ON menu.id = person_order.menu_id
WHERE menu.pizza_name = 'pepperoni pizza' OR menu.pizza_name = 'mushroom pizza'
ORDER BY men_list.name DESC;