#ifndef HH_CHALLENGE_2_HH
#define HH_CHALLENGE_2_HH

#include <iostream>
#include <vector>

namespace Challenge
{
  int sort_and_find_median(
    const std::vector<int>::iterator &first,
    const std::vector<int>::iterator &last 
  );


  namespace recursive
  {
    int find_pivot(
      const std::vector<int>::iterator &first,
      const std::vector<int>::iterator &last
    );

    int worstCaseLinearTimeSelection(
      const std::vector<int>::iterator &first,
      const std::vector<int>::iterator &last,
      const std::vector<int>::iterator &rank
    );

    inline int inVectorRanking(
      std::vector<int> &input,
      const size_t rank
    )
    {
      if (rank < input.size())
      {
        return worstCaseLinearTimeSelection(
          input.begin(), input.end(), input.begin() + rank
        );
      }
      else
      {
        //fprintf(stderr, "ERROR: in function \"inVectorRanking\", rank must be between 0 and input.size()");
        //exit(EXIT_FAILURE);
        throw std::invalid_argument("ERROR: in function \"inVectorRanking\", rank must be between 0 and input.size()");
      }
    }

  }

  namespace non_recursive
  {

    int find_pivot(
      const std::vector<int>::iterator &first,
      const std::vector<int>::iterator &last
    );


    int worstCaseLinearTimeSelection(
      const std::vector<int>::iterator &first,
      const std::vector<int>::iterator &last,
      const std::vector<int>::iterator &rank
    );


    inline int inVectorRanking(
      std::vector<int> &input,
      const size_t rank
    )
    {
      if (rank < input.size())
      {
        return worstCaseLinearTimeSelection(
          input.begin(), input.end(), input.begin() + rank
        );
      }
      else
      {
        //fprintf(stderr, "ERROR: in function \"inVectorRanking\", rank must be between 0 and input.size()");
        //exit(EXIT_FAILURE);
        throw std::invalid_argument("ERROR: in function \"inVectorRanking\", rank must be between 0 and input.size()");
      }
    }

  }


}

#endif