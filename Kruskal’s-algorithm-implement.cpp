#include <fstream>
#include <iostream>
#include <vector> 
#include<bits/stdc++.h>

using namespace std;
typedef pair<int,int> edge;

vector<pair<int,edge> > admatrix;

int find(int* parent,int u){       //find the vertex's root
	while(parent[u]>=0){
		u=parent[u];
	}
	return u;
}

void unionmerge(int* parent,int rfrom,int rto){
	if(parent[rfrom]<=parent[rto]){          //if the parent[rform] has more children, parent[rto] will be a subtree to it
		parent[rfrom]+=parent[rto];
		parent[rto]=rfrom;
	}
	else{
		parent[rto]+=parent[rfrom];
		parent[rfrom]=rto;
	}
}

int Kruskal(int V){
	int ans=0;
	sort(admatrix.begin(),admatrix.end());    //sort the admatrix in increasing order (base on the edge)
	int parent[V];                           //parent is an array which represent the indexs' root, and initialize to -1
	memset(parent,-1,V*sizeof(int));
	vector<pair<int,edge> >:: iterator it;
	for(it=admatrix.begin();it!=admatrix.end();it++){
		int from=it->second.first;       
		int to=it->second.second;
		int rfrom=find(parent,from);    //find two vertex's root
		int rto=find(parent,to);
		if(rfrom != rto){               //check if this path will cause a circle or not
			ans+=it->first;
			unionmerge(parent,rfrom,rto);      //merge two vertex to a set
		}
		
	}
	return ans;
}

main(){
	fstream f;
	cout<< "Please enter the file name: ";
	string name;
	cin >> name;                            //store the input file name
	f.open(name);        
	ofstream out;
	name.replace(name.find("i"),5,"output");
	out.open(name);                    //output file name
	if(!f.is_open()){                       //if input file can't open 
		exit(EXIT_FAILURE);
	}
	int V,E;
	f >>V>>E;
	int x,y,w;
	for(int i=0;i<E;i++){
		f >> x >> y >> w;      
		admatrix.push_back({w,{x,y}});    //store two vertexs and the edge between them
	}
	int ans=Kruskal(V);    //ans is represent the shortest path
	out<<ans;
	cout<<name<<" "<<"has been created successfully.";
	f.close();
	out.close();
	return 0;
}
