#include<iostream>
using namespace std;

template<class T>
struct node//����ڵ� 
{
	T element;//ֵ 
	node *next;//ָ�� 
	
	//���캯�� 
	node(){}
	node(const T& theElement,node<T> *theNext)
	{
		element=theElement;
		next=theNext;
	}
};

template<class T>
class sortedChain//�������� 
{
public:
	sortedChain();
	~sortedChain(){}
	
	void find(const T& x)const;//���� 
	void insert(const T& x);//���� 
	void erase(const T& x);	//ɾ�� 
	int getSize()const{return size;}//��ȡ������ 
protected:
	node<T> *firstNode;//ͷ�ڵ� 
	int size;//������ 
};

template<class T>
sortedChain<T>::sortedChain()//���캯�� 
{
	firstNode=NULL;
	size=0;
}

template<class T>
void sortedChain<T>::find(const T& x)const//���� 
{
	node<T> *currentNode=firstNode;
	
	while(currentNode!=NULL&&currentNode->element!=x)
		currentNode=currentNode->next;
	
	if(currentNode!=NULL)//�ҵ��� 
		cout<<size<<endl;
	
	else//δ�ҵ� 
		cout<<"Not Found"<<endl;
} 

template<class T>
void sortedChain<T>::insert(const T& x)//���� 
{
	node<T> *p=firstNode,*tp=NULL;//tp���ڼ�¼p��λ�� 
	
	while(p!=NULL&&p->element<x)
	{
		tp=p;
		p=p->next;
	}
	
	if(p!=NULL&&p->element==x)//Ԫ���Ѵ��� 
	{
		cout<<"Existed"<<endl;
		return;
	}
	
	//Ԫ�ز����� 
	node<T> *newNode=new node<T>(x,p);
	
	if(tp==NULL)//����ͷ�ڵ� 
		firstNode=newNode;
	
	else//���������ڵ� 
		tp->next=newNode;
	
	size++;
}

template<class T>
void sortedChain<T>::erase(const T& x)//ɾ�� 
{
	node<T> *p=firstNode,*tp=NULL;//tp���ڼ�¼p��λ�� 
	
	while(p!=NULL&&p->element<x)
	{
		tp=p;
		p=p->next;
	}
	
	if(p!=NULL&&p->element==x)//Ԫ�ش��� 
	{
		if(tp==NULL)//ɾ��ͷ�ڵ� 
			firstNode=p->next;
		
		else//ɾ�������ڵ� 
			tp->next=p->next;
		
		delete p;
		size--;
		cout<<size<<endl;
	}
	
	else//Ԫ�ز����� 
		cout<<"Delete Failed"<<endl;
}

template<class T>
class hashChains//����ɢ�� 
{
public:
	hashChains(int theDivisor=11);
	~hashChains(){delete[]table;}
	
	void find(const T& x)const{table[x%divisor].find(x);}//���� 
	void insert(const T& x){table[x%divisor].insert(x);}//���� 
	void erase(const T& x){table[x%divisor].erase(x);}//ɾ�� 
protected:
	sortedChain<T> *table;//ɢ�б� 
	int divisor;//���� 
};

template<class T>
hashChains<T>::hashChains(int theDivisor)//���캯�� 
{
	divisor=theDivisor;
	table=new sortedChain<T>[divisor];
}

int main()
{
	int D,m;
	
	cin>>D>>m;
	hashChains<int> h(D);
	
	for(int i=0;i<m;i++)
	{
		int opt,x;
		
		cin>>opt>>x;
		switch(opt)
		{
			case 0:
				h.insert(x);
				break;
			case 1:
				h.find(x);
				break;
			case 2:
				h.erase(x);
				break;
		}
	}
	return 0;
}
