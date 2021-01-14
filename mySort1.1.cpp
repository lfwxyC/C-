#include<iostream>
using namespace std;

template<class T>
class mySort
{
public:
	mySort(T a[],int n);
	~mySort(){delete []p;}
	void rank();//��������
	void selectionSort();//��ʱ��ֹ��ѡ������
	void bubbleSort();//��ʱ��ֹ��ð������
	void insertSort();//�������� 
	void output();//����ź�������� 
private:
	T *p;//ָ����������  
	int n;//���鳤��		
};

template<class T>
mySort<T>::mySort(T a[],int n):n(n)//���캯�� 
{
	p=new T [n];
	
	for(int i=0;i<n;i++)
	{
		p[i]=a[i];
	} 
}

template<class T>
void mySort<T>::rank()//��������
{
	T *r=new T[n];//�����������ε����� 
	
	//��ʼ��r
	for(int i=0;i<n;i++)
		r[i]=0;
		
	//�������� 
	for(int i=1;i<n;i++)
		for(int j=0;j<i;j++)
		{
			if(p[i]>=p[j])//p[i]������ߵ�Ԫ�رȽ� 
				r[i]++;
			else
				r[j]++;
		}
			
	T *u=new T[n];//������������
		 
	//���������� 
	for(int i=0;i<n;i++)
		u[r[i]]=p[i];
	for(int i=0;i<n;i++)
		p[i]=u[i];
		
	delete []r;
}

template<class T>
void mySort<T>::selectionSort()//��ʱ��ֹ��ѡ������
{
	bool sorted=false;//��ʼʱδ�ź��� 
	
	for(int i=n;(i>1)&&(!sorted);i--)//�������Ѿ��ź�����ѭ��ֹͣ 
	{
		int indexOfMax=0;
		sorted=true;//�����Ѿ��ź��� 
		
		for(int j=1;j<i;j++)
		{
			if(p[indexOfMax]<p[j])//��ÿһ��Ԫ�ؾ�С�����һ�������������� 
				indexOfMax=j;
			else
				sorted=false;
		}
		swap(p[indexOfMax],p[i-1]); 
	}	
}

template<class T>
void mySort<T>::bubbleSort()//��ʱ��ֹ��ð������
{
	bool swapped=true;
	
	for(int i=0;(i<n-1)&&(swapped);i++)
	{
		swapped=false;//��ʼʱû�н��н��� 
		
		for(int j=0;j<n-i-1;j++)
			if(p[j]>p[j+1])
			{
				swap(p[j],p[j+1]);
				swapped=true;
			}	
	}		
}

template<class T>
void mySort<T>::insertSort()//��������
{
	for(int i=1;i<n;i++)
	{
		T t=p[i];
		int j;
		
		for(j=i-1;j>=0&&t<p[j];j--)//�Ӻ���ǰ�ң���Ԫ�ر�tСʱֹͣ 
			p[j+1]=p[j];
		p[j+1]=t;		
	}	
}

template<class T>
void mySort<T>::output()//����ź��������
{
	for(int i=0;i<n;i++)
		cout<<p[i]<<" ";
	cout<<endl;
}

int main()
{
	int n;
	cin>>n;
	
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
		
	mySort<int> s(a,n);
	s.bubbleSort();
	s.output();
	return 0;
}
