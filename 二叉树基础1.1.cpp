#include<iostream>
using namespace std;

template<class T>
class arrayQueue//ѭ�������� 
{
public:
	arrayQueue(int initialCapacity=10);
	~arrayQueue(){delete[]queue;}
	
	bool empty(){return queueFront==queueBack;}
	void push(const T& theElement);//���뵽��β 
	void pop();//ɾ������Ԫ�� 
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

template<class T>
struct binaryTreeNode//�������ڵ� 
{
	T element;//��ֵ 
	binaryTreeNode<T> *leftChild,*rightChild;//���Һ��� 
	
	//���캯�� 
	binaryTreeNode(){leftChild=rightChild=NULL;}
	binaryTreeNode(const T& theElement)
	{
		element=theElement;
		leftChild=rightChild=NULL;
	}
	binaryTreeNode(const T& theElement,binaryTreeNode<T> *theLeftChild,binaryTreeNode<T> *theRightChild)
	{
		element=theElement;
		leftChild=theLeftChild;
		rightChild=theRightChild;
	}
};

template<class E>
class linkedBinaryTree//������ 
{
public:
	linkedBinaryTree(){root=NULL;treeSize=0;}
	~linkedBinaryTree(){erase();}
	
	void postOrder(void(*theVisit)(binaryTreeNode<E>*)){visit=theVisit;postOrder(root);}//������� 
	void levelOrder();//��α������ 
	void erase(){postOrder(dispose);root=NULL;}//ɾ�� 
	void createTree();//������ 
	void size();//�����������С 
	void height();//����������߶� 
private:
	binaryTreeNode<E> *root;//���ڵ� 
	int treeSize;//�ڵ���� 
	int *sizeArray;//��Ÿ�������С 
	int *heightArray;//��Ÿ������߶� 
	
	static void (*visit)(binaryTreeNode<E>*);
	static void postOrder(binaryTreeNode<E> *t);//������� 
	static void dispose(binaryTreeNode<E> *t){delete t;}//ɾ�� 
	static int size(binaryTreeNode<E> *t);//����������С 
	static int height(binaryTreeNode<E> *t);//���������߶� 
};

template<class E>
void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)//������� 
{
	if(t!=NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedBinaryTree<E>::visit(t);
	}
}

template<class E>
void linkedBinaryTree<E>::levelOrder()//��α������ 
{
	arrayQueue<binaryTreeNode<E>*> q;//��Žڵ� 
	binaryTreeNode<E> *t=root;
	
	while(t!=NULL)
	{
		cout<<t->element<<" ";//����ڵ� 
		
		if(t->leftChild!=NULL)
		{
			q.push(t->leftChild);
		}
		if(t->rightChild!=NULL)
		{
			q.push(t->rightChild);
		}
		
		t=q.front();
		
		if(q.empty())
		{
			break;
		}
		q.pop();
	}
	cout<<endl;
}

template<class E>
void linkedBinaryTree<E>::createTree()//������ 
{
	int n;//�ڵ���� 
	
	cin>>n;
	root=new binaryTreeNode<E>(1);//���ڵ�Ϊ1 
	binaryTreeNode<E>* a[n*2];//����Ŵ�Žڵ� 
	a[0]=root;//���ڵ�������� 
	treeSize++;
	
	for(int i=0;i<n;i++)
	{
		E left,right;//���Һ��ӵ���ֵ 
		cin>>left>>right;
		
		binaryTreeNode<E> *t=a[i];
		
		if(left!=-1)
		{
			binaryTreeNode<E> *leftChild=new binaryTreeNode<E>(left);
			
			t->leftChild=leftChild;
			a[left-1]=leftChild;
			treeSize++;
		}
		if(right!=-1)
		{
			binaryTreeNode<E> *rightChild=new binaryTreeNode<E>(right);
			
			t->rightChild=rightChild;
			a[right-1]=rightChild;
			treeSize++;
		}
	}
}

template<class E>
void linkedBinaryTree<E>::size()//�����������С 
{
	sizeArray=new int[treeSize];
	arrayQueue<binaryTreeNode<E>*> q;
	binaryTreeNode<E> *t=root;
	
	while(t!=NULL)
	{
		sizeArray[t->element-1]=size(t);//�����Ըýڵ�Ϊ����������С�������Ŷ�Ӧ������λ�� 
	
		if(t->leftChild!=NULL)
		{
			q.push(t->leftChild);
		}
		if(t->rightChild!=NULL)
		{
			q.push(t->rightChild);
		}
		
		t=q.front();
		
		if(q.empty())
		{
			break;
		}
		q.pop();
	}
	
	for(int i=0;i<treeSize;i++)//����������������С 
	{
		cout<<sizeArray[i]<<" ";
	}
	cout<<endl;
	delete[]sizeArray;
}

template<class E>
int linkedBinaryTree<E>::size(binaryTreeNode<E> *t)//�ݹ�����������С 
{
	if(t==NULL)//û�нڵ� 
	{
		return 0;
	}
	return size(t->leftChild)+size(t->rightChild)+1;//���Ӹ���+�Һ��Ӹ���+���ڵ� 
}

template<class E>
void linkedBinaryTree<E>::height()//����������߶� 
{
	heightArray=new int[treeSize];
	arrayQueue<binaryTreeNode<E>*> q;
	binaryTreeNode<E> *t=root;
	
	while(t!=NULL)
	{
		heightArray[t->element-1]=height(t);
	
		if(t->leftChild!=NULL)
		{
			q.push(t->leftChild);
		}
		if(t->rightChild!=NULL)
		{
			q.push(t->rightChild);
		}
		
		t=q.front();
		
		if(q.empty())
		{
			break;
		}
		q.pop();
	}
	
	for(int i=0;i<treeSize;i++)
	{
		cout<<heightArray[i]<<" ";
	}
	cout<<endl;
	delete[]heightArray;
}

template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)//���������߶� 
{
	if(t==NULL)//û�нڵ� 
	{
		return 0;
	}
	
	int hl=height(t->leftChild);//�������߶� 
	int hr=height(t->rightChild);//�������߶� 
	
	if(hl>hr)
	{
		return ++hl;
	}
	else
	{
		return ++hr;
	}
}

int main()
{
	linkedBinaryTree<int> l;
	
	l.createTree();
	l.levelOrder();
	l.size();
	l.height();
	return 0;
}
