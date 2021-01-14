#include<iostream>
using namespace std;

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
	linkedBinaryTree(){root=NULL;}
	~linkedBinaryTree(){erase();}
	
	void postOrder(void(*theVisit)(binaryTreeNode<E>*)){visit=theVisit;postOrder(root);}//������� 	
	void postOrderOutput(){postOrder(output);cout<<endl;}//���������� 
	void erase(){postOrder(dispose);root=NULL;}//ɾ�� 
	binaryTreeNode<E>* createTree(int preOrder[],int inOrder[],int preBegin,int preEnd,int inBegin,int inEnd);//����ǰ��������� 
private:
	binaryTreeNode<E> *root;//���ڵ�	
	
	static void (*visit)(binaryTreeNode<E>*);
	static void postOrder(binaryTreeNode<E> *t);//������� 
	static void dispose(binaryTreeNode<E> *t){delete t;}//ɾ�� 
	static void output(binaryTreeNode<E> *t){cout<<t->element<<" ";}//��� 
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
binaryTreeNode<E>* linkedBinaryTree<E>::createTree(int preOrder[],int inOrder[],int preBegin,int preEnd,int inBegin,int inEnd)//���� 
{
	binaryTreeNode<E> *t=new binaryTreeNode<E>(preOrder[preBegin]);//�����ĸ��ڵ� 
	
	if(preBegin==preEnd&&inBegin==inEnd)//ֻ��һ���ڵ� 
	{
		root=t;
		return t;
	}
	
	int i=inBegin;
	
	for(;i<inEnd;i++)//������������Ѱ�Ҹ��ڵ� 
		if(inOrder[i]==preOrder[preBegin])
			break;
	
	if(i-inBegin)//���������У����ڵ�֮ǰ��Ԫ������������ 
		t->leftChild=createTree(preOrder,inOrder,preBegin+1,preBegin+i-inBegin,inBegin,i-1);//�ݹ鴴�������� 
	
	if(inEnd-i)//������ 
		t->rightChild=createTree(preOrder,inOrder,preBegin+i-inBegin+1,preEnd,i+1,inEnd);
	
	root=t;
	return t;
}

int main()
{
	int n; 
	linkedBinaryTree<int> l;
	
	cin>>n;
	int preOrder[n],inOrder[n];//ǰ����������� 
	
	for(int i=0;i<n;i++)
		cin>>preOrder[i];
	
	for(int i=0;i<n;i++)
		cin>>inOrder[i];
	
	l.createTree(preOrder,inOrder,0,n-1,0,n-1);
	l.postOrderOutput();
	return 0;
}
