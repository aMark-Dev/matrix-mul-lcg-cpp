# Matrix Multiplication with LCG in C++

This is a simple educational C++ project that implements random matrix generation and naive matrix multiplication from scratch.

The goal of this project is to understand the connection between linear algebra, memory layout, indexing, and low-level C++ implementation.

The whole implementation is kept in `main.cpp` for simplicity.

## What this project does

This program generates two random matrices:

$A \in R^{m \times n}$

$W \in R^{n \times p}$

Then it computes:

$C = A \times W$

where:

$C \in R^{m \times p}$

The matrix multiplication follows the standard definition:

$C(i, k) =$ sum of $A(i, j) \times W(j, k)$

## Random number generation

The project uses a deterministic Linear Congruential Generator, LCG.

The generator is based on a fixed seed, so the generated matrices are reproducible. This is useful for testing and debugging.

The generated values are mapped to an interval chosen by the user:

$[v_{min}, v_{max}] $

## Memory layout

Matrices are stored as one-dimensional vectors using row-major layout.

For a matrix M with `cols` columns:

$M(i, j)$ is stored at:

$M[i \times cols + j]$

This is useful for understanding how matrices and tensors are represented in memory.

## How to build

Using g++:

```bash
g++ -std=c++20 -O2 src/main.cpp -o matrix_mul
```
How to run
```
./matrix_mul
```

The program expects the input in this order:

$m, n, p, v_{min}, v_{max}$

Example:

$m = 2, n = 3, p = 4, v_{min} = -1, v_{max} = 1$

This means:

- A has shape $2 \times 3$
- W has shape $3 \times 4$
- C will have shape $2 \times 4$
- random values will be generated between -1 and 1
Current version

---

This is version 0.1.

It is a simple learning project, not an optimized HPC library.

Future improvements
Add unit tests
Add benchmarks
Compare with optimized libraries
Study cache blocking
Study SIMD
Study OpenMP parallelization
Purpose

This project is part of my learning path in Machine Learning Systems.

The main idea is to build strong fundamentals before moving to optimized libraries, CUDA, BLAS, and deep learning frameworks.
