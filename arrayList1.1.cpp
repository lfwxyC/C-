#include<iostream>
using namespace std;

struct Student
{
	string name;//���� 
	string phone;//�绰����
	int class_id;//�༶
	int dormitory;//����
};

template<class T>
void changeLength(T*& element,int oldLength,int newLength)//�������鳤�� 
{
	T *temp=new T[newLength];//�����³��ȵ����� 
	
	for(int i=0;i<oldLength;i++)//�Ѿ������Ԫ�ظ��Ƶ�������
		temp[i]=element[i]; 
	delete []element;//�ͷž�����Ŀռ� 
	element=temp;
}

template<class T>
class arrayList
{
public:
	arrayList(int initialCapacity=5);
	~arrayList(){delete []element;}
	 
	int indexOf(string name1)const;//����������ȡ���� 
	void insert(T stu1);//���� 
	void erase(string name1);//��������ɾ�� 
	void edit_phone(string name1,string phone1);//�༭�绰 
	void edit_cid(string name1,int cid);//�༭�༶
	void edit_dorm(string name1,int dorm);//�༭���� 
	void search(string name1);//������������ 
	void output(int cid);//����ð༶�����г�Ա������ŵ����ֵ 
private:
	T *element; 
	int listSize;//���Ա���
	int arrayLength;//�������� 
};

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
	arrayLength=initialCapacity;
	element=new T[arrayLength];
	listSize=0;//��ʼʱû��Ԫ�� 
}

template<class T>
int arrayList<T>::indexOf(string name1)const
{
	for(int i=0;i<listSize;i++)
		if(element[i].name==name1)
			return i;
	return -1;//û���ҵ�Ԫ�� 
} 

template<class T>
void arrayList<T>::insert(T stu1)
{
	if(listSize==arrayLength)//��������ʱ�������� 
	{
		changeLength<struct Student>(element,arrayLength,arrayLength*2);
		arrayLength*=2;
	}
	element[listSize]=stu1;
	listSize++;//���Ա���+1 
}

template<class T>
void arrayList<T>::erase(string name1)
{
	int theIndex=indexOf(name1);
	for(int i=theIndex;i<listSize-1;i++)
		element[i]=element[i+1];
	element[--listSize].~T();//���Ա���-1	
}

template<class T>
void arrayList<T>::edit_phone(string name1,string phone1)
{
	int theIndex=indexOf(name1);//���������������� 
	element[theIndex].phone=phone1;
}

template<class T>
void arrayList<T>::edit_cid(string name1,int cid)
{
	int theIndex=indexOf(name1);
	element[theIndex].class_id=cid;
}
template<class T>
void arrayList<T>::edit_dorm(string name1,int dorm)
{
	int theIndex=indexOf(name1);
	element[theIndex].dormitory=dorm;
}

template<class T>
void arrayList<T>::search(string name1)
{
	int theIndex=indexOf(name1);
	if(theIndex==-1)//δ�ҵ�Ԫ�� 
		cout<<"0"<<endl;
	else//�ҵ�Ԫ�� 
		cout<<"1"<<endl;
}

template<class T>
void arrayList<T>::output(int cid)
{
	int sum=0;
	
	for(int i=0;i<listSize;i++)
		if(element[i].class_id==cid)//�ҵ�ָ���༶ 
			sum^=element[i].dormitory;//�������� 
	cout<<sum<<endl;
}

template<class T>
void addressBook(arrayList<T> &a)//��ͨѶ¼���й��� 
{
	int m;//������ 
		
	cin>>m;
	switch(m)
	{
		case 0://���� 
			{
			struct Student stu1;
			
			cin>>stu1.name>>stu1.phone>>stu1.class_id>>stu1.dormitory;
			a.insert(stu1);
			break;
			}
		case 1://ɾ�� 
			{
				string name1;
			
			cin>>name1;
			a.erase(name1);
			break;
			}
		case 2://�༭ 
			{
			string name1;
			int k;//�༭��Ŀ 
			
			cin>>name1>>k;
			switch(k)
			{
				case 1://�༭�绰 
					{
					string phone1;
					
					cin>>phone1;
					a.edit_phone(name1,phone1);
					break;
					}					
				case 2://�༭�༶ 
					{
					int cid;
					
					cin>>cid;
					a.edit_cid(name1,cid);
					break;
					}					
				case 3://�༭���� 
					{
					int dorm;
					
					cin>>dorm;
					a.edit_dorm(name1,dorm); 
					break;
					}					
			}
			break;
			}			
		case 3://���� 
			{
			string name1;
			
			cin>>name1;
			a.search(name1);
			break;
			}			
		case 4://������� 
			{
			int cid;
			
			cin>>cid;
			a.output(cid);
			break;
			}
	}
}

int main()
{
	int n;//������Ŀ 
	arrayList<struct Student> a;
	
	cin>>n;
	for(int i=0;i<n;i++)
		addressBook(a);
	return 0;
}
