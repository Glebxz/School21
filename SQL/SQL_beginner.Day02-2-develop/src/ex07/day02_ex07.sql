SELECT pizzeria.name AS pizzeria_name
FROM person_visits
INNER JOIN person ON person.id = person_visits.person_id
INNER JOIN menu ON menu.pizzeria_id = person_visits.pizzeria_id
INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE person.name = 'Dmitriy' AND person_visits.visit_date = '2022-01-08' AND menu.price < 800;