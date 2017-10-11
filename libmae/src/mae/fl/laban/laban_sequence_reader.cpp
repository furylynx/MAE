#include "laban_sequence_reader.hpp"

//internal includes
#include "internal_laban_sequence_reader.hh"


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			laban_sequence_reader::laban_sequence_reader()
			{
			}

			laban_sequence_reader::~laban_sequence_reader()
			{
			}

			std::shared_ptr<laban_sequence> laban_sequence_reader::read_sequence_file(std::string file_name)
			{
				return internal_laban_sequence_reader().read_sequence_file(file_name);
			}

			std::shared_ptr<laban_sequence> laban_sequence_reader::read_sequence_str(std::string xml_string)
			{
				return internal_laban_sequence_reader().read_sequence_str(xml_string);
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
