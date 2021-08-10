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
map<invoice, pair<bool, int>, greater <invoice> > Invoices;
map<int, pair<string, string> > User_Data;

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
        string RFC, name;
    	bool vis;
        int folio;
    	while(fin >> id >> folio >> date >> vis >> total >> RFC){
            getline(fin, name);
    		Invoices[mp(stoi(delete_commas(total), nullptr), mp(id, date))] = make_pair(vis, folio);
            User_Data[folio] = make_pair(RFC, name);            
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

        string num = delete_commas(row[7]);
        cout << cont << " ";
        if(num.size() > 0 && num[0] >= '0' && num[0] <= '9' && row[2].size() > 0 && row[4].size() > 0 && row[3].size() > 0){
        	if(Invoices.find(make_pair(stoi(num, nullptr), mp(row[4], row[2]))) == Invoices.end()){
        		Invoices[mp(stoi(num, nullptr), mp(row[4], row[2]))] = make_pair(false, stoi(row[3]));
        		User_Data[stoi(row[3])] = make_pair(row[5], row[6]);
                cout << "Agregado";
        	}
        }
        cout << "\n";
        cont++;
    }	

    fin.close();
    
    fout.open("Facturas.txt", ios::out);

    for(map<invoice, pair<bool, int> >::iterator it = Invoices.begin(); it != Invoices.end(); it++){
		fout << (it->st).nd.st << " " << (it->nd).nd << " " << (it->st).nd.nd << " " << (it->nd).st << " " << (it->st).st/100 << "." << (((it->st).st)%100)/10 << ((it->st).st)%10 << " ";
        fout << User_Data[(it->nd).nd].st << " " << User_Data[(it->nd).nd].nd << "\n";
 	}

 	fout.close();

	system("pause");
	return 0;
}