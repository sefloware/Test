#include <iostream>
#include <vector>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/statement.hpp>
#include <boost/phoenix/stl.hpp>
#include <boost/phoenix/function.hpp>

//template< typename T1>
//void print(  T1 y)
//{
//    std::cout << y() << std::endl;
//}

//int main()
//{
//    using boost::phoenix::ref;
//    using boost::phoenix::arg_names::arg1;
//    using boost::phoenix::arg_names::arg2;
//    using boost::phoenix::if_;
//    using boost::phoenix::stl::size;

//    int init[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//    std::vector<int> v(init, init+10);

//    std::cout << v.size() << std::endl;

//    return 0;
//}

struct factorial_impl
{
    template <typename Sig>
    struct result;

    template <typename This, typename Arg>
    struct result<This(Arg)>
        : result<This(Arg const &)>
    {};

    template <typename This, typename Arg>
    struct result<This(Arg &)>
    {
        typedef Arg type;
    };

    template <typename Arg>
    Arg operator()(Arg n) const
    {
        return (n <= 0) ? 1 : n * this->operator()(n-1);
    }
};


int
main()
{
    using boost::phoenix::arg_names::arg1;
    using boost::phoenix::arg_names::arg2;
    using boost::phoenix::arg_names::arg3;
    boost::phoenix::function<factorial_impl> factorial;
    int i = 4;
    std::cout << ( - arg1 + arg2 + arg3)( 1, 2, 3) << std::endl;
    std::cout << factorial(arg1)(i) << std::endl;
    return 0;
}
