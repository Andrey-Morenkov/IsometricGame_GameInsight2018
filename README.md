# IsometricGame_GameInsight2018

Движок: SDL2.
Запускать из /Release/MyGame.exe.
Управление камерой WASD, Создать/удалить барьер ПКМ, Задать точку назначения для игрока ЛКМ. 

Особенности:
* Скорость обновления игры не зависит от скорости кадров (FPS), можно выставить любое. Корректность проверена программой Fraps
* Подсвечивается клетка, на которую указывает курсор
* Клик по клетке спавнит препятствие (текстура выбирается случайным образом). Повторный клик убирает его
* Выход из игры через ESC или крестик на окне
* Закончена реалзация похода персонажа к точке с огибом препятствий (алгоритм А*):
* * Персонаж динамически реагирует на создание препятствий. То есть во время хождения по пути при постановке препятствия он его обойдет/срежет путь если препятстви убрали. С ботами пока не работает в силу нехватки времени.
* В настройках можно выставить кастомные параметры карты (размеры по осям, не обязательно квадрат), FPS, Tickrate, итд.
* Формула нахождения плитки под курсором в одноименном jpg файле
* Ботов (NPC) может быть сколько угодно, так же можно задать любой путь (для примера использован циклический только)
* При создании любого объекта можно его кастомизировать (в демо есть 2 пушки, стреляющие с разной скоростью)
* При попадании игрока на NPC или на выстрел пушки - игра окончена с поражением. Цель - дойти до финиша (фиолетовая клетка)

Были использованы в качестве помощи при создании:
* канал https://www.youtube.com/user/TheSolarString/
* SDL wiki
* исходный код игры OpenTTD на SDL
