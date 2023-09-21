setwd("C:/Users/Anderson/Desktop/Paralela/Taller 2")

# Leer las tres matrices desde los archivos CSV
matrixA <- as.matrix(read.csv("matrixA.csv", header = FALSE))
matrixB <- as.matrix(read.csv("matrixB.csv", header = FALSE))
matrixResult <- as.matrix(read.csv("matrixResult.csv", header = FALSE))

# Realizar la multiplicación de matrices
resultado <- matrixA %*% matrixB

# Imprimir el resultado
print(resultado)

# Verificar si las matrices son iguales
# Comprobar si todas las entradas son TRUE (iguales)
iguales <- all.equal(matrixResult, resultado, tolerance = 1e-6)

if (iguales) {
  cat("Los resultados son iguales.\n")
} else {
  cat("Los resultados son diferentes.\n")
}
