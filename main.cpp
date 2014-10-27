#include <iostream>
#include "paser.h"

using namespace std;

bool caculate( const std::string &str )
{
    using boost::spirit::ascii::space;

    bool result;
    std::string::const_iterator iter = str.begin();
    calculator<std::string::const_iterator> calc;
    bool r = phrase_parse(iter, str.end(), calc, space, result);

    if (r && iter == str.end() )
    {
        //Parsing succeeded\n;
        return result;
    }

    return true;
}

int main()
{
    std::string str( " =1>2; ");
    cout << caculate(str) << endl;
    return 0;
}

