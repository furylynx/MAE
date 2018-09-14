//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "aligned_distance"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/math/aligned_distance.hpp"
#include "../../../src/mae/math/dtw.hpp"
#include "../../../src/mae/math/discrete_frechet_distance.hpp"
#include "../../../src/mae/math/edr.hpp"
#include "../../../src/mae/math/erp.hpp"
#include "../../../src/mae/math/lcs_distance.hpp"
#include "../../../src/mae/math/minkowski_distance.hpp"


//define distance measure

BOOST_AUTO_TEST_CASE( equalsequence_dtw )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping_measure = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure, 0, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {3}, {5}, {7}, {9}};

    double d = aligned_measure->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be zero and is " << d);

}

BOOST_AUTO_TEST_CASE( alignedsequence_dtw )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping_measure = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure, 0, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    double d = aligned_measure->distance(sequence1,sequence2);

    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be greater than zero and is " << d);

}

BOOST_AUTO_TEST_CASE( aligned_equal_dtw )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping_measure = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure, 0, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(2 == s, "Alignment startpos should be two and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(5 == e, "Alignment endpos should be five and is " << e);

}


BOOST_AUTO_TEST_CASE( unalignable_dtw )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping_measure = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure, 0, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {3}, {5}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

}

BOOST_AUTO_TEST_CASE( aligned_similar_dtw )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping_measure = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure, 0, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{2}, {3}, {5}, {7}};

    std::vector<std::vector<double> > sequence2 = {{6}, {9}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(3 == s, "Alignment startpos should be three and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(6 == e, "Alignment endpos should be six and is " << e);

}

BOOST_AUTO_TEST_CASE( aligned_equal_frechet )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::discrete_frechet_distance<std::vector<double> > > warping_measure = std::make_shared<mae::math::discrete_frechet_distance<std::vector<double> > >(distance_measure, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(2 == s, "Alignment startpos should be two and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(5 == e, "Alignment endpos should be five and is " << e);

}

BOOST_AUTO_TEST_CASE( aligned_similar_frechet )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::discrete_frechet_distance<std::vector<double> > > warping_measure = std::make_shared<mae::math::discrete_frechet_distance<std::vector<double> > >(distance_measure, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{2}, {3}, {5}, {7}};

    std::vector<std::vector<double> > sequence2 = {{6}, {9}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(3 == s, "Alignment startpos should be three and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(6 == e, "Alignment endpos should be six and is " << e);

}

BOOST_AUTO_TEST_CASE( aligned_equal_edr )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    double epsilon = 0.5;
    std::shared_ptr<mae::math::edr<std::vector<double> > > warping_measure = std::make_shared<mae::math::edr<std::vector<double> > >(distance_measure, epsilon, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(2 == s, "Alignment startpos should be two and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(5 == e, "Alignment endpos should be five and is " << e);

}

BOOST_AUTO_TEST_CASE( aligned_similar_edr )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    double epsilon = 0.5;
    std::shared_ptr<mae::math::edr<std::vector<double> > > warping_measure = std::make_shared<mae::math::edr<std::vector<double> > >(distance_measure, epsilon, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{2}, {3}, {5}, {7}};

    std::vector<std::vector<double> > sequence2 = {{6}, {9}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(2 == s, "Alignment startpos should be two and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(6 == e, "Alignment endpos should be six and is " << e);

}

BOOST_AUTO_TEST_CASE( aligned_equal_erp )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::vector<double> gap = {0};
    std::shared_ptr<mae::math::erp<std::vector<double> > > warping_measure = std::make_shared<mae::math::erp<std::vector<double> > >(distance_measure, gap, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(d == 0, "Warping distance should be zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(2 == s, "Alignment startpos should be two and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(5 == e, "Alignment endpos should be five and is " << e);

}

BOOST_AUTO_TEST_CASE( aligned_similar_erp )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::vector<double> gap = {0};
    std::shared_ptr<mae::math::erp<std::vector<double> > > warping_measure = std::make_shared<mae::math::erp<std::vector<double> > >(distance_measure, gap, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{2}, {3}, {5}, {7}};

    std::vector<std::vector<double> > sequence2 = {{6}, {9}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(2 == s, "Alignment startpos should be two and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(6 == e, "Alignment endpos should be six and is " << e);

}


BOOST_AUTO_TEST_CASE( aligned_equal_lcs )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::lcs_distance<std::vector<double> > > warping_measure = std::make_shared<mae::math::lcs_distance<std::vector<double> > >(distance_measure, true, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > target_sequence = {{1}, {3}, {5}};

    std::vector<std::vector<double> > actual_sequence = {{1}, {2}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(target_sequence,actual_sequence);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(d == 0, "Warping distance should be zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(2 == s, "Alignment startpos should be two and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(5 == e, "Alignment endpos should be five and is " << e);

}

BOOST_AUTO_TEST_CASE( aligned_similar_lcs )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::lcs_distance<std::vector<double> > > warping_measure = std::make_shared<mae::math::lcs_distance<std::vector<double> > >(distance_measure, true, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{2}, {3}, {5}, {7}};

    std::vector<std::vector<double> > sequence2 = {{6}, {9}, {1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1,sequence2);
    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(d > 0, "Warping distance should be greater than zero and is " << d);

    double s = details.get_startpos();

    BOOST_CHECK_MESSAGE(3 == s, "Alignment startpos should be three and is " << s);

    double e = details.get_endpos();

    BOOST_CHECK_MESSAGE(6 == e, "Alignment endpos should be six and is " << e);

}

BOOST_AUTO_TEST_CASE( warpingpath_equalsequence_dtw )
{
    double minkowski_p = 1;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping_measure = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure, 0, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {3}, {5}, {7}, {9}};

    std::vector<std::vector<double> > sequence2 = {{1}, {3}, {5}, {7}, {9}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1, sequence2);

    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be zero and is " << d);

    std::vector<mae::math::warping_path_element> warping_path = details.get_warping_path();

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

    std::shared_ptr<mae::math::dtw<std::vector<double> > > warping_measure = std::make_shared<mae::math::dtw<std::vector<double> > >(distance_measure, 0, true);

    std::shared_ptr<mae::math::aligned_distance<std::vector<double> > > aligned_measure = std::make_shared<mae::math::aligned_distance<std::vector<double> > >(warping_measure);

    std::vector<std::vector<double> > sequence1 = {{1}, {2}, {3}};

    std::vector<std::vector<double> > sequence2 = {{1}, {2}, {2}, {3}};

    mae::math::aligned_distance_details details = aligned_measure->distance_details(sequence1, sequence2);

    double d = details.get_distance();

    BOOST_CHECK_MESSAGE(0 == d, "Warping distance should be zero and is " << d);

    std::vector<mae::math::warping_path_element> warping_path = details.get_warping_path();

    BOOST_CHECK_MESSAGE(warping_path.at(0).get_x() == 1 && warping_path.at(0).get_y() == 1, "Warping path first element should be (1,1) and is (" << warping_path.at(0).get_x() << "," << warping_path.at(0).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(1).get_x() == 2 && warping_path.at(1).get_y() == 2, "Warping path first element should be (2,2) and is (" << warping_path.at(1).get_x() << "," << warping_path.at(1).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(2).get_x() == 2 && warping_path.at(2).get_y() == 3, "Warping path first element should be (2,3) and is (" << warping_path.at(2).get_x() << "," << warping_path.at(2).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(3).get_x() == 3 && warping_path.at(3).get_y() == 4, "Warping path first element should be (3,4) and is (" << warping_path.at(3).get_x() << "," << warping_path.at(3).get_y() << ")");

}