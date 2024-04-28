#include "challenge2.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

std::ostream &operator<<(std::ostream &os, const std::vector<int> vec)
{
  os<<"[ ";
  for(const auto &val : vec)
    os<<val<<" ";
  os<<"]";

  return os;
}

void do_tests(std::function<int(std::vector<int> &, const size_t)> func, std::vector<int> &input)
{
  std::vector<int> ordered_array = input;
  std::sort(ordered_array.begin(), ordered_array.end());

  for (size_t rank = 0; rank < input.size(); ++rank)
  {
    const int value = func(input, rank);
    //const int value = Challenge::inVectorRanking(input, rank);
    const int true_val = ordered_array[rank];

    std::cout<<"Rank = "<<rank;
    std::cout<<"\tExpected value: "<<true_val;
    std::cout<<"\tActual value:"<<value;
    std::cout<<"\t\tTest "<<((value == true_val) ? "PASSED" : "FAILED")<<std::endl;
  }
}

int main()
{ 
  
  std::vector<int> input = {97, 34, 16, 13, 25, 57, 88,
  15, 23, 98, 29, 77, 14, 58, 83, 49, 60, 40, 52, 65,
  31, 55, 2, 33, 30, 35, 42, 20, 8, 75};
  
  std::cout<<input<<std::endl;

  do_tests(Challenge::non_recursive::inVectorRanking, input);

  std::cout<<input<<std::endl;

  return 0;
}