WITH no_order AS (SELECT menu.id AS menu_id
FROM menu 
EXCEPT
SELECT person_order.menu_id 
FROM person_order 
ORDER BY 1)
SELECT menu.pizza_name, menu.price, pizzeria.name AS pizzeria_name
FROM no_order
INNER JOIN menu ON no_order.menu_id = menu.id
INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
ORDER BY 1, 2;