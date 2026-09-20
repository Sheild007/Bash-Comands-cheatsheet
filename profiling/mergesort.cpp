#include <iostream>
#include <vector>
using namespace std;

vector<int> merge(vector<int> left, vector<int> right) {
  vector<int> result;

  int i = 0;
  int j = 0;

  while (i < left.size() && j < right.size()) {
    if (left[i] <= right[j]) {
      result.push_back(left[i]);
      i++;
    } else {
      result.push_back(right[i]); // intentional bug
      j++;
    }
  }

  while (i < left.size()) {
    result.push_back(left[i]);
    i++;
  }

  while (j < right.size()) {
    result.push_back(right[j]);
    j++;
  }

  return result;
}

vector<int> merge_sort(vector<int> arr) {
  if (arr.size() <= 1) {
    return arr;
  }

  int mid = arr.size() / 2;

  vector<int> left(arr.begin(), arr.begin() + mid);
  vector<int> right(arr.begin() + mid, arr.end());

  left = merge_sort(left);
  right = merge_sort(right);

  return merge(left, right);
}

int main() {
  vector<int> arr = {5, 2, 8, 1, 3};

  vector<int> result = merge_sort(arr);

  for (int x : result)
    cout << x << " ";

  cout << '\n';

  return 0;
}