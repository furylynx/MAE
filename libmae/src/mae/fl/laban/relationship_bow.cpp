/*
 * relationship_bow.cpp
 *
 *  Created on: 22.08.2014
 *      Author: keks
 */

#include "relationship_bow.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			relationship_bow::relationship_bow(e_relationship_type type, bool grasping, bool passing, bool hold, unsigned int measure, double beat, std::shared_ptr<mv::relationship_endpoint> left_endpoint, std::shared_ptr<mv::relationship_endpoint> right_endpoint)
			{
				type_ = type;
				grasping_ = grasping;
				passing_ = passing;
				hold_ = hold;
				measure_ = measure;
				beat_ = beat;
				left_endpoint_ = left_endpoint;
				right_endpoint_ = right_endpoint;

				if (left_endpoint == nullptr || right_endpoint == nullptr)
				{
					throw std::invalid_argument("Endpoints must not be null.");
				}

				if (beat < 0)
				{
					throw std::invalid_argument("Beat must not be negative.");
				}

				if (type == e_relationship_type::NONE)
				{
					throw std::invalid_argument("Type must not be NONE.");
				}

			}

			relationship_bow::~relationship_bow()
			{
			}

			e_relationship_type relationship_bow::get_type()
			{
				return type_;
			}

			bool relationship_bow::get_grasping()
			{
				return grasping_;
			}

			bool relationship_bow::get_passing()
			{
				return passing_;
			}

			bool relationship_bow::get_hold()
			{
				return hold_;
			}

			std::shared_ptr<mv::relationship_endpoint> relationship_bow::get_left_endpoint()
			{
				return left_endpoint_;
			}

			std::shared_ptr<mv::relationship_endpoint> relationship_bow::get_right_endpoint()
			{
				return right_endpoint_;
			}


			int relationship_bow::get_column()
			{
				return 0;
			}

			unsigned int relationship_bow::get_measure()
			{
				return measure_;
			}

			double relationship_bow::get_beat()
			{
				return beat_;
			}

			double relationship_bow::get_duration()
			{
				return 0;
			}


			std::string relationship_bow::xml(unsigned int indent, std::string namesp)
			{
				std::stringstream indent_stream;

				for (unsigned int i = 0; i < indent; i++)
				{
					indent_stream << "\t";
				}

				std::string ns = namesp;
				if (ns.size() > 0 && ns.at(ns.size()-1) != ':')
				{
					ns.push_back(':');
				}

				std::stringstream sstr;

				sstr << std::boolalpha ;

				//print relationship bow
				sstr << indent_stream.str() << "<" << ns << "relationship>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "type>" << e_relationship_type_c::str(type_) << "</" << ns << "type>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "grasping>" << grasping_ << "</" << ns << "grasping>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "passing>" << passing_ << "</" << ns << "passing>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "hold>" << hold_ << "</" << ns << "hold>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "measure>" << measure_ << "</" << ns << "measure>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "beat>" << beat_ << "</" << ns << "beat>" << std::endl;

				//print endpoints
				sstr << indent_stream.str() << "\t" << "<" << ns << "endPoints>" << std::endl;


				//left endpoint
				sstr << indent_stream.str() << "\t\t" << "<" << ns << "left>" << std::endl;
				sstr << left_endpoint_->xml(indent+3, namesp);
				sstr << indent_stream.str() << "\t\t"  << "</" << ns << "left>" << std::endl;

				//right endpoint
				sstr << indent_stream.str() << "\t\t" << "<" << ns << "right>" << std::endl;
				sstr << right_endpoint_->xml(indent+3, namesp);
				sstr << indent_stream.str() << "\t\t"  << "</" << ns << "right>" << std::endl;

				sstr << indent_stream.str() << "\t"  << "</" << ns << "endPoints>" << std::endl;

				sstr << indent_stream.str() << "</" << ns << "relationship>" << std::endl;

				return sstr.str();
			}

			std::shared_ptr<i_movement> relationship_bow::recreate(std::unordered_map<int, int> column_mapping, unsigned int measure, double beat, double duration) const
			{
				std::shared_ptr<i_movement> result;

				result = std::shared_ptr<i_movement>(new relationship_bow(type_, grasping_, passing_, hold_, measure, beat, left_endpoint_->recreate(column_mapping), right_endpoint_->recreate(column_mapping)));

				return result;
			}

			std::string relationship_bow::str() const
			{
				std::stringstream sstr;

				sstr << "(RELATIONSHIP_BOW)";

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
