# OTUS-CPP-Basics 05 homework Project

## 1. Stack
Statistics utility.
Developed by means of C++17 / UNIX / GCC.

## 2. Description
### 2.1 Task
Для реализации таблицы рекордов пользователю при старте приложения выводится предложение
представиться. Введенное значение запоминается в переменную строкового типа. Далее
приложение считает количество попыток, которое потребовалось пользователю для угадывания
числа. Это число так же запоминается. Затем имя пользователя и число попыток дописываются в
файл с таблицей рекордов и выводится полное текущее содержимое таблицы рекордов. См пример
high_scores.cpp.
Пример работы приложения:
```cmd
> guess_the_number
Hi! Enter your name, please:
Nemo
Enter your number:
25
greater than 25
38
greater than 38
44
less than 44
41
greater than 41
43
less than 43
42
you're right!
High scores table (best results):
Max     8
Biba    4
Boba    3
Morphius        9
Pound   4
Keira   8
Fifa    1
Nemo    6
```

### 2.2 Notes
All the extra tasks (1-5) have been solved as well.  
The default values range if no options have been specified - 0..50.  

## 3. Getting started
### 3.1 Clone the project 
```bash
cd </path/to/workspace>
git clone https://github.com/mattaku5hi/otus-cpp-basic_3/
```
### 3.2 Build the project
To build a project one may simply execute a script:  
to build a release executable:
```bash
cd </path/to/project>
chmod +x ./tools/stat_build_release.sh
./tools/guess_build_release.sh  
```
to build a debug executable:
```bash
cd </path/to/project>
chmod +x ./tools/stat_build_debug.sh
./tools/guuess_build_debug.sh  
```

## 4. Usage
The utility takes no options.  
However it is a console game so the utility is interactive and works with standard input.  
Example play:
```bash
./release/guess_the_number

```
