# my-arkanoid

![screenshot](https://github.com/OtryvnoyKalendar/my-arkanoid/blob/main/screenshots/screenshot%203.png)

### Общее описание
my-arkanoid - это консольная игра по мотивам Арканоид, которая работает в Linux. Это только прототип игры, которую я написал для практики языка C.
Игра сделана на основе видео с ютуб канала Begin End и адаптирована под Linux. Вот *ссылки на видео*:  
[Урок 17 (часть 1)](https://www.youtube.com/watch?v=g1MSTO1wCko&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=17)  
[Урок 17 (часть 2)](https://www.youtube.com/watch?v=868_DV1ksqE&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=18)  
[Урок 20](https://www.youtube.com/watch?v=onBq1l8AxyE&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=21)  
[Урок 68](https://www.youtube.com/watch?v=PQnjcHbqRPw&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=69)  
[Урок 69](https://www.youtube.com/watch?v=u66oun_8GKk&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=70)  

### Как играть
Чтобы начать играть, нужно открыть консоль и перейти в папку с проектом. Дальше просто выполните скрипт:
```sh
sh project_start
```

- Управление:  
'Q' - выйти из игры  
'W' - запустить мяч  
'A' - влево  
'D' - вправо  
'R' - пропустить уровень  
'SPACE' - стрелять  

Если вы хотите **изменить код игры**, то вам не нужно ничего перекомпелировать и удалять вручную. После внесения изменений в файлы игры, просто снова запустите скрипт `project_start`, он всё сделает за вас.

Если вы захотите воспользоваться **отладчиком GDB**, чтобы дебажить код, то скрипт нужно запускать так:
```sh
sh project_start gdb
```
Этот скрипт создаст отдельный терминал с отладчиком и присоединиться к процессу игры.
