#ifndef MERGESORT_H
#define MERGESORT_H

int count1 = 0, count2 = 0; //count1:比较次数, count2:赋值次数 
template <typename T> void Merge(T *arr, int size)
{
    T temp[size]; 
    int b = 0;  
    int mid = size / 2;   
    int i = 0, j = mid;    
 
    while (i < mid && j < size)
    {
        count1 += 2;
		if (arr[i] <= arr[j]){
			count1++;
			temp[b++] = arr[i++];
			count2++;
		}   
        else{
            count1++;
			temp[b++] = arr[j++];
			count2++;        	
		}

    }
	count1++;
    while(i < mid){
    	count1++;
        temp[b++] = arr[i++];
		count2++;    	
	}              
	count1++;
    while(j < size)
    {
        count1++;
		temp[b++] = arr[j++];
		count2++;   	
	}
	count1++;
    for (int i = 0; i < size; i++)  {
    	count1++;
		arr[i] = temp[i];
		count2++;
	}  
	count1++;
}

template <typename T> void MergeSort_rec(T *arr, int size) //归并排序（递归版） 
{

	if (size <= 1){
		count1++;
		return;
	}    
    if (size > 1)
    {
        count1++;
		MergeSort(arr, size / 2);    
        MergeSort(arr + size / 2, size - size / 2);    
        Merge(arr, size);    
    }
}

template<typename T> void MergeSort_iter(T *arr, int size)  //归并排序（迭代） 
{
    T *a = arr;
    T *b = new T[size];
    for (int seg = 1; seg < size; seg += seg) 
	{
        count1++; 
		for (int start = 0; start < size; start += seg + seg) 
		{
            count1++;
			int left = start, mid = min(start + seg, size), right = min(start + seg + seg, size);
            int k = left;
            int left1 = left, right1 = mid;
            int left2 = mid, right2 = right;
            while (left1 < right1 && left2 < right2){
            	count1+=2;
                b[k++] = a[left1] < a[left2] ? a[left1++] : a[left2++]; 
				count2++;           	
			}
			count1++;
            while (left1 < right1)
            {
            	count1++;
            	b[k++] = a[left1++];
            	count2++;
			}
            count1++;    
            while (left2 < right2)
            {
            	count1++;
            	b[k++] = a[left2++];
            	count2++;
			}
			count1++;
                
        }
        count1++;
        T *temp = a;
        a = b;
        b = temp;
        count2 += 3;
    }
    if (a != arr) {
    	count1++;
        for (int i = 0; i < size; i++){
        	count1++;
        	b[i] = a[i];
        	count2++;
		}
		count1++;
        b = a;
    }
    delete[] b;
}
#endif

