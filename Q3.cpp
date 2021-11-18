#include <vector>
#include <iostream>
#include <climits>
using namespace std;

class TrieNode{
public:
TrieNode* left;
TrieNode* right;
};


long long powerOf(long long base,long long exp){
long long returnValue=1;
for(long long i=1;i<=exp;i++){
returnValue=base*returnValue;
}
return returnValue;
}


void insert(TrieNode* head,long long element){
TrieNode* curr=head;
for(long long i=63;i>=0;i--){
long long b=(element>>i)&1;
if(b==0){
if(curr->left==NULL){
curr->left=new TrieNode();
}
curr=curr->left;
}
else{
if(curr->right==NULL)
curr->right=new TrieNode();

curr=curr->right;
}
}
}

long long MaxXor(long long x,TrieNode *head){
TrieNode* curr=head;
long long max_xor=0;
for(long long i=63;i>=0;i--){
long long bit=(x>>i)&1;
if(bit==0){

if(curr->right!=NULL){
max_xor+=powerOf(2,i);
curr=curr->right;
}
else
curr=curr->left;

}

else{
if(curr->left!=NULL){
max_xor+=powerOf(2,i);
curr=curr->left;
}
else
curr=curr->right;

}

}




return max_xor;

}
int main(){
vector<long long> vec;
vector<long long> que;
TrieNode *head=new TrieNode();
int N,q;
cin>>N>>q;
for(int i=0;i<N;i++){
long long ele;
cin>>ele;
//vec.push_back(ele);
insert(head,ele);
}

for(int i=0;i<q;i++)
{
long long query;
cin>>query;
que.push_back(query);
}

for(int i=0;i<q;i++)
cout<<MaxXor(que[i],head)<<endl;

return 0;
}


