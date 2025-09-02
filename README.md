# OTUS-CPP-Basics 07 homework Project

## 1. Stack
Statistics utility.
Developed by means of C++17 / UNIX / GCC / GTest.

## 2. Description
Реализовать не менее 10-ти тестовых сценариев для каждого из контейнеров. Конкретные
сценарии придумать самостоятельно, но проверять они должны основную функциональность
контейнеров:
- создание контейнера
- вставка элементов в конец
- вставка элементов в начало
- вставка элементов в середину
- удаление элементов из конца
- удаление элементов из начала
- удаление элементов из середины
- получение элементов из контейнера
- получение размера контейнера (фактическое количество элементов)    

Итоговые требования:
1. реализовать два контейнера и код их использования
2. для сборки использовать CMake
3. выгрузить результат на github.com в свой аккаунт  

## 3. Preparing
### 3.1 Install the dependencies
Make sure that all the dependencies are already installed on your machine  
```bash
sudo apt update 
sudo apt install -y libgtest-dev
```

## 4. Getting started
### 4.1 Clone the project 
```bash
cd </path/to/workspace>
git clone https://github.com/mattaku5hi/otus-cpp-basic_7/
```
### 4.2 Build the project
To build a project one may simply execute a script:  
to build the release executable and tests for it:
```bash
cd </path/to/workspace>
chmod +x ./tools/container_build_release.sh
./tools/build_release.sh  
```
to build the debug executable:
```bash
cd </path/to/workspace>
chmod +x ./tools/container_build_release.sh
./tools/build_debug.sh  
```

## 5. Usage
The utility is able to accept the GTest compatible options depending on what and how the user wants to test.  
Example launch of all the tests (for both vector and singly linked list):
```bash
./release/container_test 
[==========] Running 34 tests from 11 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from LinkedListBasicTest
[ RUN      ] LinkedListBasicTest.Creation
[       OK ] LinkedListBasicTest.Creation (0 ms)
[ RUN      ] LinkedListBasicTest.PushBack
[       OK ] LinkedListBasicTest.PushBack (0 ms)
[ RUN      ] LinkedListBasicTest.Insert
[       OK ] LinkedListBasicTest.Insert (0 ms)
[ RUN      ] LinkedListBasicTest.Erase
[       OK ] LinkedListBasicTest.Erase (0 ms)
[ RUN      ] LinkedListBasicTest.Clear
[       OK ] LinkedListBasicTest.Clear (0 ms)
[----------] 5 tests from LinkedListBasicTest (0 ms total)

[----------] 2 tests from LinkedListAccessTest
[ RUN      ] LinkedListAccessTest.OperatorBracket
[       OK ] LinkedListAccessTest.OperatorBracket (0 ms)
[ RUN      ] LinkedListAccessTest.ConstOperatorBracket
[       OK ] LinkedListAccessTest.ConstOperatorBracket (0 ms)
[----------] 2 tests from LinkedListAccessTest (0 ms total)

[----------] 2 tests from LinkedListCopyTest
[ RUN      ] LinkedListCopyTest.CopyConstructor
[       OK ] LinkedListCopyTest.CopyConstructor (0 ms)
[ RUN      ] LinkedListCopyTest.CopyAssignment
[       OK ] LinkedListCopyTest.CopyAssignment (0 ms)
[----------] 2 tests from LinkedListCopyTest (0 ms total)

[----------] 2 tests from LinkedListMoveTest
[ RUN      ] LinkedListMoveTest.MoveConstructor
[       OK ] LinkedListMoveTest.MoveConstructor (0 ms)
[ RUN      ] LinkedListMoveTest.MoveAssignment
[       OK ] LinkedListMoveTest.MoveAssignment (0 ms)
[----------] 2 tests from LinkedListMoveTest (0 ms total)

[----------] 6 tests from LinkedListIteratorTest
[ RUN      ] LinkedListIteratorTest.BasicIteration
[       OK ] LinkedListIteratorTest.BasicIteration (0 ms)
[ RUN      ] LinkedListIteratorTest.ConstIteration
[       OK ] LinkedListIteratorTest.ConstIteration (0 ms)
[ RUN      ] LinkedListIteratorTest.IteratorInsert
[       OK ] LinkedListIteratorTest.IteratorInsert (0 ms)
[ RUN      ] LinkedListIteratorTest.IteratorErase
[       OK ] LinkedListIteratorTest.IteratorErase (0 ms)
[ RUN      ] LinkedListIteratorTest.EraseFromBeginning
[       OK ] LinkedListIteratorTest.EraseFromBeginning (0 ms)
[ RUN      ] LinkedListIteratorTest.EraseFromEnd
[       OK ] LinkedListIteratorTest.EraseFromEnd (0 ms)
[----------] 6 tests from LinkedListIteratorTest (0 ms total)

[----------] 4 tests from VectorBasicTest
[ RUN      ] VectorBasicTest.Creation
[       OK ] VectorBasicTest.Creation (0 ms)
[ RUN      ] VectorBasicTest.PushBack
[       OK ] VectorBasicTest.PushBack (0 ms)
[ RUN      ] VectorBasicTest.Insert
[       OK ] VectorBasicTest.Insert (0 ms)
[ RUN      ] VectorBasicTest.Erase
[       OK ] VectorBasicTest.Erase (0 ms)
[----------] 4 tests from VectorBasicTest (7 ms total)

[----------] 2 tests from VectorAccessTest
[ RUN      ] VectorAccessTest.OperatorBracket
[       OK ] VectorAccessTest.OperatorBracket (0 ms)
[ RUN      ] VectorAccessTest.ConstOperatorBracket
[       OK ] VectorAccessTest.ConstOperatorBracket (0 ms)
[----------] 2 tests from VectorAccessTest (0 ms total)

[----------] 2 tests from VectorCopyTest
[ RUN      ] VectorCopyTest.CopyConstructor
[       OK ] VectorCopyTest.CopyConstructor (0 ms)
[ RUN      ] VectorCopyTest.CopyAssignment
[       OK ] VectorCopyTest.CopyAssignment (0 ms)
[----------] 2 tests from VectorCopyTest (0 ms total)

[----------] 2 tests from VectorMoveTest
[ RUN      ] VectorMoveTest.MoveConstructor
[       OK ] VectorMoveTest.MoveConstructor (0 ms)
[ RUN      ] VectorMoveTest.MoveAssignment
[       OK ] VectorMoveTest.MoveAssignment (0 ms)
[----------] 2 tests from VectorMoveTest (0 ms total)

[----------] 4 tests from VectorIteratorTest
[ RUN      ] VectorIteratorTest.BasicIteration
[       OK ] VectorIteratorTest.BasicIteration (0 ms)
[ RUN      ] VectorIteratorTest.ConstIteration
[       OK ] VectorIteratorTest.ConstIteration (0 ms)
[ RUN      ] VectorIteratorTest.IteratorInsert
[       OK ] VectorIteratorTest.IteratorInsert (0 ms)
[ RUN      ] VectorIteratorTest.IteratorErase
[       OK ] VectorIteratorTest.IteratorErase (0 ms)
[----------] 4 tests from VectorIteratorTest (0 ms total)

[----------] 3 tests from VectorCapacityTest
[ RUN      ] VectorCapacityTest.SizeAndCapacity
[       OK ] VectorCapacityTest.SizeAndCapacity (0 ms)
[ RUN      ] VectorCapacityTest.Reserve
[       OK ] VectorCapacityTest.Reserve (0 ms)
[ RUN      ] VectorCapacityTest.Clear
[       OK ] VectorCapacityTest.Clear (0 ms)
[----------] 3 tests from VectorCapacityTest (0 ms total)

[----------] Global test environment tear-down
[==========] 34 tests from 11 test suites ran. (8 ms total)
[  PASSED  ] 34 tests.
```
Example launch of all the tests (for both vector and singly linked list) and store report to the specified XML file:
```bash
./release/container_test --gtest_output=xml:./container_test_report.xml
[==========] Running 34 tests from 11 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from LinkedListBasicTest
[ RUN      ] LinkedListBasicTest.Creation
[       OK ] LinkedListBasicTest.Creation (0 ms)
[ RUN      ] LinkedListBasicTest.PushBack
[       OK ] LinkedListBasicTest.PushBack (0 ms)
[ RUN      ] LinkedListBasicTest.Insert
[       OK ] LinkedListBasicTest.Insert (0 ms)
[ RUN      ] LinkedListBasicTest.Erase
[       OK ] LinkedListBasicTest.Erase (0 ms)
[ RUN      ] LinkedListBasicTest.Clear
[       OK ] LinkedListBasicTest.Clear (0 ms)
[----------] 5 tests from LinkedListBasicTest (0 ms total)

[----------] 2 tests from LinkedListAccessTest
[ RUN      ] LinkedListAccessTest.OperatorBracket
[       OK ] LinkedListAccessTest.OperatorBracket (0 ms)
[ RUN      ] LinkedListAccessTest.ConstOperatorBracket
[       OK ] LinkedListAccessTest.ConstOperatorBracket (0 ms)
[----------] 2 tests from LinkedListAccessTest (0 ms total)

[----------] 2 tests from LinkedListCopyTest
[ RUN      ] LinkedListCopyTest.CopyConstructor
[       OK ] LinkedListCopyTest.CopyConstructor (0 ms)
[ RUN      ] LinkedListCopyTest.CopyAssignment
[       OK ] LinkedListCopyTest.CopyAssignment (0 ms)
[----------] 2 tests from LinkedListCopyTest (0 ms total)

[----------] 2 tests from LinkedListMoveTest
[ RUN      ] LinkedListMoveTest.MoveConstructor
[       OK ] LinkedListMoveTest.MoveConstructor (0 ms)
[ RUN      ] LinkedListMoveTest.MoveAssignment
[       OK ] LinkedListMoveTest.MoveAssignment (0 ms)
[----------] 2 tests from LinkedListMoveTest (0 ms total)

[----------] 6 tests from LinkedListIteratorTest
[ RUN      ] LinkedListIteratorTest.BasicIteration
[       OK ] LinkedListIteratorTest.BasicIteration (0 ms)
[ RUN      ] LinkedListIteratorTest.ConstIteration
[       OK ] LinkedListIteratorTest.ConstIteration (0 ms)
[ RUN      ] LinkedListIteratorTest.IteratorInsert
[       OK ] LinkedListIteratorTest.IteratorInsert (0 ms)
[ RUN      ] LinkedListIteratorTest.IteratorErase
[       OK ] LinkedListIteratorTest.IteratorErase (0 ms)
[ RUN      ] LinkedListIteratorTest.EraseFromBeginning
[       OK ] LinkedListIteratorTest.EraseFromBeginning (0 ms)
[ RUN      ] LinkedListIteratorTest.EraseFromEnd
[       OK ] LinkedListIteratorTest.EraseFromEnd (0 ms)
[----------] 6 tests from LinkedListIteratorTest (0 ms total)

[----------] 4 tests from VectorBasicTest
[ RUN      ] VectorBasicTest.Creation
[       OK ] VectorBasicTest.Creation (0 ms)
[ RUN      ] VectorBasicTest.PushBack
[       OK ] VectorBasicTest.PushBack (0 ms)
[ RUN      ] VectorBasicTest.Insert
[       OK ] VectorBasicTest.Insert (0 ms)
[ RUN      ] VectorBasicTest.Erase
[       OK ] VectorBasicTest.Erase (0 ms)
[----------] 4 tests from VectorBasicTest (0 ms total)

[----------] 2 tests from VectorAccessTest
[ RUN      ] VectorAccessTest.OperatorBracket
[       OK ] VectorAccessTest.OperatorBracket (0 ms)
[ RUN      ] VectorAccessTest.ConstOperatorBracket
[       OK ] VectorAccessTest.ConstOperatorBracket (0 ms)
[----------] 2 tests from VectorAccessTest (0 ms total)

[----------] 2 tests from VectorCopyTest
[ RUN      ] VectorCopyTest.CopyConstructor
[       OK ] VectorCopyTest.CopyConstructor (0 ms)
[ RUN      ] VectorCopyTest.CopyAssignment
[       OK ] VectorCopyTest.CopyAssignment (0 ms)
[----------] 2 tests from VectorCopyTest (0 ms total)

[----------] 2 tests from VectorMoveTest
[ RUN      ] VectorMoveTest.MoveConstructor
[       OK ] VectorMoveTest.MoveConstructor (0 ms)
[ RUN      ] VectorMoveTest.MoveAssignment
[       OK ] VectorMoveTest.MoveAssignment (0 ms)
[----------] 2 tests from VectorMoveTest (0 ms total)

[----------] 4 tests from VectorIteratorTest
[ RUN      ] VectorIteratorTest.BasicIteration
[       OK ] VectorIteratorTest.BasicIteration (0 ms)
[ RUN      ] VectorIteratorTest.ConstIteration
[       OK ] VectorIteratorTest.ConstIteration (0 ms)
[ RUN      ] VectorIteratorTest.IteratorInsert
[       OK ] VectorIteratorTest.IteratorInsert (0 ms)
[ RUN      ] VectorIteratorTest.IteratorErase
[       OK ] VectorIteratorTest.IteratorErase (0 ms)
[----------] 4 tests from VectorIteratorTest (0 ms total)

[----------] 3 tests from VectorCapacityTest
[ RUN      ] VectorCapacityTest.SizeAndCapacity
[       OK ] VectorCapacityTest.SizeAndCapacity (0 ms)
[ RUN      ] VectorCapacityTest.Reserve
[       OK ] VectorCapacityTest.Reserve (0 ms)
[ RUN      ] VectorCapacityTest.Clear
[       OK ] VectorCapacityTest.Clear (0 ms)
[----------] 3 tests from VectorCapacityTest (0 ms total)

[----------] Global test environment tear-down
[==========] 34 tests from 11 test suites ran. (0 ms total)
[  PASSED  ] 34 tests.

```
Example launch the single test of move semantics (including move ctor) for linked list container only:
```bash
./release/container_test --gtest_filter=LinkedListMoveTest.MoveConstructor
Note: Google Test filter = LinkedListMoveTest.MoveConstructor
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from LinkedListMoveTest
[ RUN      ] LinkedListMoveTest.MoveConstructor
[       OK ] LinkedListMoveTest.MoveConstructor (0 ms)
[----------] 1 test from LinkedListMoveTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```
Example launch basic tests group for linked list container only with the stated repeats:
```bash
./release/container_test --gtest_filter=LinkedListBasicTest.*
Note: Google Test filter = LinkedListBasicTest.*
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from LinkedListBasicTest
[ RUN      ] LinkedListBasicTest.Creation
[       OK ] LinkedListBasicTest.Creation (0 ms)
[ RUN      ] LinkedListBasicTest.PushBack
[       OK ] LinkedListBasicTest.PushBack (0 ms)
[ RUN      ] LinkedListBasicTest.Insert
[       OK ] LinkedListBasicTest.Insert (0 ms)
[ RUN      ] LinkedListBasicTest.Erase
[       OK ] LinkedListBasicTest.Erase (0 ms)
[ RUN      ] LinkedListBasicTest.Clear
[       OK ] LinkedListBasicTest.Clear (0 ms)
[----------] 5 tests from LinkedListBasicTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```
