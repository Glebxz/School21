--WITH list_of_pizzas AS (SELECT DISTINCT menu.pizza_name FROM menu)
SELECT DISTINCT ON (menu1.pizza_name) menu1.pizza_name, pz1.name AS pizzeria_name1, pz2.name AS pizzeria_name2, menu1.price
FROM menu menu1
INNER JOIN menu menu2 ON menu2.pizza_name = menu1.pizza_name AND menu2.price = menu1.price AND menu1.pizzeria_id != menu2.pizzeria_id
INNER JOIN pizzeria pz1 ON menu1.pizzeria_id = pz1.id
INNER JOIN pizzeria pz2 ON menu2.pizzeria_id = pz2.id
ORDER BY 1;