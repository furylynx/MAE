#ifndef MAE_FL_LABAN_REWRITING_RULES_READER_HPP_
#define MAE_FL_LABAN_REWRITING_RULES_READER_HPP_

//custom includes
#include "decision_value.hpp"
#include "i_movement.hpp"


//global includes
#include <memory>
#include <string>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class rewriting_rules_reader
			{
				public:
					/**
					 * Creates a new reader for rewriting rules.
					 */
					rewriting_rules_reader();
					virtual ~rewriting_rules_reader();

					/**
					 * Reads the rewriting rules XML file and generates a vector of rules from it.
					 *
					 * @param xml_string The path to the XML file.
					 * @return A shared pointer to the sequence.
					 */
					virtual std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > read_rules_file(std::string file_name);

					/**
					 * Reads the rewriting rules XML string and generates a vector of rules from it.
					 *
					 * @param xml_string The XML string.
					 * @return A shared pointer to the sequence.
					 */
					virtual std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > read_rules_str(std::string xml_string);

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_REWRITING_RULES_READER_HPP_
