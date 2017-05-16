#include "digit_part.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				digit_part::digit_part(e_digit digit, unsigned int knuckle)
				{
					digit_ = digit;
					knuckle_ = knuckle;

					if (digit == e_digit::INDEXFINGER || digit == e_digit::LITTLEFINGER
							|| digit == e_digit::MIDDLEFINGER || digit == e_digit::RINGFINGER
							|| digit == e_digit::THUMB)
					{
						if (knuckle > 4)
						{
							throw std::invalid_argument(
									"Knuckle must not be greater than 4 since a finger is addressed.");
						}
					}
					else if (digit == e_digit::NONE_DIGIT)
					{
						throw std::invalid_argument("Digit is set to NONE which is invalid.");
					}
					else
					{
						if (knuckle > 3)
						{
							throw std::invalid_argument("Knuckle must not be greater than 3 since a toe is addressed.");
						}
					}
				}

				digit_part::~digit_part()
				{
				}

				e_digit digit_part::get_digit() const
				{
					return digit_;
				}

				unsigned int digit_part::get_knuckle() const
				{
					return knuckle_;
				}

				std::string digit_part::xml(unsigned int indent, std::string namesp) const
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
					sstr << indent_stream.str() << "<" << ns << "digit>" << std::endl;

					//print digit
					sstr << indent_stream.str() << "\t" << "<" << ns << "digit>" << e_digit_c::str(digit_) << "</" << ns
							<< "digit>" << std::endl;

					//print joint
					sstr << indent_stream.str() << "\t" << "<" << ns << "joint>" << knuckle_ << "</" << ns << "joint>"
							<< std::endl;

					sstr << indent_stream.str() << "</" << ns << "digit>" << std::endl;

					return sstr.str();
				}

				std::string digit_part::svg(std::string identifier, double posx, double posy, double width,
						double height, bool left) const
				{
					std::stringstream sstr;

					//TODO

					return sstr.str();
				}

				std::shared_ptr<i_endpoint> digit_part::get_fixed_end() const
				{
					if (knuckle_ == 0)
					{
						if (digit_ == e_digit::INDEXFINGER || digit_ == e_digit::LITTLEFINGER
								|| digit_ == e_digit::MIDDLEFINGER || digit_ == e_digit::RINGFINGER
								|| digit_ == e_digit::THUMB)
						{
							return std::shared_ptr<i_endpoint>(new joint_part(e_joint::HAND));
						}
						else
						{
							return std::shared_ptr<i_endpoint>(new joint_part(e_joint::FOOT));
						}
					}
					else
					{
						return std::shared_ptr<i_endpoint>(new digit_part(digit_, knuckle_-1));
					}
				}

				bool digit_part::equals(std::shared_ptr<i_endpoint> a) const
				{
					if (std::shared_ptr<digit_part> a_casted = std::dynamic_pointer_cast<digit_part>(a))
					{
						return (digit_ == a_casted->get_digit() && knuckle_ == a_casted->get_knuckle());
					}

					return false;
				}

				bool digit_part::equals(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
					{
						return equals(a_casted);
					}

					return false;
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
