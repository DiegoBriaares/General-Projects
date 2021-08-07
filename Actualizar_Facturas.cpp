#include <bits/stdc++.h>

	using namespace std;

#define mp make_pair
#define st first
#define nd second

string filename;

fstream fin, fout;
vector<string> row;
string line, word, temp;
int cont = 0;

typedef pair< int, pair< string, string > > invoice;
map<invoice, bool, greater <invoice> > Invoices;

string delete_commas(string S){
	string ans; 
	for(int i=0; i<S.size(); i++){
		if(S[i] >= '0' && S[i] <= '9'){
			ans.push_back(S[i]);
		}
	}
	return ans;
}

int main(){
	
	fin.open("Facturas.txt", ios::in);

    if(!fin.fail()){
    	string id, date, total;
    	bool vis;
    	while(fin >> id >> date >> vis >> total){
    		Invoices[mp(stoi(delete_commas(total), nullptr), mp(id, date))] = vis;
    	}
    }

 	fin.close();

	cout << "Ingresa el nombre del archivo:\n";
	getline(cin, filename);

	fin.open(filename, ios::in);

	if(fin.fail()){
		cout << "No se pudo abrir el archivo correctamente.\n";
		system("Pause");
		return 0;
	}

  	getline(fin, line);

    while (getline(fin, line)) {
  
        row.clear();
        stringstream s(line);
  
        while (getline(s, word, '|')) {
  			row.push_back(word);
        }

        string num = delete_commas(row[11]);
        cout << cont << " ";
        if(num.size() > 0 && num[0] >= '0' && num[0] <= '9' && row[2].size() > 0 && row[4].size() > 0){
        	if(Invoices.find(mp(stoi(num, nullptr), mp(row[4], row[2]))) == Invoices.end()){
        		Invoices[mp(stoi(num, nullptr), mp(row[4], row[2]))] = false;
        		cout << "Agregado";
        	}
        }
        cout << "\n";
        cont++;
    }	

    fin.close();
    
    fout.open("Facturas.txt", ios::out);

    for(map<invoice, bool>::iterator it = Invoices.begin(); it != Invoices.end(); it++){
		fout << (it->st).nd.st << " " << (it->st).nd.nd << " " << it->nd << " " << (it->st).st/100 << "." << (((it->st).st)%100)/10 << ((it->st).st)%10 << "\n";
 	}

 	fout.close();

	system("pause");
	return 0;
}