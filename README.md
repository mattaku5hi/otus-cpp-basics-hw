# OTUS-CPP-Basics 09 homework Project

## 1. Stack
Hacker utility.  
Developed by means of C++17 / UNIX / GCC.

## 2. Description
В задании требуется реализовать многопоточный поиск повторяющихся слов в переданных утилите в качестве аргументов  
файлах на основе уже имеющейся однопоточной реализации.  
Также в качестве дополнительных фич было реализовано:  
- простой бенчмарк-тест для определения оптимального максимального количества потоков, одновременно решающих задачу:  
файлы для обработки помещаются в очередь и, если файлов было задано больше, чем максимальное число потоков, то очередь сокращается  
по мере появления освободившегося потока;  
- возможность условной компиляцией выбирать, будет ли конечный словарь получен слиянием _thread_local_ (каждого потока-задачи) словарей или  
он изначально будет единственным (защищенным мьютексом). Тестовые запуски показали, что при малом числе файлов и, следовательно, потоков (<6)  
производительность не меняется. Однако при бОльшем числе потоков слияние дает все более и более существенный выигрыш в производительности.  
И это при том, что был реализован "не худший" вариант использования единственного словаря, то есть, все равно, в каждом потоке создавалась локальная копия,  
она же передавалась в функцию обхода файла, единственный файл затем блокировался только при локальном слиянии. Смею предположить, что если бы общий словарь блокировался  
для обхода файла, производительность бы заметно сократилась.       

## 3. Getting started
### 3.1 Clone the project 
```bash
cd </path/to/workspace>
git clone https://github.com/mattaku5hi/otus-cpp-basic_9/
```
### 3.2 Build the project
To build a project one may simply execute a script:  
to build a release executable:
```bash
cd </path/to/workspace>
chmod +x ./tools/build_release.sh
./tools/build_release.sh  
```
to build a debug executable:
```bash
cd </path/to/workspace>
chmod +x ./tools/build_debug.sh
./tools/build_debug.sh  
```
### 4. Project modifications
It's possible to use project in single-threaded:    
_-DUSE_MULTI_THREADING=0_ or _-DUSE_MULTI_THREADING_ is absent  
or in multi-threaded:  
_-DUSE_MULTI_THREADING=1_  
modes.  
It's possible to use project in thread_local dictionaries:    
_-DUSE_SHARED_DICT=0_ or _-DUSE_SHARED_DICT_ is absent  
or in multi-threaded:  
_-DUSE_SHARED_DICT=1_  
modes.    

## 5. Usage
The utility prints logs and results to standard input and takes user-defined amount of options - input files to search in:

```bash
./release/crc32_crack 
Call with two args: ./release/crc32_crack <input file> <output file>
```
Example for multi-threaded utility in thread_local dictionaries mode:
```bash
./release/most_used_words ./tools/karenina.txt ./tools/karenina_2.txt ./tools/gatsby.txt ./tools/gatsby_2.txt ./tools/gatsby_3.txt ./tools/the_double.txt ./tools/the_double_2.txt ./tools/karenina.txt ./tools/karenina_2.txt ./tools/gatsby.txt ./tools/gatsby_2.txt ./tools/gatsby_3.txt ./tools/the_double.txt ./tools/the_double_2.txt ./tools/karenina.txt ./tools/karenina_2.txt ./tools/gatsby.txt ./tools/gatsby_2.txt ./tools/gatsby_3.txt ./tools/the_double.txt ./tools/the_double_2.txt
Using multi-threading.
Start simple benchmark test...
  1 threads: 5392.16 ms
  2 threads: 2655.68 ms
  3 threads: 1869.97 ms
  4 threads: 1335.21 ms
  5 threads: 1171.79 ms
  6 threads: 988.799 ms
  7 threads: 864.713 ms
  8 threads: 692.319 ms
  9 threads: 687.195 ms
  10 threads: 700.753 ms
  11 threads: 597.234 ms
  12 threads: 607.194 ms
  13 threads: 639.806 ms
  14 threads: 573.138 ms
  15 threads: 598.533 ms
  16 threads: 466.877 ms
Optimal thread count: 16
Using local dictionaries with final merge.
52970 the
37016 and
29593 to
26212 a
24496 of
20112 he
18383 in
16612 was
16039 his
15028 i
Elapsed time is 76485 us
```

Example for multi-threaded utility in single dictionary mode:
```bash
./release/most_used_words ./tools/karenina.txt ./tools/karenina_2.txt ./tools/gatsby.txt ./tools/gatsby_2.txt ./tools/gatsby_3.txt ./tools/the_double.txt ./tools/the_double_2.txt ./tools/karenina.txt ./tools/karenina_2.txt ./tools/gatsby.txt ./tools/gatsby_2.txt ./tools/gatsby_3.txt ./tools/the_double.txt ./tools/the_double_2.txt ./tools/karenina.txt ./tools/karenina_2.txt ./tools/gatsby.txt ./tools/gatsby_2.txt ./tools/gatsby_3.txt ./tools/the_double.txt ./tools/the_double_2.txt
Using multi-threading.
Start simple benchmark test...
  1 threads: 5880.21 ms
  2 threads: 2910.8 ms
  3 threads: 1971.13 ms
  4 threads: 1449.59 ms
  5 threads: 1245.3 ms
  6 threads: 1069.91 ms
  7 threads: 895.003 ms
  8 threads: 734.186 ms
  9 threads: 728.656 ms
  10 threads: 739.961 ms
  11 threads: 624.288 ms
  12 threads: 610.505 ms
  13 threads: 610.75 ms
  14 threads: 628.398 ms
  15 threads: 597.865 ms
  16 threads: 497.756 ms
Optimal thread count: 16
Using the shared dictionary protected by mutex
139875 the
99231 and
79608 to
67116 of
56652 a
56637 he
47073 in
42567 was
42024 his
37581 that
Elapsed time is 92903 us
```

