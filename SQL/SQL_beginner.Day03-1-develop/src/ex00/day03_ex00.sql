WITH kate AS (SELECT * FROM person WHERE person.name = 'Kate')
SELECT menu.pizza_name, menu.price, pizzeria.name AS pizzeria_name, person_visits.visit_date
FROM kate
INNER JOIN person_visits ON person_visits.person_id = kate.id
INNER JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
INNER JOIN menu ON menu.pizzeria_id = pizzeria.id
WHERE menu.price BETWEEN 800 AND 1000
ORDER BY 1, 2, 3;