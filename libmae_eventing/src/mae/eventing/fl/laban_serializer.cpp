/*
 * laban_serializer.cpp
 *
 *  Created on: 03.09.2014
 *      Author: keks
 */

#include "laban_serializer.hpp"

namespace mae
{
	namespace eventing
	{
		namespace fl
		{

			laban_serializer::laban_serializer()
			{
			}

			laban_serializer::~laban_serializer()
			{
			}

			std::string laban_serializer::serialize(std::shared_ptr<mae::fl::laban::laban_sequence> sequence, bool short_type, bool no_header, unsigned int indent, std::string namesp)
			{
				//no namespace
				if (!short_type)
				{
					return sequence->xml(no_header, indent, namesp);
				}
				else
				{
					std::stringstream sstr;
					for (unsigned int i = 0; i < indent; i++)
					{
						sstr << "\t";
					}
					sstr << "<title>" << sequence->get_title() << "</title>";

					return sstr.str();
				}
			}

			std::shared_ptr<mae::fl::laban::laban_sequence> laban_serializer::deserialize(std::string sequence)
			{
				return laban_reader_.read_sequence_str(sequence);
			}

		} // namespace fl
	} // namespace eventing
} // namespace mae
