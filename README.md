# OTUS-CPP-Basics 04 homework Project

## 1. Stack
Statistics utility.
Developed by means of C++17 / UNIX / GCC.

## 2. Description
Доработать исходный код из примера, реализовав приведенные выше методы класса  
Ball (их объявления и реализации-заглушки уже есть в файлах Ball.hpp и Ball.сpp  
соответственно). Для этого понадобится добавить несколько полей. При  
необходимости можем добавить любые другие методы (например, для создания  
объектов нашего класса в конструкторе World будет удобно добавить конструктор  
класса Ball).
Ожидается, что после доработки исходный код программы будет компилироваться и
запускаться командой ./physics <путь к файлу smile.txt>, например, ./physics  
/home/user/physics/data/smile.txt (тестовая модель находится в подкаталоге data  
примера), а в ходе работы программы увидим процесс симуляции столкновений
шаров, завершающийся упорядоченной структурой.

## 3. Getting started
### 3.1 Clone the project 
```bash
cd </path/to/workspace>
git clone https://github.com/mattaku5hi/otus-cpp-basic_4/
```
### 3.2 Build the project
To build a project one may simply execute a script:  
to build a release executable:
```bash
cd </path/to/project>
chmod +x ./tools/simulator_build_release.sh
./tools/simulator_build_release.sh  
```
to build a debug executable:
```bash
cd </path/to/project>
chmod +x ./tools/simulator_build_debug.sh
./tools/simulator_build_debug.sh  
```

## 4. Usage
The utility takes the only option - simulation model text file name:
```bash
cd </path/to/project>
./release/physics
Please, call with one argument ( example: ./release/physics <path to file smile.txt> )
```
Example:
```bash
./release/statistics ./data/smile.txt
```
***some graphic magic occurs here***
