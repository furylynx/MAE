// fl_movement_controller.i - SWIG interface
 
//custom includes
%include "../bone.i"
%include "../movement_controller.i"
%include "../general_skeleton.i"
%include "fl_skeleton.i"
%include "fl_pose_detector.i"

%include "laban/column_definition.i"
%include "laban/laban_sequence.i"
%include "laban/laban_sequence_recognizer.i"
%include "laban/laban_sequence_generator.i"

 
//global includes
%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"


//module definition
%module w_fl_movement_controller
%{
	#include "../../../src/mae/fl/fl_movement_controller.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::fl::fl_pose_detector);
%shared_ptr(mae::fl::laban::laban_sequence_generator);
%shared_ptr(mae::fl::laban::laban_sequence_recognizer);

//templates
%template (bone_vector) std::vector<mae::bone>;
%template (fl_skel_laban_movement_controller) mae::movement_controller<mae::fl::fl_skeleton, mae::fl::laban::laban_sequence>;
%template (coldef_vector) std::vector<std::shared_ptr<mae::fl::laban::column_definition> >;

// Parse the original header file
%include "../../../src/mae/fl/fl_movement_controller.hpp"
