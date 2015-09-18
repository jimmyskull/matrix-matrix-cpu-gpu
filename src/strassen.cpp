#include "strassen.hpp"

namespace {

// function to sum two matrices
static void sum(float *a, float *b, float *result, int tam) {
  int i, j;
  for (i = 0; i < tam; i++) {
    for (j = 0; j < tam; j++) {
      result[i * tam + j] = a[i * tam + j] + b[i * tam + j];
    }
  }
}

// function to subtract two matrices
static void subtract(float *a, float *b, float *result, int tam) {
  int i, j;
  for (i = 0; i < tam; i++) {
    for (j = 0; j < tam; j++) {
      result[i * tam + j] = a[i * tam + j] - b[i * tam + j];
    }
  }
}

// naive method
void naive(float *A, float *B, float *C, int tam) {
  for (int i = 0; i < tam; i++)
    for (int j = 0; j < tam; j++)
      for (int k = 0; k < tam; k++)
        C[i * tam + j] += A[i * tam + k] * B[k * tam + j];
}

// http://www.bo-yang.net/2013/03/20/implementation-of-strassens-algorithm-for-matrix-multiplication/
// Strassen's method
static void strassen(float *a, float *b, float *c, int tam) {
  // Key observation: call naive method for matrices small
  if (tam <= 4) {
    naive(a, b, c, tam);
    return;
  }
  // other cases are treated here:
  int newTam = tam / 2;
  float *a11, *a12, *a21, *a22;
  float *b11, *b12, *b21, *b22;
  float *c11, *c12, *c21, *c22;
  float *p1, *p2, *p3, *p4, *p5, *p6, *p7;
  // memory allocation:
  a11 = new float[newTam * newTam];
  a12 = new float[newTam * newTam];
  a21 = new float[newTam * newTam];
  a22 = new float[newTam * newTam];
  b11 = new float[newTam * newTam];
  b12 = new float[newTam * newTam];
  b21 = new float[newTam * newTam];
  b22 = new float[newTam * newTam];
  c11 = new float[newTam * newTam];
  c12 = new float[newTam * newTam];
  c21 = new float[newTam * newTam];
  c22 = new float[newTam * newTam];
  p1 = new float[newTam * newTam];
  p2 = new float[newTam * newTam];
  p3 = new float[newTam * newTam];
  p4 = new float[newTam * newTam];
  p5 = new float[newTam * newTam];
  p6 = new float[newTam * newTam];
  p7 = new float[newTam * newTam];
  float *aResult = new float[newTam * newTam];
  float *bResult = new float[newTam * newTam];
  // dividing the matrices in 4 sub-matrices:
  for (int i = 0; i < newTam; i++) {
    for (int j = 0; j < newTam; j++) {
      a11[i * newTam + j] = a[i * newTam + j];
      a12[i * newTam + j] = a[i * newTam + j + newTam];
      a21[i * newTam + j] = a[(i + newTam) * newTam + j];
      a22[i * newTam + j] = a[(i + newTam) * newTam + j + newTam];
      b11[i * newTam + j] = b[i * newTam + j];
      b12[i * newTam + j] = b[i * newTam + j + newTam];
      b21[i * newTam + j] = b[(i + newTam) * newTam + j];
      b22[i * newTam + j] = b[(i + newTam) * newTam + j + newTam];
    }
  }
  // Calculating p1 to p7:
  sum(a11, a22, aResult, newTam);         // a11 + a22
  sum(b11, b22, bResult, newTam);         // b11 + b22
  strassen(aResult, bResult, p1, newTam); // p1 = (a11+a22) * (b11+b22)
  sum(a21, a22, aResult, newTam);         // a21 + a22
  strassen(aResult, b11, p2, newTam);     // p2 = (a21+a22) * (b11)
  subtract(b12, b22, bResult, newTam);    // b12 - b22
  strassen(a11, bResult, p3, newTam);     // p3 = (a11) * (b12 - b22)
  subtract(b21, b11, bResult, newTam);    // b21 - b11
  strassen(a22, bResult, p4, newTam);     // p4 = (a22) * (b21 - b11)
  sum(a11, a12, aResult, newTam);         // a11 + a12
  strassen(aResult, b22, p5, newTam);     // p5 = (a11+a12) * (b22)
  subtract(a21, a11, aResult, newTam);    // a21 - a11
  sum(b11, b12, bResult, newTam);         // b11 + b12
  strassen(aResult, bResult, p6, newTam); // p6 = (a21-a11) * (b11+b12)
  subtract(a12, a22, aResult, newTam);    // a12 - a22
  sum(b21, b22, bResult, newTam);         // b21 + b22
  strassen(aResult, bResult, p7, newTam); // p7 = (a12-a22) * (b21+b22)
  // calculating c21, c21, c11 e c22:
  sum(p3, p5, c12, newTam);           // c12 = p3 + p5
  sum(p2, p4, c21, newTam);           // c21 = p2 + p4
  sum(p1, p4, aResult, newTam);       // p1 + p4
  sum(aResult, p7, bResult, newTam);  // p1 + p4 + p7
  subtract(bResult, p5, c11, newTam); // c11 = p1 + p4 - p5 + p7
  sum(p1, p3, aResult, newTam);       // p1 + p3
  sum(aResult, p6, bResult, newTam);  // p1 + p3 + p6
  subtract(bResult, p2, c22, newTam); // c22 = p1 + p3 - p2 + p6
  // Grouping the results obtained in a single matrix:
  for (int i = 0; i < newTam; i++) {
    for (int j = 0; j < newTam; j++) {
      c[i * newTam + j] = c11[i * newTam + j];
      c[i * newTam + j + newTam] = c12[i * newTam + j];
      c[(i + newTam) * newTam + j] = c21[i * newTam + j];
      c[(i + newTam) * newTam + j + newTam] = c22[i * newTam + j];
    }
  }
  delete[] a11;
  delete[] a12;
  delete[] a21;
  delete[] a22;
  delete[] b11;
  delete[] b12;
  delete[] b21;
  delete[] b22;
  delete[] c11;
  delete[] c12;
  delete[] c21;
  delete[] c22;
  delete[] p1;
  delete[] p2;
  delete[] p3;
  delete[] p4;
  delete[] p5;
  delete[] p6;
  delete[] p7;
  delete[] aResult;
  delete[] bResult;
}

} // namespace

namespace core {

void Strassen::Compute() {
  strassen(A, B, C, entry.vertices);
}

} // namespace core
