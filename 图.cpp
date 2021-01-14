#include<queue>
#include<iostream>
using namespace std;

template<class T>
struct chainNode//������ 
{
	T element;//Ԫ��ֵ 
	chainNode *next;//ָ����һ����� 
	
	chainNode(const T& element,chainNode<T> *next)//���캯�� 
	{
		this->element=element;
		this->next=next;
	}
};

class linkedGraph;

template<class T>
class graphChain//ͼ���� 
{
public:
	graphChain(int initialCapacity=10);
	~graphChain();
	
	void insert(const T& theElement);//���� 
	void erase(int theIndex);//������ɾ�� 
	int indexOf(const T& theElement);//��ȡ���� 
	int size()const{return listSize;}//��ȡ������ 
	void eraseElement(int theVertex);//��Ԫ��ֵɾ�� 
	
	friend linkedGraph;
protected:
	chainNode<T> *firstNode;//ͷ��� 
	int listSize;//������ 
};

template<class T>
graphChain<T>::graphChain(int initialCapacity)//���캯�� 
{
	firstNode=NULL;
	listSize=0;
}

template<class T>
graphChain<T>::~graphChain()//ɾ�������е����н�� 
{
	while(firstNode!=NULL)
	{
		chainNode<T> *nextNode=firstNode->next;
		delete firstNode;
		firstNode=nextNode;
	}
}

template<class T>
void graphChain<T>::insert(const T& theElement)//���� 
{
	chainNode<T> *p=firstNode,*pp=NULL;
	
	//��������� 
	while(p!=NULL&&theElement>p->element)
	{
		pp=p;
		p=p->next;
	}
	
	if(pp!=NULL)
		pp->next=new chainNode<T>(theElement,pp->next);
	
	else//����ͷ�ڵ� 
		firstNode=new chainNode<T>(theElement,firstNode);
	
	listSize++;
}

template<class T>
void graphChain<T>::erase(int theIndex)//������ɾ�� 
{
	chainNode<T> *deleteNode;
	
	if(theIndex==0)//ɾ��ͷ��� 
	{
		deleteNode=firstNode;
		firstNode=firstNode->next;
	}
	else//ɾ������λ�õĽ�� 
	{
		chainNode<T> *p=firstNode;
		for(int i=0;i<theIndex-1;i++)
			p=p->next;
		
		deleteNode=p->next;
		p->next=p->next->next;
	}
	delete deleteNode;
	listSize--;
}

template<class T>
int graphChain<T>::indexOf(const T& theElement)//��ȡ���� 
{
	int index=0;
	chainNode<T> *p=firstNode;
	
	while(p!=NULL&&p->element!=theElement)
	{
		p=p->next;
		index++;
	}
	if(p==NULL)//��δ�ҵ��򷵻�-1 
		return -1;
	else
		return index;
}

template<class T>
void graphChain<T>::eraseElement(int theVertex)//��Ԫ��ֵɾ�� 
{
	int index=indexOf(theVertex);
	erase(index);
}

template<class T>
class arrayQueue//ѭ�������� 
{
public:
	arrayQueue(int initialCapacity=10);
	~arrayQueue(){delete[]queue;}
	
	bool empty()const{return queueFront==queueBack;}//�ж϶����Ƿ�Ϊ�� 
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
			int j=0;//newQueue�е�Ԫ�ش�0��ʼ��� 
			
			for(int i=start;i<=queueBack;i++)
			{
				newQueue[j]=queue[i];
				j++;
			}
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

class edge//�� 
{
public:
	edge(int i,int j);
	
	int vertex1()const{return v1;}//��ȡ����1 
	int vertex2()const{return v2;}//��ȡ����2 
private:
	int v1;//����1 
	int v2;//����2 
};

edge::edge(int i,int j)//���캯�� 
{
	v1=i;
	v2=j;
}

class linkedGraph//����Ǽ�Ȩͼ 
{
protected:
	int n;//������ 
	int e;//���� 
	graphChain<int> *aList;//�ڽ����� 
public:
	linkedGraph(int numberOfVertices=0);
	~linkedGraph();
	
	void insertEdge(edge *theEdge);//����� 
	void eraseEdge(int i,int j);//ɾ���� 
	int numberOfVertices()const{return n;}//��ȡ������� 
	
	void bfs(int v,int reach[],int label);//bfs
	void dfs(int v,int reach[],int label);//dfs
	void rDfs(int v);//dfs�ĵݹ鷽�� 
	
	void findPath(int theSource,int theDestination);//Ѱ�����·�� 
	int labelComponents();//������� 
	void outputComponents();//�������������ͨ��ͼ����С��ı��
	void outputBfs(int v);//���bfs���г��Ⱥ��ֵ�����С������ 
	void outputDfs(int v);//���dfs���г��Ⱥ��ֵ�����С������ 
	
	class myIterator//������ 
	{
	public:
		myIterator(chainNode<int> *theNode)//���캯�� 
		{
			node=theNode;
		}	
		
		int next()//������һ������ 
		{
			if(node!=NULL)
			{
				int theElement=node->element;
				node=node->next;
				
				return theElement;
			}
			
			else//������ 
				return 0;
		}
	protected:
		chainNode<int> *node;
	};
	myIterator* iterator(int theVertex){return new myIterator(aList[theVertex].firstNode);}
private:
	int *reach;//��Ƕ����Ƿ񱻷��� 
	int label;//�������� 
	int length;//���г��� 
	int *c;//��ǹ��� 
	int *bfsArray;//bfs���� 
	int *dfsArray;//dfs���� 
};

linkedGraph::linkedGraph(int numberOfVertices)//���캯�� 
{
	n=numberOfVertices;
	e=0;
	
	aList=new graphChain<int>[n+1];
	c=new int[n+1];
	bfsArray=new int[n+1];
	dfsArray=new int[n+1];
	reach=new int[n+1];
}

linkedGraph::~linkedGraph()//�������� 
{
	delete[]aList;
	delete[]c;
	delete[]bfsArray;
	delete[]dfsArray;
	delete[]reach;
}

void linkedGraph::insertEdge(edge *theEdge)//����� 
{
	int v1=theEdge->vertex1();
	int v2=theEdge->vertex2();
	
	if(aList[v1].indexOf(v2)==-1)
	{
		aList[v1].insert(v2);
		aList[v2].insert(v1);
		e++;
	}
}

void linkedGraph::eraseEdge(int i,int j)//ɾ���� 
{
	if(i>=1&&j>=1&&i<=n&&j<=n)
	{
		aList[i].eraseElement(j);
		aList[j].eraseElement(i);
		e--;
	}
}

void linkedGraph::bfs(int v,int reach[],int label)//bfs
{
	arrayQueue<int> q;
	
	reach[v]=label;//���ﶥ��v 
	length=1;//��ʼ���г��� 
	bfsArray[1]=v; 
	q.push(v);
	
	while(!q.empty())
	{
		int w=q.front();
		q.pop();
		
		for(chainNode<int>* u=aList[w].firstNode;u!=NULL;u=u->next)
			if(reach[u->element]==0)//����uδ������ 
			{
				q.push(u->element);
				reach[u->element]=label;
				length++;
				bfsArray[length]=u->element;
			}
	}
}

void linkedGraph::dfs(int v,int reach[],int label)//dfs
{
	this->reach=reach;
	this->label=label;
	length=0;
	rDfs(v);
}

void linkedGraph::rDfs(int v)//dfs�ĵݹ�ʵ�� 
{
	reach[v]=label;
	length++;
	dfsArray[length]=v;
	myIterator *iv=iterator(v);
	int u;
	
	while((u=iv->next())!=0)
		if(reach[u]==0)
			rDfs(u);      
	
	delete iv;
}

void linkedGraph::findPath(int theSource,int theDestination)//Ѱ�����·�� 
{
	arrayQueue<int> q;
	int *size=new int[n+1];//bfs��δ�С 
	int index=2,count=0;
	bool find=false;//����Ƿ��ҵ� 
	
	for(int i=1;i<=n;i++)
		reach[i]=0;
	
	reach[theSource]=label;
	q.push(theSource);
	size[1]=1;//��һ��ֻ��theSourceһ������ 
	
	for(int i=2;i<=n;i++)
		size[i]=0;
	
	while(!q.empty())
	{
		int w=q.front();
		q.pop();
		count++;//��¼ÿһ���ѷ��ʵĶ������ 
		
		if(w==theDestination)//�ҵ��յ� 
		{
			cout<<index-2<<endl;
			find=true;
			break;
		}
		
		for(chainNode<int>* u=aList[w].firstNode;u!=NULL;u=u->next)
			if(reach[u->element]==0)
			{
				q.push(u->element);
				reach[u->element]=label;
				size[index]++;//����ÿһ���ȫ��������� 
			}
		
		if(count==size[index-1])//������һ�� 
		{
			count=0;
			index++;
		}
	}
	
	if(!find)//·�������� 
		cout<<-1<<endl;
}

int linkedGraph::labelComponents()//��ǹ��� 
{
	int n=numberOfVertices();
	
	for(int i=1;i<=n;i++)
		c[i]=0;
	
	label=0;
	
	for(int i=1;i<=n;i++)
		if(c[i]==0)
		{
			label++;
			bfs(i,c,label);
		}
	
	return label;
}

void linkedGraph::outputComponents()//�������������ͨ��ͼ����С��ı��
{
	int count=1;
	
	for(int i=1;i<=n;i++)
		if(c[i]==count)
		{
			cout<<i<<" ";
			if(count==label) 
			{
				cout<<endl;
				break;
			}
			count++;
		}
}

void linkedGraph::outputBfs(int v)//���bfs���г��Ⱥ��ֵ�����С������ 
{
	for(int i=1;i<=n;i++)
		reach[i]=0;
	
	bfs(v,reach,1);
	cout<<length<<endl;//���bfs���г��� 
	
	for(int i=1;i<=length;i++)
		cout<<bfsArray[i]<<" ";//���bfs���� 
	
	cout<<endl;
}

void linkedGraph::outputDfs(int v)//���dfs���г��Ⱥ��ֵ�����С������ 
{
	for(int i=0;i<=n;i++)
		reach[i]=0;
	
	dfs(v,reach,1);
	cout<<length<<endl;
	
	for(int i=1;i<=length;i++)
		cout<<dfsArray[i]<<" ";
	
	cout<<endl;
}

int main()
{
	int n,m,s,t;//���������������������㣬�յ� 
	
	cin>>n>>m>>s>>t;
	linkedGraph graph(n);
	
	for(int i=0;i<m;i++)
	{
		int opt,u,v;
		
		cin>>opt>>u>>v;
		edge *theEdge=new edge(u,v);
		
		if(opt==0)//����� 
		{
			graph.insertEdge(theEdge);
		}
		else//ɾ���� 
		{
			graph.eraseEdge(u,v);
		}
		delete theEdge;
	}
	
	cout<<graph.labelComponents()<<endl;
	graph.outputComponents();
	graph.outputDfs(s);
	graph.outputBfs(t);
	graph.findPath(s,t);
	return 0;
}
