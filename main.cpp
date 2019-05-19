#include "vector.h"
#include <vector>

/*class test {
public:
    int a, b, c;
    test() {}
    test(int & _a, int & _b, int & _c): a(_a), b(_b), c(_c) {}
    test(int && _a, int && _b, int && _c): a(std::move(_a)), b(std::move(_b)), c(std::move(_c)) {}

    void print() {
        printf(" %d %d %d\n", a, b, c);
    }
};*/

int main() {
    Timer t;
// Pradėti v1 užpildymo laiko matavimą
    unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000
    std::vector<int> v1;
    for (int i = 1; i <= sz; ++i)
        v1.push_back(i);
    std::cout << "Elapsed time(push_back) with std::vector: " << t.elapsed() << " s\n";
    t.reset();
// Pradėti v2 užpildymo laiko matavimą
    Vector<int> v2;
    for (int i = 1; i <= sz; ++i)
        v2.push_back(i);
    std::cout << "Elapsed time(push_back) with class vector: " << t.elapsed() << " s\n";

    /*int i;
    time_t st;

    st = clock();
    Vector<int> v1;
    for (i = 0; i < 1000000; ++i)
        v1.push_back(i);
    printf("lni::vector %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);


    puts("\n=== Debugging Messages ===\n");

	printf("max_size() = %u", v1.max_size());
	puts("\n");

	puts("Testing emplace and emplace_back ... ");
	Vector<test> vt;
	vt.push_back( test(1, 2, 3) );
	vt.emplace_back(2, 4, 6);
	vt.emplace(vt.begin() + 1, 1, 3, 5);
	for (auto &vti: vt)
		vti.print();
	puts("\n");

	puts("Testing resize ... ");
	v1.resize(5);
	for (auto &n: v1)
	 	printf(" %d", n);
	puts("");
	v1.resize(10, 10);
	for (auto &n: v1)
		printf(" %d", n);
	puts("\n");

	puts("Testing assign ... ");
	Vector<int> v1_a;
	v1_a.assign(v1.begin() + 1, v1.begin() + 3);
	for (auto &n: v1_a)
		printf(" %d", n);
	puts("\n");

	puts("Testing front and back ... ");
	printf(" %d %d", v1.front(), v1.back());
	puts("\n");

	puts("Testing pop_back ... ");
	v1.pop_back();
	for (auto &n: v1)
		printf(" %d", n);
	puts("\n");

	puts("Testing [] operator overloading ... ");
	v1[0] = 1;
	int sz = v1.size();
	for (i = 0; i < sz; i++)
		printf(" %d", v1[i]);
	puts("\n");

	puts("Testing initializer list ... ");
	Vector<int> v2 = {10, 11, 12, 13, 14};
	for (auto &n: v2)
		printf(" %d", n);
	puts("\n");

	puts("Testing swap ... ");
	v1.swap(v2);
	for (auto &n: v1)
		printf(" %d", n);
	puts("");
	for (auto &n: v2)
		printf(" %d", n);
	puts("\n");

	puts("Testing clear ... ");
	v1.clear();
	for (auto &n: v1)
		printf(" %d", n);
	puts("\n");


	puts("Testing constructors ... ");
	Vector<double> v3(5, 2.0);
	v3[0] = 1.0; v3[4] = 3.0;
	for (auto &f: v3)
		printf(" %.3f ", f);
	puts("");
	Vector<double> v4(v3);
	for (auto &f: v4)
		printf(" %.3f ", f);
	puts("\n");

	puts("Testing assignment operators ... ");
	Vector<double> v5 = v3;
	for (auto &f: v5)
		printf(" %.3f", f);
	puts("");
	Vector<double> v6 = {3.0, 2.0, 2.0, 2.0, 1.0};
	for (auto &f: v6)
		printf(" %.3f", f);
	puts("\n");

	puts("Testing insert ... ");
	auto it = v6.insert(v6.begin() + 1, 2.5);
	printf(" Just inserted: %.3f\n", *it);
	it = v6.insert(v6.begin(), 4.0);
	printf(" Just inserted: %.3f\n", *it);
	Vector<double> vins{-2.0, -3.0};
	it = v6.insert(v6.begin() + 1, vins.begin(), vins.end());
	printf(" Just inserted: %.3f %.3f\n", *it, *(it + 1));
	for (auto &f: v6)
		printf(" %.3f", f);
	puts("\n");

	it = v6.insert(v6.end(), 2, 0.0);
	it = v6.insert(v6.end() - 2, 3, 0.5);
	it = v6.insert(v6.begin(), {1.0, 2.0, 3.0, 4.0, 5.0});
	printf(" v6:");
	for (auto &f: v6)
		printf(" %.3f", f);
	puts("");


	Vector<double> v7(2, 5.0);
	v7.insert(v7.end(), v6.begin(), v6.end());
	for (auto &f: v7)
		printf(" %.3f", f);
	puts("");

	v7.insert(v7.begin(), {8.0, 7.0, 6.0});
	v7.insert(v7.end(), {-1.0, -2.0, -2.5});
	for (auto &f: v7)
		printf(" %.3f", f);
	puts("\n");

	puts("Testing erase ... ");
	v7.erase(v7.begin());
	v7.erase(v7.begin() + 2, v7.begin() + 4);
	printf(" v7:");
	for (auto &f: v7)
		printf(" %.3f", f);
	puts("\n");

	puts("Testing shrink_to_fit ... ");
	printf("Before: %u, %u\n", v7.size(), v7.capacity());
	v7.shrink_to_fit();
	printf("After: %u, %u\n", v7.size(), v7.capacity());
	puts("");*/

	/*puts("Testing operators ... ");
	Vector<double> v8(v7);
	printf(" v6 == v8: %d\n", v6 == v8);
	printf(" v6 != v8: %d\n", v6 != v8);
	printf(" v7 == v8: %d\n", v7 == v8);
	printf(" v7 != v8: %d\n", v7 != v8);

	printf("\n v6 < v8: %d\n", v6 < v8);
	printf(" v6 <= v8: %d\n", v6 <= v8);
	printf(" v8 < v6: %d\n", v8 < v6);
	printf(" v7 <= v8: %d\n", v7 <= v8);
	printf(" v8 < v7: %d\n", v8 < v7);

	printf("\n v6 >= v8: %d\n", v6 >= v8);
	printf(" v6 > v8: %d\n", v6 > v8);
	printf(" v8 >= v6: %d\n", v8 >= v6);
	printf(" v7 > v8: %d\n", v7 > v8);
	printf(" v8 >= v7: %d\n", v8 >= v7);
	puts("\n");

	puts("Testing reverse_iterator ... ");
	for (auto it = v8.rbegin(); it != v8.rend(); ++it)
		printf(" %.3f", *it);
	puts("\n");

	puts("Testing issue #4 #5 on github.com/lnishan/vector ... ");
	Vector<int> v9(4, 5);
	puts(" v9:");
	for (auto &n: v9)
		printf(" %d", n);
	puts("");
	v9.assign(8, 7);
	puts(" v9 (after assign(8, 7)):");
	for (auto &n: v9)
		printf(" %d", n);
	puts("\n");


    st = clock();
    Vector<int> std_v1;
    for (i = 0; i < 100; ++i)
        std_v1.push_back(i);
    printf("std::vector %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);*/

    return 0;
}