# OTUS-CPP-Basics 08 homework Project

## 1. Stack
Hacker utility.  
Developed by means of C++17 / UNIX / GCC.

## 2. Description
В задании требуется реализовать эдакую хакерскую операцию:
- внедрение инъекции, а именно строки "He-he-he" в конец принимаемого на вход файла;
- внедрение беззнакового 4-байтового числа после инъекции, причем такого, что с ним контрольная сумма CRC32 конечного файла,    
именуемая в задании как хэш, будет совпадать с контрольной суммой исходного файла до внедрения инъекций.  

## 3. Getting started
### 3.1 Clone the project 
```bash
cd </path/to/workspace>
git clone https://github.com/mattaku5hi/otus-cpp-basic_8/
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
It's possible to use project in single-threaded (extra task 1):    
_-DUSE_MULTI_THREADING=0_ or _-DUSE_MULTI_THREADING_ is absent  
or in multi-threaded (extra task 2):  
_-DUSE_MULTI_THREADING=1_  
modes.  

## 5. Usage
The utility prints logs and results to standard input and takes two options:
- path to input file to be modified;
- path to output file (patched input file).

```bash
./release/crc32_crack 
Call with two args: ./release/crc32_crack <input file> <output file>
```
Example for single-threaded mode:
```bash
./release/crc32_crack ./tools/3_page.rbit ./tools/3_page_patched.rbit 
Injection: He-he-he
Original CRC32: 0x4419d23c
Using single-threaded implementation.
Bytes to add: 0x190145fe
Search completed in: 8.16708 s
Status: Success
time spent: 8 s
```

Example for single-threaded mode:
```bash
./release/crc32_crack ./tools/3_page.rbit ./tools/3_page_patched.rbit 
Injection: He-he-he
Original CRC32: 0x4419d23c
Benchmarking thread performance...
  1 threads: 21.9758 ms
  2 threads: 11.1039 ms
  4 threads: 9.72549 ms
  8 threads: 7.73153 ms
  10 threads: 9.99317 ms
  12 threads: 7.89468 ms
  14 threads: 5.78326 ms
  16 threads: 4.54708 ms
Skipping benchmark for 32 threads (more than hardware concurrency: 16)
Optimal thread count: 16 (Benchmark time: 4.54708 ms)
Starting full search...
Full search completed in: 1.1854 s
Bytes to add: 0x190145fe
Status: Success
```

