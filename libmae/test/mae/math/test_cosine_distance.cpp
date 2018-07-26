//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "cosine_distance"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/math/cosine_distance.hpp"


BOOST_AUTO_TEST_CASE( cosine_d1 )
{

    mae::math::cosine_distance dm;

    std::vector<double> el1;
    el1.push_back(1);
    el1.push_back(1);


    std::vector<double> el2;
    el2.push_back(4);
    el2.push_back(5);

    double d = dm.distance(el1,el2);

    BOOST_CHECK_CLOSE(d, 0.006116, 0.01);
}

BOOST_AUTO_TEST_CASE( cosine_d2 )
{

    mae::math::cosine_distance dm;

    std::vector<double> el1;
    el1.push_back(0);
    el1.push_back(0);


    std::vector<double> el2;
    el2.push_back(1);
    el2.push_back(2);

    double d = dm.distance(el1,el2);

    BOOST_CHECK_CLOSE(d, 0.0, 0.01);

}