SELECT pizzeria.name, pizzeria.rating
FROM pizzeria LEFT OUTER JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
WHERE visit_date IS NULL
ORDER BY pizzeria.id;