#include<iostream>
using namespace std;

template<class T>
class hashTable//ɢ�б� 
{
public:
	hashTable(int theDivisor=11);
	~hashTable(){delete[]table;}
	
	void find(const T&)const;//���� 
	void insert(const T&);//���� 
	void erase(const T&);//ɾ�� 
protected:
	int search(const T&)const;//����Ԫ����Ͱ�е�λ�� 
	T *table;//ɢ�б� 
	int divisor;//���� 
};

template<class T>
hashTable<T>::hashTable(int theDivisor)//���캯�� 
{
	divisor=theDivisor;
	table=new T[divisor];
	
	for(int i=0;i<divisor;i++)//��ʼ��ɢ�б���Ͱȫ���ÿ� 
		table[i]=-1;
}

template<class T>
int hashTable<T>::search(const T& x)const//����Ԫ����Ͱ�е�λ�� 
{
	int i=x%divisor;//Ԫ��Ӧ���ڵ�λ�� 
	int j=i;
	
	do
	{
		if(table[j]==-1||table[j]==x)//��λ��Ϊ�ջ��Ԫ���Ѵ���
			return j;
			 
		j=(j+1)%divisor;
	}while(j!=i);
	
	return j;//ɢ�б����� 
}

template<class T>
void hashTable<T>::insert(const T& x)//���� 
{
	int i=search(x);
	
	if(table[i]==-1||table[i]!=x)//��λ��Ϊ�ջ�ɢ�б����� 
	{
		table[i]=x;
		cout<<i<<endl;
	}
	else //Ԫ���Ѵ��� 
		cout<<"Existed"<<endl;
}

template<class T>
void hashTable<T>::find(const T& x)const//���� 
{
	int i=search(x);
	
	if(table[i]==-1||table[i]!=x)//Ԫ�ز����� 
		cout<<-1<<endl;
	
	else
		cout<<i<<endl;
}

template<class T>
void hashTable<T>::erase(const T& x)//ɾ�� 
{
	int i=search(x);
	
	if(table[i]==-1||table[i]!=x)//Ԫ�ز����� 
		cout<<"Not Found"<<endl;
	
	else
	{
		int j=(i+1)%divisor;
		int move=i;
		int count=0;//����Ԫ���ƶ����� 
		table[i]=-1;//ɾ��Ԫ�� 
		
		while(j!=i&&table[j]!=-1)//����ɾ��Ԫ�ػ�������Ͱʱֹͣѭ�� 
		{
			if(move<j)//δ�ɻ� 
			{
				if(table[j]%divisor<=move||table[j]%divisor>j)
				{
					table[move]=table[j];//�ƶ�Ԫ�� 
					table[j]=-1;
					move=j;
					count++;
				}
			}
			else//�γɻ� 
			{
				if(table[j]%divisor<=move&&table[j]%divisor>j)
				{
					table[move]=table[j];
					table[j]=-1;
					move=j;
					count++;
				}
			}
			j=(j+1)%divisor;
		}
		cout<<count<<endl;
	}
}

int main()
{
	int D,m;//�������������� 
	
	cin>>D>>m;
	hashTable<int> h(D);
	
	for(int i=0;i<m;i++)
	{
		int opt,x;//�������ͣ������� 
		
		cin>>opt>>x;
		switch(opt)
		{
			case 0://���� 
				h.insert(x);
				break;
			case 1://���� 
				h.find(x);
				break;
			case 2://ɾ�� 
				h.erase(x);
				break;
			default:
				break;
		}
	}
	return 0;
}
