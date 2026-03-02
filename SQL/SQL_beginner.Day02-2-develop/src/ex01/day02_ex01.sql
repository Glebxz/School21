SELECT date_list.visit_date
FROM (SELECT person_visits.visit_date FROM person_visits GROUP BY person_visits.visit_date) AS date_list
LEFT JOIN person_visits pv1 ON date_list.visit_date = pv1.visit_date AND pv1.person_id = 1
LEFT JOIN person_visits pv2 ON date_list.visit_date = pv2.visit_date AND pv2.person_id = 2
WHERE pv1.id IS NULL AND pv2.id IS NULL
ORDER BY date_list.visit_date ASC;