---

# Cálculo de Pi usando OpenMP en C

Este repositorio contiene dos programas en C para calcular el valor de Pi usando la Fórmula de Leibniz. Ambos programas utilizan OpenMP para la paralelización. Uno de los programas trata de mitigar el problema del "false sharing" usando "padding".

## Archivos en el Repositorio

- `pi_calculator.c`: Este programa calcula Pi usando OpenMP de la forma más sencilla.
- `pi_calculator_no_false_sharing.c`: Este programa también calcula Pi pero trata de evitar el problema del "false sharing" usando "padding".

## Cómo compilar y ejecutar los programas

1. Asegúrate de tener GCC instalado en tu sistema, así como soporte para OpenMP.
2. Abre una terminal y navega hasta el directorio donde se encuentran los archivos `.c`.

Para compilar `pi_calculator.c`, ejecuta:

```bash
gcc -o pi_calculator -fopenmp pi_calculator.c
```

Para compilar `pi_calculator_no_false_sharing.c`, ejecuta:

```bash
gcc -o pi_calculator_no_false_sharing -fopenmp pi_calculator_no_false_sharing.c
```

3. Una vez compilados, puedes ejecutar cada programa con el comando correspondiente:

```bash
./pi_calculator
```

o

```bash
./pi_calculator_no_false_sharing
```

## Cambio del número de hilos

Es importante notar que el número de hilos está configurado manualmente en cada archivo de programa. Busca la línea que dice:

```c
#define NUM_THREADS 2
```

Puedes cambiar el número `2` por el número de hilos que desees utilizar (1, 2, 4, 8, 16, etc.) y luego recompilar el programa para ver los efectos.

---

