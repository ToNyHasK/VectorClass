#include "header.h"
#include <vector>

void analyseInt() {
    // Pradėti v1 užpildymo laiko matavimą
    std::cout << "Laiko matavimas su std::vector(int)" << std::endl;
    Timer t;
    unsigned int sz = 10000;  // 100000, 1000000, 10000000, 100000000
    std::vector<int> v1;
    Vector<int> v2;
    for (int sz = 10000; sz <= 100000000; sz*=10) {
        for (int i = 0; i <= sz; ++i)
            v1.push_back(i);
        std::cout << "Elapsed time with size of: " + std::to_string(sz) + " std::vector(int): " << t.elapsed()
                  << " s\n";
        v1.clear();

        t.reset();
        for (int k = 0; k <= sz; k++) {
            v2.push_back(k);
        }
        std::cout << "Elapsed time with size of: " + std::to_string(sz) + " Class vector(int): " << t.elapsed()
                  << " s\n";
        v2.clear();
    }
}
studentas generate() {
    studentas stud = studentas();
    stud.setNd({6, 7, 8, 9, 10, 9, 8, 9, 10});
    stud.setEgz(9);
    return stud;
}

void analyseStud() {
    studentas stud = studentas();

    Timer t;
    std::vector<studentas> v1;
    Vector<studentas> v2;
    for (int sz = 10000; sz <=10000000; sz *= 10) {
        for (int i = 0; i<=sz; i++) {
            v1.push_back(stud);
        }
        std::cout << "Elapsed time with size of: " + std::to_string(sz) + " std::vector(studentas): " << t.elapsed()
                  << " s\n";
        v1.clear();

        t.reset();

        for(int i = 0; i <= sz; i++) {
            v2.push_back(stud);
        }
        std::cout << "Elapsed time with size of: " + std::to_string(sz) + " Class vector(studentas): " << t.elapsed()
                  << " s\n";
        //v2.clear();

        t.reset();
    }
}

void analyseCap() {

        std::cout << "perskirstymu skaiciavimas su std::vector(int) ir Class vector(int)" << std::endl;
        int pv = 0;
        int pc = 0;
        unsigned int sz =100000000 ;
        std::vector<int> v3;
        for (int i = 1; i <= sz; ++i)
        {
            if(v3.capacity() == v3.size())
            {
                ++pv;
            }
            v3.push_back(i);
        }
        v3.clear();
        Vector<int> v4;
        for (int i = 1; i <= sz; ++i)
        {
            if(v4.capacity() == v4.size())
            {
                ++pc;
            }
            v4.push_back(i);

        }
        std::cout <<"std::vector capacity: "<<v3.capacity() <<" std::vector perskirstymu skaicius(int): " << pv << std::endl <<"Vector capacity: " <<   v4.capacity() << " Vector perskirstymu skaicius(int):" << pc << std::endl;
        v4.clear();
}

int main()
{
    //vector cap
    analyseCap();
    //vector int
    analyseInt();
    //vector stud
    analyseStud();

    return 0;
}