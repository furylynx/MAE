%include <std_common.i>

%{
#include <typeindex>
//#include <stdexcept>
%}

namespace std {

    class type_index {
    public:
        typedef size_t size_type;
        type_index();
        size_type hash_code() const;
        const char* name() const;
    };
}