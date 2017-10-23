#include "dynamic_sign.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				dynamic_sign::dynamic_sign(e_dynamic dynamic)
				{
					dynamic_ = dynamic;

					if (dynamic == e_dynamic::NONE_DYNAMIC)
					{
						throw std::invalid_argument("Dynamic must not be NONE.");
					}
				}

				dynamic_sign::~dynamic_sign()
				{
				}

				e_dynamic dynamic_sign::get_dynamic() const
				{
					return dynamic_;
				}

				bool dynamic_sign::equals(std::shared_ptr<i_dynamics_sign> a) const
				{
					if (std::shared_ptr<dynamic_sign> a_dyn = std::dynamic_pointer_cast<dynamic_sign>(a))
					{
						if (a_dyn->get_dynamic() == dynamic_)
						{
							return true;
						}
					}

					return false;
				}


				std::vector<double> dynamic_sign::feature_vector() const
				{
					std::vector<double> result;

					result.push_back(e_dynamic_c::to_int(dynamic_));

					return result;
				}

				std::string dynamic_sign::xml(unsigned int indent, std::string namesp) const
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

					sstr << indent_stream.str() << "\t" << "<" << ns << "dynamic>" << e_dynamic_c::str(dynamic_) << "</" << ns << "dynamic>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "dynamics>" << std::endl;

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
