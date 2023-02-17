#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string fn, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream data(fn);
    string t;
    char format[] = "%[^:]: %d %d %d";
    while(getline(data,t)){
        char n[50];
        int a = 0, b = 0, c = 0, sum = 0;
        sscanf(t.c_str(),format,n,&a,&b,&c);
        sum = a+b+c;
        names.push_back(n);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }  
}

void getCommand(string &cmd, string &key){
    string input;
    cout << "Please input your command: ";
    getline(cin,input);
    int end = input.find_first_of(" ");
    cmd = input.substr(0,end);
    key = input.substr(end+1,input.length());
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(key == toUpperStr(names[i])){
        cout << names[i] << "'s score = " << scores[i] << endl;
        cout << names[i] << "'s grade = " << grades[i] << endl;
        found = true;
        }
        else if(i == names.size()-1 && !found) cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    int count = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < grades.size(); i++){
        if(grades[i] == key[0]){          
            cout << names[i] << " (" << scores[i] << ")\n";
            count++;
        }
    }
    if(count < 1) cout << "Cannot found.";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}