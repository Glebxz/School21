COMMENT ON TABLE person_discounts IS 'Таблица хранит информацию о клиентах и их персональных скидках в каждой из пиццерий';
COMMENT ON COLUMN person_discounts.id IS 'Первичный ключ, идентификатор строки';
COMMENT ON COLUMN person_discounts.person_id IS 'Идентификатор клиента';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Идентификатор пиццерии';
COMMENT ON COLUMN person_discounts.discount IS 'Размер скидки в процентах';

SELECT obj_description('person_discounts'::regclass);
