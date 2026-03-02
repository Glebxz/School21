CREATE VIEW v_symmetric_union AS (
WITH jan2r AS (
    SELECT person_visits.person_id FROM person_visits WHERE person_visits.visit_date = '2022-01-02'
), jan6s AS (
    SELECT person_visits.person_id FROM person_visits WHERE person_visits.visit_date = '2022-01-06'
)
(SELECT * FROM jan2r
EXCEPT
SELECT * FROM jan6s)
UNION
(SELECT * FROM jan6s
EXCEPT
SELECT * FROM jan2r)
ORDER BY 1);