#include "challenge2.hpp"

int Challenge::sort_and_find_median(
    const std::vector<int>::iterator &first,
    const std::vector<int>::iterator &last
)
{
  int size = std::distance(first, last);
  if (size > 1)
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
    return *(first + (size + 1) / 2 - 1);
  }
  else if(size == 1)
  {
    return *first; 
  }
  else
  {
    fprintf(stderr, "ERROR: in function \"sort_and_find_median\", \"last\" iterator must be greater than \"first\" iterator !\n");
    exit(EXIT_FAILURE);
  }
}


int Challenge::recursive::find_pivot(
  const std::vector<int>::iterator &first,
  const std::vector<int>::iterator &last
)
{ 
  int size = std::distance(first, last);
  if (size > 0)
  {
    int last_chunk_size = size % 5;
    const int size_medians = size / 5 + ((0 != last_chunk_size) ? 1 : 0);   //lol, yoda notation
    std::vector<int> medians(size_medians);
    std::vector<int>::iterator index = medians.begin();
    
    std::vector<int>::iterator j;
    for(j = first; j < last - last_chunk_size; j += 5)
    {
      *(index) = sort_and_find_median(j, j + 5);
      ++index;
    }
    if (last_chunk_size > 0)
    {
      *(index) = sort_and_find_median(j, j + last_chunk_size);
      ++index;
    }

    if(size_medians != 1)
      return find_pivot(medians.begin(), medians.end());
    else
      return medians.at(0);
  }
  else
  {
    fprintf(stderr, "ERROR: in function \"find_pivot\", \"last\" iterator must be greater than \"first\" iterator !\n");
    exit(EXIT_FAILURE);
  }
}


int Challenge::non_recursive::find_pivot(
  const std::vector<int>::iterator &first,
  const std::vector<int>::iterator &last
)
{
  int size = std::distance(first, last);
  if (size > 0)
  { 
    std::vector<int> *temp1 = new std::vector<int>(size / 5 + 5);
    std::vector<int> *temp2 = new std::vector<int>(size / 5 + 5);


    std::vector<int>::iterator start = first;
    std::vector<int>::iterator stop = last;


    while (size > 1)
    {
      const int last_chunk_size = size % 5;
      size = size / 5 + ((0 != last_chunk_size) ? 1 : 0);

      //temp1->resize(size);
      std::vector<int>::iterator index = temp1->begin();
      std::vector<int>::iterator j;

      for (j = start; j < stop - last_chunk_size; j += 5)
      { 
        *(index) = sort_and_find_median(j, j + 5);
        ++index;
      }
      if (last_chunk_size > 0)
      {
        *(index) = sort_and_find_median(j, stop);
        ++index;
      }

      std::swap(temp1, temp2);

      start = temp2->begin();
      stop = start + size;
    }

    int result = *(start);

    delete temp1;
    delete temp2;

    return result;
  }
  else
  {
    fprintf(stderr, "ERROR: in function \"find_pivot\", \"last\" iterator must be greater than \"first\" iterator !\n");
    exit(EXIT_FAILURE);
  }
}



int Challenge::recursive::worstCaseLinearTimeSelection(
  const std::vector<int>::iterator &first,
  const std::vector<int>::iterator &last,
  const std::vector<int>::iterator &rank
)
{
  int size = std::distance(first, last);

  if (size > 0)
  {
  
    auto k = first;
    int pivot = find_pivot(first, last);
    for(auto j = first; j < last; ++j)
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

    if (k < rank + 1)
      return worstCaseLinearTimeSelection(k, last, rank);
    if (k > rank + 1)
      return worstCaseLinearTimeSelection(first, k - 1, rank);
    else
      return pivot;

  }
  else
  {
    fprintf(stderr, "ERROR: in function \"partition_vector\", \"last\" iterator must be greater than \"first\" iterator !\n");
    exit(EXIT_FAILURE);
  }
}



int Challenge::non_recursive::worstCaseLinearTimeSelection(
  const std::vector<int>::iterator &first,
  const std::vector<int>::iterator &last,
  const std::vector<int>::iterator &rank
)
{
  int size = std::distance(first, last);

  if (size > 0)
  {
    std::vector<int>::iterator start = first;
    std::vector<int>::iterator stop = last;
    std::vector<int>::iterator k;
    int pivot;

    do
    {
      pivot = find_pivot(start, stop);
      k = start;
    
      for(auto j = start; j < stop; ++j)
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

      if (k < rank + 1)
        start = k;
      else if(k > rank + 1)
        stop = k - 1;

    } while (k != rank + 1);
    
    return pivot;
    
  }
  else
  {
    fprintf(stderr, "ERROR: in function \"partition_vector\", \"last\" iterator must be greater than \"first\" iterator !\n");
    exit(EXIT_FAILURE);
  }
}
