SELECT COALESCE(person.name, '-') AS person_name, pv1.visit_date AS visit_date, COALESCE(pizzeria.name, '-') AS pizzeria_name
FROM (SELECT * FROM person_visits WHERE person_visits.visit_date BETWEEN '2022-01-01' AND '2022-01-03') AS pv1
FULL JOIN pizzeria ON pv1.pizzeria_id = pizzeria.id
FULL JOIN person ON pv1.person_id = person.id
ORDER BY person_name, visit_date, pizzeria_name;