//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "angular_distance"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/math/angular_distance.hpp"


BOOST_AUTO_TEST_CASE( angular_d1 )
{

    mae::math::angular_distance dm;

    std::vector<double> el1;
    el1.push_back(1);
    el1.push_back(1);


    std::vector<double> el2;
    el2.push_back(4);
    el2.push_back(5);

    double d = dm.distance(el1,el2);

    BOOST_CHECK_SMALL((d - 0.0352), 0.0001);
}

BOOST_AUTO_TEST_CASE( angular_d2 )
{

    mae::math::angular_distance dm;

    std::vector<double> el1;
    el1.push_back(0);
    el1.push_back(0);


    std::vector<double> el2;
    el2.push_back(1);
    el2.push_back(2);

    double d = dm.distance(el1,el2);

    BOOST_CHECK_SMALL(d, 0.0001);

}

BOOST_AUTO_TEST_CASE( angular_equal )
{

    mae::math::angular_distance dm;

    std::vector<double> el1;
    el1.push_back(1);
    el1.push_back(1);


    std::vector<double> el2;
    el2.push_back(1);
    el2.push_back(1);

    double d = dm.distance(el1,el2);

    BOOST_CHECK_SMALL(d, 0.0001);

}

BOOST_AUTO_TEST_CASE( angular_opposed )
{

    mae::math::angular_distance dm;

    std::vector<double> el1;
    el1.push_back(1);
    el1.push_back(1);


    std::vector<double> el2;
    el2.push_back(-1);
    el2.push_back(-1);

    double d = dm.distance(el1,el2);

    BOOST_CHECK_CLOSE(d, 1.0, 0.00001);

}