# OTUS-CPP-Basics 05 homework Project

## 1. Stack
Statistics utility.
Developed by means of C++17 / UNIX / GCC.

## 2. Description
На вход (стандартный ввод) приложению подаётся последовательность (заранее неизвестного
размера) числовых значений. Приложение должно в ходе своей работы считать всю
последовательность из стандартного ввода и вывести на экран набор следующих статистических
характеристик:
- min – минимальное значение из последовательности
- max – максимальное значение из последовательности
- mean – арифметическое среднее, посчитанное на основе всех элементов последовательности
- std - среднеквадратическое отклонение
- [опционально] pct90 - 90-й процентиль
- [опционально] pct95 - 95-й процентиль
Пункты, помеченные как [опционально] представляю собой «задачу со звёздочкой» и могут не
выполняться.
Остановка ввода последовательности предполагается путём передачи признака EOF (End Of File). В
Windows это делается путём следующего набора команд: Ctrl+Z, Enter. В Linux это делается путём
нажатия Ctrl+D.
Пример работы приложения:
```bash
> statistics
0 1 2 3 4 5 6 7 8 9 10
min = 0
max = 10
mean = 5
std = 3.162277
pct90 = 9
pct95 = 10
```

## 3. Getting started
### 3.1 Clone the project 
```bash
cd </path/to/workspace>
git clone https://github.com/mattaku5hi/otus-cpp-basic_5/
```
### 3.2 Build the project
To build a project one may simply execute a script:  
to build a release executable:
```bash
cd </path/to/workspace>
chmod +x ./tools/stat_build_release.sh
./tools/stat_build_release.sh  
```
to build a debug executable:
```bash
cd </path/to/workspace>
chmod +x ./tools/stat_build_debug.sh
./tools/stat_build_debug.sh  
```

## 4. Usage
The utility takes no options but awaits double values (until _EOF_) to be sent to standard input:
```bash
./release/statistics
```
Example:
```bash
./release/statistics
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

min = 0
max = 20
mean = 10
std = 6.0553
pct90 = 18
pct95 = 19
```
