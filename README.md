# OTUS-CPP-Basics 06 homework Project

## 1. Stack
Statistics utility.
Developed by means of C++17 / UNIX / GCC.

## 2. Description
В задании требуется реализовать два контейнера динамического размера – последовательный и
спискового типа – и пользовательский код с демонстрацией возможностей этих контейнеров.
1. Последовательный контейнер
Отличительная черта такого контейнера – расположение элементов друг за другом подряд
(как и у обычного массива в стиле Си).
2. Контейнер спискового типа – не предоставляет гарантий расположения элементов друг за
другом в памяти. Связь между элементами осуществляется через указатели (указатель на
предыдущий элемент и/или указатель на следующий элемент).
Пользовательский код (вызывается из функции main) должен содержать следующий набор
действий с обоими контейнерами:
1. создание объекта контейнера для хранения объектов типа int
2. добавление в контейнер десяти элементов (0, 1 … 9)
3. вывод содержимого контейнера на экран
ожидаемый результат: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
4. вывод размера контейнера на экран
ожидаемый результат: 10
5. удаление третьего (по счёту), пятого и седьмого элементов
6. вывод содержимого контейнера на экран
ожидаемый результат: 0, 1, 3, 5, 7, 8, 9
7. добавление элемента 10 в начало контейнера
8. вывод содержимого контейнера на экран
ожидаемый результат: 10, 0, 1, 3, 5, 7, 8, 9
9. добавление элемента 20 в середину контейнера
10. вывод содержимого контейнера на экран
ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9
11. добавление элемента 30 в конец контейнера
12. вывод содержимого контейнера на экран
ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
Требования к минимальному интерфейсу:
- метод/ы (может быть несколько) добавления элементов в конец контейнера ( push_back )
- метод/ы вставки элементов в произвольную позицию ( insert )
- метод/ы удаления элементов из контейнера ( erase )
- метод получения текущего размера контейнера ( size )
- метод/ы получения доступа по индексу ( operator[] )

## 3. Getting started
### 3.1 Clone the project 
```bash
cd </path/to/workspace>
git clone https://github.com/mattaku5hi/otus-cpp-basic_6/
```
### 3.2 Build the project
To build a project one may simply execute a script:  
to build a release executable:
```bash
cd </path/to/workspace>
chmod +x ./tools/container_build_release.sh
./tools/container_build_release.sh  
```
to build a debug executable:
```bash
cd </path/to/workspace>
chmod +x ./tools/container_build_debug.sh
./tools/containter_build_debug.sh  
```

## 4. Usage
The utility takes no options and prints results to standard input:
```bash
./release/containter
```
Example:
```bash
./release/containter

<<< container ContainerCont<int> example >>>
Print with dereference: 0 1 2 3 4 5 6 7 8 9 
Print with get(): 0 1 2 3 4 5 6 7 8 9 
Container 'vector' size: 10
Print after erasing: 0 1 3 5 7 8 9 
Print after inserting at the start: 10 0 1 3 5 7 8 9 
Print after inserting in the middle: 10 0 1 3 20 5 7 8 9 
Print after inserting at the end: 10 0 1 3 20 5 7 8 9 30 

<<< container ContainerListDoubly<int> example >>>
Print with dereference: 0 1 2 3 4 5 6 7 8 9 
Print with get(): 0 1 2 3 4 5 6 7 8 9 
Container 'doubly-linked list' size: 10
Print after erasing: 0 1 3 5 7 8 9 
Print after inserting at the start: 10 0 1 3 5 7 8 9 
Print after inserting in the middle: 10 0 1 3 20 5 7 8 9 
Print after inserting at the end: 10 0 1 3 20 5 7 8 9 30 

<<< container ContainerListSingly<int> example >>>
Print with dereference: 0 1 2 3 4 5 6 7 8 9 
Print with get(): 0 1 2 3 4 5 6 7 8 9 
Container 'singly-linked list' size: 10
Print after erasing: 0 1 3 5 7 8 9 
Print after inserting at the start: 10 0 1 3 5 7 8 9 
Print after inserting in the middle: 10 0 1 3 20 5 7 8 9 
Print after inserting at the end: 10 0 1 3 20 5 7 8 9 30
```
