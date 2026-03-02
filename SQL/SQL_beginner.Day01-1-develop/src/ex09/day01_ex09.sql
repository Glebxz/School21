SELECT pizzeria.name FROM pizzeria
WHERE NOT EXISTS (SELECT person_visits.pizzeria_id FROM person_visits WHERE person_visits.pizzeria_id = pizzeria.id);

SELECT pizzeria.name FROM pizzeria
WHERE pizzeria.id NOT IN (SELECT person_visits.pizzeria_id FROM person_visits WHERE person_visits.pizzeria_id IS NOT NULL);