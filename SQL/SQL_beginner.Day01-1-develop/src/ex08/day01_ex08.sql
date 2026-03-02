SELECT person_order.order_date, CONCAT(prsn.name, ' (age:', prsn.age, ')') AS person_information
FROM person_order NATURAL JOIN (SELECT id AS person_id, name, age FROM person) AS prsn
ORDER BY order_date, person_information; 