WITH genders AS (SELECT pizzeria.name, SUM(CASE WHEN gender = 'male' THEN 1 ELSE 0 END) AS male_count, SUM(CASE WHEN gender = 'female' THEN 1 ELSE 0 END) AS female_count
FROM person_visits
INNER JOIN person ON person.id = person_visits.person_id
INNER JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
GROUP BY pizzeria.name)
SELECT genders.name AS pizzeira_name
FROM genders
WHERE genders.male_count != genders.female_count
ORDER BY pizzeira_name;