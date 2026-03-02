CREATE UNIQUE INDEX idx_menu_unique ON menu(pizzeria_id, pizza_name);
EXPLAIN ANALYZE
SELECT pizzeria_id, pizza_name FROM menu WHERE pizzeria_id = 1 AND pizza_name = (SELECT menu.pizza_name FROM menu WHERE id = 1);