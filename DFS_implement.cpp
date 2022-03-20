#include <fstream>
#include <iostream>
#include <vector>
#define max 100
using namespace std;

ofstream out;
void DFS(vector<int> adlist[],int v,int visit[]){
	visit[v]=1;               //mark the visited vertex, and print it
	out << v <<" ";
	vector<int> ::iterator it;
	for(it=adlist[v].begin();it!=adlist[v].end();it++){
		if(visit[*it]==0)DFS(adlist,*it,visit);        //choose the smallest one and traversal 
	}
}
main(){
	fstream f;
	cout<< "Please enter the file name: ";     
	string name;
	cin >> name;                 //store the input file name
	f.open(name);
	name.replace(name.find("i"),5,"output");
	out.open(name);         //output file name
	if(!f.is_open()){           //if input file can't open   
		exit(EXIT_FAILURE);
	}
	int times;
	f >> times;
	while(times>0){
		int m,t;
		f >> m >>t;
		int temp;
		vector<int> adlist[m];
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				f >> temp;
				if(temp){
					adlist[i].push_back(j);              //store the adjacency matrix to adjacency list
				}
			}
		}
		int visit[max]={0};         //use to check if this vertex had been visited
		DFS(adlist,t,visit);
		out<<'\n';
		times--;
	}
	cout<<name<<" "<<"has been created successfully.";
	f.close();
	out.close();
	return 0;
}
