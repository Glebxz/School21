## Part 1. Готовый докер

1. ![Установка докер-образа nginx из репозитория](./screenshots/Part1/1.1.png)

2. ![Установка докер-контейнера](./screenshots/Part1/1.2.png)

3. ![docker ps](./screenshots/Part1/1.3.png)

4. 
- ![docker inspect size](./screenshots/Part1/1.4.1.png)
- SizeRw — это размер, занимаемый контейнером для записываемых данных. Он включает в себя все изменения, которые были внесены в файловую систему контейнера после его создания, такие как новые файлы, изменения существующих файлов и т.д.

- SizeRootFs — это общий размер всей файловой системы контейнера. Этот параметр включает в себя размер всех слоёв образа, из которого был создан контейнер, а также все изменения, внесённые в контейнер (то есть, SizeRw + размер слоёв образа).
- ![docker inspect network settings](./screenshots/Part1/1.4.2.png)

5. ![stop docker](./screenshots/Part1/1.5.png)

6. 
- ![docker with port map](./screenshots/Part1/1.6.1.png)
- ![localhost 80](./screenshots/Part1/1.6.2.png)

7. ![docker restart](./screenshots/Part1/1.7.png)

## Part 2. Операции с контейнером

1. ![nginx.conf](./screenshots/Part2/2.1.png)
2. ![changes](./screenshots/Part2/2.2.png)
3. ![cp to container](./screenshots/Part2/2.3.png)
4. ![reload nginx](./screenshots/Part2/2.4.png)
5. ![check](./screenshots/Part2/2.5.png)
6. ![make container.tar](./screenshots/Part2/2.6.png)
7. ![delete image with flag -f](./screenshots/Part2/2.7.png)
8. ![delete container](./screenshots/Part2/2.8.png)
9. ![import from tar and run](./screenshots/Part2/2.9.png)
10. ![check localhost/status page](./screenshots/Part2/2.10.png)

## Part 3. Мини веб-сервер

1. ![run spawn](./screenshots/Part3/3.1.png)
2. ![check page](./screenshots/Part3/3.2.png)

## Part 4. Свой докер

1. ![build docker image](./screenshots/Part4/4.1.png)
2. ![run docker image](./screenshots/Part4/4.2.png)
3. ![check in browser](./screenshots/Part4/4.3.png)
4. ![restart docker](./screenshots/Part4/4.4.png)
5. ![check in browser](./screenshots/Part4/4.5.png)

## Part 5. Dockle

- Файлы приложены в src

## Part 6. Базовый Docker Compose

1. ![build-compose build](.//Part6/6.1.png)
2. ![build-compose run](./Part6/6.2.png)