# Problem C — Budgeted Study Plan (0/1 Knapsack)

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
n T
t1 v1
t2 v2
...
tn vn
```

## Formato de salida
```
best
```

## Ejemplo
```
$ echo "3 10
3 4
4 5
7 10" | ./main
14
```

## Pruebas
Ver carpeta `tests/`. Ejecutar `bash tests/run_tests.sh`.
