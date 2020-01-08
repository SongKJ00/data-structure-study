#include <iostream>

int arr[10] = {3, 1, 4, 6, 2, 0, 9, 7, 8, 5};
int tempArr[10];

void Merge(int start, int mid, int end)
{
  for(int i = start; i <= end; i++)
  {
    tempArr[i] = arr[i];
  }

  int part1 = start;
  int part2 = mid+1;
  int index = start;

  while(part1 <= mid && part2 <= end)
  {
    if(tempArr[part1] <= tempArr[part2])
    {
      arr[index] = tempArr[part1];
      part1++;
    }
    else
    {
      arr[index] = tempArr[part2];
      part2++;
    }
    index++;
  }

  for(int i = 0; i <= mid - part1; i++)
  {
    arr[index + i] = tempArr[part1+i];
  }
}

void MergeSort(int start, int end)
{
  if(start < end)
  {
    int mid = (start + end) / 2;
    MergeSort(start, mid);
    MergeSort(mid+1, end);
    Merge(start, mid, end);
  }
}

void PrintArr()
{
  for(int i : arr)
  {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main(void)
{
  PrintArr();
  MergeSort(0, sizeof(arr)/sizeof(int) - 1);
  PrintArr();
  return 0;
}