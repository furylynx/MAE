//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "warping_path_finder"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/math/warping_path_finder.hpp"


//define distance measure

BOOST_AUTO_TEST_CASE( warping_path_finder_full_path )
{

    //TODO

}

BOOST_AUTO_TEST_CASE( warping_path_finder_partial_y )
{
//    double minkowski_p = 1;
//    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);
//
//    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping_measure = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure, 0, true);
//
//    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);
//
//    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};
//
//    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};
//
//    double d = aligned_measure->distance(sequence1,sequence2);
//
//    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be greater than zero and is " << d);

}

BOOST_AUTO_TEST_CASE( warping_path_finder_partial_x )
{
    //TODO
}
