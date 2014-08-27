/*
 * direction_symbol.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "direction_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				direction_symbol::direction_symbol(e_level vertical, e_direction horizontal,
						std::shared_ptr<pin> modification_pin, std::shared_ptr<pin> relationship_pin,
						std::shared_ptr<i_dynamics_sign> dynamics, std::shared_ptr<space_measurement> space_measurement,
						e_contact_hook contact_hook)
				{
					vertical_ = vertical;
					horizontal_ = horizontal;
					modification_pin_ = modification_pin;
					relationship_pin_ = relationship_pin;
					dynamics_ = dynamics;
					space_measurement_ = space_measurement;
					contact_hook_ = contact_hook;

					if (vertical == e_level::NONE || horizontal == e_direction::NONE)
					{
						throw std::invalid_argument("Direction and level must not be NONE.");
					}
				}

				direction_symbol::~direction_symbol()
				{
				}

				e_level direction_symbol::get_vertical()
				{
					return vertical_;
				}

				e_direction direction_symbol::get_horizontal()
				{
					return horizontal_;
				}

				std::shared_ptr<pin> direction_symbol::get_modification_pin()
				{
					return modification_pin_;
				}

				std::shared_ptr<pin> direction_symbol::get_relationship_pin()
				{
					return relationship_pin_;
				}

				std::shared_ptr<i_dynamics_sign> direction_symbol::get_dynamics()
				{
					return dynamics_;
				}

				std::shared_ptr<space_measurement> direction_symbol::get_space_measurement()
				{
					return space_measurement_;
				}

				e_contact_hook direction_symbol::get_contact_hook()
				{
					return contact_hook_;
				}

				bool direction_symbol::equals(std::shared_ptr<i_symbol> a)
				{
					if (std::shared_ptr<direction_symbol> a_dir = std::dynamic_pointer_cast<direction_symbol>(a))
					{
						if (a_dir->get_horizontal() == horizontal_ && a_dir->get_vertical() == vertical_
								&& a_dir->get_contact_hook() == contact_hook_)
						{
							//check modification pin
							if ((modification_pin_ != nullptr
									&& modification_pin_->equals(a_dir->get_modification_pin()))
									|| (modification_pin_ == nullptr && a_dir->get_modification_pin() == nullptr))
							{
								//check relationship pin
								if ((relationship_pin_ != nullptr
										&& relationship_pin_->equals(a_dir->get_relationship_pin()))
										|| (relationship_pin_ == nullptr && a_dir->get_relationship_pin() == nullptr))
								{
									//check dynamics sign
									if ((dynamics_ != nullptr && dynamics_->equals(a_dir->get_dynamics()))
											|| (dynamics_ == nullptr && a_dir->get_dynamics() == nullptr))
									{
										//check space measurement
										if ((space_measurement_ != nullptr && space_measurement_->equals(a_dir->get_space_measurement()))
												|| (space_measurement_ == nullptr && a_dir->get_space_measurement() == nullptr))
										{
											return true;
										}
									}
								}
							}

						}
					}

					return false;
				}

				std::string direction_symbol::xml(unsigned int indent, std::string namesp)
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

					//print accent sign
					sstr << indent_stream.str() << "<" << ns << "direction>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "vertical>" << e_level_c::str(vertical_) << "</"
							<< ns << "vertical>" << std::endl;
					sstr << indent_stream.str() << "\t" << "<" << ns << "horizontal>" << e_direction_c::str(horizontal_)
							<< "</" << ns << "horizontal>" << std::endl;

					if (modification_pin_ != nullptr)
					{
						sstr << indent_stream.str() << "\t" << "<" << ns << "modificationPin>" << std::endl;
						sstr << modification_pin_->xml(indent + 1, namesp);
						sstr << indent_stream.str() << "\t" << "</" << ns << "modificationPin>" << std::endl;
					}

					if (relationship_pin_ != nullptr)
					{
						sstr << indent_stream.str() << "\t" << "<" << ns << "relationshipPin>" << std::endl;
						sstr << relationship_pin_->xml(indent + 1, namesp);
						sstr << indent_stream.str() << "\t" << "</" << ns << "relationshipPin>" << std::endl;
					}

					if (space_measurement_ != nullptr)
					{
						sstr << space_measurement_->xml(indent + 1, namesp);
					}

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent + 1, namesp);
					}

					if (contact_hook_ != e_contact_hook::NONE)
					{
						sstr << indent_stream.str() << "\t" << "<" << ns << "contactHook>"
								<< e_contact_hook_c::str(contact_hook_) << "</" << ns << "contactHook>" << std::endl;
					}

					sstr << indent_stream.str() << "</" << ns << "direction>" << std::endl;

					return sstr.str();
				}

				std::string direction_symbol::str() const
				{
					std::stringstream sstr;

					sstr << "(" << e_direction_c::str(horizontal_) << "+" << e_level_c::str(vertical_) << ")";

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
