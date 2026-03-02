SELECT person.address, ROUND(MAX(person.age)::NUMERIC - MIN(person.age)::NUMERIC / MAX(person.age)::NUMERIC, 2) AS formula, 
    ROUND(AVG(person.age), 2) AS average,
    CASE 
        WHEN ROUND(MAX(person.age)::NUMERIC - MIN(person.age)::NUMERIC / MAX(person.age)::NUMERIC, 2) > ROUND(AVG(person.age), 2) 
        THEN true 
        ELSE false 
    END AS comparison
FROM person
GROUP BY person.address
ORDER BY 1;