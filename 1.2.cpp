#include<iostream>
using namespace std;

int value=0;//���� 
int subset(int k,int m,int a[],int b[])//k:��ʼֵΪ0�����ڼ��� m:����Ԫ�ظ��� a:��������� b:���0/1���� 
{
	int sum=0;//��ֵ 
	
	//�ݹ�Ľ�����������ǰ�� 
	if(k==m){//�õ�һ��0/1���� 
		int count=0;//���Ԫ���������еĵڼ��� 
		for(int i=0;i<m;i++)
			if(b[i]){//b[i]=1ʱԪ���������� 
				count++;
				sum+=count*a[i];
			}
	}
	//�ݹ����0/1���� 
	else{
		b[k]=0;
		subset(k+1,m,a,b);
		b[k]=1;
		subset(k+1,m,a,b);
	}
	value^=sum;
	return value;
}

int main()
{
	int n;
	cin>>n;
	
	int a[n],b[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<subset(0,n,a,b)<<endl;
	return 0;
}
