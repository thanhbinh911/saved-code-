#include<stdio.h>
#include<stdlib.h>
#include<math.h>



int isbeautifulSubset(int*subSet, int subSet_size, int k) {
	//if the subset has only 1 element then the for loop won't run
	// with this condition , the empty subset is also qualified
	for(int i=0; i<subSet_size; i++) {
		for(int j=i+1; j<subSet_size; j++) {
			if(abs(subSet[i]-subSet[j])==k)
				return 0;
		}
	}
	return 1;
}


void solution(int*nums, int numsSize, int k, int*subSet, int subSet_size, int *cnt, int idx) {
	//backtrack phase
	if(idx==numsSize) {
		if(isbeautifulSubset(subSet, subSet_size,k))
			(*cnt)++;
		return;
	}
	solution(nums, numsSize, k, subSet, subSet_size, cnt, idx+1);
	subSet[subSet_size]=nums[idx];
	solution(nums, numsSize, k, subSet,subSet_size+1,cnt,idx+1);
}


int beautifulSubsets(int* nums, int numsSize, int k) {
	int*subSet=(int*)malloc(sizeof(int)*numsSize);
	int cnt=0;
	solution(nums, numsSize, k, subSet, 0, &cnt, 0);
	free(subSet);
	return cnt-1;
}



int main () {
	int numsSize;
	scanf("%d", &numsSize);
	int nums[numsSize];
	for(int i=0; i<numsSize; i++)
		scanf("%d", &nums[i]);
	int k;
	scanf("%d", &k);
	int cnt=beautifulSubsets(nums, numsSize, k);
	printf("%d", cnt);
}