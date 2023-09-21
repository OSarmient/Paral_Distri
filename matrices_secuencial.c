#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Función para generar una matriz aleatoria de nxn con valores decimales redondeados a un decimal
double *generateMatrix(int n)
{
    int size = n * n * sizeof(double);

    double *matrix = (double *)malloc(size);

    // Generar números aleatorios
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int rowStart = n * i;
            double randomValue = ((double)rand() / RAND_MAX) * 9.9;
            *(matrix + j + rowStart) = round(randomValue * 10) / 10.0; // Redondear a un decimal
        }
    }

    return matrix;
}

// Función para imprimir una matriz de nxn
void printMatrix(double *matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int rowStart = n * i;
            printf("%.2lf  ", *(matrix + j + rowStart));
        }
        printf("\n\n");
    }
}

// Función para multiplicar matrices
double *matrixMul(double *matrixA, double *matrixB, int n)
{
    int size = n * n * sizeof(double);

    double *result = (double *)malloc(size);

    if (result == NULL)
    {
        perror("Error al asignar memoria. \n");
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int rowStart = n * i;
            *(result + j + rowStart) = 0.0;
            for (int k = 0; k < n; k++)
            {
                *(result + j + rowStart) = *(result + j + rowStart) + *(matrixA + k + rowStart) * *(matrixB + j + (k * n));
            }
        }
    }

    return result;
}

// Funcion para guardar matrices como csv
void saveMatrixToCSV(double *matrix, int n, const char *filename)
{
    FILE *csvFile = fopen(filename, "w");
    if (csvFile == NULL)
    {
        perror("Error al abrir el archivo CSV");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(csvFile, "%.2lf", matrix[i * n + j]); // Escribe un valor
            if (j < n - 1)
            {
                fprintf(csvFile, ","); // Separador de columnas
            }
        }
        fprintf(csvFile, "\n"); // Nueva línea para cada fila
    }

    fclose(csvFile);
}

int main()
{
    int n;
    while (1)
    {
        printf("Opciones de tamanio de matriz:\n");
        printf("1. 2x2\n");
        printf("2. 5x5\n");
        printf("3. 10x10\n");
        printf("4. 128x128\n");
        printf("5. 256x256\n");
        printf("6. 512x512\n");
        printf("7. 1024x1024\n");
        printf("8. Salir\n");
        printf("Selecciona una opcion: ");

        int opcion;
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            n = 2;
            break;
        case 2:
            n = 5;
            break;
        case 3:
            n = 10;
            break;
        case 4:
            n = 128;
            break;
        case 5:
            n = 256;
            break;
        case 6:
            n = 512;
            break;
        case 7:
            n = 1024;
            break;
        case 8:
            exit(0); // Salir del programa
        default:
            printf("\nOpcion no valida. Introduce un numero del 1 al 8.\n\n");
            continue; // Vuelve al inicio del bucle
        }

        // Inicializar el generador de números aleatorios con una semilla
        srand(time(NULL));

        printf("\n--------------------------------------------------------------------------------\n");
        printf("\nGenerando matrices (%dx%d)...\n", n, n);

        double *matrixA = generateMatrix(n);
        double *matrixB = generateMatrix(n);

        if (matrixA == NULL || matrixB == NULL)
        {
            perror("Error al asignar memoria. \n");
            return 1;
        }

        printf("Multiplicando matrices...\n");

        clock_t start_time = clock(); // Registra el tiempo de inicio

        double *result = matrixMul(matrixA, matrixB, n);

        clock_t end_time = clock(); // Registra el tiempo de finalización

        if (result == NULL)
        {
            return 0;
        }

        double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula el tiempo transcurrido en segundos

        if (n <= 5)
        {
            printf("MATRIZ A: \n");
            printMatrix(matrixA, n);
            printf("\nMATRIZ B: \n");
            printMatrix(matrixB, n);
            printf("\nRESULTADO: \n");
            printMatrix(result, n);
        }

        printf("Tiempo de ejecucion de la multiplicacion de matrices: %.6f segundos\n\n", total_time);
        printf("\nGuardando matrices como csv...\n");

        // Especifica los nombres de archivo
        const char *filename1 = "matrixA.csv";
        const char *filename2 = "matrixB.csv";
        const char *filename3 = "matrixResult.csv";

        saveMatrixToCSV(matrixA, n, filename1);
        saveMatrixToCSV(matrixB, n, filename2);
        saveMatrixToCSV(result, n, filename3);

        printf("Matrices guardadas con exito!!!\n");
        printf("\n--------------------------------------------------------------------------------\n");
        // Liberar la memoria asignada
        free(matrixA);
        free(matrixB);
        free(result);
    }

    return 0;
}