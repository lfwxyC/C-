#include<iostream>
using namespace std;

int value=0;//��ֵ�Ļ� 
int permutation(int k,int m,int a[])//k:��ʼֵΪ0�����ڼ��� m:����Ԫ�ظ��� a:��������� 
{
	int sum=0;//��ֵ 
	
	if(k==m){//�õ�һ��ȫ���� 
		for(int i=0;i<m;i++)
			sum+=(i+1)^a[i];
	}
	else{//����ȫ���� 
		for(int i=k;i<m;i++){
			swap(a[i],a[k]);
			permutation(k+1,m,a);
			swap(a[i],a[k]);//������ԭ 
		}
	}
	value|=sum;
	return value;
} 

int main()
{
	int n;
	cin>>n;
	
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<permutation(0,n,a)<<endl;
	return 0;
}
