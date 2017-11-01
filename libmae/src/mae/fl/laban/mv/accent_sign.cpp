#include "accent_sign.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				accent_sign::accent_sign(unsigned int accent)
				{
					accent_ = accent;

					if (accent > 5 || accent == 0)
					{
						throw std::invalid_argument("Accent must be a value between 1 and 5.");
					}
				}

				accent_sign::~accent_sign()
				{
				}

				unsigned int accent_sign::get_accent() const
				{
					return accent_;
				}

				bool accent_sign::equals(std::shared_ptr<i_dynamics_sign> a) const
				{
					if (std::shared_ptr<accent_sign> a_dyn = std::dynamic_pointer_cast<accent_sign>(a))
					{
						if (a_dyn->get_accent() == accent_)
						{
							return true;
						}
					}

					return false;
				}

				bool accent_sign::all_types_equal(std::shared_ptr<i_dynamics_sign> a) const
				{
					if (std::shared_ptr<accent_sign> a_dyn = std::dynamic_pointer_cast<accent_sign>(a))
					{
						return true;
					}

					return false;
				}

				std::vector<double> accent_sign::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * accent_/(double) 5);

					return result;
				}

				std::string accent_sign::xml(unsigned int indent, std::string namesp) const
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

					//print accent sign
					sstr << indent_stream.str() << "<" << ns << "dynamics>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "accent>" << accent_ << "</" << ns << "accent>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "dynamics>" << std::endl;

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
