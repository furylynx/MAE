//-- fl_movement_controller.i - SWIG interface

//-- custom includes
%include "../bone.i"
%include "../movement_controller.i"
%include "../general_skeleton.i"
%include "fl_skeleton.i"
%include "fl_pose_detector.i"

%include "laban/column_definition.i"
%include "laban/laban_sequence.i"
%include "laban/laban_sequence_recognizer.i"
%include "laban/laban_sequence_generator.i"

 
//-- global includes

%include "std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//-- pre-definitions for templates
%shared_ptr(mae::fl::laban::laban_sequence_generator);
%shared_ptr(mae::fl::laban::laban_sequence_recognizer);
%shared_ptr(mae::i_sequence_listener<mae::fl::laban::laban_sequence>);
%shared_ptr(mae::i_recognition_listener<mae::fl::laban::laban_sequence>);
%shared_ptr(mae::fl::laban::laban_sequence);
%shared_ptr(mae::i_sequence_generator<mae::fl::laban::laban_sequence>);
%shared_ptr(mae::fl::laban::laban_sequence_generator);
%shared_ptr(mae::i_sequence_recognizer<mae::fl::laban::laban_sequence>);
%shared_ptr(mae::i_pose_detector<mae::fl::fl_skeleton>);
%shared_ptr(mae::i_movement_detector<mae::fl::fl_skeleton, mae::fl::laban::laban_sequence>);

//-- TODO director
//-- update shared_ptr defs for director
//%typemap(javadirectorin) std::shared_ptr<mae::fl::laban::laban_sequence> "new laban_sequence($jniinput, false)"
//%feature("director") mae::i_sequence_listener<mae::fl::laban::laban_sequence>;
//%feature("director") mae::i_recognition_listener<mae::fl::laban::laban_sequence>;

%template (LabanSequenceSequenceListener) mae::i_sequence_listener<mae::fl::laban::laban_sequence>;
%template (LabanSequenceVector) std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> >;
%template (LabanSequenceRecognitionListener) mae::i_recognition_listener<mae::fl::laban::laban_sequence>;
%template (LabanSequenceSequenceGenerator) mae::i_sequence_generator<mae::fl::laban::laban_sequence>;
%template (LabanSequenceSequenceRecognizer) mae::i_sequence_recognizer<mae::fl::laban::laban_sequence>;
%template (FlSkeletonPoseDetector) mae::i_pose_detector<mae::fl::fl_skeleton>;
%template (FlSkeletonLabanSequenceMovementDetector) mae::i_movement_detector<mae::fl::fl_skeleton, mae::fl::laban::laban_sequence>;
%template (FlSkeletonLabanSequenceMovementController) mae::movement_controller<mae::fl::fl_skeleton, mae::fl::laban::laban_sequence>;

//-- module definition
%module(directors="1") w_fl_movement_controller
%{
	#include "../../../src/mae/fl/fl_movement_controller.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::general_skeleton);
%shared_ptr(mae::fl::fl_pose_detector);
%shared_ptr(mae::fl::laban::column_definition);


//-- Parse the original header file
%include "../../../src/mae/fl/fl_movement_controller.hpp"

//-- templates
%template (BoneVector) std::vector<mae::bone>;
%template (ColumnDefinitionVector) std::vector<std::shared_ptr<mae::fl::laban::column_definition> >;
