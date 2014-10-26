#ifndef PASER_H
#define PASER_H

#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include <utility>
#include <string>
#include <map>
#include <cmath>

namespace client
{
namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;
namespace ascii = boost::spirit::ascii;

    template <typename Iterator>
    struct calculator : qi::grammar<Iterator, std::vector<double>(), ascii::space_type>
    {
        calculator();
        qi::rule<Iterator, double, ascii::space_type> expression, term, power, factor,start;
    };

template <typename Iterator>
calculator<Iterator>::calculator() :  calculator::base_type(start)
{
    using qi::double_;
    using qi::lexeme;
    using qi::alpha;
    using qi::alnum;
    using qi::char_;

    start = '=' >> expression[ qi::_val = qi::_1 ] >> ( qi::eoi | ';' ) ;

    expression =
            term[qi::_val = qi::_1]
        >>  *(  '+' >> term  [ qi::_val += qi::_1 ]
            |     '-' >> term  [ qi::_val -= qi::_1 ] ) ;

    term =
            power[ qi::_val = qi::_1]
        >>  *(  '*' >> power   [ qi::_val *= qi::_1 ]
            |   '/' >> power   [qi::_val /= qi::_1 ] );

    power = factor[ qi::_val = qi::_1 ] >> * ( '^' >> factor [ phoenix::bind(&std::pow<double,double>, qi::_val, qi::_1) ] );

    factor =
                double_             [ qi::_val = qi::_1 ]
            |    '(' >> expression  [ qi::_val = qi::_1 ] >> ')';
}

}
#endif // PASER_H
