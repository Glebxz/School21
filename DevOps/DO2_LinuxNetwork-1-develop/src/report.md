## Part 1. Инструмент ipcalc
1. Сети и маски

- Адрес сети 192.167.38.54/13 = 192.160.0.0
- Маска 255.255.255.0 = /24 = 11111111.11111111.11111111.00000000
- Маска /15 = 255.254.0.0 = 11111111.11111110.00000000.00000000
- Маска 11111111.11111111.11111111.11110000 = /28 = 255.255.255.240

- Минимальный и максимальный хост для адреса 12.167.38.4/8 = 12.0.0.1 - 12.255.255.254
- Минимальный и максимальный хост для адреса 12.167.38.4/16 = 12.167.0.1 - 12.167.255.254
- Минимальный и максимальный хост для адреса 12.167.38.4/23 = 12.167.38.1 - 12.167.39.254
- Минимальный и максимальный хост для адреса 12.167.38.4/4 = 0.0.0.1 - 15.255.255.254


2. localhost

- Под localhost зарезервирована сеть 127.0.0.0/8, поэтому обратиться можно только с адресов  127.0.0.2 и 127.1.0.1


3. Диапазоны и сегменты сетей

- Частные: 10.0.0.45, 10.10.10.10, 172.20.250.4, 172.16.255.255, 192.168.4.2, публичные: 134.43.0.2, 172.0.2.1, 192.172.0.1, 172.68.0.2, 192.169.168.1

- Возможные адреса: 10.10.0.2, 10.10.10.10, 10.10.100.1

## Part 2. Статическая маршрутизация между двумя машинами

- ![ip a на двух машинах](./screenshots/Part2a.png)
- ![Вывод файла конфигурации](./screenshots/Part2b.png)
- ![netplan apply](./screenshots/Part2c.png)

1. 
- ![ip r add](./screenshots/Part2d.png)
- ![ping](./screenshots/Part2e.png)

2. 
- ![Вывод файла конфигурации](./screenshots/Part2d.png)
- ![ping](./screenshots/Part2e.png)

## Part 3. Утилита iperf3

1. 
- 8 Mbps = 1 MB/s
- 100 MB/s = 100000 Kbps
- 1 Gbps = 1000 Mbps
2. 
- ![ws1 > ws2](./screenshots/Part3a.png)
- ![ws2 > ws1](./screenshots/Part3b.png)

## Part 4. Сетевой экран
1. 
- ![Создание таблиц](./screenshots/Part4a.png)
- ![Создание таблиц](./screenshots/Part4b.png)
- Разница между стратегиями, применёнными в первом и втором файлах, в том, что всегда в приоритете первое правило. Машина ws1 первым правилом блокирует все исходящие пакеты протокола ICMP типа 8 (ICMPv4 echo request). Машина ws2 первым правилом разрешает прохождения пакетов протокола ICMP типа 8.

2. 
- ![nmap](./screenshots/Part4d.png)

## Part 5. Статическая маршрутизация сети

1. 
- ![r1 netplan](./screenshots/Part5a.png)
- ![r2 netplan](./screenshots/Part5b.png)
- ![ws11 netplan](./screenshots/Part5c.png)
- ![ws21 netplan](./screenshots/Part5d.png)
- ![ws22 netplan](./screenshots/Part5e.png)

- ![r1 ip](./screenshots/Part5a1.png)
- ![r2 ip](./screenshots/Part5b1.png)
- ![ws11 ip](./screenshots/Part5c1.png)
- ![ws21 ip](./screenshots/Part5d1.png)
- ![ws22 ip](./screenshots/Part5e1.png)

- ![ping ws2](./screenshots/Part5ws2.png)
- ![ping ws1](./screenshots/Part5ws1.png)

2. 
- ![sysctl](./screenshots/Part5.2a.png)
- ![sysctl](./screenshots/Part5.2b.png)

3. 
- ![основной шлюз](./screenshots/Part5.3a.png)
- ![основной шлюз](./screenshots/Part5.3b.png)
- ![основной шлюз](./screenshots/Part5.3c.png)


4. 
- ![Статическая маршрутизация](./screenshots/Part5.4a.png)
- ![Статическая маршрутизация](./screenshots/Part5.4b.png)
- ![Вывод ip r list](./screenshots/Part5.4c.png)
- Маршрут 10.10.0.0/18 не является маршрутом по умолчанию так как для него уже определен конкретный маршрут в таблице маршрутизации 

5. 
- ![Трассировка](./screenshots/Part5.5.png)
- Команда traceroute linux использует UDP пакеты. Она отправляет пакет с TTL=1 и смотрит адрес ответившего узла, дальше TTL=2, TTL=3 и так пока не достигнет цели. Каждый раз отправляется по три пакета и для каждого из них измеряется время прохождения. Пакет отправляется на случайный порт, который, скорее всего, не занят. Когда утилита traceroute получает сообщение от целевого узла о том, что порт недоступен трассировка считается завершенной.

6. 
- ![ICMP](./screenshots/Part5.6.png)

## Part 6. Динамическая настройка IP с помощью DHCP

1. 
- ![DHCP FILE](./screenshots/Part6.1a.png)

2. 
- ![CONF FILE](./screenshots/Part6.2a.png)
- ![DHCP REBOOT](./screenshots/Part6.2b.png)
- ![ping](./screenshots/Part6.2c.png)
- ![r1](./screenshots/Part6.2d.png)
- ![ws11](./screenshots/Part6.2e.png)
- ![Refresh IP](./screenshots/Part6.2f.png)
- ![Refresh IP](./screenshots/Part6.2g.png)

- sudo dhclint -v - запрашивает новый ip-адрес и выводит дополнительную информацию
- sudo dhclint -r - освобождает текущий ip-адрес

## Part 7. NAT

1. 
- ![r2 appache](./screenshots/Part7/Screenshot_1.png)
- ![r1 appache](./screenshots/Part7/Screenshot_2.png)
- ![ws22 appache](./screenshots/Part7/Screenshot_3.png)
- ![apply appache](./screenshots/Part7/Screenshot_4.png)
- ![config ip tables](./screenshots/Part7/Screenshot_6.png)
- ![apply ip tables](./screenshots/Part7/Screenshot_6.png)
- ![try ping](./screenshots/Part7/Screenshot_7.png)
- ![change ip tables](./screenshots/Part7/Screenshot_8.png)
- ![apply new firewall](./screenshots/Part7/Screenshot_11.png)
- ![ping ws22](./screenshots/Part7/Screenshot_10.png)
- ![new ip tables](./screenshots/Part7/Screenshot_13.png)
- ![telnet ws22 > r1](./screenshots/Part7/Screenshot_12.png)
- ![ping r1 > ws22](./screenshots/Part7/Screenshot_14.png)

## Part 8. Дополнительно. Знакомство с SSH Tunnels

- ![firewall](./screenshots/Part7/Screenshot_23.png)
- ![apache2 port](./screenshots/Part7/Screenshot_16.png)

1. 
- Команда sudo ssh -L 8888:127.0.0.1:80 10.20.0.3
- ![ssh w21 > w22](./screenshots/Part7/Screenshot_17.png)
- ![telnet1](./screenshots/Part7/Screenshot_18.png)

2. 

- Команда sudo ssh -R 8080:localhost:80 10.20.0.17
- ![ssh ws22 > ws11](./screenshots/Part7/Screenshot_21.png)
- ![telnet ws11](./screenshots/Part7/Screenshot_22.png)

