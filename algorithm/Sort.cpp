/************************************************************
Copyright:  wust
Author: sean
Date:  2016-03-01
Description:  algorithm of sort
**************************************************************/
#include <iostream>
using namespace std;


template <class T>
class Sort
{
public:
	Sort() {};
	~Sort() {};
	static void print(T *SL, int size);
	static T* quicksort(T *SL, int low, int high);
	static int partion(T *SL, int low, int high);
	static T* bubblesort(T *SL, int size);
	static T* selectsort(T *SL, int size);
	static T* insertsort(T *SL, int size);
	static T* shellsort(T *SL, int size);

private:

};

template <class T>
void Sort<T>::print(T * SL, int size)
{
	for (int i = 0; i < size; i++) {
		cout << SL[i] << "    ";
	}
	cout << endl;
}

template <class T>
T * Sort<T>::quicksort(T *SL, int low, int high)
{
	//每次确定一位准确的排序位置，并从该位划分成两部分，再次选择排序
	if (low < high) {
		int pivot = partion(SL, low, high);
		quicksort(SL, low, pivot - 1);
		quicksort(SL, pivot + 1, high);
	}
	return SL;
}

template <class T>
int Sort<T>::partion(T *SL, int low, int high)
{
	T pivot = SL[low];
	while (low < high) {
		while (low < high && SL[high] > pivot) {
			high--;
		}
		SL[low] = SL[high];
		while (low < high && SL[low] < pivot) {
			low++;
		}
		SL[high] = SL[low];
	}
	SL[low] = pivot;
	return low;
}

template<class T>
T * Sort<T>::bubblesort(T * SL, int size)
{
	//遍历n*(n-i),交换相邻值
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (SL[j] > SL[j+1]) {
				T tmp = SL[j];
				SL[j] = SL[j+1];
				SL[j+1] = tmp;
			}
		}
	}
	return SL;
}

template<class T>
T * Sort<T>::selectsort(T * SL, int size)
{
	//第n次循环选择最小的一个，插入第n位
	for (int i = 0; i < size - 1; i++) {
		int k = i;
		for (int j = i + 1; j < size; j++) {
			if (SL[k] > SL[j]) {
				k = j;
			}
		}
		if (i != k) {
			T tmp = SL[i];
			SL[i] = SL[k];
			SL[k] = tmp;
		}
	}
	return SL;
}

template<class T>
T * Sort<T>::insertsort(T * SL, int size)
{
	//将数组一个个添加进有序的数据集
	int j;
	for (int i = 1; i < size; i++) {
		T pivot = SL[i];
		for (j = i - 1; j >= 0 && SL[j] > pivot; j--) {
			SL[j + 1] = SL[j];
		}
		SL[j+1] = pivot;
	}
	return SL;
}

template<class T>
T * Sort<T>::shellsort(T * SL, int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < size; i++) {
			for (int j = i - gap; j >= 0 && SL[j]>SL[j+gap]; j -= gap) {
				T tmp = SL[j];
				SL[j] = SL[j+gap];
				SL[j+gap] = tmp;
			}
		}
	}
	return SL;
}



int main() {
	int s[] = { 1,3,5,7,9,2,4,6,8,0 };
	//Sort<int>::quicksort(s, 0, sizeof(s)/sizeof(int)-1);
	//Sort<int>::bubblesort(s, sizeof(s) / sizeof(int));
	//Sort<int>::selectsort(s, sizeof(s) / sizeof(int));
	//Sort<int>::insertsort(s, sizeof(s) / sizeof(int));
	Sort<int>::shellsort(s, sizeof(s) / sizeof(int));
	Sort<int>::print(s, sizeof(s) / sizeof(int));
	return 0;
}