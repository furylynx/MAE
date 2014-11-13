// basis.i - SWIG interface

//custom includes
%include "vec3d.i"

//global includes
//%include "std_shared_ptr.i"
%include "swig_fixed_std_shared_ptr.i"
%include "std_string.i"
%include "exception.i"

//typemap
%typemap(out) SWIGTYPE_p_std__shared_ptrT_mae__math__vec3d_t {vec3d};

//module definition
%module(directors="1") w_basis
%{
	#include "../../../src/mae/math/basis.hpp"
%}

//shared_ptr
%shared_ptr(mae::math::basis);
%shared_ptr(mae::math::vec3d);

// Parse the original header file
%include "../../../src/mae/math/basis.hpp"

//templates
%rename(vec3d) std::shared_ptr<vec3d>;
