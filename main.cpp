#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef struct node{
    string correct="";
    vector<string> incorrect;
}node;

map<string,node> Data;

bool IN(string &str,vector<string> &strs){
    for(auto i:strs){
        if(i==str) return true;
    }
    return false;
}


int main(){
    string q,t;
    ifstream input("answer");
    while(getline(input,q)){
        getline(input,t);
        Data[q].correct=t;
    }
    input.close();
    
    int n=10;
    string option,question,wrongans,trash;
    vector<string> questions(n);
    vector<int> ans(n);

    while(true){
        if(cin.peek()=='.') break;

        for(int i=0;i<n;i++){
            getline(cin,questions[i]);
            vector<string> options;
            while(getline(cin,option)){
                if(option=="Check Answers") break;

                if(option.size()){
                    options.push_back(option);
                    if(cin.peek()!='\n') break;
                }
                /*
                if(option=="False"){
                    cin.ignore();
                    if(i==n-1){
                        cin.ignore();
                        getline(cin,trash);
                    }
                    break;
                }
                */
            }
            
            
            if(Data[questions[i]].correct!=""){
                for(int j=0;j<options.size();j++){
                    if(options[j]==Data[questions[i]].correct) ans[i]=j;
                }
            }else{
                for(int j=options.size()-1;j>=0;j--){
                    if(!IN(options[j],Data[questions[i]].incorrect)){
                        ans[i]=j;
                        Data[questions[i]].correct=options[j];
                        break;
                    }
                }
            }
        }
        
        for(int i=0;i<n;i++) cout << ans[i]+1 << ' ';
        cout << '\n';

        getline(cin,trash);
        cin.ignore();
        getline(cin,trash);
        
        getline(cin,question);
        while(true){
            cin.ignore();
            getline(cin,wrongans);
            wrongans=wrongans.substr(13);
            Data[question].correct="";
            Data[question].incorrect.push_back(wrongans);

            cin.ignore();
            getline(cin,question);
            if(question=="COURSE FEEDBACK") break;
        }
    }
    ofstream file("answer");
    for(auto i:Data){
        if(i.second.correct.size()){
            file << i.first << '\n' << i.second.correct << '\n';
        }
    }
    file.close();
}

