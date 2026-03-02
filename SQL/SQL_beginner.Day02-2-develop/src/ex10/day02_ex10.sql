SELECT pr1.name AS person_name1, pr2.name AS person_name2, pr1.address AS common_address, pr2.address
FROM person pr1 INNER JOIN person pr2 ON pr1.address = pr2.address AND pr1.id > pr2.id
ORDER BY person_name1, person_name2, common_address;