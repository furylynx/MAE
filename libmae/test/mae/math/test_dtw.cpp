//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "minkowski_distance"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/math/dtw.hpp"
#include "../../../src/mae/math/minkowski_distance.hpp"


//define distance measure

BOOST_AUTO_TEST_CASE( equalsequence )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {3}, {5}, {7}, {9}};

    double d = warping->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d == 0, "Warping distance should be zero and is " << d);

}

BOOST_AUTO_TEST_CASE( timewarped )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {1}, {1}, {3}, {5}, {7}, {9}};

    double d = warping->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d == 0, "Warping distance should be zero and is " << d);

}


BOOST_AUTO_TEST_CASE( distance )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    double d = warping->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

}

BOOST_AUTO_TEST_CASE( unaligned )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    double d = warping->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

}
