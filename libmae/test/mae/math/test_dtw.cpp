//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "dtw"

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



BOOST_AUTO_TEST_CASE( warpingpath_equalsequence_dtw )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);
    
    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure);
    
    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};
    
    std::vector<std::vector<double> > sequence2 = {{1}, {3}, {5}, {7}, {9}};
    
    mae::math::aligned_distance_details details = warping->optimal_alignment(sequence1, sequence2);
    
    double d = details.get_distance();
    
    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be zero and is " << d);
    
    std::vector<mae::math::warping_path_element> warping_path = details.get_warping_path();

    BOOST_CHECK_MESSAGE(warping_path.size() == 5, "Warping path length should be 5 and is " << warping_path.size());
    
    BOOST_CHECK_MESSAGE(warping_path.at(0).get_x() == 1 && warping_path.at(0).get_y() == 1, "Warping path first element should be (1,1) and is (" << warping_path.at(0).get_x() << "," << warping_path.at(0).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(1).get_x() == 2 && warping_path.at(1).get_y() == 2, "Warping path first element should be (2,2) and is (" << warping_path.at(1).get_x() << "," << warping_path.at(1).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(2).get_x() == 3 && warping_path.at(2).get_y() == 3, "Warping path first element should be (3,3) and is (" << warping_path.at(2).get_x() << "," << warping_path.at(2).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(3).get_x() == 4 && warping_path.at(3).get_y() == 4, "Warping path first element should be (4,4) and is (" << warping_path.at(3).get_x() << "," << warping_path.at(3).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(4).get_x() == 5 && warping_path.at(4).get_y() == 5, "Warping path first element should be (5,5) and is (" << warping_path.at(4).get_x() << "," << warping_path.at(4).get_y() << ")");
    
    
}

BOOST_AUTO_TEST_CASE( warpingpath_nonequal_dtw )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);
    
    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure);
    
    std::vector<std::vector<double> > sequence1 = {{1}, {2}, {3}};
    
    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {2}, {3}};
    
    mae::math::aligned_distance_details details = warping->optimal_alignment(sequence1, sequence2);
    
    double d = details.get_distance();
    
    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be zero and is " << d);
    
    std::vector<mae::math::warping_path_element> warping_path = details.get_warping_path();
    
    
    BOOST_CHECK_MESSAGE(1 == details.get_startpos(), "Startpos should be 1 and is " << details.get_startpos());
    BOOST_CHECK_MESSAGE(4 == details.get_endpos(), "Endpos should be 4 and is " << details.get_endpos());
    
    BOOST_CHECK_MESSAGE(warping_path.size() == 4, "Warping path length should be 4 and is " << warping_path.size());
    
    BOOST_CHECK_MESSAGE(warping_path.at(0).get_x() == 1 && warping_path.at(0).get_y() == 1, "Warping path first element should be (1,1) and is (" << warping_path.at(0).get_x() << "," << warping_path.at(0).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(1).get_x() == 2 && warping_path.at(1).get_y() == 2, "Warping path first element should be (2,2) and is (" << warping_path.at(1).get_x() << "," << warping_path.at(1).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(2).get_x() == 2 && warping_path.at(2).get_y() == 3, "Warping path first element should be (2,3) and is (" << warping_path.at(2).get_x() << "," << warping_path.at(2).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(3).get_x() == 3 && warping_path.at(3).get_y() == 4, "Warping path first element should be (3,4) and is (" << warping_path.at(3).get_x() << "," << warping_path.at(3).get_y() << ")");
    
}