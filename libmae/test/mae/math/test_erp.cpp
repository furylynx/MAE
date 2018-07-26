//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "erp"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/math/erp.hpp"
#include "../../../src/mae/math/minkowski_distance.hpp"


//define distance measure

BOOST_AUTO_TEST_CASE( equalsequence )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::vector<double> gap = {0};
    std::shared_ptr<mae::math::erp<std::vector<double> > > warping_measure = std::make_shared<mae::math::erp<std::vector<double> > >(distance_measure, gap);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {3}, {5}, {7}, {9}};

    double d = warping_measure->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d == 0, "Warping distance should be zero and is " << d);

}

BOOST_AUTO_TEST_CASE( timewarped )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::vector<double> gap = {0};
    std::shared_ptr<mae::math::erp<std::vector<double> > > warping_measure = std::make_shared<mae::math::erp<std::vector<double> > >(distance_measure, gap);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {1}, {1}, {3}, {5}, {7}, {9}};

    double d = warping_measure->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d == 2, "Warping distance should two and is " << d);

}

BOOST_AUTO_TEST_CASE( timewarped_gap_1 )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::vector<double> gap = {1};
    std::shared_ptr<mae::math::erp<std::vector<double> > > warping_measure = std::make_shared<mae::math::erp<std::vector<double> > >(distance_measure, gap);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {1}, {1}, {3}, {5}, {7}, {9}};

    double d = warping_measure->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d == 0, "Warping distance should zero and is " << d);

}

BOOST_AUTO_TEST_CASE( timewarped_gap_2 )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::vector<double> gap = {2};
    std::shared_ptr<mae::math::erp<std::vector<double> > > warping_measure = std::make_shared<mae::math::erp<std::vector<double> > >(distance_measure, gap);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {1}, {1}, {3}, {5}, {7}, {9}};

    double d = warping_measure->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d == 2, "Warping distance should zero and is " << d);

}

BOOST_AUTO_TEST_CASE( distance )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::vector<double> gap = {0};
    std::shared_ptr<mae::math::erp<std::vector<double> > > warping_measure = std::make_shared<mae::math::erp<std::vector<double> > >(distance_measure, gap);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    double d = warping_measure->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

}

BOOST_AUTO_TEST_CASE( unaligned )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::vector<double> gap = {0};
    std::shared_ptr<mae::math::erp<std::vector<double> > > warping_measure = std::make_shared<mae::math::erp<std::vector<double> > >(distance_measure, gap);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    double d = warping_measure->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

}
