/*
 * relationship_bow.hpp
 *
 *  Created on: 22.08.2014
 *      Author: keks
 */

#ifndef RELATIONSHIP_BOW_HPP_
#define RELATIONSHIP_BOW_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "i_movement.hpp"
#include "e_relationship_type.hpp"
#include "mv/relationship_endpoint.hpp"

//global includes
#include <string>
#include <memory>
#include <stdexcept>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class relationship_bow : public i_movement
			{
				public:
					//TODO doxygen
					relationship_bow(e_relationship_type type, bool grasping, bool passing, bool hold, unsigned int measure, double beat, std::shared_ptr<mv::relationship_endpoint> left_endpoint, std::shared_ptr<mv::relationship_endpoint> right_endpoint);
					virtual ~relationship_bow();


					e_relationship_type get_type();
					bool get_grasping();
					bool get_passing();
					bool get_hold();

					std::shared_ptr<mv::relationship_endpoint> get_left_endpoint();
					std::shared_ptr<mv::relationship_endpoint> get_right_endpoint();

					/**
					 * Returns the column this movement is attached to. Room direction
					 * and path sign have their own specific column only for those signs
					 * and therefore return 0.
					 *
					 * @return The column id.
					 */
					virtual int get_column();

					/**
					 * Returns the measure in which this symbols begins.
					 * @return
					 */
					virtual unsigned int get_measure();

					/**
					 * Returns the beat in which this symbol begins.
					 *
					 * @return
					 */
					virtual double get_beat();

					/**
					 * Returns the duration of the symbol. Room direction symbols do not have a duration and will return 0.
					 *
					 * @return
					 */
					virtual double get_duration();


					/**
					 * Returns the XML representation for this element.
					 *
					 * @param indent The applied indent.
					 * @param namesp The prefixed XML namespace.
					 *
					 * @return The XML string.
					 */
					virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					/**
					 * Returns the string representation for this element.
					 *
					 * @return The string.
					 */
					virtual std::string str() const;

					friend std::ostream& operator<<(std::ostream& os, const relationship_bow& obj)
					{
						os << obj.str();
						return os;
					}

					friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<relationship_bow>& obj)
					{
						os << obj->str();
						return os;
					}


				private:
					e_relationship_type type_;
					bool grasping_;
					bool passing_;
					bool hold_;
					unsigned int measure_;
					double beat_;

					std::shared_ptr<mv::relationship_endpoint> left_endpoint_;
					std::shared_ptr<mv::relationship_endpoint> right_endpoint_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // RELATIONSHIP_BOW_HPP_
