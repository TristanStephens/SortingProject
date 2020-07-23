//Lab 3: Algorithm Sort
//Tristan Stephens
//November 17, 2018

#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

//function templates
void selectionSort(vector<int>& a);
void mergeSort(vector<int>& a);
void innerSort(vector<int>& left, vector<int>& right, vector<int>& a);
void quickSort(vector<int>& a, int left, int right);
void quickSwap(vector<int>& a, int x, int y);
void heapSort(vector<int>& a);
void heapSwap(vector<int>& a, int i, int j);
void buildHeap(vector<int>& a);
void percHeap(vector<int>& a, int heapSize, int nextNode);

int main()
{
	vector<int> arr; //vector to be sorted
	int arrStart = 0; //beginning of array
	int maxSize = 500; //maximum number of items in array

	//random int generator to fill array
	mt19937 gen;
	uniform_int_distribution<unsigned int> rdm(1, 200);

	for (int i = arrStart; i <= maxSize; i++) {
		int b = rdm(gen);
		arr.push_back(b);
	}

	//copy randomly created vector to be used over four tests
	vector<int> selectionArr = arr;
	vector<int> mergeArr = arr;
	vector<int> quickArr = arr;
	vector<int> heapArr = arr;


	//timers return in milliseconds how long it roughly takes for each sort
	cout << "Computing sorts: selection, merge, quick and heap" << endl;

	cout << "Start selection sort" << endl;
	auto start = chrono::steady_clock::now();
	selectionSort(selectionArr);
	auto end = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	cout << "Start merge sort" << endl;
	auto start2 = chrono::steady_clock::now();
	mergeSort(mergeArr);
	auto end2 = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(end2 - start2).count() << endl;

	cout << "Start quick sort" << endl;
	auto start3 = chrono::steady_clock::now();
	quickSort(quickArr, arrStart, maxSize - 1);
	auto end3 = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(end3 - start3).count() << endl;

	cout << "Start heap sort" << endl;
	auto start4 = chrono::steady_clock::now();
	heapSort(heapArr);
	auto end4 = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(end4 - start4).count() << endl;
}

//simple selection sort
void selectionSort(vector<int>& a)
{
	int i;
	int j;
	int temp;

	for (i = 0; i < a.size(); i++)
	{
		for (j = i + 1; j < a.size(); j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

//merge sort function
void mergeSort(vector<int>& a)
{
	if (a.size() <= 1)
		return;

	int mid = a.size() / 2;
	vector<int> left;
	vector<int> right;

	for (int j = 0; j < mid; j++)
		left.push_back(a[j]);
	for (int j = 0; j < (a.size()) - mid; j++)
		right.push_back(a[mid + j]);

	mergeSort(left);
	mergeSort(right);
	innerSort(left, right, a);
}

//support function for merge sort
void innerSort(vector<int>& left, vector<int>& right, vector<int>& a)
{
	int numLeft = left.size();
	int numRight = right.size();
	int i = 0;
	int j = 0;
	int k = 0;

	while (j < numLeft && k < numRight)
	{
		if (left[j] < right[k])
		{
			a[i] = left[j];
			j++;
		}
		else
		{
			a[i] = right[k];
			k++;
		}

		i++;
	}
	while (j < numLeft)
	{
		a[i] = left[j];
		j++; i++;
	}
	while (k < numRight)
	{
		a[i] = right[k];
		k++; i++;
	}
}

//quick sort function
void quickSort(vector<int>& a, int left, int right)
{
	int i;
	int j;
	int mid;
	int pivot;

	i = left;
	j = right;
	mid = left + (right - left) / 2;
	pivot = a[mid];

	while (i < right || j > left) {
		while (a[i] < pivot)
			i++;
		while (a[j] > pivot)
			j--;

		if (i <= j)
		{
			quickSwap(a, i, j);
			i++;
			j--;
		}
		else
		{
			if (i < right)
				quickSort(a, i, right);
			if (j > left)
				quickSort(a, left, j);
			return;
		}
	}
}

//support function for quicksort
void quickSwap(vector<int>& a, int x, int y)
{
	int temp = a[x];
	a[x] = a[y];
	a[y] = temp;
}

//heap sort function
void heapSort(vector<int>& a)
{
	buildHeap(a);
	for (int i = a.size() - 1; i > 0; --i)
	{
		heapSwap(a, i, 0);
		percHeap(a, i, 0);
	}
}

//support function for heap
void heapSwap(vector<int>& a, int i, int j)
{
	if (i == j)
		return;

	int temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

//support function for heap
void buildHeap(vector<int>& a)
{
	for (int i = a.size() - 1; i >= 0; --i)
	{
		percHeap(a, a.size(), i);
	}
}

//support function for heap
void percHeap(vector<int>& a, int heapSize, int nextNode)
{
	int i;
	int j;

	j = nextNode;
	do
	{
		i = j;
		if (((2 * i + 1) < heapSize) && a[j] < a[2 * i + 1])
			j = 2 * i + 1;
		if (((2 * i + 2) < heapSize) && a[j] < a[2 * i + 2])
			j = 2 * i + 2;

		heapSwap(a, i, j);
	} while (i != j);
}