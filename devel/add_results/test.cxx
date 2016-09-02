#include <iostream>
#include <iomanip>
using namespace std;

int test(){
    double f1 = 13.14159;
    double f2 = 1.234567;
    cout << fixed;
    cout << setprecision(3) << f1 << "	" << f2 << endl;
    return 0;
}
