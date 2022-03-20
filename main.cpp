#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#define max 1000000
using namespace std;

ofstream out;

void path(vector<pair<long,long> > adlist[],long root,long ans[],long add){
    vector<pair<long,long> >:: iterator it;
    for(it=adlist[root].begin();it!=adlist[root].end();it++){
        ans[it->first]=it->second+add;
        path(adlist,it->first,ans,it->second);
    }
}

main(){
    fstream f;
    cout<< "Please enter the file name: ";
    string name;
    cin >> name;
    f.open(name);
    out.open("output.txt");
    if(!f.is_open()){
        exit(EXIT_FAILURE);
    }
    long V;
    vector<pair<long,long> > adlist[V+1];
    f>>V;
    long ans[max]={0};
    for(long i=0;i<V-1;i++){
        long s,t,w;
        f>>s>>t>>w;
        adlist[s].push_back(make_pair(t,w));
        adlist[t].push_back(make_pair(s,w));
    }

    long root;
    f>>root;
    path(adlist,root,ans,0);
    cout<<"output.txt has been created successfully.";
    f.close();
    out.close();
    return 0;
}