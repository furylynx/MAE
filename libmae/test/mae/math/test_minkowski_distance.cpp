//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "minkowski_distance"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/math/minkowski_distance.hpp"


BOOST_AUTO_TEST_CASE( l2dist )
{

    mae::math::minkowski_distance dm(2);

    std::vector<double> el1;
    el1.push_back(1);
    el1.push_back(1);


    std::vector<double> el2;
    el2.push_back(4);
    el2.push_back(5);

    double d = dm.distance(el1,el2);

    BOOST_CHECK_MESSAGE(5 == d, "Minkowski distance should be five and is " << d);

}

BOOST_AUTO_TEST_CASE( manhattan )
{

    mae::math::minkowski_distance dm(1);

    std::vector<double> el1;
    el1.push_back(0);
    el1.push_back(0);


    std::vector<double> el2;
    el2.push_back(1);
    el2.push_back(2);

    double d = dm.distance(el1,el2);

    BOOST_CHECK_MESSAGE(3 == d, "Minkowski distance should be three and is " << d);

}