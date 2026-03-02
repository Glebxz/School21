CREATE VIEW v_price_with_discount AS
SELECT person.name, menu.pizza_name, menu.price, (menu.price - menu.price * 0.1)::integer AS discount_price
FROM person_order INNER JOIN menu ON menu.id = person_order.menu_id INNER JOIN person ON person.id = person_order.person_id
ORDER BY  1, 2;