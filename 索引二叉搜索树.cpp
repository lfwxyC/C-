#include<iostream>
using namespace std;

template<class T>
struct binaryTreeNode//�������ڵ� 
{
	T element;//��ֵ 
	int leftSize;//�Ըýڵ�Ϊ������������С 
	binaryTreeNode<T> *leftChild,*rightChild;//���Һ��� 
	
	//���캯�� 
	binaryTreeNode(){leftChild=rightChild=NULL;leftSize=0;}
	binaryTreeNode(const T& theElement)
	{
		element=theElement;
		leftChild=rightChild=NULL;
		leftSize=0;
	}
	binaryTreeNode(const T& theElement,binaryTreeNode<T> *theLeftChild,binaryTreeNode<T> *theRightChild)
	{
		element=theElement;
		leftChild=theLeftChild;
		rightChild=theRightChild;
		leftSize=0;
	}
};

template<class T>
class indexedBinarySearchTree//�������������� 
{
public:
	indexedBinarySearchTree(){root=NULL;treeSize=0;}
	~indexedBinarySearchTree(){eraseAll();}
	
	T* find(const T& theElement)const;//���� 
	void insert(const T& theElement);//���� 
	void erase(const T& theElement);//ɾ�� 
	void findIndex(int theIndex)const;//���������� 
	void eraseIndex(int theIndex);//������ɾ�� 
	
	void eraseAll(){postOrder(dispose);root=NULL;}
	void postOrder(void(*theVisit)(binaryTreeNode<T>*)){visit=theVisit;postOrder(root);}//������� 
private:
	binaryTreeNode<T> *root;//���ڵ� 
	int treeSize;//���Ĵ�С 
	
	static void (*visit)(binaryTreeNode<T>*);
	static void postOrder(binaryTreeNode<T> *t);//������� 
	static void dispose(binaryTreeNode<T> *t){delete t;}//ɾ�� 		
};

template<class T>
void (*indexedBinarySearchTree<T>::visit)(binaryTreeNode<T>*);

template<class T>
void indexedBinarySearchTree<T>::postOrder(binaryTreeNode<T> *t)//������� 
{
	if(t!=NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		indexedBinarySearchTree<T>::visit(t);
	}
}

template<class T>
T* indexedBinarySearchTree<T>::find(const T& theElement)const//���� 
{
	binaryTreeNode<T> *t=root;
	T value=0;//���ֵ 
	
	while(t!=NULL) 
	{
		value^=t->element;//�ͱȽ�Ԫ������� 
		
		if(t->element>theElement)//����Ԫ���������� 
		{
			t=t->leftChild;
		}
		else if(t->element<theElement)//����Ԫ���������� 
		{
			t=t->rightChild;
		}
		else//�ҵ� 
		{
			cout<<value<<endl;
			return &t->element;
		}
	}
	cout<<0<<endl;//δ�ҵ� 
	return NULL;
}

template<class T>
void indexedBinarySearchTree<T>::insert(const T& theElement)//���� 
{
	binaryTreeNode<T> *t=root;
	T value=0;//���ֵ 
	
	//����Ԫ���Ƿ���� 
	while(t!=NULL)
	{
		value^=t->element;//�ͱȽ�Ԫ������� 
		
		if(t->element>theElement)//Ԫ���������� 
		{
			t=t->leftChild;
		}
		else if(t->element<theElement)//Ԫ���������� 
		{
			t=t->rightChild;
		}
		else//Ԫ���Ѵ��� 
		{
			cout<<0<<endl;
			return;
		}
	}
	cout<<value<<endl;
	
	binaryTreeNode<T> *p=root,*pp=NULL;
	
	while(p!=NULL)
	{
		pp=p;
		
		if(p->element>theElement)//���뵽������ 
		{
			p=p->leftChild;
			pp->leftSize++;
		}
		else//���뵽������ 
		{
			p=p->rightChild;
		}
	}
	
	binaryTreeNode<T> *newNode=new binaryTreeNode<T>(theElement);//����Ԫ�� 
	
	if(root!=NULL)
	{
		if(pp->element>theElement)
		{
			pp->leftChild=newNode;
		}
		else
		{
			pp->rightChild=newNode;
		}
	}
	else//���뵽���ڵ� 
	{
		root=newNode;
	}
	treeSize++;
}

template<class T>
void indexedBinarySearchTree<T>::erase(const T& theElement)//ɾ�� 
{
	T *t=find(theElement);//����Ԫ���Ƿ���� 
	if(t==NULL)//������ 
	{
		return;
	}
	
	binaryTreeNode<T> *p=root,*pp=NULL;
	
	while(p!=NULL&&p->element!=theElement)
	{
		pp=p;
		
		if(p->element>theElement)//ɾ��Ԫ���������� 
		{
			p=p->leftChild;
			pp->leftSize--;
		}
		else//ɾ��Ԫ���������� 
		{
			p=p->rightChild;
		}
	}
	
	if(p->leftChild!=NULL&&p->rightChild!=NULL)//ɾ��Ԫ������������ 
	{
		binaryTreeNode<T> *s=p->rightChild,*ps=p;//�滻����������СԪ�� 
		
		while(s->leftChild!=NULL)//����ߵĽڵ���С 
		{
			ps=s;
			s->leftSize--;
			s=s->leftChild;
		}
		
		p->element=s->element;//����ɾ��Ԫ�ص�ֵ 
		p=s;//p�ƶ����滻�ڵ� 
		pp=ps;
	}
	
	binaryTreeNode<T> *c;
	
	//ֻ��һ������ 
	if(p->leftChild!=NULL)//ֻ�������� 
	{
		c=p->leftChild;
	}
	else//ֻ�������� 
	{
		c=p->rightChild;
	}
	
	if(p==root)//ɾ�����ڵ� 
	{
		root=c;
	}
	else//ɾ�������ڵ� 
	{
		if(p==pp->leftChild) 
		{
			pp->leftChild=c;
		}
		else 
		{
			pp->rightChild=c;
		}
	}
	treeSize--;
	delete p;
}

template<class T>
void indexedBinarySearchTree<T>::findIndex(int theIndex)const//���������� 
{
	theIndex--;//����=��Ŀ��������-1 
	binaryTreeNode<T> *t=root;
	T value=0;//���ֵ 
	
	while(t!=NULL)
	{
		value^=t->element;//�ͱȽ�Ԫ������� 
		
		if(t->leftSize>theIndex)//Ԫ���������� 
		{
			t=t->leftChild;
		}
		else if(t->leftSize<theIndex)//Ԫ���������� 
		{
			theIndex=theIndex-(t->leftSize+1);//�ı����� 
			t=t->rightChild;
		}
		else//�ҵ� 
		{
			cout<<value<<endl;
			return;
		}
	}
	cout<<0<<endl;//δ�ҵ� 
}

template<class T>
void indexedBinarySearchTree<T>::eraseIndex(int theIndex)//������ɾ�� 
{
	theIndex--;//����=��Ŀ��������-1 
	binaryTreeNode<T> *t=root;
	
	while(t!=NULL)
	{
		if(t->leftSize>theIndex)//Ԫ���������� 
		{
			t=t->leftChild;
		}
		else if(t->leftSize<theIndex)//Ԫ���������� 
		{
			theIndex=theIndex-(t->leftSize+1);//�ı����� 
			t=t->rightChild;
		}
		else//�ҵ� 
		{
			erase(t->element);//��Ԫ��ֵɾ�� 
			return;
		}
	}
	cout<<0<<endl;//δ�ҵ� 
}

int main()
{
	int m;//���������� 
	indexedBinarySearchTree<int> tree;
	
	cin>>m;
	for(int i=0;i<m;i++)
	{
		int a,b;
		
		cin>>a>>b;
		switch(a)
		{
			case 0://���� 
				tree.insert(b);
				break;
			case 1://���� 
				tree.find(b);
				break;
			case 2://ɾ�� 
				tree.erase(b);
				break;
			case 3://���������� 
				tree.findIndex(b);
				break;
			case 4://������ɾ�� 
				tree.eraseIndex(b);
				break;
		}
	}
	return 0;
}
