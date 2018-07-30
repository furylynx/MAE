//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "movement_comparator"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../../src/mae/fl/laban/movement_comparator.hpp"
#include "../../../../src/mae/fl/laban/movement.hpp"
#include "../../../../src/mae/fl/laban/mv/direction_symbol.hpp"
#include "../../../../src/mae/e_bone.hpp"
#include "../../../../src/mae/fl/laban/mv/turn_symbol.hpp"

BOOST_AUTO_TEST_CASE( equal_movement_symbol )
{
    mae::fl::laban::movement_comparator comparator (std::make_shared<mae::math::minkowski_distance>(), std::make_shared<mae::math::sologub_tree_type_distance>(), 2);

    std::shared_ptr<mae::fl::laban::movement> m1 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT));
    std::shared_ptr<mae::fl::laban::movement> m2 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT));

    double d = comparator.distance(m1,m2);
    BOOST_CHECK_MESSAGE(d == 0, "Distance should be zero and is " << d);
}

BOOST_AUTO_TEST_CASE( different_movement_symbol )
{
    mae::fl::laban::movement_comparator comparator (std::make_shared<mae::math::minkowski_distance>(), std::make_shared<mae::math::sologub_tree_type_distance>(), 2);

    std::shared_ptr<mae::fl::laban::movement> m1 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT));
    std::shared_ptr<mae::fl::laban::movement> m2 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT));

    double d = comparator.distance(m1,m2);
    BOOST_CHECK_MESSAGE(d >= 0, "Distance should be greater than zero and is " << d);
}

BOOST_AUTO_TEST_CASE( comp_movement_symbols )
{
    mae::fl::laban::movement_comparator comparator (std::make_shared<mae::math::minkowski_distance>(), std::make_shared<mae::math::sologub_tree_type_distance>(), 2);

    std::shared_ptr<mae::fl::laban::movement> m1 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT));
    std::shared_ptr<mae::fl::laban::movement> m2 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT));
    std::shared_ptr<mae::fl::laban::movement> m3 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::HIGH, mae::fl::laban::mv::e_direction::LEFT));

    double d1 = comparator.distance(m1,m2);
    double d2 = comparator.distance(m1,m3);
    BOOST_CHECK_MESSAGE(d2 >= d1, "Distance 1 should be greater than distance 2. d1=" << d1 << ", d2=" << d2);
}

BOOST_AUTO_TEST_CASE( comp_movement_symbols2 )
{
    mae::fl::laban::movement_comparator comparator (std::make_shared<mae::math::minkowski_distance>(), std::make_shared<mae::math::sologub_tree_type_distance>(), 2);

    std::shared_ptr<mae::fl::laban::movement> m1 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT));
    std::shared_ptr<mae::fl::laban::movement> m2 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT));
    std::shared_ptr<mae::fl::laban::movement> m3 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT), true);

    double d1 = comparator.distance(m1,m2);
    double d2 = comparator.distance(m1,m3);
    BOOST_CHECK_MESSAGE(d2 >= d1, "Distance 1 should be greater than distance 2. d1=" << d1 << ", d2=" << d2);
}

BOOST_AUTO_TEST_CASE( nullptr_comp )
{
    mae::fl::laban::movement_comparator comparator (std::make_shared<mae::math::minkowski_distance>(), std::make_shared<mae::math::sologub_tree_type_distance>(), 2);

    std::shared_ptr<mae::fl::laban::movement> m1 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT));

    double d1 = comparator.distance(m1,nullptr);
    BOOST_CHECK_MESSAGE(2 == d1, "Distance should be two and is " << d1);


    double d2 = comparator.distance(nullptr, m1);
    BOOST_CHECK_MESSAGE(2 == d2, "Distance should be two and is " << d2);
}

BOOST_AUTO_TEST_CASE( nullptrs )
{
    mae::fl::laban::movement_comparator comparator (std::make_shared<mae::math::minkowski_distance>(), std::make_shared<mae::math::sologub_tree_type_distance>(), 2);

    double d = comparator.distance(nullptr,nullptr);
    BOOST_CHECK_MESSAGE(0 == d, "Distance should be zero and is " << d);
}


BOOST_AUTO_TEST_CASE( different_types_movement_symbol )
{
    mae::fl::laban::movement_comparator comparator (std::make_shared<mae::math::minkowski_distance>(), std::make_shared<mae::math::sologub_tree_type_distance>(), 2);

    std::shared_ptr<mae::fl::laban::movement> m1 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT));
    std::shared_ptr<mae::fl::laban::movement> m2 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::turn_symbol>(mae::fl::laban::mv::e_turn_direction::CLOCKWISE));

    double d = comparator.distance(m1,m2);
    BOOST_CHECK_MESSAGE(d >= 0, "Distance should be greater than zero and is " << d);
}

BOOST_AUTO_TEST_CASE( different_types_movement_symbol_direct_tree_type_distance )
{
    mae::fl::laban::movement_comparator comparator (std::make_shared<mae::math::minkowski_distance>(), std::make_shared<mae::math::direct_tree_type_distance>(1), 2);

    std::shared_ptr<mae::fl::laban::movement> m1 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT));
    std::shared_ptr<mae::fl::laban::movement> m2 = std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::turn_symbol>(mae::fl::laban::mv::e_turn_direction::CLOCKWISE));

    double d = comparator.distance(m1,m2);
    BOOST_CHECK_MESSAGE(d >= 0, "Distance should be greater than zero and is " << d);
}
