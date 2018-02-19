// Floyd-Warshallov algoritem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

struct Vozlisce {
	int ime;
	int cena;
	int predhodnik;
};
int vel = 0;
int C[30][30];
int P[30][30];
int D[30][30];

void meni() {
	cout << endl;
	cout << "Floyd-Warshallow algoritem - izbira:" << endl;
	cout << "1 Preberi graf" << endl;
	cout << "2 Zagon algoritma" << endl;
	cout << "3 Izpis najkrajse poti med vozliscema s in g" << endl;
	cout << "4 Konec" << endl;
	cout << "5 Izpis celotne matike" << endl;
	cout << endl;
	cout << "Vasa izbira: ";
}
void izpis(int P[30][30]) {
	for (int i = 0; i < vel; i++) {
		for (int j = 0; j < vel; j++) {
			if (P[i][j] == -1) {
				cout << "NIL ";
			}
			else {
				cout << P[i][j] << " ";
			}
		}
		cout << endl;
	}
}
void vnosMatrikeC() {
	int n,a;
	cout << "vnesi tabelo C " << endl;
	cout << "vnesi velikost: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a;
			C[i][j] = a;
		}
	}
	vel = n;
}
enum {
	NIL = -1,
	NESKONCNO = INT_MAX
};
void beri(string f)
{
	fstream dat(f.c_str(), fstream::in);
	dat >> vel;
	for (int i = 0; i < vel; i++) {
		for (int j = 0; j < vel; j++) {
			if (i == j) {
				D[i][j] = 0;
				C[i][j] = 0;
			}
			else {
				D[i][j] = NESKONCNO;
				C[i][j] = NESKONCNO;
			}
		}
	}
	
	
	
	int i = 0;
	int p, q, c;

	while (!dat.eof())
	{
		dat >> p >> q >> c;
		C[p - 1][q - 1] = c;
		i++;
	}
	dat.close();
}

void floydWarshall(int C[30][30]) {
	for (int i = 0; i <= vel-1 ; i++) {
		for (int j = 0; j <= vel-1 ; j++) {
			D[i][j] = C[i][j];
			if (i != j && C[i][j] != NESKONCNO) {
				P[i][j] = i;
			}
			else {
				P[i][j] = NIL;
			}
		}
	}
	for (int k = 0; k <= vel-1; k++) {
		for (int i = 0; i <= vel-1 ; i++) {
			for (int j = 0; j <= vel-1; j++) {
				if (D[i][j] > (D[i][k] + D[k][j]) && D[i][k] != NESKONCNO && D[k][j] != NESKONCNO) {
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = P[k][j];
				}
				
			}
		}
	}
}



void izpisPoti(int P[30][30], int s, int g){
	if (s == g) {
		cout << s  << ": dolzina: " << D[s][g] << endl;
	}
	else {
		if (P[s][g] == NIL) {
			cout << "Med " << s << " in " <<g << " ni poti" << endl;
		}
		else {
			izpisPoti(P, s, P[s][g]);
			cout << g << ": dolzina: " << D[s][g] << endl;
		}
	}
}

int main()
{
	int vnos;
	int zacetek, konec;
	int tmp;
	do {
		meni();
		cin >> vnos;
		switch (vnos)
		{
		case 1:
			beri("graf.txt");
			cout << "Velikost: " << vel << endl;
			cout << "Matika C" << endl;
			izpis(C);
			break;
		case 2:
			floydWarshall(C);
			break;
		case 3:
			cout << "Zacetek: ";
			cin >> zacetek;
			cout << "Konec";
			cin >> konec;
			izpisPoti(P, zacetek, konec);
			break;
		case 5:
			cout << "Matrika D" << endl;
			izpis(D);
			cout << "Matrika P" << endl;
			izpis(P);
			break;
		default:
			break;
		}
	} while (vnos != 4);

	return 0;
}

