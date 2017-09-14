#include <iostream>
#include <Document.hpp>
#include <Variable.hpp>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    vars::Document doc(argv[1]);
    vars::Var v = doc["float_var"];
    cout << (float) doc["d"][2] << endl;
    return 0;
}