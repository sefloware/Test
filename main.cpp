#include <iostream>
#include "paser.h"

using namespace std;

double caculate( const std::string &str )
{
    using boost::spirit::ascii::space;

    double result;
    std::string::const_iterator iter = str.begin();

    bool r = phrase_parse(iter, str.end(), calc, space, result);

    if (r && iter == end )
    {
        //Parsing succeeded\n;
        return result;
    }

    return 0.0;
}

int main()
{
    std::string str( " 1+2^2 ");
    cout << caculate(str) << endl;
    return 0;
}

