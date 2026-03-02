WITH andrey_data AS (SELECT person.id, person.name FROM person WHERE person.name = 'Andrey')
SELECT pizzeria.name AS pizzeria_name
FROM andrey_data INNER JOIN person_visits ON person_visits.person_id = andrey_data.id
LEFT JOIN person_order ON person_order.person_id = person_visits.person_id AND person_order.order_date = person_visits.visit_date
INNER JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
WHERE person_order.order_date IS NULL
ORDER BY person_visits.person_id;