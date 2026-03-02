SELECT person.name, COUNT(person_visits.id) AS count_of_visits
FROM person_visits INNER JOIN person ON person.id = person_visits.person_id
GROUP BY person.name
ORDER BY 2 DESC, 1
LIMIT 4;