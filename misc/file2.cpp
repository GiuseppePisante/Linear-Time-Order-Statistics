#include <iostream>
#include <vector>
#include <numeric>
#include <tuple>

int sort_and_find_median(
  std::vector<int>::iterator first,
  std::vector<int>::iterator last
);

int find_pivot(
  std::vector<int>::iterator start,
  std::vector<int>::iterator end
);

int partition_vector(
  std::vector<int>::iterator start,
  std::vector<int>::iterator end,
  const unsigned int rank
);


std::ostream &operator<<(std::ostream &os, const std::vector<int> vec)
{
  os<<"[ ";
  for(const auto &val : vec)
    os<<val<<" ";
  os<<"]";

  return os;
}

int main()
{   
  std::vector<int> input = {97, 34, 16, 13, 25, 57, 88,
  15, 23, 98, 29, 77, 14, 58, 83, 49, 60, 40, 52, 65,
  31, 55, 2, 33, 30, 35, 42, 20, 8, 75};

  std::cout<<partition_vector(input.begin(), input.end(), 5)<<std::endl;
  std::cout<<input<<std::endl;

  return 0;
}


int sort_and_find_median(
  std::vector<int>::iterator first,
  std::vector<int>::iterator last
)
{

  for(auto j = first; j != last; ++j)
  {
    int key = *j;
    auto i = j - 1;

    while(i >= first && *i > key)
    {
      *(i + 1) = *i;
      --i;
    }
    *(i + 1) = key;
  }
  return *(first + (std::distance(first, last) / 2));
}


int find_pivot(
  std::vector<int>::iterator start,
  std::vector<int>::iterator end
)
{
  int last_chunk_size = std::distance(start, end) % 5;
  std::vector<int> medians;
  
  std::vector<int>::iterator j;
  for(j = start; j < end - last_chunk_size; j += 5)
  {
    medians.push_back(sort_and_find_median(j, j + 5));
  }
  medians.push_back(sort_and_find_median(j, j + last_chunk_size));

  if(medians.size() != 1)
    return find_pivot(medians.begin(), medians.end());
  else
    return medians.at(0);
}


int partition_vector(
  std::vector<int>::iterator start,
  std::vector<int>::iterator end,
  const unsigned int rank
)
{
  auto k = start;
  int pivot = find_pivot(start, end);
  for(auto j = start; j < end; ++j)
  {
    if(*j <= pivot)
    {
      if(j == k)
      {
        ++k;
      }
      else
      {
        int key = *k;
        *k = *j;
        *j = key;
        ++k;
      }
    }
  }

  auto k_val = std::distance(start, k);
  std::cout<<k_val<<std::endl;
  if(k_val< rank)
    return partition_vector(k + 1, end, rank);

  else if(k_val > rank)
    return partition_vector(start, k, rank);

  else
    return pivot;
}
