#include <iostream>

int arr[10] = {3, 1, 4, 6, 2, 0, 9, 7, 8, 5};

int DividePartition(int start, int end)
{
  int pivot = arr[(start+end)/2];
  while(start <= end)
  {
    while(arr[start] < pivot) start++;
    while(arr[end] > pivot) end--;
    if(start <= end)
    {
      std::swap(arr[start], arr[end]);
      start++;
      end--;
    }
  }

  return start;
}

void QuickSort(int start, int end)
{
  int part2 = DividePartition(start, end);
  if(start < part2 - 1)
  {
    QuickSort(start, part2 - 1);
  }
  if(part2 < end)
  {
    QuickSort(part2, end);
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
  QuickSort(0, sizeof(arr)/sizeof(int) - 1);
  PrintArr();

  return 0;
}