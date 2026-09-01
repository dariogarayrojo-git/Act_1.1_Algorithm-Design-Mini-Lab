# Mini-Lab: Divide & Conquer, Greedy, Dynamic Programming

Este repositorio contiene la solución a los tres problemas del mini-lab.
Cada problema usa una técnica de diseño de algoritmos distinta, elegida
según la estructura de cada problema (no fue indicada por el enunciado):

| Problema | Nombre                          | Técnica usada          | Complejidad tiempo |
|----------|----------------------------------|-------------------------|---------------------|
| A        | Inversion Counter                | Divide & Conquer (merge sort modificado) | O(n log n) |
| B        | Minimum Meeting Rooms            | Greedy (barrido de eventos)              | O(m log m) |
| C        | Budgeted Study Plan (0/1 Knapsack) | Programación Dinámica                  | O(n·T)     |

## Estructura del repo

```
problemA_inversions/
    main.cpp
    README.md
    tests/
problemB_rooms/
    main.cpp
    README.md
    tests/
problemC_knapsack/
    main.cpp
    README.md
    tests/
report.md
README.md
```

## Cómo compilar y correr cada problema

Todos usan C++17, entrada por `stdin` y salida por `stdout`.

```bash
# Problema A
cd problemA_inversions
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/t1.in

# Problema B
cd ../problemB_rooms
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/t1.in

# Problema C
cd ../problemC_knapsack
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/t1.in
```

Cada carpeta incluye un script `tests/run_tests.sh` que compila y corre
automáticamente los 3 casos de prueba de ese problema:

```bash
bash problemA_inversions/tests/run_tests.sh
bash problemB_rooms/tests/run_tests.sh
bash problemC_knapsack/tests/run_tests.sh
```

## Supuestos

- Se usa `long long` (64 bits) para cualquier valor que pueda exceder el
  rango de un entero de 32 bits (conteo de inversiones, valores del
  knapsack).
- En el Problema B se asume que si una reunión termina exactamente cuando
  otra empieza, ambas pueden compartir la misma sala (no se consideran
  traslapadas), tal como indica el enunciado.
- En el Problema C se asume que ningún módulo puede tomarse más de una vez
  (0/1 knapsack, no fraccional ni repetible).

Ver `report.md` para la explicación detallada, pseudocódigo y análisis de
complejidad de cada problema.
