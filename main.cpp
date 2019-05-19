#include "vector.h"
#include <vector>

int main()
{
    int pv = 0;
    int pc = 0;
    unsigned int sz =100000000 ;
    std::vector<int> v1;
    for (int i = 1; i <= sz; ++i)
    {
        if(v1.capacity() == v1.size())
        {
            ++pv;
        }
        v1.push_back(i);
    }
    v1.clear();
    Vector<int> v2;
    for (int i = 1; i <= sz; ++i)
    {
        if(v2.capacity() == v2.size())
        {
            ++pc;
        }
        v2.push_back(i);

    }
    std::cout <<"std::vector capacity: "<<v1.capacity() <<" std::vector perskirstymu skaicius: " << pv << std::endl <<"Vector capacity: " <<   v2.capacity() << " Vector perskirstymu skaicius:" << pc << std::endl;
    v2.clear();

    return 0;
}