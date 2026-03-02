CREATE TABLE graph1 (
    id BIGSERIAL PRIMARY KEY,
    point1 VARCHAR NOT NULL,
    point2 VARCHAR NOT NULL,
    cost BIGINT NOT NULL DEFAULT 0
);

INSERT INTO graph1 (point1, point2, cost) VALUES
('A', 'B', 10),
('B', 'A', 10),
('A', 'D', 20),
('D', 'A', 20),
('A', 'C', 15),
('C', 'A', 15),
('B', 'D', 25),
('D', 'B', 25),
('B', 'C', 35),
('C', 'B', 35),
('D', 'C', 30),
('C', 'D', 30);

CREATE VIEW full_list_of_tours AS
WITH RECURSIVE tours_list AS (
    SELECT point1, point2, cost, point1 || ',' || point2 AS pth, 0 AS dept FROM graph1 WHERE graph1.point1 = 'A'
    UNION ALL
    SELECT tours_list.point1, graph1.point2, tours_list.cost + graph1.cost AS cost, tours_list.pth || ',' || graph1.point2, tours_list.dept + 1
    FROM tours_list
    INNER JOIN graph1 ON graph1.point1 = tours_list.point2 AND graph1.point2 != tours_list.point1
    WHERE tours_list.pth NOT LIKE '%' || graph1.point2 || '%'
)
SELECT tours_list.cost + graph1.cost AS total_cost, tours_list.pth || ',' || graph1.point2 AS tour
FROM tours_list
INNER JOIN graph1 ON graph1.point1 = tours_list.point2 AND graph1.point2 = tours_list.point1
WHERE dept = 2
ORDER BY 1, 2;

SELECT full_list_of_tours.total_cost, '{' || full_list_of_tours.tour || '}' AS tour FROM full_list_of_tours WHERE total_cost = (SELECT MIN(total_cost) FROM full_list_of_tours);
