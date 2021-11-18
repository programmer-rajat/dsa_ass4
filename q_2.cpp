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
long long element;
long long index;
};

void swap(MinHeapNode *x,MinHeapNode *y){

MinHeapNode temp=*x;
*x=*y;
*y=temp;
}

class MinHeap{
MinHeapNode *heaparr;
long long heap_size;

public:

void MinHeapify(long long i){
long long left=2*i + 1;
long long right=2*i +2;
long long smallest=i;

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

MinHeap(MinHeapNode arr[],long long size){
heap_size=size;
heaparr=arr;
long long i=(heap_size-1)/2;
while(i>=0){
MinHeapify(i);
i--;
}
}

MinHeapNode getMin(){
return heaparr[0];
}
};

void MergeFiles(char *outputfile,long long chunksize){
long long numfiles=tempfiles.size();
vector< FILE* > input;
for(long long i=0;i<numfiles;i++){
char fileName[10000];
snprintf(fileName,sizeof(fileName),"%lld",i);
input.push_back(fopen(fileName,"r"));
}

MinHeapNode* heaparr=new MinHeapNode[numfiles];
long long i;
for(i=0;i<numfiles;i++){
long long val=fscanf(input[i],"%lld ",&heaparr[i].element);
if(val!=1)
break;

heaparr[i].index=i;

}

MinHeap heap(heaparr,i);
long long count=0;
FILE *output=fopen(outputfile,"w");
while(count!=i){
MinHeapNode root=heap.getMin();
if(count==i-1)
fprintf(output,"%lld",root.element);
else
fprintf(output,"%lld,",root.element);
long long numb=fscanf(input[root.index],"%lld ",&root.element);
if(numb!=1){
count++;
root.element=LLONG_MAX;
}

heap.replaceMin(root);
}



for(long long i=0;i<numfiles;i++){
fclose(input[i]);
char fileName[10000];
snprintf(fileName,sizeof(fileName),"%lld",i);
remove(fileName);
}
fclose(output);
}

void createtempFiles(char *inputfile,char *outputfile,long long chunksize){
ifstream file;
file.open(inputfile);


string line;
vector<long long> tempvec;

long long i=0;
while(getline(file,line))
{
std::stringstream linestream(line);
std::string value;
long long count=0;

while(getline(linestream,value,','))
{

if(count==chunksize){
sort(tempvec.begin(),tempvec.end());
char fileName[10000];
snprintf(fileName,sizeof(fileName),"%lld",i);
tempfiles.push_back(fopen(fileName,"w"));
//cout<<tempfiles[i]<<" ";
for(long long j=0;j<tempvec.size();j++){
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

fprintf(tempfiles[i],"%lld ",tempvec[j]);
}
i++;
//cout<<endl;
tempvec.clear();
count=0;
}
tempvec.push_back(stoll(value));
count++;
}
}
//vec.push_back(tempvec);
sort(tempvec.begin(),tempvec.end());
char fileName[10000];
snprintf(fileName,sizeof(fileName),"%lld",i);
tempfiles.push_back(fopen(fileName,"w"));
//cout<<tempfiles[i]<<" ";
for(long long j=0;j<tempvec.size();j++){
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
fprintf(tempfiles[i],"%lld ",tempvec[j]);
}
i++;
tempvec.clear();
for(long long k=0;k<tempfiles.size();k++)
fclose(tempfiles[k]);

file.close();

}

void externalSort(char *inputfile,char *outputfile,long long chunksize){

createtempFiles(inputfile,outputfile,chunksize);

MergeFiles(outputfile,chunksize);
}


int main(int argc,char **argv){
long long chunksize=1000;
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
