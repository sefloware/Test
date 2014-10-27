/*=============================================================================
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A Roman Numerals Parser (demonstrating the symbol table). This is
//  discussed in the "Symbols" chapter in the Spirit User's Guide.
//
//  [ JDG August 22, 2002 ] spirit1
//  [ JDG March 13, 2007 ]  spirit2
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <iostream>
#include <string>

unsigned print(unsigned x)
{
   std::cout << x << std::endl;
   return x;
}
typedef unsigned (*uf)(unsigned);
namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    qi::symbols<char, unsigned> para;
    qi::symbols<char, uf> fun;

    template <typename Iterator>
    struct roman : qi::grammar<Iterator, unsigned(), qi::locals<uf> >
    {
        roman() : roman::base_type(end)
        {
            using qi::eps;
            using qi::lit;
            using qi::_val;
            using qi::_1;
            using ascii::char_;

            start = para [ _val = _1 ] >> '*' >> qi::double_[ _val *= _1 ] ;
            end = fun[ qi::_a = _1] >> '(' >> start[ _val = phoenix::bind( qi::_a, _1 ) ] >>  ')';
        }

        qi::rule<Iterator, unsigned()> start;
        qi::rule<Iterator, unsigned(), qi::locals<uf> > end;
    };
    //]
}

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int
main()
{
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tRoman Numerals Parser\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Type a Roman Numeral ...or [q or Q] to quit\n\n";
    client::para.add("pi", 3);
    client::fun.add("print",print);

    typedef std::string::const_iterator iterator_type;
    typedef client::roman<iterator_type> roman;

    roman roman_parser; // Our grammar

    std::string str;
    unsigned result;
    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        //[tutorial_roman_grammar_parse
        bool r = parse(iter, end, roman_parser, result);

        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "result = " << result << std::endl;
            std::cout << "-------------------------\n";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: \": " << rest << "\"\n";
            std::cout << "-------------------------\n";
        }
        //]
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}


