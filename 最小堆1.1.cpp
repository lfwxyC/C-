#include<iostream>
using namespace std;

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
class minHeap//С���� 
{
public:
	minHeap(int initialCapacity=10);
	~minHeap() {delete[]heap;}

	bool empty() { return heapSize == 0; }//�ж϶��Ƿ�Ϊ�� 
	int size()const { return heapSize; }//��ȡ�ѵĴ�С 
	T& top()const { return heap[1]; }//��ȡ�ѵĸ��ڵ� 
	void push(const T& theElement);//���� 
	void pop();//ɾ���ѵĸ��ڵ� 
	void initialize(int theSize);//��ʼ�� 
	void deactiveArray() { heap = NULL; }
private:
	T* heap;//����ָ�� 
	int arrayLength;//�������� 
	int heapSize;//�Ѵ�С 
};

template<class T>
minHeap<T>::minHeap(int initialCapacity)//���캯�� 
{
	arrayLength =initialCapacity;
	heap = new T[arrayLength];
	heapSize = 0;
}

template<class T>
void minHeap<T>::push(const T& theElement)//���� 
{
	if (heapSize == arrayLength - 1)//�������� 
	{
		changeLength1D(heap, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;//����Ԫ������λ�� 

	while (currentNode != 1 && theElement < heap[currentNode / 2])//�ж��Ƿ���Բ��� 
	{
		heap[currentNode] = heap[currentNode / 2];//���ڵ����� 
		currentNode /= 2;//currentNode�������ڵ� 
	}
	heap[currentNode] = theElement;//����Ԫ�� 
}

template<class T>
void minHeap<T>::pop()//ɾ�� 
{
	heap[1].~T();//ɾ�����ڵ� 

	T lastElement = heap[heapSize--];//���һ��Ԫ�� 
	int currentNode = 1;//���һ��Ԫ������λ�� 
	int child = 2;

	while (child <= heapSize)//�ж��ܷ���� 
	{
		if (child<heapSize && heap[child]>heap[child + 1])//lastElement���С�ĺ��ӱȽ� 
		{
			child++;
		}
		if (lastElement <= heap[child])//���Է��룬ֹͣѭ�� 
		{
			break;
		}
		heap[currentNode] = heap[child];//��С�������� 
		currentNode = child;//currentNode�Ƶ���С��������λ�� 
		child *= 2;
	}
	heap[currentNode] = lastElement;//����lastElement 
}

template<class T>
void minHeap<T>::initialize(int theSize)//��ʼ�� 
{
	delete[]heap;//ɾ������ԭ��Ԫ�� 
	heap = new T[theSize+1];//��1��ʼ���Ԫ�� 
	heapSize = theSize;
	arrayLength=theSize+1;

	for (int i = 1; i <= theSize; i++)//����ѵ�Ԫ�� 
	{
		cin >> heap[i];
	}

	for (int root = heapSize / 2; root >= 1; root--)//��ӵ��Ҷ�ӵĽڵ㿪ʼ��ʼ�� 
	{
		T rootElement = heap[root];//�����ĸ��ڵ� 
		int child = root * 2;

		while (child <= heapSize)//�жϸ��ڵ��Ƿ���Ҫ�ƶ� 
		{
			if (child<heapSize && heap[child]>heap[child + 1])//Ѱ�ҽ�С���ӵ�λ�� 
			{
				child++;
			}
			if (rootElement <= heap[child])//�����ƶ���ֹͣѭ�� 
			{
				break;
			}
			heap[child / 2] = heap[child];//��С�������� 
			child *= 2;//���±Ƚ� 
		}
		heap[child / 2] = rootElement;//����rootElement 
	}
}

template<class T>
void heapSort(int n)//������ 
{
	minHeap<T> heap;
	heap.initialize(n);

	for (int i = 0; i < n; i++)
	{
		cout << heap.top() << " ";//���ڵ�Ϊ��СԪ�� 
		heap.pop();
	}
	cout << endl;
	heap.deactiveArray();
}

int main()
{
	int n, m; 

	cin >> n;//��Ԫ�ظ��� 
	minHeap<long long> heap;

	heap.initialize(n);
	cout << heap.top() << endl;
	cin >> m;//���������� 

	for (int i = 0; i < m; i++)
	{
		int opt;

		cin >> opt;
		switch (opt)
		{
		case 1://���� 
		{
			int num;

			cin >> num;
			heap.push(num);
			cout << heap.top() << endl;
			break;
		}
		case 2://ɾ�� 
		{
			heap.pop();
			cout << heap.top() << endl;
			break;
		}
		case 3://���� 
		{
			int n;

			cin >> n;
			heapSort<long long>(n);
			break;
		}
		default:
			break;
		}
	}
	return 0;
}
