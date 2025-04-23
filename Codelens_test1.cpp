#include<bits/stdc++.h>

using namespace std;

// Merges two sorted subarrays into a single sorted subarray
void merge(int a[],int begin,int mid,int end){
	// Calculate subarray sizes
	int subarr1=mid-begin+1;
	int subarr2=end-mid;
	// Create temporary arrays
	int sub1[subarr1];
	int sub2[subarr2];
	// Copy data to temporary arrays
	for(int i=0;i<subarr1;i++){
		sub1[i]=a[begin+i];
	}
	for(int i=0;i<subarr2;i++){
		sub2[i]=a[mid+1+i];
	}
	// Initial indexes of subarrays and merged array
	int j=0;
	int k=0;
	int main=begin;
	// Merge the temporary arrays back into the original array
	while(j<subarr1 && k<subarr2){
		if(sub1[j]<sub2[k]){
			a[main]=sub1[j];
			j++;
		}
		else {
			a[main]=sub2[k];
			k++;
		}
		main++;
	}
	// Copy any remaining elements from sub1
	while(j<subarr1){
		a[main]=sub1[j];
		j++;
		main++;
	}
	// Copy any remaining elements from sub2
	while(k<subarr2){
		a[main]=sub2[k];
		k++;
		main++;
	}	
}

// Recursive function to sort the array using merge sort
void mergeSort(int a[] , int begin,int end){
	if(begin>=end)
		return;
	// Calculate middle index
	int mid=begin + (end-begin)/2;
	// Recursively sort the two halves
	mergeSort(a,begin,mid);
	mergeSort(a,mid+1,end);
	// Merge the sorted halves
	merge(a,begin,mid,end);
}
int main(){

	int a[]={54,26,93,17,77,31,44,55,20,85};
	int length=sizeof(a)/sizeof(a[0]);
	// Sort the array using merge sort
	mergeSort(a,0,length-1);
	// Print the sorted array
	for(int i=0;i<length;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	cout<<"Enter the element to search"<<endl;
	int x;
	cin>>x;
	// Perform binary search on the sorted array
	int left=0;
	int right=length-1;
	while(left<=right){
		// Calculate middle index
		int middle=left +(right-left)/2;
		if(a[middle]==x){
			cout<<"Element is present at index "<<middle<<endl;
			return 0;}
		else if(a[middle]<x)
			left=middle+1;
		else
			right=middle-1;
	}
	cout<<"-1"<<endl; // Element not found
	return 0;
}