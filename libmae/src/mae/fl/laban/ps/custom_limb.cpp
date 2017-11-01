#include "custom_limb.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				custom_limb::custom_limb(std::shared_ptr<i_endpoint> extremity, std::shared_ptr<i_endpoint> fixed_end)
				{
					fixed_end_ = fixed_end;
					extremity_ = extremity;

					if (extremity == nullptr)
					{
						throw std::invalid_argument("Extremity end must not be null.");
					}
				}

				custom_limb::~custom_limb()
				{
				}

				std::shared_ptr<i_endpoint> custom_limb::get_fixed_end() const
				{
					return fixed_end_;
				}

				std::shared_ptr<i_endpoint> custom_limb::get_extremity() const
				{
					return extremity_;
				}

				std::string custom_limb::xml(unsigned int indent, std::string namesp) const
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::string ns = namesp;
					if (ns.size() > 0 && ns.at(ns.size() - 1) != ':')
					{
						ns.push_back(':');
					}

					std::stringstream sstr;

					//print definition
					sstr << indent_stream.str() << "<" << ns << "limb>" << std::endl;

					//custom
					sstr << indent_stream.str() << "\t" << "<" << ns << "custom>" << std::endl;

					//print extremity
					sstr << extremity_->xml(indent + 2, namesp);

					if (fixed_end_ != nullptr)
					{
						//print fixed_end_
						sstr << fixed_end_->xml(indent + 2, namesp);
					}

					sstr << indent_stream.str() << "\t" << "</" << ns << "custom>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "limb>" << std::endl;

					return sstr.str();
				}

				std::string custom_limb::svg(std::string identifier, double posx, double posy, double width,
						double height, bool left) const
				{
					std::stringstream sstr;

					//TODO

					return sstr.str();
				}

				bool custom_limb::equals(std::shared_ptr<i_limb> a) const
				{
					if (std::shared_ptr<custom_limb> a_casted = std::dynamic_pointer_cast<custom_limb>(a))
					{
						if (extremity_->equals(a_casted->get_extremity()))
						{
							return (fixed_end_ == nullptr && a_casted->get_fixed_end() == nullptr)
									|| (fixed_end_ != nullptr
											&& fixed_end_->equals(a_casted->get_extremity()->get_fixed_end()))
									|| (a_casted->get_fixed_end() != nullptr
											&& a_casted->get_fixed_end()->equals(extremity_->get_fixed_end()));
						}
					}

					return false;
				}

				bool custom_limb::equals(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_limb> a_casted = std::dynamic_pointer_cast<i_limb>(a))
					{
						return equals(a_casted);
					}

					return false;
				}

				bool custom_limb::all_types_equal(std::shared_ptr<i_limb> a) const
				{
					if (std::shared_ptr<custom_limb> a_casted = std::dynamic_pointer_cast<custom_limb>(a))
					{
						if (extremity_->all_types_equal(a_casted->get_extremity()))
						{
							return (fixed_end_ == nullptr && a_casted->get_fixed_end() == nullptr)
								   || (fixed_end_ != nullptr
									   && fixed_end_->all_types_equal(a_casted->get_extremity()->get_fixed_end()))
								   || (a_casted->get_fixed_end() != nullptr
									   && a_casted->get_fixed_end()->all_types_equal(extremity_->get_fixed_end()));
						}
					}

					return false;
				}

				bool custom_limb::all_types_equal(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_limb> a_casted = std::dynamic_pointer_cast<i_limb>(a))
					{
						return all_types_equal(a_casted);
					}

					return false;
				}

				std::vector<double> custom_limb::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					std::vector<double> fvec_fe;

					if (nullptr != fixed_end_)
					{
						fvec_fe= fixed_end_->feature_vector(std::pow(hierarchy_factor,2));
					}

					std::vector<double> fvec_ex = extremity_->feature_vector(std::pow(hierarchy_factor,2));

					result.insert(result.end(), fvec_fe.begin(), fvec_fe.end());
					result.insert(result.end(), fvec_ex.begin(), fvec_ex.end());

					return result;
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
