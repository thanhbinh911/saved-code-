#include<stdio.h>
#include<stdbool.h>

//INSERTION SORT
void swap(int*a, int*b) {
	int temp=*a;
	*a=*b;
	*b=temp;
}

void insertion_sort(int arr[], int n) {
	for(int i=1; i<=n-1; i++) {
		int temp=arr[i];
		int pos=i-1;
		while(pos>=0 && temp<arr[pos]) {
			// whenever encounter a element that greater than 
			// the cur element, we shift it to right 
			arr[pos+1]=arr[pos];
			pos--;
		}
		arr[pos+1]=temp; 
	}
}


//SELECTION SORT 


void selection_sort(int* arr, int n) {
	for(int i=0; i<n-1; i++) {
		int min=i;
		for(int j=i+1; j<n; j++) {
			if(arr[j]<arr[min])
				min=j;
		}
		if(min!=i)
			swap(&arr[i], &arr[min]);
	}
}

void bubble_sort(int arr[], int n) {
	for(int i=n-1; i>=1; i--) {
		bool flag=true;
		for(int j=0; j<i; j++) {
			if(arr[j]>arr[j+1]) {
				swap(&arr[j], &arr[j+1]);
				flag=false;
			}
		}
		if(flag)
			return;	
	}
}


//int find_pivot(int arr[], int l,int r) {
//	int pivot=l;
//	int value=arr[r];
//	for(int i=l; i<r; i++) {
//		if(arr[i]<value) {
//			swap(&arr[i], &arr[pivot]);
//			pivot++;
//		}
//	}
//	swap(&arr[r], &arr[pivot]);
//	return pivot;
//}


int partition(int arr[], int left, int right) {
	int i=left, j=right+1;
	int pivot=arr[left];
	while(1) {
		i++;
		while(i<=right && arr[i]<pivot) 
			i++;
		j--;
		while(j>left && arr[j]>pivot)
			j--;
		if(i>=j)
			break;
		swap(&arr[i],&arr[j]);
	}
	swap(&arr[j],&arr[left]);
	return j;
}




void quick_sort(int arr[], int l, int r) {
	if(l<r) {
//		int pivot=find_pivot(arr,l,r);
		int pivot=partition(arr,l,r);
		quick_sort(arr,l,pivot-1);
		quick_sort(arr,pivot+1,r);
	}
}

void merge(int arr[], int l, int mid, int r) {
	int length1=mid-l+1;
	int length2=r-mid;
	int arr1[length1];
	int arr2[length2];
	for(int i=0; i<length1; i++)
		arr1[i]=arr[l+i];
	for(int i=0; i<length2; i++)
		arr2[i]=arr[mid+1+i];
	int i=0,j=0;
	while(i<length1 && j<length2) {
		if(arr1[i]<=arr2[j]) 
			arr[l++]=arr1[i++];
		else 
			arr[l++]=arr2[j++];
	}
	while(i<length1) 
		arr[l++]=arr1[i++];
	while(j<length2)
		arr[l++]=arr2[j++];
}

void merge_sort(int arr[], int l, int r) {
	if(l<r) {
		int mid=(l+r)/2;
		merge_sort(arr,l,mid);
		merge_sort(arr,mid+1,r);
		merge(arr,l,mid,r);
	}
}



void Heapify(int arr[],int idx, int n) {
	int largest=idx;
	int left_child=2*idx+1;
	int right_child=2*idx+2;
	if(left_child<n && arr[left_child]>arr[largest])
		largest=left_child;
	if(right_child<n && arr[right_child]>arr[largest])
		largest=right_child;
	if(largest!=idx) {
		swap(&arr[largest], &arr[idx]);
		Heapify(arr, largest,n);
	}
}

void build_heap(int arr[], int n) {
	for(int i=(n/2-1); i>=0; i--) 
		Heapify(arr,i,n);
}

void heap_sort(int arr[], int n) {
	build_heap(arr,n);
	for(int i=n-1; i>=1; i--) {
		swap(&arr[0], &arr[i]);
		Heapify(arr,0,i);
	}
}

int main () {
	int n;
	scanf("%d", &n);
	int arr[n];
	for(int i=0; i<n; i++)
		scanf("%d", &arr[i]);
//	insertion_sort(arr,n);
//	selection_sort(arr,n);
//	bubble_sort(arr, n);
//	merge_sort(arr,0,n-1);
//	quick_sort(arr,0,n-1);
	heap_sort(arr,n);
	for(int i=0; i<n; i++)
		printf("%d ", arr[i]);
}