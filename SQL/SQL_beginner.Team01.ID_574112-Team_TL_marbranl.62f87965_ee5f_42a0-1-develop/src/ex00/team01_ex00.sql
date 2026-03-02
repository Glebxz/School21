SELECT *
FROM (
    SELECT
        COALESCE("user".name, 'not defined')::VARCHAR AS name,
        COALESCE("user".lastname, 'not defined')::VARCHAR AS lastname,
        balance.type AS type,
        SUM(balance.money) AS volume,
        COALESCE(curnc.name, 'not defined')::VARCHAR AS currency_name,
        COALESCE(curnc.last_rate_to_usd, 1) AS last_rate_to_usd,
        SUM(balance.money) * COALESCE(curnc.last_rate_to_usd, 1) AS total_volume_in_usd
    FROM balance
    FULL JOIN "user"
        ON "user".id = balance.user_id
    FULL JOIN (
        SELECT DISTINCT ON (id)
            id,
            name,
            rate_to_usd AS last_rate_to_usd
        FROM currency
        ORDER BY id, updated
    ) AS curnc
        ON curnc.id = balance.currency_id
    GROUP BY
        "user".name,
        "user".lastname,
        balance.type,
        curnc.name,
        curnc.last_rate_to_usd
) AS result
ORDER BY
    name DESC,
    lastname ASC,
    type ASC