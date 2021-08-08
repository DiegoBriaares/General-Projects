/**

   * Made by:    Diego Briaares
   * At:   07.08.2021 00:48:42
**/

#include <bits/stdc++.h>
using namespace std;

	int main () {        
		string date, amount;
		cin >> date >> amount;
		ifstream readD("Depositos.txt");
		string d, a, b, c, xx, yy, bazura;
		set<string> to_delete;
		while (readD >> d) {
			if (d == date) {
				readD >> a;
				if (a == amount) {
					readD >> xx >> yy;
					while (readD >> a) {
						if ((int)a.size() > 15) {
							to_delete.insert(a);
							readD >> b >> bazura >> c;
						}
						else break;
					}
					break;
				}
			}
		}
		ifstream readF("Facturas.txt");
		stringstream outF;
		int p = 0;
		while (readF >> d) {
			if (p % 5 == 0) {
				if (to_delete.find(d) != to_delete.end()) {
					readF >> bazura >> a >> b >> c;
					outF << d << " " << bazura << " " << a << " 0 " << c << "\n";
					to_delete.erase(to_delete.find(d));
					continue;
				}
			}
			outF << d;
			p++;
			if (p % 5 == 0) outF << "\n";
			else outF << " ";
		}
		readF.close();
		ofstream writeF("Facturas.txt");
		writeF << outF.rdbuf(); 
	}