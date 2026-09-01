# Problem A — Inversion Counter

## Compilar
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Ejecutar
```bash
./main < input.txt
```

## Formato de entrada
```
n
a1 a2 ... an
```

## Formato de salida
```
inv
```

## Ejemplo
```
$ echo "5
2 4 1 3 5" | ./main
3
```

## Pruebas
Ver carpeta `tests/` (3 casos: ejemplo del enunciado, arreglo ordenado, arreglo
en orden inverso). Ejecutar `bash tests/run_tests.sh`.
