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
    
    mae::math::warping_path_finder finder = mae::math::warping_path_finder();
    
    std::vector<std::vector<double> > cost_matrix = {{1,5,5},{5,2,5},{5,5,3}};
    
    std::vector<mae::math::warping_path_element> warping_path = finder.path(cost_matrix, mae::math::warping_path_selement(0,0), mae::math::warping_path_element(2,2));
    
    BOOST_CHECK_MESSAGE(warping_path.size() == 3, "Warping path size should be 3 and is " << warping_path.size());
    
    BOOST_CHECK_MESSAGE(warping_path.at(0).get_x() == 0 && warping_path.at(0).get_y() == 0, "Warping path first element should be (0,0) and is (" << warping_path.at(0).get_x() << "," << warping_path.at(0).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(1).get_x() == 1 && warping_path.at(1).get_y() == 1, "Warping path first element should be (1,1) and is (" << warping_path.at(1).get_x() << "," << warping_path.at(1).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(2).get_x() == 2 && warping_path.at(2).get_y() == 2, "Warping path first element should be (2,2) and is (" << warping_path.at(2).get_x() << "," << warping_path.at(2).get_y() << ")");
   
}

BOOST_AUTO_TEST_CASE( warping_path_finder_full_path_larger )
{
    
    mae::math::warping_path_finder finder = mae::math::warping_path_finder();
    
    std::vector<std::vector<double> > cost_matrix = {{1,1,5,5},{5,5,2,5},{5,5,5,3}};
    
    std::vector<mae::math::warping_path_element> warping_path = finder.path(cost_matrix, mae::math::warping_path_selement(0,0), mae::math::warping_path_element(2,3));
    
    BOOST_CHECK_MESSAGE(warping_path.size() == 4, "Warping path size should be 4 and is " << warping_path.size());
    
    BOOST_CHECK_MESSAGE(warping_path.at(0).get_x() == 0 && warping_path.at(0).get_y() == 0, "Warping path first element should be (0,0) and is (" << warping_path.at(0).get_x() << "," << warping_path.at(0).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(1).get_x() == 0 && warping_path.at(1).get_y() == 1, "Warping path first element should be (0,1) and is (" << warping_path.at(1).get_x() << "," << warping_path.at(1).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(2).get_x() == 1 && warping_path.at(2).get_y() == 2, "Warping path first element should be (1,2) and is (" << warping_path.at(2).get_x() << "," << warping_path.at(2).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(3).get_x() == 2 && warping_path.at(3).get_y() == 3, "Warping path first element should be (2,3) and is (" << warping_path.at(3).get_x() << "," << warping_path.at(3).get_y() << ")");
    
}

BOOST_AUTO_TEST_CASE( warping_path_finder_partial_y )
{
    mae::math::warping_path_finder finder = mae::math::warping_path_finder();
    
    std::vector<std::vector<double> > cost_matrix = {{1,1,5,5},{5,5,2,5},{5,5,5,3}};
    
    std::vector<mae::math::warping_path_element> warping_path = finder.path(cost_matrix, mae::math::warping_path_selement(0,0,false,true), mae::math::warping_path_element(2,3));
    
    BOOST_CHECK_MESSAGE(warping_path.size() == 3, "Warping path size should be 3 and is " << warping_path.size());
    
    BOOST_CHECK_MESSAGE(warping_path.at(0).get_x() == 0 && warping_path.at(0).get_y() == 1, "Warping path first element should be (0,1) and is (" << warping_path.at(0).get_x() << "," << warping_path.at(0).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(1).get_x() == 1 && warping_path.at(1).get_y() == 2, "Warping path first element should be (1,2) and is (" << warping_path.at(1).get_x() << "," << warping_path.at(1).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(2).get_x() == 2 && warping_path.at(2).get_y() == 3, "Warping path first element should be (2,3) and is (" << warping_path.at(2).get_x() << "," << warping_path.at(2).get_y() << ")");
    
}

BOOST_AUTO_TEST_CASE( warping_path_finder_partial_x )
{
    mae::math::warping_path_finder finder = mae::math::warping_path_finder();
    
    std::vector<std::vector<double> > cost_matrix = {{1,5,5,5},{1,5,5,5},{5,2,3,3}};
    
    std::vector<mae::math::warping_path_element> warping_path = finder.path(cost_matrix, mae::math::warping_path_selement(0,0,true,false), mae::math::warping_path_element(2,2));
    
    BOOST_CHECK_MESSAGE(warping_path.size() == 3, "Warping path size should be 3 and is " << warping_path.size());
    
    BOOST_CHECK_MESSAGE(warping_path.at(0).get_x() == 1 && warping_path.at(0).get_y() == 0, "Warping path first element should be (1,0) and is (" << warping_path.at(0).get_x() << "," << warping_path.at(0).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(1).get_x() == 2 && warping_path.at(1).get_y() == 1, "Warping path first element should be (2,1) and is (" << warping_path.at(1).get_x() << "," << warping_path.at(1).get_y() << ")");
    BOOST_CHECK_MESSAGE(warping_path.at(2).get_x() == 2 && warping_path.at(2).get_y() == 2, "Warping path first element should be (2,2) and is (" << warping_path.at(2).get_x() << "," << warping_path.at(2).get_y() << ")");
    
}
