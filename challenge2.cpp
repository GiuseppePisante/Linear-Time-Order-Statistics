
#include <iostream>
#include <vector>

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
        else if (input[j] == pivot)
        {
            input[j] = input[input.size() - tmp - 1];
            input[input.size() - tmp - 1] = pivot;
            tmp++;
            j--;
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
        std::vector<int>::const_iterator stop = input.begin() + k - tmp;

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

    std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                              11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
                              23, 24, 25, 26, 27, 28, 29};

    for (int rank = 1; rank <= input.size(); rank++)
    {
        int value = linearTimeOrderStatistics(input, rank);
        std::cout << "Valore " << value << std::endl;
    }
    return 0;
}
