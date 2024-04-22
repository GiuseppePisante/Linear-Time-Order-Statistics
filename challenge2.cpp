
#include <iostream>
#include <vector>
#include <algorithm>

std::ostream &operator<<(std::ostream &os, const std::vector<int> vec)
{
    os << "[ ";
    for (const auto &val : vec)
        os << val << " ";
    os << "]";

    return os;
}

int find_medians(std::vector<int> &input, const size_t first, const int last)
{
    if (last != 1)
    {

        for (auto j = first + 1; j < first + last; ++j)
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
        if (last == 5)
        {
            return input[2 + first];
        }
        if (last == 4)
        {
            return input[first + last / 2 - 1];
        }
        else if (last == 3)
        {
            return input[first + 1];
        }
        else
        {
            return input[first + last / 2 - 1];
        }
    }
    else
        return input[first];
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
    if (input.size() != 5)
    {
        medians.push_back(find_medians(input, input.size() - last, last));
    }

    if (medians.size() != 1)
        pivot = find_pivot(medians);

    else
        pivot = medians.at(0);

    return pivot;
}

std::vector<int> partition_vector(std::vector<int> input, int &rank, int pivot)
{
    std::vector<int> partitioned;
    int k = 0;
    int tmp = 0;

    for (int j = 0; j < input.size() - tmp; j++)
    {
        if (input[j] == pivot)
        {
            input[j] = input[input.size() - tmp - 1];
            input[input.size() - tmp - 1] = pivot;
            tmp++;
        }
        if (input[j] < pivot)
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
    for (int j = 0; j < tmp; j++)
    {
        int key = input[j + k];
        input[j + k] = input[input.size() - j - 1];
        input[input.size() - j - 1] = key;
    }
    k += tmp;

    if (k < rank)
    {
        std::vector<int>::const_iterator start = input.begin() + k;
        std::vector<int>::const_iterator stop = input.end();
        rank -= k;

        std::vector<int> partitioned(start, stop);
        return partitioned;
    }
    else if (k > rank)
    {
        std::vector<int>::const_iterator start = input.begin();
        std::vector<int>::const_iterator stop = input.begin() + k - 1;

        std::vector<int> partitioned(start, stop);
        return partitioned;
    }
    else
    {
        partitioned.push_back(pivot);
        return partitioned;
    }
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

    std::vector<int> input = {97, 34, 16, 13, 25, 57, 88,
                              15, 23, 98, 29, 77, 14, 58, 83, 49, 60, 40, 52, 65,
                              31, 55, 2, 33, 30, 35, 35, 35, 35, 35, 35, 42, 20, 8, 75};

    for (int rank = 1; rank < input.size(); rank++)
    {
        int value = linearTimeOrderStatistics(input, rank);
        std::cout << "Valore " << value << std::endl;

        int arr[] = {97, 34, 16, 13, 25, 57, 88,
                     15, 23, 98, 29, 77, 14, 58, 83, 49, 60, 40, 52, 65,
                     31, 55, 2, 33, 30, 35, 35, 35, 35, 35, 35, 42, 20, 8, 75};
        int n = sizeof(arr) / sizeof(arr[0]);
        std::sort(arr, arr + n);
        std::cout << "Valore esatto: " << arr[rank - 1] << std::endl;
    }
    return 0;
}
