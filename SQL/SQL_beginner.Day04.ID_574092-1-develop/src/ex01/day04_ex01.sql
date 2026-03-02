SELECT v_persons_male.name FROM v_persons_male
UNION
SELECT v_persons_female.name FROM v_persons_female
ORDER BY name;
