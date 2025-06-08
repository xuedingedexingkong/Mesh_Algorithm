#pragma
#include<vector>

//Quicksort
template<typename data>
int SortSolver(std::vector<data>& nums, int left, int right) {
	int middle = (left + right) / 2;
	int middleValue = nums[middle];

	int j = left;
	std::swap(nums[middle], nums[left]);
	for (int i = left + 1; i < nums.size(); i++) {
		if (nums[i] < middleValue) {
			j++;
			std::swap(nums[i], nums[j]);
		}
	}

	std::swap(nums[left], nums[j]);
	return j;
}

template<typename data>
std::vector<data> QuickSort(std::vector<data>& nums, int left, int right) {

	if (left < right) {
		int k = SortSolver(nums, left, right);
		QuickSort(nums, k + 1, right);
		QuickSort(nums, left, k);
	}
}