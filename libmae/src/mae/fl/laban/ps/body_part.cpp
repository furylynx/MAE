#include "body_part.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				body_part::body_part(e_side side, std::shared_ptr<i_part> part)
				{
					side_ = side;
					part_ = part;
				}

				body_part::~body_part()
				{
				}

				e_side body_part::get_side() const
				{
					return side_;
				}

				std::shared_ptr<i_part> body_part::get_part() const
				{
					return part_;
				}

				std::string body_part::xml(unsigned int indent, std::string namesp) const
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

					//print definition
					sstr << indent_stream.str() << "<" << ns << "preSign>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "bodyPart>" << std::endl;

					//print part
					sstr << part_->xml(indent + 2, namesp);

					//print side
					sstr << indent_stream.str() << "\t\t" << "<" << ns << "side>" << e_side_c::str(side_) << "</" << ns << "side>" << std::endl;

					sstr << indent_stream.str() << "\t" << "</" << ns << "bodyPart>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "preSign>" << std::endl;

					return sstr.str();
				}

				std::string body_part::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					std::stringstream sstr;

					sstr << part_->svg(identifier, posx, posy, width, height, (side_ == e_side::LEFT));

					return sstr.str();
				}

				bool body_part::equals(std::shared_ptr<i_pre_sign> a) const
				{
					if (std::shared_ptr<body_part> a_casted = std::dynamic_pointer_cast<body_part>(a))
					{
						return (side_ == a_casted->get_side() && part_->equals(a_casted->get_part()));
					}

					return false;
				}

				bool body_part::all_types_equal(std::shared_ptr<i_pre_sign> a) const
				{
					if (std::shared_ptr<body_part> a_casted = std::dynamic_pointer_cast<body_part>(a))
					{
						return true;
					}

					return false;
				}

				std::vector<double> body_part::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * e_side_c::to_int(side_)/(double)e_side_c::max());

					std::vector<double> fvec_part = part_->feature_vector(std::pow(hierarchy_factor,2));

					result.insert(result.end(), fvec_part.begin(), fvec_part.end());

					return result;
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
