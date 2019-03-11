//-- cancellation_symbol.i - SWIG interface

//-- custom includes
%include "i_symbol.i"
%include "e_cancel.i"

//-- global includes

%include "std_shared_ptr_fix.i"
%include "std_string.i"
%include "exception.i"

//-- module definition
%module(directors="1") w_cancellation_symbol
%{
	#include "../../../src/mae/fl/laban/mv/cancellation_symbol.hpp"
%}

//-- shared_ptr
%shared_ptr(mae::fl::laban::mv::i_symbol);
%shared_ptr(mae::fl::laban::mv::cancellation_symbol);

//-- cast method
%extend mae::fl::laban::mv::cancellation_symbol {
  static std::shared_ptr<mae::fl::laban::mv::cancellation_symbol> cast_to_cancellation_symbol(std::shared_ptr<mae::fl::laban::mv::i_symbol> base) {
    return std::dynamic_pointer_cast<mae::fl::laban::mv::cancellation_symbol>(base);
  }
}

//-- Parse the original header file
%include "../../../src/mae/fl/laban/mv/cancellation_symbol.hpp"

//-- templates
//...
