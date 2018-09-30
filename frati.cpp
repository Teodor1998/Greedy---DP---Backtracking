// Copyright 2018 Teodor Apostol

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Concurs {
  int jocuri;
  int benzi;
};

// Verific daca Jon este urmatorul care is alege concursul
bool UrmeazaJon(int n) {
  return (n % 2) == 0;
}

// Daca doua Concursuri au suma premiilor egala
bool Equal(Concurs &a, Concurs &b) {
  return (a.jocuri + a.benzi) == (b.jocuri + b.benzi);
}

// Comparator pentru sortare descrescatoare dupa suma premiilor
struct Comp {
	bool operator () (const Concurs &first, const Concurs &second) const{
		if (first.jocuri + first.benzi != second.jocuri + second.benzi) {
    		return (first.jocuri + first.benzi) > (second.jocuri + second.benzi);
  		}
  		return first.jocuri > second.jocuri;
		}
	};

// Verific unde se termina secventa de Concursuri cu aceeasi suma
int GetEqualSeq(int start, Concurs *concursuri, int num_concursuri) {
  while (start < num_concursuri - 1) {
    if (Equal(concursuri[start], concursuri[start + 1])) {
      ++start;
    } else {
      break;
    }
  }
  return start;
}

int main(void) {
  int num_concursuri = 0;
  fstream frati_in("frati.in", ios::in);
  fstream frati_out("frati.out", ios::out);

  // Salvez concursurile in vectorul concursuri
  frati_in >> num_concursuri;
  Concurs *concursuri = new Concurs[num_concursuri];

  int i = 0;
  do {
    Concurs a;
    a.jocuri = 0;
    a.benzi = 0;
	frati_in >> a.jocuri >> a.benzi;
	concursuri[i] = a;
	++i;
  } while (i < num_concursuri);
  frati_in.close();

  // Sortez descrescator vectorul dupa premii si apoi dupa jocuri
  sort(concursuri, concursuri + num_concursuri, Comp());

  // Initializez cu 0 numarul de obiecte preferate pentru fiecare
  int scor_Jon = 0;
  int scor_Sam = 0;
  for (int i = 0; i < num_concursuri; ++i) {
    int end_seq = GetEqualSeq(i, concursuri, num_concursuri);
    // Daca nu am o secventa de elemente cu sumele premiilor egale
	if (end_seq == i) {
      if ((i % 2) == 0) {
	    scor_Jon += concursuri[i].jocuri;
	  } else {
	    scor_Sam += concursuri[i].benzi;
	  }
	} else {
	  if ((i % 2) == 0) {
	  	// Jon va parcurge jumatate de secventa ->, iar Sam invers
	    for (int j = 0; j <= end_seq - i + 1; ++j) {
	      // Daca s-a trecut de mijloc
		  if (concursuri[i + j].jocuri == 0) {
		    if (concursuri[i + j].benzi == 0) {
			  break;
			}
		  }
		  scor_Jon += concursuri[j + i].jocuri;
		  concursuri[i + j].jocuri = 0;
		  concursuri[i + j].benzi = 0;

		  if (concursuri[end_seq - j].jocuri == 0) {
		    if (concursuri[end_seq - j].benzi == 0) {
			  break;
			}
		  }
		  scor_Sam += concursuri[end_seq - j].benzi;
		  concursuri[end_seq - j].jocuri = 0;
		  concursuri[end_seq - j].benzi = 0;
		}
		// Trecem mai departe (fara a relua secventa)
		i = end_seq;

	  } else {
	  	// Daca incepe Sam, procedam la fel
	    for (int j = 0; j <= end_seq - i + 1; ++j) {
		  if (concursuri[end_seq - j].jocuri == 0) {
		    if (concursuri[end_seq - j].benzi == 0) {
			  break;
			}
		  }
		  scor_Sam += concursuri[end_seq - j].benzi;
		  concursuri[end_seq - j].jocuri = 0;
		  concursuri[end_seq - j].benzi = 0;

		  if (concursuri[i + j].jocuri == 0) {
		    if (concursuri[i + j].benzi == 0) {
			  break;
			}
		  }
		  scor_Jon += concursuri[j + i].jocuri;
		  concursuri[i + j].jocuri = 0;
		  concursuri[i + j].benzi = 0;
		}
		i = end_seq;
	  }
	}
  }
  // Afisarea scorurilor
  frati_out << scor_Jon << " " << scor_Sam;
  frati_out.close();

  return 0;
}
