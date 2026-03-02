SELECT person.name AS object_name FROM person
UNION ALL
SELECT menu.pizza_name FROM menu
ORDER BY object_name;