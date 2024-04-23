#include <iostream>
#include <vector>

std::vector<int> partition_vector(std::vector<int> input, int &rank, int pivot)
{
    std::vector<int> partitioned;
    int k = 0;
    int tmp = 0;

    for (int j = 0; j < input.size()-tmp; j++)
    {
        if (input[j] < pivot)
        {
            if (j == k)
            {
                k++;
               // std::cout<<"incremento k: "<<input.at(j)<<std::endl;
            }
            else
            {
                int key = input[k];
                input[k] = input[j];
                input[j] = key;
                k++;
                //std::cout<<"incremento k: "<<input.at(j)<<std::endl;
            }
        }
        else if (input[j] == pivot)
        {
            input[j] = input[input.size() - tmp - 1];
            input[input.size() - tmp - 1] = pivot;
            tmp++;
            j--;
            std::cout<<"stampo tmp: "<<tmp<<std::endl;
        }
    }

    //std::cout<<"---------input--------"<<std::endl;
    

    for (int j = 0; j < tmp; j++)
    {
        int key = input[j + k];
        input[j + k] = input[input.size() - j - 1];
        input[input.size() - j - 1] = key;
    }
    k += tmp;
    std::cout<<"k:  ->"<<k<<std::endl;
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
std::ostream &operator<<(std::ostream &os, const std::vector<int> vec)
{
    os << "[ ";
    for (const auto &val : vec)
        os << val << " ";
    os << "]";

    return os;
}

int main()
{
    std::vector<int> input = {0,3,2,1,6,5,7,9,8,10,12,11,13,16,15,14,4};
    int rank = 6;

while(input.size() != 1){

    int pivot = find_pivot(input);
    input = partition_vector(input, rank, pivot);

    std::cout << pivot << std::endl;
    std::cout << input << std::endl;
}
/*
    pivot = find_pivot(input);
    std::cout << pivot << std::endl;
    input = partition_vector(input, rank, pivot);

    std::cout << input << std::endl;
    
    pivot = find_pivot(input);
    std::cout << pivot << std::endl;
    input = partition_vector(input, rank, pivot);

    std::cout << input << std::endl;

    pivot = find_pivot(input);
    std::cout << pivot << std::endl;
    input = partition_vector(input, rank, pivot);

    std::cout << input << std::endl;

    /*
        int value = linearTimeOrderStatistics(input, 2);
        std::cout << "Valore " << value << std::endl;
        */

    return 0;
}
