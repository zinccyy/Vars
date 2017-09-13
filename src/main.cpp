#include <iostream>
#include <Document.hpp>
#include <Variable.hpp>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    vars::Document doc(argv[1]);
    vars::Var v = doc["float_var"];

    float a = doc["d"][0];
    cout << (float)a << endl;
    return 0;
}