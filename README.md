# SoftwareDesignLab1

Необходимо реализовать структуры данных LRUCache на хешмапе и двусвязном списке. При
реализации необходимо самостоятельно продумать возможные проверки pre/post-условий и
инвариантов класса. Придуманные проверки необходимо добавить в код реализации в виде
assertions. Класс необходимо покрыть тестами.

## Сборка
### Менеджер пакетов Conan
#### При наличии python
```
pip install conan
```
#### Установка с сайта:


[conan](https://conan.io/downloads.html)

### Linux CLI

```
cmake -DCMAKE_BUILD_TYPE=Release -S. -Bbuild
cmake --build build
```

#### Тесты

```
ctest --test-dir build 
```

