// Copyright 2018 Teodor Apostol

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

long long pow3(long long x) {
  return x * x * x;
}

struct optim {
  long long minim;
  int concursuri;
};

int main(void) {
  int numarProbe;
  int durataConcurs;
  int pauza;

  // Citirea:
  FILE *in = fopen("planificare.in", "r");
  fscanf(in, "%d %d %d", &numarProbe, &durataConcurs, &pauza);
  int *probe = new int[numarProbe + 1];

  // Citesc vectorul de probe:
  for (int i = 1; i <= numarProbe; ++i) {
	fscanf(in, "%d", &probe[i]);
  }
  fclose(in);

  // Construiesc matricea de solutii optime:
  optim **dp = new optim*[numarProbe + 1];
  for (int i = 1; i <= numarProbe; ++i) {
	dp[i] = new optim[numarProbe + 1];
  }

  int i, j, k;

  // Cazul de baza:

  // 1. Initializez tot cu "infinit"
  for (i = 1; i <= numarProbe; ++i) {
	for (j = i; j <= numarProbe; ++j) {
	  dp[i][j].minim = LLONG_MAX;
	}
  }

  // d[i][j] -> modul optim de a gestiona proba i, i + 1, ... j
  for (i = 1; i <= numarProbe; ++i) {
  	// Pe cazul e baza am cate un concurs separat pentru fiecare proba
	dp[i][i].minim = durataConcurs - probe[i];
	dp[i][i].concursuri = 1;
  }

  // Apoi incerc sa introduc cat mai multe probe intr-un singur concurs
  for (i = 1; i <= numarProbe; ++i) {
	for (j = i + 1; j <= numarProbe; ++j) {
	  if (dp[i][j-1].minim - pauza - probe[j] >= 0) {
		if (j == numarProbe) {
		  // Ultima proba va fi in ultimul concurs => pierdere nula
		  dp[i][j].minim = 0;
		  dp[i][j].concursuri = 1;
		} else {
		  // Probele de la i -> j se obtin prin adaugarea probei j la i...j-1
		  dp[i][j].minim = dp[i][j-1].minim - pauza - probe[j];
		  dp[i][j].concursuri = 1;
		}
	  } else {
		break;
	  }
	}
  }

  // Ultima proba => ultimul concurs => pierdere nula
  dp[numarProbe][numarProbe].minim = 0;
  dp[numarProbe][numarProbe].concursuri = 1;

  // Pentru a obtine pierderea, ridic tot ce am calculat la puterea a 3-a
  for (i = 1; i <= numarProbe; ++i) {
	for (j = i; j <= numarProbe; ++ j) {
	  if (dp[i][j].minim != LLONG_MAX) {
		dp[i][j].minim = pow3(dp[i][j].minim);
	  }
    }
  }

  // Pe principiul parantezarii matricelor (PODM)
  for (int len = 2; len <= numarProbe; ++len) {
    for (i = 1; i + len - 1 <= numarProbe; ++i) {
      j = i + len - 1;

      // Se costruieste matricea pe baza solutiilor calculate
      // anterior.
      for (k = i; k < j; ++k) {
        long long varianta = dp[i][k].minim + dp[k + 1][j].minim;
        if (dp[i][j].minim > varianta) {
          dp[i][j].minim = varianta;
          dp[i][j].concursuri = dp[i][k].concursuri + dp[k + 1][j].concursuri;
        }
      }
    }
  }

  FILE *out = fopen("planificare.out", "w");
  fprintf(out, "%lld %d", dp[1][numarProbe].minim,
      dp[1][numarProbe].concursuri);

  fclose(out);
  return 0;
}
