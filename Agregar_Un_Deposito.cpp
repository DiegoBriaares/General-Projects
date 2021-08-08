#include <bits/stdc++.h>

    using namespace std;

#define mp make_pair
#define pii pair< int, int >
#define st first
#define nd second

fstream fin, fout;

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

int dateVal(string S){
    string sDay, sMonth, sYear;
    sDay.push_back(S[0]);
    sDay.push_back(S[1]);
    sMonth.push_back(S[3]);
    sMonth.push_back(S[4]);
    sYear.push_back(S[6]);
    sYear.push_back(S[7]);
    sYear.push_back(S[8]);
    sYear.push_back(S[9]);
    return stoi(sDay, nullptr) + stoi(sMonth, nullptr)*50 + stoi(sYear, nullptr)*500;
}

vector<string> totals;
vector<int> facts;
vector<string> ids;
vector<int> Nums;
vector<int> folios;
vector<bool> visited;
vector<string> dates;
int nFacts;

int **minVal;
bool **minId;

void solve(int i, int cash){
    //cout << "Solving " << i << "\t" << cash << "\n";
    if(minVal[i][cash] != -1){
        return;
    }
    if(i == nFacts){
        minVal[i][cash] = cash;
        minId[i][cash] = false;
        return;
    }
    solve(i+1, cash);
    minVal[i][cash] = minVal[i+1][cash];
    minId[i][cash] = false;
    if(facts[i] <= cash){
        solve(i+1, cash-facts[i]);
        if(minVal[i+1][cash-facts[i]]+1 < minVal[i+1][cash]){
            minVal[i][cash] = minVal[i+1][cash-facts[i]]+1;
            minId[i][cash] = true;
        }
    }
    return;
}

int main(){
    
    fin.open("Facturas.txt", ios::in);

    if(fin.fail()){
        cout << "No se pudo abrir el archivo de Facturas.txt\n";
    }

    string Date;
    string sDep;
    cout << "Ingrese la cantidad del deposito: ";
    cin >> sDep;
    cout << "Ingrese la fecha del deposito: ";
    cin >> Date;

    int Dep = (int)(stof(delete_commas(sDep), nullptr));

    bool vis;
    string id, date, total;
    int folio, cont = 0;
    while(fin >> id >> folio >> date >> vis >> total){
        int fval = stoi(total, nullptr);
        if(dateVal(date) <= dateVal(Date) && vis == false && fval <= Dep){
            facts.push_back(fval);
            Nums.push_back(cont);
        }
        ids.push_back(id);
        totals.push_back(total);
        dates.push_back(date);
        visited.push_back(vis);
        folios.push_back(folio);
        cont++;
    }

    fin.close();
    nFacts = facts.size();

    minVal = (int**)malloc((nFacts+1)*sizeof(int*));
    minId = (bool**)malloc((nFacts+1)*sizeof(bool*));
    for(int i=0; i<nFacts+1; i++){
        minVal[i] = (int*)malloc((Dep+1)*sizeof(int));
        minId[i] = (bool*)malloc((Dep+1)*sizeof(bool));
        for(int j=0; j<Dep+1; j++){
            minVal[i][j] = -1;
            minId[i][j] = false;
        }
    }

    solve(0, Dep);

    // Agregar el deposito

    fout.open("Depositos.txt", ios::app);
    
    int realDep = (int)(stof(delete_commas(sDep), nullptr)*100);
    fout << Date << " $" << realDep/100 << "." << (realDep%100)/10 << realDep%10 << " ";
    cout << Date << " $" << realDep/100 << "." << (realDep%100)/10 << realDep%10 << "\n";

    int cash = Dep;
    int realcash = realDep;
    for(int i=0; i<nFacts; i++){
        if(minId[i][cash] == true){
            cout << "\t" << ids[Nums[i]] << " " << folios[Nums[i]] << " " << dates[Nums[i]] << " " << totals[Nums[i]] << "\n"; 
            cash -= facts[i];
            realcash -= stoi(clear_num(totals[Nums[i]]), nullptr);
        }
    } 
    realcash *= (realcash < 0 ? -1 : 1);

    cout << "Error: " << realcash/100 << "." << (realcash%100)/10 << realcash%10 << "\n";
    fout << "Error: " << realcash/100 << "." << (realcash%100)/10 << realcash%10 << "\n";

    cash = Dep;
    realcash = realDep;
    for(int i=0; i<nFacts; i++){
        if(minId[i][cash] == true){
            fout << "\t" << ids[Nums[i]] << " " << folios[Nums[i]] << " " << dates[Nums[i]] << " " << totals[Nums[i]] << "\n"; 
            visited[Nums[i]] = true;
            cash -= facts[i];
            realcash -= stoi(clear_num(totals[Nums[i]]), nullptr);
        }
    } 
    realcash *= (realcash < 0 ? -1 : 1);
    fout << "\n";

    fout.close();

    // Actualizar las facturas

    fout.open("Facturas.txt", ios::out);
    
    for(int i=0; i<totals.size(); i++){
        fout << ids[i] << " " << folios[i] << " " << dates[i] << " " << visited[i] << " " << totals[i] << "\n";
    }

    fout.close();


    system("pause");
    return 0;
}