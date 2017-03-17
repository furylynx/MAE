cmake_minimum_required(VERSION 3.6)

# Set package infos
set(MYLIB mae)

set(MYLIB_VERSION_MAJOR 0)
set(MYLIB_VERSION_MINOR 10)
set(MYLIB_VERSION_PATCH 0)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

set(MYLIB_DESCRIPTION "Base library of the Movement Analysis Engine (MAE) for analyzing movement using depth sensors and Labanotation.")
set(MYLIB_URL "https://github.com/furylynx/MAE")

set(MYLIB_REQ_OPENCV OpenCV)
set(MYLIB_REQ_OPENCV_V opencv)
set(MYLIB_REQ_OPENCV_VERSION "2.4.8")
set(MYLIB_REQ_LIBXMLPP "LibXML++")
set(MYLIB_REQ_LIBXMLPP_V "libxml++-2.6")
set(MYLIB_REQ_LIBXMLPP_VERSION "2.6")
set(MYLIB_REQ_INTL "Intl")
set(MYLIB_REQ_INTL_V "intl")
set(MYLIB_REQ_INTL_VERSION "1.0")
set(MYLIB_REQUIRES "${MYLIB_REQ_OPENCV_V} >= ${MYLIB_REQ_OPENCV_VERSION}, ${MYLIB_REQ_LIBXMLPP_V} >= ${MYLIB_REQ_LIBXMLPP_VERSION}" )

# Define the project
project(${MYLIB} VERSION ${MYLIB_VERSION_STRING})

# Use C++11
set(CMAKE_CXX_STANDARD 11)

# Source files
set(SOURCE_FILES src/mae/bone.cpp
        src/mae/bone.hpp
        src/mae/dummy_pose_listener.cpp
        src/mae/dummy_pose_listener.hpp
        src/mae/e_bone.cpp
        src/mae/e_bone.hpp
        src/mae/e_joint.cpp
        src/mae/e_joint.hpp
        src/mae/e_kinect_joint.cpp
        src/mae/e_kinect_joint.hpp
        src/mae/fl/angular_joint.cpp
        src/mae/fl/angular_joint.hpp
        src/mae/fl/angular_skeleton.cpp
        src/mae/fl/angular_skeleton.hpp
        src/mae/fl/angular_skeleton_controller.cpp
        src/mae/fl/angular_skeleton_controller.hpp
        src/mae/fl/bvh_controller.cpp
        src/mae/fl/bvh_controller.hpp
        src/mae/fl/bvh_data.cpp
        src/mae/fl/bvh_data.hpp
        src/mae/fl/bvh_spec.cpp
        src/mae/fl/bvh_spec.hpp
        src/mae/fl/e_fl_direction.cpp
        src/mae/fl/e_fl_direction.hpp
        src/mae/fl/e_fl_joint.cpp
        src/mae/fl/e_fl_joint.hpp
        src/mae/fl/fl.hpp
        src/mae/fl/fl_movement_controller.cpp
        src/mae/fl/fl_movement_controller.hpp
        src/mae/fl/fl_pose_detector.cpp
        src/mae/fl/fl_pose_detector.hpp
        src/mae/fl/fl_skeleton.cpp
        src/mae/fl/fl_skeleton.hpp
        src/mae/fl/fl_skeleton_controller.cpp
        src/mae/fl/fl_skeleton_controller.hpp
        src/mae/fl/laban/column_definition.cpp
        src/mae/fl/laban/column_definition.hpp
        src/mae/fl/laban/decision_forest.cpp
        src/mae/fl/laban/decision_forest.hpp
        src/mae/fl/laban/decision_maker.cpp
        src/mae/fl/laban/decision_maker.hpp
        src/mae/fl/laban/decision_node.hpp
        src/mae/fl/laban/decision_tree.hpp
        src/mae/fl/laban/decision_value.hpp
        src/mae/fl/laban/e_path_type.cpp
        src/mae/fl/laban/e_path_type.hpp
        src/mae/fl/laban/e_relationship_type.cpp
        src/mae/fl/laban/e_relationship_type.hpp
        src/mae/fl/laban/e_time_unit.cpp
        src/mae/fl/laban/e_time_unit.hpp
        src/mae/fl/laban/i_decision_maker.hpp
        src/mae/fl/laban/i_movement.hpp
        src/mae/fl/laban/internal_laban_sequence_reader.cpp
        src/mae/fl/laban/internal_laban_sequence_reader.hh
        src/mae/fl/laban/internal_rewriting_rules_reader.cpp
        src/mae/fl/laban/internal_rewriting_rules_reader.hh
        src/mae/fl/laban/laban.hpp
        src/mae/fl/laban/laban_sequence.cpp
        src/mae/fl/laban/laban_sequence.hpp
        src/mae/fl/laban/laban_sequence_generator.cpp
        src/mae/fl/laban/laban_sequence_generator.hpp
        src/mae/fl/laban/laban_sequence_reader.cpp
        src/mae/fl/laban/laban_sequence_reader.hpp
        src/mae/fl/laban/laban_sequence_recognizer.cpp
        src/mae/fl/laban/laban_sequence_recognizer.hpp
        src/mae/fl/laban/movement.cpp
        src/mae/fl/laban/movement.hpp
        src/mae/fl/laban/mv/accent_sign.cpp
        src/mae/fl/laban/mv/accent_sign.hpp
        src/mae/fl/laban/mv/cancellation_symbol.cpp
        src/mae/fl/laban/mv/cancellation_symbol.hpp
        src/mae/fl/laban/mv/direction_symbol.cpp
        src/mae/fl/laban/mv/direction_symbol.hpp
        src/mae/fl/laban/mv/dynamic_sign.cpp
        src/mae/fl/laban/mv/dynamic_sign.hpp
        src/mae/fl/laban/mv/e_cancel.cpp
        src/mae/fl/laban/mv/e_cancel.hpp
        src/mae/fl/laban/mv/e_contact_hook.cpp
        src/mae/fl/laban/mv/e_contact_hook.hpp
        src/mae/fl/laban/mv/e_direction.cpp
        src/mae/fl/laban/mv/e_direction.hpp
        src/mae/fl/laban/mv/e_dynamic.cpp
        src/mae/fl/laban/mv/e_dynamic.hpp
        src/mae/fl/laban/mv/e_level.cpp
        src/mae/fl/laban/mv/e_level.hpp
        src/mae/fl/laban/mv/e_space.cpp
        src/mae/fl/laban/mv/e_space.hpp
        src/mae/fl/laban/mv/e_space_direction.cpp
        src/mae/fl/laban/mv/e_space_direction.hpp
        src/mae/fl/laban/mv/e_turn_direction.cpp
        src/mae/fl/laban/mv/e_turn_direction.hpp
        src/mae/fl/laban/mv/i_degree_sign.hpp
        src/mae/fl/laban/mv/i_dynamics_sign.hpp
        src/mae/fl/laban/mv/i_symbol.hpp
        src/mae/fl/laban/mv/mv.hpp
        src/mae/fl/laban/mv/pin.cpp
        src/mae/fl/laban/mv/pin.hpp
        src/mae/fl/laban/mv/relationship_endpoint.cpp
        src/mae/fl/laban/mv/relationship_endpoint.hpp
        src/mae/fl/laban/mv/space_measurement.cpp
        src/mae/fl/laban/mv/space_measurement.hpp
        src/mae/fl/laban/mv/space_symbol.cpp
        src/mae/fl/laban/mv/space_symbol.hpp
        src/mae/fl/laban/mv/turn_symbol.cpp
        src/mae/fl/laban/mv/turn_symbol.hpp
        src/mae/fl/laban/mv/vibration_symbol.cpp
        src/mae/fl/laban/mv/vibration_symbol.hpp
        src/mae/fl/laban/path.cpp
        src/mae/fl/laban/path.hpp
        src/mae/fl/laban/ps/area_part.cpp
        src/mae/fl/laban/ps/area_part.hpp
        src/mae/fl/laban/ps/body_part.cpp
        src/mae/fl/laban/ps/body_part.hpp
        src/mae/fl/laban/ps/custom_limb.cpp
        src/mae/fl/laban/ps/custom_limb.hpp
        src/mae/fl/laban/ps/default_limb.cpp
        src/mae/fl/laban/ps/default_limb.hpp
        src/mae/fl/laban/ps/digit_part.cpp
        src/mae/fl/laban/ps/digit_part.hpp
        src/mae/fl/laban/ps/e_area.cpp
        src/mae/fl/laban/ps/e_area.hpp
        src/mae/fl/laban/ps/e_digit.cpp
        src/mae/fl/laban/ps/e_digit.hpp
        src/mae/fl/laban/ps/e_joint.cpp
        src/mae/fl/laban/ps/e_joint.hpp
        src/mae/fl/laban/ps/e_limb.cpp
        src/mae/fl/laban/ps/e_limb.hpp
        src/mae/fl/laban/ps/e_limb_side.cpp
        src/mae/fl/laban/ps/e_limb_side.hpp
        src/mae/fl/laban/ps/e_side.cpp
        src/mae/fl/laban/ps/e_side.hpp
        src/mae/fl/laban/ps/i_endpoint.hpp
        src/mae/fl/laban/ps/i_limb.hpp
        src/mae/fl/laban/ps/i_part.hpp
        src/mae/fl/laban/ps/i_pre_sign.hpp
        src/mae/fl/laban/ps/joint_part.cpp
        src/mae/fl/laban/ps/joint_part.hpp
        src/mae/fl/laban/ps/prop.cpp
        src/mae/fl/laban/ps/prop.hpp
        src/mae/fl/laban/ps/ps.hpp
        src/mae/fl/laban/ps/surface_part.cpp
        src/mae/fl/laban/ps/surface_part.hpp
        src/mae/fl/laban/relationship_bow.cpp
        src/mae/fl/laban/relationship_bow.hpp
        src/mae/fl/laban/rewriting_decision_maker.cpp
        src/mae/fl/laban/rewriting_decision_maker.hpp
        src/mae/fl/laban/rewriting_forest.cpp
        src/mae/fl/laban/rewriting_forest.hpp
        src/mae/fl/laban/rewriting_rules_reader.cpp
        src/mae/fl/laban/rewriting_rules_reader.hpp
        src/mae/fl/laban/room_direction.cpp
        src/mae/fl/laban/room_direction.hpp
        src/mae/fl/msr_data.cpp
        src/mae/fl/msr_data.hpp
        src/mae/fl/msr_data_controller.cpp
        src/mae/fl/msr_data_controller.hpp
        src/mae/fl/msr_spec.cpp
        src/mae/fl/msr_spec.hpp
        src/mae/fl/skeleton_merger.cpp
        src/mae/fl/skeleton_merger.hpp
        src/mae/general_enriched_pose.cpp
        src/mae/general_enriched_pose.hpp
        src/mae/general_joint.cpp
        src/mae/general_joint.hpp
        src/mae/general_pose.cpp
        src/mae/general_pose.hpp
        src/mae/general_skeleton.cpp
        src/mae/general_skeleton.hpp
        src/mae/hierarchy.cpp
        src/mae/hierarchy.hpp
        src/mae/hierarchy_element.cpp
        src/mae/hierarchy_element.hpp
        src/mae/i_kp_detector.hpp
        src/mae/i_movement_detector.hpp
        src/mae/i_pose_detector.hpp
        src/mae/i_pose_listener.hpp
        src/mae/i_recognition_listener.hpp
        src/mae/i_sequence_generator.hpp
        src/mae/i_sequence_listener.hpp
        src/mae/i_sequence_recognizer.hpp
        src/mae/i_skeleton_controller.hpp
        src/mae/i_skeleton_merger.hpp
        src/mae/indexer_fix.hpp
        src/mae/ini_reader.cpp
        src/mae/ini_reader.hpp
        src/mae/internal_mxml.cpp
        src/mae/internal_mxml.hh
        src/mae/kp_detector.cpp
        src/mae/kp_detector.hpp
        src/mae/kp_movement_detector.hpp
        src/mae/mae.hpp
        src/mae/math/basis.cpp
        src/mae/math/basis.hpp
        src/mae/math/internal_math.cpp
        src/mae/math/internal_math.hh
        src/mae/math/math.cpp
        src/mae/math/math.hpp
        src/mae/math/vec3d.cpp
        src/mae/math/vec3d.hpp
        src/mae/mbool.cpp
        src/mae/mbool.hpp
        src/mae/mos.cpp
        src/mae/mos.hpp
        src/mae/movement_controller.hpp
        src/mae/mstr.cpp
        src/mae/mstr.hpp
        src/mae/sensor/sensor_farm.cpp src/mae/sensor/sensor_farm.hpp src/mae/sensor/i_sensor.hpp src/mae/sensor/sensor_info.cpp src/mae/sensor/sensor_info.hpp src/mae/sensor/sensor.hpp)


set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")
set(INSTALL_PACKAGE_LOCATION lib/cmake/lib${MYLIB})

set(INCLUDE_INSTALL_DIR include/ )
set(LIB_INSTALL_DIR lib/ )
set(BIN_INSTALL_DIR bin/ )
set(SYSCONFIG_INSTALL_DIR etc/${MYLIB}/ )

# We produce a shared library
add_library(${MYLIB} SHARED ${SOURCE_FILES})

# Install specs
install (TARGETS ${MYLIB}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        )

install(DIRECTORY src/ DESTINATION ${INCLUDE_INSTALL_DIR} FILES_MATCHING PATTERN "*.h*")


# Import additional modules (for libxml++ and libintl)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/Modules/")

# Dependencies
find_package ( ${MYLIB_REQ_LIBXMLPP} ${MYLIB_REQ_LIBXMLPP_VERSION} REQUIRED )
find_package ( ${MYLIB_REQ_OPENCV} ${MYLIB_REQ_OPENCV_VERSION} REQUIRED )
find_package ( ${MYLIB_REQ_INTL} REQUIRED )


set (MYLIB_INCLUDE_DIRS ${LibXML++_INCLUDE_DIRS} ${Intl_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
set (MYLIB_LIBRARIES ${Intl_LIBRARIES} ${LibXML++_LIBRARIES} ${OpenCV_LIBS} )

include_directories(${MYLIB_INCLUDE_DIRS})
target_link_libraries (${MYLIB} ${MYLIB_LIBRARIES} )

# Target
set_target_properties(${MYLIB} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})

# package (version) info
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}ConfigVersion.cmake"
        VERSION ${MYLIB_VERSION_STRING}
        COMPATIBILITY SameMajorVersion )

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/${MYLIB}Config.cmakein ${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}Config.cmake
        INSTALL_DESTINATION ${LIB_INSTALL_DIR}/cmake/${MYLIB}
        PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}Config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${MYLIB}ConfigVersion.cmake"
        DESTINATION ${LIB_INSTALL_DIR}/${MYLIB}/cmake )

# configure and install pkg config .pc file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib${MYLIB}.pc.cmakein ${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}.pc DESTINATION "${INSTALL_PKGCONFIG_DIR}")

#run swig
FIND_PACKAGE(SWIG REQUIRED)
FIND_PACKAGE(Java REQUIRED)
FIND_PACKAGE(JNI REQUIRED)

INCLUDE(${SWIG_USE_FILE})
include(UseJava)
include(UseSWIG)

include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/swig/release)
SET(CMAKE_SWIG_FLAGS -package maejava)

SET_SOURCE_FILES_PROPERTIES(wrappers/swig/mae/_wrapper_.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(maejava Java wrappers/swig/mae/_wrapper_.i)
SWIG_LINK_LIBRARIES(maejava mae)