#ifndef MAE_FL_LABAN_LABAN_SEQUENCE_READER_HPP_
#define MAE_FL_LABAN_LABAN_SEQUENCE_READER_HPP_

//custom includes
#include "laban_sequence.hpp"

//global includes
#include <memory>
#include <string>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class laban_sequence_reader
			{
				public:
					/**
					 * Creates a new laban sequence reader.
					 */
					laban_sequence_reader();
					virtual ~laban_sequence_reader();

					/**
					 * Reads the Labanotation XML (which is defined by the Labanotation XML schema v.0.5) file
					 * and generates a sequence of it.
					 *
					 * @param xml_string The path to the XML file.
					 * @return A shared pointer to the sequence.
					 */
					virtual std::shared_ptr<laban_sequence> read_sequence_file(std::string file_name);

					/**
					 * Reads the Labanotation XML (which is defined by the Labanotation XML schema v.0.5) string
					 * and generates a sequence of it. The string should contain the whole XML part which is
					 * validated against the XML schema.
					 *
					 * @param xml_string The XML string.
					 * @return A shared pointer to the sequence.
					 */
					virtual std::shared_ptr<laban_sequence> read_sequence_str(std::string xml_string);

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_LABAN_SEQUENCE_READER_HPP_
