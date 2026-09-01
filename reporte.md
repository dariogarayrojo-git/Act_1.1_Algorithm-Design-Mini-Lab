# Reporte — Mini-Lab de Diseño de Algoritmos

---

## Problema A — Inversion Counter for Quality Control

### 1. Resumen del problema

Dado un arreglo `A` de `n` enteros, una **inversión** es un par de índices
`(i, j)` con `i < j` y `A[i] > A[j]`. Se pide contar el número total de
inversiones. Un enfoque de fuerza bruta revisa todos los pares en `O(n²)`,
lo cual es demasiado lento para `n` hasta `2·10^5`. Se necesita un enfoque
que aproveche una estructura recursiva del problema para bajar la
complejidad a `O(n log n)`.

### 2. Idea del algoritmo

Las inversiones se pueden contar con una versión modificada de **Merge
Sort** (Divide & Conquer):

- Se divide el arreglo por la mitad recursivamente.
- Cada mitad se ordena y se cuenta el número de inversiones **dentro** de
  cada mitad (recursión).
- Al **mezclar** (merge) las dos mitades ya ordenadas, se cuentan las
  inversiones **cruzadas** (una entre la mitad izquierda y la derecha): si
  durante la mezcla se toma un elemento de la derecha antes de agotar la
  izquierda, todos los elementos restantes de la izquierda forman una
  inversión con ese elemento (porque la izquierda está ordenada
  ascendentemente, así que si `A[i] > A[j]`, también `A[i+1..mid] > A[j]`).

El total de inversiones = inversiones en la mitad izquierda + inversiones en
la mitad derecha + inversiones cruzadas detectadas durante el merge.

**Justificación de correctitud (invariante):** en cada llamada recursiva
sobre el subarreglo `[l, r]`, al terminar, el subarreglo queda ordenado y el
valor retornado es exactamente el número de inversiones originales dentro
de `[l, r]`. Esto se cumple por inducción sobre el tamaño del subarreglo:
caso base (`l >= r`) tiene 0 inversiones; el paso inductivo asume que las
llamadas sobre las dos mitades cuentan correctamente sus inversiones
internas, y el merge cuenta exactamente las cruzadas porque ambas mitades
ya están ordenadas al momento de mezclarlas.

### 3. Pseudocódigo

```
function sortCount(A, l, r):
    if l >= r: return 0
    mid = (l + r) / 2
    inv = 0
    inv += sortCount(A, l, mid)
    inv += sortCount(A, mid+1, r)
    inv += mergeCount(A, l, mid, r)
    return inv

function mergeCount(A, l, mid, r):
    i = l, j = mid+1, k = l
    inv = 0
    tmp = new array of size r-l+1
    while i <= mid and j <= r:
        if A[i] <= A[j]:
            tmp[k++] = A[i++]
        else:
            inv += (mid - i + 1)   // A[i..mid] todos forman inversión con A[j]
            tmp[k++] = A[j++]
    copiar el resto de A[i..mid] y A[j..r] a tmp
    copiar tmp de vuelta a A[l..r]
    return inv
```

### 4. Ejemplo de ejecución

Entrada: `A = [2, 4, 1, 3, 5]`

- Se divide en `[2, 4]` y `[1, 3, 5]`.
- `[2, 4]`: ya está ordenado, 0 inversiones internas.
- `[1, 3, 5]`: ya está ordenado, 0 inversiones internas.
- Merge de `[2, 4]` con `[1, 3, 5]`:
  - Comparar 2 vs 1 → 1 < 2, se toma 1 (de la derecha) antes que 2 y 4 →
    suma 2 inversiones ((2,1) y (4,1)).
  - Comparar 2 vs 3 → se toma 2.
  - Comparar 4 vs 3 → 3 < 4, se toma 3 antes que 4 → suma 1 inversión
    ((4,3)).
  - Se toma 4, luego 5.
- Total: 2 + 1 = **3 inversiones**, que coincide con el resultado esperado
  (`(2,1)`, `(4,1)`, `(4,3)`).

Salida: `3` ✔

### 5. Análisis de complejidad

**Tiempo:** el algoritmo sigue la recurrencia de Merge Sort:

```
T(n) = 2·T(n/2) + O(n)
```

Por el Teorema Maestro (caso 2, ya que `a=2, b=2, f(n)=Θ(n)= Θ(n^(log_2 2))`):

```
T(n) = O(n log n)
```

Esto se cumple tanto en el peor caso (arreglo en orden inverso, `n(n-1)/2`
inversiones) como en el mejor caso (arreglo ya ordenado, 0 inversiones):
el trabajo de dividir y mezclar es siempre `O(n log n)` independientemente
de los valores.

**Espacio:** se usa un arreglo auxiliar `tmp` de tamaño `n` para la mezcla
(`O(n)`), más la pila de recursión de profundidad `O(log n)`. Espacio
auxiliar total: `O(n)`.

---

## Problema B — Minimum Meeting Rooms (Scheduling)

### 1. Resumen del problema

Dadas `m` reuniones, cada una con hora de inicio `s_i` y fin `e_i`, se pide
el número mínimo de salas necesarias para que todas las reuniones puedan
llevarse a cabo, donde una sala solo puede alojar una reunión a la vez. Si
una reunión termina justo cuando otra empieza, se considera que **no** hay
traslape (pueden compartir sala).

### 2. Idea del algoritmo

El número mínimo de salas necesarias en cualquier instante es igual al
**máximo número de reuniones simultáneamente activas** en cualquier punto
del tiempo. Esto se calcula con un enfoque **greedy** de barrido de
eventos:

- Se ordenan por separado los tiempos de inicio y los tiempos de fin.
- Se recorren las reuniones en orden de inicio. Se mantiene un puntero al
  fin más próximo que aún no ha "liberado" su sala.
- Si la siguiente reunión empieza **antes** de que termine la reunión con
  el fin más próximo (`starts[i] < ends[j]`), se necesita una sala nueva.
- Si empieza en el mismo instante o después (`starts[i] >= ends[j]`), se
  reutiliza una sala que ya se liberó.
- Se lleva el máximo de salas usadas simultáneamente durante todo el
  barrido; ese máximo es la respuesta.

**Propiedad de elección greedy:** siempre es óptimo reutilizar una sala tan
pronto como se libera (en vez de "reservarla" para otra reunión futura),
porque cualquier reunión que empiece después puede usar esa sala
igualmente bien; posponer su reutilización nunca reduce el número total de
salas necesarias y sí podría forzar a abrir una sala nueva innecesaria.
Además, el máximo de salas simultáneas es una cota inferior inevitable
(en ese instante, cada una de esas reuniones *necesita* una sala distinta),
así que el algoritmo alcanza exactamente esa cota, siendo por lo tanto
óptimo.

### 3. Pseudocódigo

```
function minRooms(meetings[1..m]):
    starts = sort([s_i for each meeting])
    ends   = sort([e_i for each meeting])
    i = 0, j = 0
    rooms = 0, maxRooms = 0
    while i < m:
        if starts[i] < ends[j]:
            rooms += 1
            i += 1
            maxRooms = max(maxRooms, rooms)
        else:
            rooms -= 1
            j += 1
    return maxRooms
```

### 4. Ejemplo de ejecución

Entrada: reuniones `(0,30), (5,10), (15,20)`

- `starts = [0, 5, 15]`, `ends = [10, 20, 30]`
- `i=0`: `starts[0]=0 < ends[0]=10` → nueva sala. `rooms=1`, `maxRooms=1`
- `i=1`: `starts[1]=5 < ends[0]=10` → nueva sala. `rooms=2`, `maxRooms=2`
- `i=2`: `starts[2]=15 >= ends[0]=10` → se libera una sala. `rooms=1`,
  `j=1`
- Ahora `starts[2]=15 < ends[1]=20` → nueva sala. `rooms=2`, `maxRooms=2`

Salida: `2` ✔ (coincide: la reunión `(0,30)` se traslapa con `(5,10)` y
luego con `(15,20)`, pero `(5,10)` y `(15,20)` nunca coinciden, así que
basta con 2 salas).

### 5. Análisis de complejidad

**Tiempo:** ordenar `starts` y `ends` toma `O(m log m)` cada uno. El
barrido posterior recorre cada arreglo una sola vez (`i` y `j` solo
avanzan, nunca retroceden), por lo que es `O(m)`. Total: `O(m log m)`.

**Espacio:** se usan dos arreglos auxiliares de tamaño `m` (`starts`,
`ends`), por lo que el espacio auxiliar es `O(m)`.

---

## Problema C — Budgeted Study Plan (0/1 Knapsack Variant)

### 1. Resumen del problema

Se tienen `n` módulos de estudio, cada uno con un costo en horas `time[i]`
y un beneficio `value[i]`. Con un presupuesto total de `T` horas, y
pudiendo tomar cada módulo **a lo más una vez**, se busca maximizar el
valor total sin exceder `T`. Es la variante clásica de la **mochila 0/1**.
Una búsqueda exhaustiva de subconjuntos es `O(2^n)`, inviable para
`n` hasta 2000.

### 2. Idea del algoritmo

Se usa **programación dinámica**. Se define:

```
dp[j] = máximo valor alcanzable con un presupuesto de tiempo j,
        usando los módulos considerados hasta el momento
```

**Subestructura óptima:** la solución óptima para un presupuesto `j`
considerando los primeros `i` módulos, o bien no incluye el módulo `i`
(en cuyo caso el valor óptimo es el mismo que con `i-1` módulos y
presupuesto `j`), o bien lo incluye (en cuyo caso el valor óptimo es
`value[i]` más el óptimo con `i-1` módulos y presupuesto `j - time[i]`).
Esto da la recurrencia:

```
dp[i][j] = max( dp[i-1][j],  dp[i-1][j - time[i]] + value[i] )   si time[i] <= j
dp[i][j] = dp[i-1][j]                                             si time[i] > j
```

Como cada fila `i` solo depende de la fila `i-1`, se puede **comprimir la
tabla a un arreglo 1D**, siempre que se actualice `j` en **orden
decreciente** (de `T` hacia `time[i]`). Esto evita que un módulo se use más
de una vez en la misma iteración `i` (lo que ocurriría si se actualizara en
orden creciente, degenerando en mochila con repetición).

### 3. Pseudocódigo

```
function knapsack(n, T, time[1..n], value[1..n]):
    dp = array of size T+1, initialized to 0
    for i = 1 to n:
        if time[i] > T: continue
        for j = T down to time[i]:
            dp[j] = max(dp[j], dp[j - time[i]] + value[i])
    return dp[T]
```

### 4. Ejemplo de ejecución

Entrada: `T=10`, módulos `(3,4), (4,5), (7,10)`

- Tras procesar módulo 1 `(t=3, v=4)`: `dp[3..10] = 4` (se puede tomar
  este módulo en cualquier presupuesto ≥ 3).
- Tras procesar módulo 2 `(t=4, v=5)`: para `j=7`, `dp[7] = max(4,
  dp[3]+5) = max(4, 9) = 9`; para `j=10`, similar, `dp[10]` sube a 9.
- Tras procesar módulo 3 `(t=7, v=10)`: para `j=10`, `dp[10] = max(9,
  dp[3] + 10) = max(9, 4+10) = 14`.

Salida: `14` ✔ (se toman los módulos 1 y 3: tiempo `3+7=10`, valor
`4+10=14`).

### 5. Análisis de complejidad

**Tiempo:** dos ciclos anidados, el externo recorre los `n` módulos y el
interno recorre hasta `T` valores de presupuesto. Cada actualización de
`dp[j]` es `O(1)`. Total: `O(n·T)`. Con las cotas dadas (`n ≤ 2000`,
`T ≤ 5000`), esto son a lo más `10^7` operaciones, perfectamente factible.

**Espacio:** gracias a la compresión a 1D, solo se guarda un arreglo
`dp[0..T]`, es decir `O(T)` (en vez de `O(n·T)` que requeriría una tabla
2D completa).

---

## Resumen de complejidades

| Problema | Técnica | Tiempo | Espacio |
|----------|---------|--------|---------|
| A — Inversion Counter | Divide & Conquer | O(n log n) | O(n) |
| B — Minimum Meeting Rooms | Greedy | O(m log m) | O(m) |
| C — Budgeted Study Plan | Programación Dinámica | O(n·T) | O(T) |
