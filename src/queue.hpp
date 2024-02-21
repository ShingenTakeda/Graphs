#pragma once
#include <vector>

template <typename T>
struct Queue
{
  Queue() {}
  ~Queue() {}

  void add(T data)
  {
    arr.insert(arr.begin(), data);
  }

  void pop()
  {
    if(arr.size() > 0)
    {
      arr.erase(arr.begin());
    }
  }

  int get_size()
  {
    return arr.size();
  }

  T get_element_at_index(unsigned int index)
  {
    return arr[index];
  }

  T get_data()
  {
    return arr.front();
  }

  private:
    std::vector<T> arr;
};
