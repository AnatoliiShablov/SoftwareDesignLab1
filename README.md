# SoftwareDesignLab1
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
cmake -S. -Bbuild
cmake --build build
```

#### Тесты

```
ctest --test-dir build 
```

