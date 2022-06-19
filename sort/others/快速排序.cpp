template <typename T> void Qsort(T *a, int size)	// 快速排序
{
quick(a,0,size-1);	
}
template <typename T> void quick(T *a,int low,int high)
{
        if(low > high)
		{
		
            return;
        }
		m++;
        //第一个优化：当low,high之间的数据个数少于某一个范围，可以调用直接插入排序
        if(high-low+1 < 100)
		{
            insertsort2(a,low,high);
            return;
        }
        m++;
        //第二次优化，取三个数中位数,这样的基准就不会出现极端情况
        mid(a,low,high);
        int par = parttion(a,low,high);
        quick(a,low,par-1);
        quick(a,par+1,high);
}
template <typename T> void insertsort2(T *a,int low,int high)
{
        for(int i = low+1;i <= high;i++)
		 {
            int tmp = a[i];
            n++; 
            int j = i-1;
            for (;j >= low;j--)
			{
				m++;
                if (a[j] > tmp) 
				{
                    a[j+1] = a[j];
                    n++;
                }
				else
				{
                    break;
                }
            }
            a[j+1] = tmp;
            n++;
        }
    }
template <typename T> void swap(T *a,int low,int high)
{
        int tmp = a[low];
        a[low] = a[high];
        a[high] = tmp;
        n+=3;
    }
template <typename T> void mid(T *a,int low,int high)
{
        m=m+3;
        int mid = (low+high)/2;
        if(a[low] >= a[high]) 
		{
            swap(a,low,high);
        }
        if(a[low] <= a[mid])
		{
            swap(a,low,mid);
        }
        if(a[mid] >= a[high]) 
		{
            swap(a,low,mid);
        }
    }

template <typename T> int parttion(T *a,int start,int end)
{
        int tmp = a[start];
        n++;
        while(start < end){
            while(start < end && a[end] >= tmp)
			{
				m++;
                end--;
        }
            m++; 
            if (start >= end){
                break;
            }else{
                a[start] = a[end];
                n++;
            }
            while(start < end && a[start] <= tmp){
            	m++;
                start++;
            }
            
            m++;
            if (start > end){
                
                break;
            }else{
                a[end] = a[start];
                n++;
            }
        }
        a[start] = tmp;
        n++;
        return start;
}


