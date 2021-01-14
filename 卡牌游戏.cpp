#include<iostream>
using namespace std;

template<class T>
class arrayQueue//ѭ�������� 
{
public:
	arrayQueue(int initialCapacity=10);
	~arrayQueue(){delete[]queue;}
	
	void push(const T& theElement);//���뵽��β 
	void pop();//ɾ������Ԫ�� 
	int size()const{return (arrayLength+queueBack-queueFront)%arrayLength;}//��ȡ���г��� 
	T& front()const{return queue[(queueFront+1)%arrayLength];}//��ȡ����Ԫ�� 
private:
	int queueFront;//ָ�����Ԫ����ʱ�����һ�� 
	int queueBack;//ָ���βԪ�� 
	int arrayLength;//�������� 
	T *queue;//ָ����е����� 
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)//���캯�� 
{
	arrayLength=initialCapacity;
	queue=new T[arrayLength];
	queueFront=queueBack=0;//��1��ʼ���Ԫ�� 
}

template<class T>
void arrayQueue<T>::push(const T& theElement)//���� 
{
	if(queueFront==(queueBack+1)%arrayLength)//�����������������鳤�� 
	{
		T *newQueue=new T[arrayLength*2];
		int start=(queueFront+1)%arrayLength;//ָ�����Ԫ�� 
		
		if(start<2)//δ�γɻ� 
		{ 
			for(int i=start;i<=queueBack;i++)
				newQueue[i]=queue[i];
		} 
		else//�γɻ����ֿ����� 
		{
			int j=0;//��¼newQueue������Ԫ�ص�λ�� 
			
			for(int i=start;i<arrayLength;i++)
			{
				newQueue[j]=queue[i];
				j++;
			}
			for(int i=0;i<=queueBack;i++)
			{
				newQueue[j]=queue[i];
				j++;
			}
		}
		queueFront=arrayLength*2-1;//�������0��ʼ���Ԫ�� 
		queueBack=arrayLength-2; 
		arrayLength*=2;
		delete[]queue;
		queue=newQueue;
	}
	
	queueBack=(queueBack+1)%arrayLength;
	queue[queueBack]=theElement;
}

template<class T>
void arrayQueue<T>::pop()//ɾ�� 
{
	queueFront=(queueFront+1)%arrayLength; 
	queue[queueFront].~T();
}

int main()
{
	int n;
	arrayQueue<int> q;
	
	cin>>n;
	for(int i=0;i<n;i++)
		q.push(i+1);//��1-n������� 
		
	while(q.size()>=2)//������������ʱ���в��� 
	{
		q.pop();//�ӵ���һ���� 
		
		int x=q.front();//��ȡ�µĵ�һ���Ƶ�ֵ 
		//���µĵ�һ���Ʒŵ���� 
		q.pop(); 
		q.push(x);
	}
	cout<<q.front()<<endl;//������һ���� 
	q.pop();//��ն��� 
	return 0;
}
