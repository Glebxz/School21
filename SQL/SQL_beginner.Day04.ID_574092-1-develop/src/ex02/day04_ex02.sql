CREATE VIEW v_generated_dates AS
SELECT generate_series::DATE AS generated_date
FROM generate_series('2022-01-01'::DATE, '2022-01-31'::DATE, '1 day'::interval)
ORDER BY 1;