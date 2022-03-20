#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#define max 1000
using namespace std;
ofstream out;
int search(int in[],int root,int node){      //find the index in inoder, which value equal to root
	for(int i=0;i<node;i++){
		if(in[i]==root)return i;
	}
	return -1;
}
void postorder(int in[],int pre[],int node){
	int rootindex=search(in,pre[0],node);     //the first node in preorder is represent the D(root), 
	                                         //so the left of nodes of D in inorder represent lift children
	if(rootindex!=0){                        //check if there is any lift children 
		postorder(in,pre+1,rootindex);
	}
	if(rootindex!=node-1){                  // check if there is any right children
		postorder(in+rootindex+1,pre+rootindex+1,node-rootindex-1);
	}
	out << pre[0] <<" ";
}
int postindex;
void prestack(int in[],int post[],int stindex,int endindex,stack<int> &ans,int node){
	if(stindex>endindex){
		return;
	}
	int root=post[postindex];        //the last node in the postorder represent the D(root)
	int rootindex=search(in,root,node);
	postindex--;
	prestack(in,post,rootindex+1,endindex,ans,node);
	prestack(in,post,stindex,rootindex-1,ans,node);
	ans.push(root);
}
void preorder(int in[],int post[],int node){
	stack<int> ans;                 //use stack to store the postorder
	postindex=node-1;
	prestack(in,post,0,node-1,ans,node);
	while(ans.size()>0){
		out << ans.top() << " ";
		ans.pop();
	}
}

main(){
	fstream f;
	cout<< "Please enter the file name: ";
	string name;
	cin >> name;                           //store the input file name
	f.open(name);
	name.replace(name.find("i"),5,"output");
	out.open(name);                   //output file name
	if(!f.is_open()){                     //if input file can't open 
		exit(EXIT_FAILURE);
	}
	int times;
	f >> times;
	string type1="preorder-inorder";
	string type2="postorder-inorder";
	while(times>0){
		string S;
		f >> S;
		int nodes;
		f >> nodes;
		int p[max]={};
	    int in[max]={};
	    for(int i=0;i<nodes;i++){
			f >> p[i];        
		}
		for(int i=0;i<nodes;i++){
			f >> in[i];       //in represent the inorder
		}
		if(S.compare(type1)==0){
			postorder(in,p,nodes);     //p represent the preorder in type1
		}
		else{
			preorder(in,p,nodes);     //p represent the postorder in type2
		}
		out<< '\n';
		times--;
	}
	cout<<name<<" "<<"has been created successfully.";
	f.close();
	out.close();
	return 0;
}
