#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define max 100
using namespace std;

ofstream out;
void BFS(vector<int> adlist[],queue<int> ans,int visit[]){
	if(ans.empty()){       // if the queue is empty, which mean that all of the vertex had been visit
		return;
	}
	int v=ans.front();
	ans.pop();
	vector<int> ::iterator it;
	for(it=adlist[v].begin();it!=adlist[v].end();it++){
		if(visit[*it]==0){       //visit the unvisited vertexes around the node
			visit[*it]=1;       //mark the visited vertex, print it, and push in the queue
			out<<*it<<" ";
			ans.push(*it);
		}
	}
	BFS(adlist,ans,visit);
}
main(){
	fstream f;
	cout<< "Please enter the file name: ";
	string name;
	cin >> name;                        //store the input file name
	f.open(name);
	name.replace(name.find("i"),5,"output");
	out.open(name);                //output file name
	if(!f.is_open()){                   //if input file can't open 
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
					adlist[i].push_back(j);     //store the adjacency matrix to adjacency list
				}
			}
		}
		int visit[max]={0};    //use to check if this vertex had been visited
		queue<int> ans;        
		ans.push(t);
		visit[t]=1;
		out<<t<<" ";
		BFS(adlist,ans,visit);
		out<<'\n';
		times--;
	}
	cout<<name<<" "<<"has been created successfully.";
	f.close();
	out.close();
	return 0;
}
