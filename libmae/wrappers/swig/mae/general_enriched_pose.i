// general_enriched_pose.i - SWIG interface


//custom includes
%include "general_pose.i"

//global includes
//%include "stl.i"
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "exception.i"


%module(directors="1") w_general_enriched_pose
%{
	#include "../../../src/mae/general_enriched_pose.hpp"
%}

//shared_ptr
%shared_ptr(mae::general_pose);
%shared_ptr(mae::general_enriched_pose);

// Parse the original header file
%include "../../../src/mae/general_enriched_pose.hpp"

//templates



