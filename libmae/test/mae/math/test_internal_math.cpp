//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "internal_math"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/math/internal_math.hh"



BOOST_AUTO_TEST_CASE( quaternion )
{
    cv::Vec3d a(1,0,0);
    cv::Vec3d b(1,0,0);
    cv::Vec4d q = mae::math::internal_math::quaternion(a, b);
    
    double qw = q[0];
    double qx = q[1];
    double qy = q[2];
    double qz = q[3];
    
    BOOST_CHECK_MESSAGE(qw == 1, "qw should be 1 and is " << qw);
    BOOST_CHECK_MESSAGE(qx == 0, "qx should be 0 and is " << qx);
    BOOST_CHECK_MESSAGE(qy == 0, "qy should be 0 and is " << qy);
    BOOST_CHECK_MESSAGE(qz == 0, "qz should be 0 and is " << qz);
}

BOOST_AUTO_TEST_CASE( quaternion_2 )
{
    cv::Vec3d a(1,0,0);
    cv::Vec3d b(-1,0,0);
    cv::Vec4d q = mae::math::internal_math::quaternion(a, b);
    
    double qw = q[0];
    double qx = q[1];
    double qy = q[2];
    double qz = q[3];
    
    BOOST_CHECK_MESSAGE(qw == 0, "qw should be 0 and is " << qw);
    BOOST_CHECK_MESSAGE(qx == 0, "qx should be 0 and is " << qx);
    BOOST_CHECK_MESSAGE(qy == 0, "qy should be 0 and is " << qy);
    BOOST_CHECK_MESSAGE(qz == 1, "qz should be 1 and is " << qz);
}


BOOST_AUTO_TEST_CASE( rotation_angles_yzx )
{
    cv::Vec3d angles = mae::math::internal_math::rotation_angles_yzx(cv::Vec3d(1,0,0), cv::Vec3d(0,0,-1));
    double yrot = mae::math::internal_math::rad_to_deg(angles[0]);
    double zrot = mae::math::internal_math::rad_to_deg(angles[1]);
    double xrot = mae::math::internal_math::rad_to_deg(angles[2]);
    
    BOOST_CHECK_MESSAGE(yrot == 90, "YRotation should be 90° and is " << yrot);
    BOOST_CHECK_MESSAGE(zrot == 0, "ZRotation should be 0° and is " << zrot);
    BOOST_CHECK_MESSAGE(xrot == 0, "XRotation should be 0° and is " << xrot);
}

BOOST_AUTO_TEST_CASE( rotation_angles_yzx_2 )
{
    cv::Vec3d angles = mae::math::internal_math::rotation_angles_yzx(cv::Vec3d(1,0,0), cv::Vec3d(1,0,0));
    double yrot = mae::math::internal_math::rad_to_deg(angles[0]);
    double zrot = mae::math::internal_math::rad_to_deg(angles[1]);
    double xrot = mae::math::internal_math::rad_to_deg(angles[2]);
    
    BOOST_CHECK_MESSAGE(yrot == 0, "YRotation should be 0° and is " << yrot);
    BOOST_CHECK_MESSAGE(zrot == 0, "ZRotation should be 0° and is " << zrot);
    BOOST_CHECK_MESSAGE(xrot == 0, "XRotation should be 0° and is " << xrot);
}

BOOST_AUTO_TEST_CASE( rotation_angles_yzx_3 )
{
    cv::Vec3d angles = mae::math::internal_math::rotation_angles_yzx(cv::Vec3d(1,0,0), cv::Vec3d(-1,0,0));
    double yrot = mae::math::internal_math::rad_to_deg(angles[0]);
    double zrot = mae::math::internal_math::rad_to_deg(angles[1]);
    double xrot = mae::math::internal_math::rad_to_deg(angles[2]);
    
    BOOST_CHECK_MESSAGE(yrot == 180, "YRotation should be 180° and is " << yrot);
    BOOST_CHECK_MESSAGE(zrot == 0, "ZRotation should be 0° and is " << zrot);
    BOOST_CHECK_MESSAGE(xrot == 0, "XRotation should be 0° and is " << xrot);
}

BOOST_AUTO_TEST_CASE( rotation_angles_zxy )
{
    cv::Vec3d angles = mae::math::internal_math::rotation_angles_zxy(cv::Vec3d(1,0,0), cv::Vec3d(0,0,-1));
    double zrot = mae::math::internal_math::rad_to_deg(angles[0]);
    double xrot = mae::math::internal_math::rad_to_deg(angles[1]);
    double yrot = mae::math::internal_math::rad_to_deg(angles[2]);
    
    BOOST_CHECK_MESSAGE(yrot == 90, "YRotation should be 90° and is " << yrot);
    BOOST_CHECK_MESSAGE(zrot == 0, "ZRotation should be 0° and is " << zrot);
    BOOST_CHECK_MESSAGE(xrot == 0, "XRotation should be 0° and is " << xrot);
}

BOOST_AUTO_TEST_CASE( rotation_angles_zxy_rot )
{
    cv::Vec3d a(1,3,0);
    cv::Vec3d b(3,0,-1);
    cv::Vec3d angles = mae::math::internal_math::rotation_angles_zxy(a, b);
    double zrot = mae::math::internal_math::rad_to_deg(angles[0]);
    double xrot = mae::math::internal_math::rad_to_deg(angles[1]);
    double yrot = mae::math::internal_math::rad_to_deg(angles[2]);
    
    cv::Vec3d r = mae::math::internal_math::rotate_zxy(a, angles[0], angles[1], angles[2]);
    
    BOOST_CHECK_MESSAGE(std::abs(r[0] - b[0]) < 0.001, "r[0] should be " << b[0] << " and is " << r[0]);
    BOOST_CHECK_MESSAGE(std::abs(r[1] - b[1]) < 0.001, "r[1] should be " << b[1] << " and is " << r[1]);
    BOOST_CHECK_MESSAGE(std::abs(r[2] - b[2]) < 0.001, "r[2] should be " << b[2] << " and is " << r[2]);
}
