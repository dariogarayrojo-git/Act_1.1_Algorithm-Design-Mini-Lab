# Problem B — Minimum Meeting Rooms

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
m
s1 e1
s2 e2
...
sm em
```

## Formato de salida
```
rooms
```

## Ejemplo
```
$ echo "3
0 30
5 10
15 20" | ./main
2
```

## Pruebas
Ver carpeta `tests/`. Ejecutar `bash tests/run_tests.sh`.
