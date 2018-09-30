// Copyright 2018 Teodor Apostol

#include <iostream>
#include <fstream>

using namespace std;

void bktr(int *sum, int suma_curenta,
	int suma, int &isuma, int cautat, int termen, int n) {
  // Caz de baza:
  if (termen == n - 1) {
  	// Ultimul element
    if (suma - suma_curenta <= sum[termen - 1]) {
      // Se pastreaza ordinea descrescatoare
	  sum[termen] = suma - suma_curenta;
	  ++isuma;
      if (isuma == cautat) {
		return;
	  }
	}
	return;
  }

  // Daca recursiv nu putem forma suma in continuare, ne intoarcem
  if (suma - suma_curenta < n - termen - 1) {
    return;
  }

  // Iau toate posibilitatile mai mici sau egale cu termenul precedent
  for (int i = sum[termen - 1]; i > 0; --i) {
    sum[termen] = i;
	suma_curenta += i;
	if (suma_curenta < suma) {
	  // Daca am depasit suma, nu mai are sens sa continuam
	  bktr(sum, suma_curenta, suma, isuma, cautat, termen + 1, n);
	}

	if (isuma == cautat) {
	  // Daca s-a gasit mai adanc in parcurgere solutia, iesim
	  return;
	}
	suma_curenta -= i;
  }
}

int main(void) {
  int s, n, i;

  // Citirea:
  FILE *fin = fopen("numaratoare.in", "r");
  fscanf(fin, "%d%d%d", &s, &n, &i);
  fclose(fin);

  int *sum = new int[n];
  int isuma = -1;

  // Pornesc de la cazul: sum = numar_max + 1 + 1 + ...
  // apoi scad numarul de pe prima pozitie si le ajustez pe celelalte
  for (int j = s - n + 1; j > 0; --j) {
  	// Ajustez primul lelement
    sum[0] = j;
	bktr(sum, j, s, isuma, i, 1, n);
	// Daca s-a gasit suma cu indexul cautat iesim
	if (isuma == i) {
	  break;
	}
  }

  // Afisarea:
  FILE *fout = fopen("numaratoare.out", "w");
  if (isuma < i) {
    fprintf(fout, "-");
  } else {
    fprintf(fout, "%d=%d", s, sum[0]);
	for (int j = 1; j < n; ++j) {
	  fprintf(fout, "+%d", sum[j]);
	}
  }
  fclose(fout);
  return 0;
}
