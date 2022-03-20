#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#define max 1000000
using namespace std;



void path(vector<pair<long,long> > adlist[],long root,long pre,long ans[],long add){
	vector<pair<long,long> >:: iterator it;
	for(it=adlist[root].begin();it!=adlist[root].end();it++){
		if(it->first!=pre){
			ans[it->first]=it->second+add;                      //store the length from the root in array
			path(adlist,it->first,root,ans,it->second+add);     //depth search
		}
	}
}

main(){
	fstream f;
	ofstream out;
	cout<< "Please enter the file name: ";
	string name;
	cin >> name;                     //store the input file name
	f.open(name);
    name.replace(name.find("i"),5,"output");
	out.open(name);                 //output file name
	if(!f.is_open()){               //if input file can't open 
		exit(EXIT_FAILURE);
	}
	long V;
	f>>V;
	vector<pair<long,long> > adlist[V+1];            
	long ans[V+1]={0};
	for(long i=0;i<V-1;i++){                         //store the vertexes and the path length
		long s,t,w;
		f>>s>>t>>w;
		adlist[s].push_back(make_pair(t,w));
		adlist[t].push_back(make_pair(s,w));
	}
	long root;
	f>>root; 
	path(adlist,root,root,ans,0);             //the function to calculate the sum of length in every vertex
	for(long i=1;i<V+1;i++){                  //print the answer in the file
		out<<i<<" "<<ans[i]<<endl;
	}
	cout<<name<<" "<<"has been created successfully.";
	f.close();
	out.close();
	return 0;
}
