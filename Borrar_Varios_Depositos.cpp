#include <bits/stdc++.h>

    using namespace std;

#define mp make_pair
#define pii pair< int, int >
#define st first
#define nd second

fstream fin, fout;
stringstream aux_stream;

string clear_num(string S){
    string ans; 
    for(int i=0; i<S.size(); i++){
        if(S[i] >= '0' && S[i] <= '9'){
            ans.push_back(S[i]);
        }
    }
    return ans;
}

string delete_commas(string S){
    string ans; 
    for(int i=0; i<S.size(); i++){
        if((S[i] >= '0' && S[i] <= '9') || S[i] == '.'){
            ans.push_back(S[i]);
        }
    }
    return ans;
}

vector<string> totals;
vector<string> ids;
vector<bool> visited;
vector<string> dates;

map<int, bool> Deps;
vector<string> changeIds;

int main(){
    
    fin.open("Facturas.txt", ios::in);

    if(fin.fail()){
        cout << "No se pudo abrir el archivo de Facturas.txt\n";
    }

    string Date;
    string sDep;

    cout << "Ingrese la fecha de los depositos: ";
    cin >> Date;

    cout << "Ingrese las cantidades de los depositos:\n";
    

    while(cin >> sDep){
        if(sDep[0] >= '0' && sDep[0] <= '9'){
            Deps[(int)(stof(delete_commas(sDep), nullptr)*100)] = false;
            continue;
        }
        break;
    }

    bool vis;
    string id, date, total;
    int cont = 0;
    while(fin >> id >> date >> vis >> total){
        ids.push_back(id);
        totals.push_back(total);
        dates.push_back(date);
        visited.push_back(vis);
        cont++;
    }

    fin.close();

    // Actualizar el archivo de depositos y editar las facturas correspondinetes.

    fout.open("Depositos.txt", ios::in);
   
    fout << dDate << ;
    while(true){

    }


    fout.close();

    // Actualizar el archivo de facturas.

    fout.open("Facturas.txt", ios::out);
    
    for(int i=0; i<totals.size(); i++){
        fout << ids[i] << " " << dates[i] << " " << visited[i] << " " << totals[i] << "\n";
    }

    fout.close();


    system("pause");
    return 0;
}