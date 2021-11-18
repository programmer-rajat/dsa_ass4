#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <climits>

using namespace std;
vector< FILE* > tempfiles;

struct MinHeapNode{
int element;
int index;
};

void swap(MinHeapNode *x,MinHeapNode *y){

MinHeapNode temp=*x;
*x=*y;
*y=temp;
}

class MinHeap{
MinHeapNode *heaparr;
int heap_size;

public:

void MinHeapify(int i){
int left=2*i + 1;
int right=2*i +2;
int smallest=i;

if(heap_size>left && heaparr[left].element<heaparr[i].element)
smallest=left;

if(heap_size>right && heaparr[smallest].element>heaparr[right].element)
smallest=right;

if(smallest!=i)
{
swap(&heaparr[i],&heaparr[smallest]);
MinHeapify(smallest);
}

}


void replaceMin(MinHeapNode x){
heaparr[0]=x;
MinHeapify(0);
}

MinHeap(MinHeapNode arr[],int size){
heap_size=size;
heaparr=arr;
int i=(heap_size-1)/2;
while(i>=0){
MinHeapify(i);
i--;
}
}

MinHeapNode getMin(){
return heaparr[0];
}
};

void MergeFiles(char *outputfile,int chunksize){
int numfiles=tempfiles.size();
vector< FILE* > input;
for(int i=0;i<numfiles;i++){
char fileName[1000000];
snprintf(fileName,sizeof(fileName),"%d",i);
input.push_back(fopen(fileName,"r"));
}

MinHeapNode* heaparr=new MinHeapNode[numfiles];
int i;
for(i=0;i<numfiles;i++){
int val=fscanf(input[i],"%d ",&heaparr[i].element);
if(val!=1)
break;

heaparr[i].index=i;

}

MinHeap heap(heaparr,i);
int count=0;
FILE *output=fopen(outputfile,"w");
while(count!=i){
MinHeapNode root=heap.getMin();
if(count==i-1)
fprintf(output,"%d",root.element);
else
fprintf(output,"%d,",root.element);
int numb=fscanf(input[root.index],"%d ",&root.element);
if(numb!=1){
count++;
root.element=INT_MAX;
}

heap.replaceMin(root);
}



for(int i=0;i<numfiles;i++){
fclose(input[i]);
char fileName[1000000];
snprintf(fileName,sizeof(fileName),"%d",i);
remove(fileName);
}
fclose(output);
}

void createtempFiles(char *inputfile,char *outputfile,int chunksize){
ifstream file;
file.open(inputfile);


string line;
vector<int> tempvec;

int i=0;
while(getline(file,line))
{
std::stringstream linestream(line);
std::string value;
int count=0;

while(getline(linestream,value,','))
{

if(count==chunksize){
sort(tempvec.begin(),tempvec.end());
char fileName[1000000];
snprintf(fileName,sizeof(fileName),"%d",i);
tempfiles.push_back(fopen(fileName,"w"));
//cout<<tempfiles[i]<<" ";
for(int j=0;j<tempvec.size();j++){
/*
if(j!=tempvec.size()-1){
fprintf(tempfiles[i],"%d,",tempvec[j]);
//cout<<tempvec[j]<<" ";
}
else{
fprintf(tempfiles[i],"%d",tempvec[j]);
//cout<<tempvec[j]<<" ";

}
*/

fprintf(tempfiles[i],"%d ",tempvec[j]);
}
i++;
//cout<<endl;
tempvec.clear();
count=0;
}
tempvec.push_back(stoi(value));
count++;
}
}
//vec.push_back(tempvec);
sort(tempvec.begin(),tempvec.end());
char fileName[1000000];
snprintf(fileName,sizeof(fileName),"%d",i);
tempfiles.push_back(fopen(fileName,"w"));
//cout<<tempfiles[i]<<" ";
for(int j=0;j<tempvec.size();j++){
/*
if(j!=tempvec.size()-1){
fprintf(tempfiles[i],"%d,",tempvec[j]);
//cout<<tempvec[j]<<" ";
}
else{
fprintf(tempfiles[i],"%d",tempvec[j]);
//cout<<tempvec[j]<<" ";

}
*/
fprintf(tempfiles[i],"%d ",tempvec[j]);
}
i++;
tempvec.clear();
for(int k=0;k<tempfiles.size();k++)
fclose(tempfiles[k]);

file.close();

}

void externalSort(char *inputfile,char *outputfile,int chunksize){

createtempFiles(inputfile,outputfile,chunksize);

MergeFiles(outputfile,chunksize);
}


int main(int argc,char **argv){
int chunksize=10000;
vector<vector<int>> vec;
//ifstream file;
char *inputfile=argv[1];
char *outputfile=argv[2];
externalSort(inputfile,outputfile,chunksize);
/*
//file.open(inputfile);
string line;
vector<int> tempvec;


while(getline(file,line))
{
std::stringstream linestream(line);
std::string value;
int count=0;

while(getline(linestream,value,','))
{

if(count==10){
vec.push_back(tempvec);
tempvec.clear();
count=0;
}
tempvec.push_back(stoi(value));
count++;
}
}
vec.push_back(tempvec);

for(int i=0;i<vec.size();i++)
{
for(int j=0;j<vec[i].size();j++)
cout<<vec[i][j]<<" ";
cout<<endl;
}
*/
return 0;
}
