-- INSERT INTO currency VALUES (100, 'EUR', 0.85, '2022-01-01 13:29');
-- INSERT INTO currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

SELECT COALESCE("user".name, 'not defined') as name,
       COALESCE("user".lastname, 'not defined') as lastname,
       currency.name AS currency_name,
       COALESCE(cp.past, cp.future) * cp.money as currency_in_usd
FROM balance LEFT JOIN "user" ON balance.user_id = "user".id LEFT JOIN (SELECT balance.user_id,
                           balance.money, balance.currency_id,
                           (SELECT currency.rate_to_usd FROM currency WHERE currency.id = balance.currency_id AND currency.updated <= balance.updated ORDER BY currency.updated DESC LIMIT 1) AS past,
                           (SELECT currency.rate_to_usd FROM currency WHERE currency.id = balance.currency_id AND currency.updated >= balance.updated ORDER BY currency.updated LIMIT 1) AS future
                    FROM balance) AS cp ON balance.user_id = cp.user_id
         RIGHT JOIN currency ON cp.currency_id = currency.id
        GROUP BY "user".name, currency_in_usd, lastname, currency_name
ORDER BY name DESC, lastname, currency_name ASC;