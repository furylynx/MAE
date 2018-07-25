cmake_minimum_required(VERSION 3.8)

# Include json parser cmake module
INCLUDE("${CMAKE_SOURCE_DIR}/../cmake/Modules/JSONParser.cmake")
file(READ "${CMAKE_SOURCE_DIR}/../mae.json" MAEJSONCONTENT)
sbeParseJson(MAEJSON MAEJSONCONTENT)

# Set package infos
set(MYLIB mae)

SET(MYLIB_VERSION_MAJOR ${MAEJSON.version_major})
SET(MYLIB_VERSION_MINOR ${MAEJSON.version_minor})
SET(MYLIB_VERSION_PATCH ${MAEJSON.version_patch})
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

set(MYLIB_DESCRIPTION "Base library of the Movement Analysis Engine (MAE) for analyzing movement using depth sensors and Labanotation.")
set(MYLIB_URL "https://github.com/furylynx/MAE")

set(MYLIB_REQ_OPENCV OpenCV)
set(MYLIB_REQ_OPENCV_V opencv)
set(MYLIB_REQ_OPENCV_VERSION "2.4.0")
# apply additional versions if actually compatible
set(MYLIB_REQ_OPENCV_COMPATIBLE_VERSIONS "2" "3")

set(MYLIB_REQ_LIBXMLPP "LibXML++")
set(MYLIB_REQ_LIBXMLPP_V "libxml++-2.6")
set(MYLIB_REQ_LIBXMLPP_R "libxml++")
set(MYLIB_REQ_LIBXMLPP_VERSION "2.36")

set(MYLIB_REQ_INTL "Intl")
set(MYLIB_REQ_INTL_V "intl")
set(MYLIB_REQ_INTL_VERSION "1.0")

set(MYLIB_REQUIRES "${MYLIB_REQ_OPENCV_V} >= ${MYLIB_REQ_OPENCV_VERSION}, ${MYLIB_REQ_LIBXMLPP_V} >= ${MYLIB_REQ_LIBXMLPP_VERSION}" )
set(MYLIB_REQUIRES_RPM "glibc >= 2.17, libgcc >= 4.8.5, glibmm24 >= 2.50.0, libstdc++ >= 4.8.5, ${MYLIB_REQ_OPENCV_V} >= ${MYLIB_REQ_OPENCV_VERSION}, ${MYLIB_REQ_LIBXMLPP_R} >= ${MYLIB_REQ_LIBXMLPP_VERSION}" )

set(MYLIB_JNI maejava)

# Define the project
project(${MYLIB} VERSION ${MYLIB_VERSION_STRING})

# Use C++14
set(CMAKE_CXX_STANDARD 14)

# Source files
set(SOURCE_FILES src/mae/bone.cpp
        src/mae/bone.hpp
        src/mae/e_bone.cpp
        src/mae/e_bone.hpp
        src/mae/e_hand_bone.cpp
        src/mae/e_hand_bone.hpp
        src/mae/e_hand_joint.cpp
        src/mae/e_hand_joint.hpp
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
        src/mae/fl/fl_direction_map.cpp
        src/mae/fl/fl_direction_map.hpp
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
        src/mae/sensor/sensor_farm.cpp src/mae/sensor/sensor_farm.hpp
        src/mae/sensor/i_sensor.hpp
        src/mae/sensor/sensor_info.cpp src/mae/sensor/sensor_info.hpp
        src/mae/sensor/sensor.hpp src/mae/general_skeleton_basis_pair.cpp src/mae/general_skeleton_basis_pair.hpp
        src/mae/math/dtw.hpp
        src/mae/math/i_similarity_measure
        src/mae/math/i_aligned_similarity_measure.hpp
        src/mae/math/i_distance_measure.hpp
        src/mae/math/i_warping_distance_measure.hpp
        src/mae/math/minkowski_distance.hpp
        src/mae/math/minkowski_distance.cpp
        src/mae/fl/laban/movement_comparator.hpp src/mae/fl/laban/movement_comparator.cpp
        src/mae/fl/laban/laban_sequence_comparator.cpp src/mae/fl/laban/laban_sequence_comparator.hpp
        src/mae/math/cosine_distance.hpp src/mae/math/cosine_distance.cpp
        src/mae/math/cosine_similarity.hpp src/mae/math/cosine_similarity.cpp
        src/mae/fl/laban/laban_subsequence_mapper.cpp src/mae/fl/laban/laban_subsequence_mapper.hpp
        src/mae/fl/laban/laban_target_sequence_comparator.cpp src/mae/fl/laban/laban_target_sequence_comparator.hpp
        src/mae/fl/laban/aligned_laban_sequence_comparator.cpp src/mae/fl/laban/aligned_laban_sequence_comparator.hpp
        src/mae/math/aligned_similarity_details.cpp src/mae/math/aligned_similarity_details.hpp
        src/mae/math/lcs_distance.hpp
        src/mae/math/discrete_frechet_distance.hpp src/mae/math/mahalanobis_distance.cpp
        src/mae/math/mahalanobis_distance.hpp
        src/mae/math/edr.hpp
        src/mae/math/erp.hpp
        src/mae/math/i_type_distance_measure.hpp
        src/mae/math/direct_tree_type_distance.cpp src/mae/math/direct_tree_type_distance.hpp
        src/mae/math/sologub_tree_type_distance.cpp src/mae/math/sologub_tree_type_distance.hpp
        src/mae/math/aligned_distance.hpp
        src/mae/math/aligned_distance_details.cpp src/mae/math/aligned_distance_details.hpp
        src/mae/math/aligned_distances_details.cpp src/mae/math/aligned_distances_details.hpp)


# define test files
set(TEST_FILES
        test/mae/math/test_minkowski_distance.cpp
        test/mae/math/test_dtw.cpp
        test/mae/math/test_edr.cpp
        test/mae/math/test_erp.cpp
        test/mae/math/test_discrete_frechet_distance.cpp
        test/mae/math/test_aligned_distance.cpp
        )



INCLUDE("GNUInstallDirs")

set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")
set(INSTALL_PACKAGE_LOCATION ${CMAKE_INSTALL_LIBDIR}/cmake/lib${MYLIB})

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR} )
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR} )
set(BIN_INSTALL_DIR ${CMAKE_INSTALL_BINDIR} )
set(JNI_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/jni/ )
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
find_package ( ${MYLIB_REQ_INTL} REQUIRED )

# Check OpenCV
find_package ( ${MYLIB_REQ_OPENCV} REQUIRED )
if ("${${MYLIB_REQ_OPENCV}_VERSION_MAJOR}" IN_LIST MYLIB_REQ_OPENCV_COMPATIBLE_VERSIONS)
    message( STATUS "Found OpenCV version ${${MYLIB_REQ_OPENCV}_VERSION}." )
else()
    message( FATAL_ERROR "Cannot find a compatible OpenCV version." )
endif()


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

# create java wrapper using swig
FIND_PACKAGE(SWIG REQUIRED)
FIND_PACKAGE(Java REQUIRED)
FIND_PACKAGE(JNI REQUIRED)
FIND_PACKAGE(Gradle REQUIRED)

INCLUDE(${SWIG_USE_FILE})
include(UseJava)
include(UseSWIG)

include_directories(${JNI_INCLUDE_DIRS})


set(WRAPPER_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/swig/generated_java_project)
set(CMAKE_SWIG_OUTDIR ${WRAPPER_PROJECT_DIR}/src/main/java/mae/maejava)
set(SWIG_OUTFILE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/swig/release/)

#create directory for generated java project
file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR})
file(MAKE_DIRECTORY ${SWIG_OUTFILE_DIR})
add_custom_command(TARGET ${MYLIB} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SWIG_OUTDIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SWIG_OUTFILE_DIR}
        )

SET(CMAKE_SWIG_FLAGS -package ${MYLIB_JNI})

SET_PROPERTY(SOURCE wrappers/swig/mae/_wrapper_.i PROPERTY CPLUSPLUS ON)
SWIG_ADD_LIBRARY(${MYLIB_JNI} LANGUAGE Java SOURCES wrappers/swig/mae/_wrapper_.i)
SWIG_LINK_LIBRARIES(${MYLIB_JNI} mae)

#append version number to jnilib
if (APPLE)
    #macos
    set(JNILIB_FILENAME_EXTENSION ".jnilib")
    set(JNILIB_PREFIX "lib")
elseif (WIN32)
    #windows
    set(JNILIB_FILENAME_EXTENSION ".dll")
    set(JNILIB_PREFIX "")
else()
    #unix
    set(JNILIB_FILENAME_EXTENSION ".so")
    set(JNILIB_PREFIX "lib")
endif ()

#compile java project
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/build.gradle.cmakein  ${WRAPPER_PROJECT_DIR}/build.gradle @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/settings.gradle.cmakein  ${WRAPPER_PROJECT_DIR}/settings.gradle @ONLY)

ADD_CUSTOM_COMMAND(TARGET ${MYLIB_JNI}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename "${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}" "${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}.${MYLIB_VERSION_STRING}"
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}.${MYLIB_VERSION_STRING}" "${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}.${MYLIB_VERSION_MAJOR}"
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}.${MYLIB_VERSION_MAJOR}" "${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}"
        COMMAND ${CMAKE_COMMAND} -E echo "Building Java Project, installing the java library in the local maven repository..."
        COMMAND ${GRADLE_EXECUTABLE} -b ${WRAPPER_PROJECT_DIR}/build.gradle install copyJar
        )

# install .jnilib into jni folder
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}.${MYLIB_VERSION_STRING} DESTINATION "${JNI_INSTALL_DIR}")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}.${MYLIB_VERSION_MAJOR} DESTINATION "${JNI_INSTALL_DIR}")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION} DESTINATION "${JNI_INSTALL_DIR}")

# install .jar file to jni folder (besides the installation into the local maven repository)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}-${MYLIB_VERSION_STRING}.jar DESTINATION "${JNI_INSTALL_DIR}")

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        "${CMAKE_SWIG_OUTDIR}"
        "${SWIG_OUTFILE_DIR}"
        "${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}.${MYLIB_VERSION_STRING}"
        "${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}.${MYLIB_VERSION_MAJOR}"
        "${CMAKE_CURRENT_BINARY_DIR}/${JNILIB_PREFIX}${MYLIB_JNI}${JNILIB_FILENAME_EXTENSION}"
        "${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}-${MYLIB_VERSION_STRING}.jar"
        "${CMAKE_CURRENT_BINARY_DIR}/lib${MYLIB}.jar"
        )


# Unit Testing
ENABLE_TESTING ( )

# Use Boost.Test
FIND_PACKAGE (Boost COMPONENTS unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})

# Iterate test files
FOREACH(TEST_FILE ${TEST_FILES})
    # Get the filename without an extension (see NAME_WE)
    GET_FILENAME_COMPONENT (TEST_NAME ${TEST_FILE} NAME_WE)

    # Add a compile target
    ADD_EXECUTABLE (${TEST_NAME} ${TEST_FILE})

    # Link Boost.Test and MAE target and MAE dependencies
    TARGET_LINK_LIBRARIES(${TEST_NAME} ${Boost_LIBRARIES} ${MYLIB} ${MYLIB_LIBRARIES})

    # Move testing binaries to the build_test directory
    SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/build_test)

    # Add the test (WORKING_DIRECTORY is set to our build_test directory and COMMAND executes the test
    ADD_TEST(NAME ${TEST_NAME}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build_test
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build_test/${TEST_NAME} )
ENDFOREACH(TEST_FILE)

# configure cpack
INCLUDE("${CMAKE_SOURCE_DIR}/../cmake/Modules/MAECPack.cmake")
