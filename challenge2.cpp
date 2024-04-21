
#include <iostream>
#include <vector>

std::vector<int> partition_vector(std::vector<int> input, int rank, int pivot)
{
    std::vector<int> partitioned;
    int k = 0;

    for (int j = 0; j < input.size(); j++)
    {
        if (input[j] <= pivot)
        {
            if (j == k)
            {
                k++;
            }
            else
            {
                int key = input[k];
                input[k] = input[j];
                input[j] = key;
                k++;
            }
        }
    }
    if (k < rank)
    {
        std::vector<int>::const_iterator start = input.begin() + k + 1;
        std::vector<int>::const_iterator stop = input.end();

        std::vector<int> partitioned(start, stop);
        return partitioned;
    }
    else if (k > rank)
    {
        std::vector<int>::const_iterator start = input.begin();
        std::vector<int>::const_iterator stop = input.begin() + k;

        std::vector<int> partitioned(start, stop);
        return partitioned;
    }
    else
    {
        partitioned.push_back(pivot);
        return partitioned;
    }
}

int find_medians(std::vector<int> &input, const size_t first, const int size)
{
    for (auto j = first + 1; j < first + size; ++j)
    {
        int key = input[j];
        int i = j - 1;

        while (i >= first && input[i] > key)
        {
            input[i + 1] = input[i];
            i--;
        }
        input[i + 1] = key;
    }
    return input[first + (size / 2)];
}

int find_pivot(std::vector<int> input)
{
    int last = input.size() % 5;
    std::vector<int> medians;
    int pivot;

    for (int j = 0; j < input.size() - last; j += 5)
    {
        medians.push_back(find_medians(input, j, 5));
    }
    medians.push_back(find_medians(input, input.size() - last, last));

    if (medians.size() != 1)
        pivot = find_pivot(medians);

    else
        pivot = medians.at(0);

    return pivot;
}

int linearTimeOrderStatistics(std::vector<int> input, int rank)
{
    int pivot = find_pivot(input);
    input = partition_vector(input, rank, pivot);
    int value;

    if (input.size() != 1)
    {
        value = linearTimeOrderStatistics(input, rank);
    }
    else
        value = input.at(0);
    return value;
}

int main()
{
    std::vector<int> input = {97, 2, 4, 55, 60, 70};

    int value = linearTimeOrderStatistics(input, 2);
    std::cout << "Valore " << value << std::endl;

    return 0;
}
