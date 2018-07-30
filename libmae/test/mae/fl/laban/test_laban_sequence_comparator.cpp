//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "laban_sequence_comparator"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../../src/mae/fl/laban/laban_sequence_comparator.hpp"
#include "../../../../src/mae/fl/laban/mv/direction_symbol.hpp"

BOOST_AUTO_TEST_CASE( equal_laban_sequence )
{
    mae::fl::laban::laban_sequence_comparator similarity_measure;

    std::string title = "s1";
    std::string author = "unit-test";
    unsigned int measures = 2;
    mae::fl::laban::e_time_unit time_unit = mae::fl::laban::e_time_unit::MILLISECOND;
    unsigned int beat_duration = 200;
    unsigned int beats = 5;

    std::shared_ptr<mae::fl::laban::laban_sequence> s1 = std::make_shared<mae::fl::laban::laban_sequence>("s1", author, measures, time_unit, beat_duration, beats);
    s1->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT)));
    s1->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 1, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT)));

    std::shared_ptr<mae::fl::laban::laban_sequence> s2 = std::make_shared<mae::fl::laban::laban_sequence>("s2", author, measures, time_unit, beat_duration, beats);
    s2->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT)));
    s2->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 1, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT)));


    double similarity = similarity_measure.similarity(s1,s2);
    BOOST_CHECK_CLOSE(similarity, 1.0, 0.1);
}

BOOST_AUTO_TEST_CASE( different_laban_sequence )
{

    mae::fl::laban::laban_sequence_comparator similarity_measure;

    std::string title = "s1";
    std::string author = "unit-test";
    unsigned int measures = 2;
    mae::fl::laban::e_time_unit time_unit = mae::fl::laban::e_time_unit::MILLISECOND;
    unsigned int beat_duration = 200;
    unsigned int beats = 5;

    std::shared_ptr<mae::fl::laban::laban_sequence> s1 = std::make_shared<mae::fl::laban::laban_sequence>("s1", author, measures, time_unit, beat_duration, beats);
    s1->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT)));
    s1->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 1, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT)));

    std::shared_ptr<mae::fl::laban::laban_sequence> s2 = std::make_shared<mae::fl::laban::laban_sequence>("s2", author, measures, time_unit, beat_duration, beats);
    s2->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT)));
    s2->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 1, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT_FORWARD)));

    double similarity = similarity_measure.similarity(s1,s2);
    BOOST_CHECK_MESSAGE(similarity > 0, "Distance should be greater than zero and is " << similarity);
}

BOOST_AUTO_TEST_CASE( warped_laban_sequence )
{

    mae::fl::laban::laban_sequence_comparator similarity_measure;

    std::string title = "s1";
    std::string author = "unit-test";
    unsigned int measures = 2;
    mae::fl::laban::e_time_unit time_unit = mae::fl::laban::e_time_unit::MILLISECOND;
    unsigned int beat_duration = 200;
    unsigned int beats = 5;

    std::shared_ptr<mae::fl::laban::laban_sequence> s1 = std::make_shared<mae::fl::laban::laban_sequence>("s1", author, measures, time_unit, beat_duration, beats);
    s1->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT)));
    s1->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 1, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT)));

    std::shared_ptr<mae::fl::laban::laban_sequence> s2 = std::make_shared<mae::fl::laban::laban_sequence>("s2", author, measures, time_unit, beat_duration, beats);
    s2->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 0, 0, 5, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::LOW, mae::fl::laban::mv::e_direction::LEFT)));
    s2->add_movement(std::make_shared<mae::fl::laban::movement>(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), 1, 0, 10, std::make_shared<mae::fl::laban::mv::direction_symbol>(mae::fl::laban::mv::e_level::MIDDLE, mae::fl::laban::mv::e_direction::LEFT)));

    double similarity = similarity_measure.similarity(s1,s2);
    BOOST_CHECK_CLOSE(similarity, 1.0, 0.1);
}