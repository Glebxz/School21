WITH full_list AS (SELECT pizzeria.name, COUNT(*)
FROM person_order INNER JOIN menu ON menu.id = person_order.menu_id INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
GROUP BY pizzeria.name
UNION
SELECT pizzeria.name, COUNT(*)
FROM person_visits INNER JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
GROUP BY pizzeria.name
ORDER BY 2 DESC)
SELECT full_list.name, SUM(count) AS total_count
FROM full_list
GROUP BY full_list.name
ORDER BY 2 DESC;