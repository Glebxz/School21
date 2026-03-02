DO $$
DECLARE
    count_rows INTEGER;
BEGIN
    SELECT COUNT(*) INTO count_rows FROM person_discounts;
    EXECUTE format(
        'CREATE SEQUENCE seq_person_discounts START WITH %s INCREMENT BY 1;',
        count_rows + 1
    );
END $$;
ALTER TABLE person_discounts ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');