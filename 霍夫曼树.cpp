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
	linkedBinaryTree(){root=NULL;treeSize=0;}
	~linkedBinaryTree(){erase();}
	
	void erase(){postOrder(dispose);root=NULL;}//ɾ�� 
	void postOrder(void(*theVisit)(binaryTreeNode<E>*)){visit=theVisit;postOrder(root);}//�������
	void makeTree(const E&,linkedBinaryTree<E>&,linkedBinaryTree<E>&); 
private:
	binaryTreeNode<E> *root;//���ڵ� 
	int treeSize;//�ڵ���� 

	static void (*visit)(binaryTreeNode<E>*);
	static void postOrder(binaryTreeNode<E> *t);//������� 
	static void dispose(binaryTreeNode<E> *t){delete t;}//ɾ�� 
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
void linkedBinaryTree<E>::makeTree(const E& element,linkedBinaryTree<E>& left,linkedBinaryTree<E>& right)
{
	root=new binaryTreeNode<E>(element,left.root,right.root);
	treeSize=left.treeSize+right.treeSize+1;
	
	left.root=right.root=NULL;
	left.treeSize=right.treeSize=0;
}

template<class T>
void changeLength1D(T*& element, int oldLength, int newLength)//�������鳤�� 
{
	T* temp = new T[newLength];//�����³��ȵ����� 

	//copy(element + 1, element + oldLength, temp+1);
	for (int i = 1; i < oldLength; i++)//�Ѿ������Ԫ�ظ��Ƶ�������
		temp[i] = element[i];
	delete[]element;//�ͷž�����Ŀռ� 
	element = temp;
}

template<class T>
class minHeap
{
public:
	minHeap(int initialCapacity = 10);
	//~minHeap() { delete[]heap; }

	T& top()const { return heap[1]; }
	void push(const T& theElement);
	void pop();
	void initialize(T* theHeap, int theSize);
	void deactiveArray() { heap = NULL; }
private:
	T* heap;
	int arrayLength;
	int heapSize;
};

template<class T>
minHeap<T>::minHeap(int initialCapacity)
{
	arrayLength = initialCapacity+1;
	heap = new T[arrayLength];
	heapSize = 0;
}

template<class T>
void minHeap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1)
	{
		changeLength1D(heap, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;

	while (currentNode != 1 && theElement < heap[currentNode / 2])
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

template<class T>
void minHeap<T>::pop()
{
	heap[1].~T();

	T lastElement = heap[heapSize--];
	int currentNode = 1;
	int child = 2;

	while (child <= heapSize)
	{
		if (child<heapSize && heap[child]>heap[child + 1])
		{
			child++;
		}
		if (lastElement <= heap[child])
		{
			break;
		}
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<class T>
void minHeap<T>::initialize(T* theHeap, int theSize)
{
	delete[]heap;
	heap = theHeap;
	heapSize = theSize;

	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];
		int child = root * 2;

		while (child <= heapSize)
		{
			if (child<heapSize && heap[child]>heap[child + 1])
			{
				child++;
			}
			if (rootElement <= heap[child])
			{
				break;
			}
			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = rootElement;
	}
}

template<class T>
class huffmanNode
{
public:
	operator T()const{return weight;}
	friend void huffmanTree(int weight[],int n);

	linkedBinaryTree<T> *tree;
	T weight;			
};

void huffmanTree(int weight[],int n)
{
	huffmanNode<int> *hNode=new huffmanNode<int>[n+1];
	linkedBinaryTree<int> emptyTree;
	int length=0;
	
	for(int i=1;i<=n;i++)
	{
		hNode[i].weight=weight[i];
		hNode[i].tree=new linkedBinaryTree<int>;
		hNode[i].tree->makeTree(i,emptyTree,emptyTree);
	}
	
	minHeap<huffmanNode<int> > heap(1);
	heap.initialize(hNode,n);
	
	for(int i=1;i<n;i++)
	{
		huffmanNode<int> w,x,y;
		linkedBinaryTree<int> *z=new linkedBinaryTree<int>;
		
		x=heap.top();
		heap.pop();
		
		y=heap.top();
		heap.pop();
		
		z->makeTree(0,*x.tree,*y.tree);
		w.weight=x.weight+y.weight;
		length+=w.weight;
		w.tree=z;
		heap.push(w);
		
		delete x.tree;
		delete y.tree;
		delete z;
	}
	
	cout<<length<<endl;
	delete[]hNode;
}

int main()
{
	string str;
	int a[26];
	int n=0,count=1;
	
	cin>>str;
	for(int i=0;i<26;i++)
	{
		a[i]=0;
	}
	
	for(int i=0;i<str.size();i++)
	{
		int index=str[i]-'a';
		
		a[index]++;
		if(a[index]==1)
		{
			n++;
		}
	}
	
	int *b=new int[n+1];
	
	for(int i=0;i<26;i++)
	{
		if(a[i])
		{
			b[count]=a[i];
			count++;
		}
	}
	
	huffmanTree(b,n);
	return 0;
}
