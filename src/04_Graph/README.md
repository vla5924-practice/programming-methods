# Полезная информация

## Проекты

* __lib__ - содержит библиотеку классов для работы со структурами данных "куча" и "разделенное множество"
* __graph__ - содержит блиблиотеку классов для работы с графами, использующих библиотеку _lib_
* __kruskal__ - содержит функцию, реализующую алгоритм Краскала на графе, а также тестирующую программу
* __dijkstra__ - содержит функцию, реализующую алгоритм Дейкстры на графе, а также тестирующую программу
* __sort__ - содержит статический класс, реализующий пирамидальную сортировку, и программу, тестирующую ее

## Конфигурация

* Проекты необходимо собирать в конфигурации Debug/x64
* Перед запуском тестирующих программ необходимо собрать библиотеку из проекта _lib_ и библиотеку из проекта __graph__
* В качестве версии языка в проектах выбран стандарт C++17 (хотя подойдет и C++11: в коде используются новые классы стандартной библиотеки, а также применяются конструкторы и операторы присваивания перемещения)
* Для подключения заголовочных файлов в проектах должен быть указан путь _./../../include/_ (Каталоги VC++ - Включаемые каталоги)

## Рекомендации по запуску

* __kruskal, dijkstra__ - ручной ввод графа: сначала вводится количество вершин графа, затем количество ребер, затем для каждого ребра вершина начала, вершина конца, вес; все значения вводятся через пробел или перенос строки
* __sort__ - размер массива вводится вручную, далее массив генерируется и сортируется автоматически