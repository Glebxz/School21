SELECT v_generated_dates.generated_date AS missing_date FROM v_generated_dates
EXCEPT
SELECT DISTINCT person_visits.visit_date FROM person_visits WHERE person_visits.visit_date < '2022-02-01'
ORDER BY missing_date;