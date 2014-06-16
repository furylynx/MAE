/*
 * GeneralSkeleton.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef GENERALSKELETON_HPP_
#define GENERALSKELETON_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "GeneralJoint.hpp"
#include "MAEJ.hpp"

//global includes
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

namespace mae
{
	namespace model
	{

		class GeneralSkeleton
		{
			public:
				virtual ~GeneralSkeleton();
				GeneralSkeleton();

				/**
				 * Sets a new joint for the given body part.
				 *
				 * @param bodyPart The addressed body part.
				 * @param joint A shared pointer to the joint.
				 */
				virtual void setJoint(int bodyPart, std::shared_ptr<GeneralJoint> joint);

				/**
				 * Returns a shared pointer to the joint of the body part.
				 *
				 * @param bodyPart The addressed body part.
				 * @return A shared pointer to the joint.
				 */
				virtual std::shared_ptr<GeneralJoint> getJoint(int bodyPart) const;

				virtual std::string str() const;

				/**
				 * Exports the skeleton data in the Stanford Triagle format as a string.
				 * @return
				 */
				virtual std::string ply_str();

				/**
				 * Exports the skeleton data to the file using the Stanford Triangle Format format.
				 *
				 * @param filename The target output file.
				 *
				 */
				virtual void ply_file(std::string filename);


				/**
				 * Prints the object to the stream.
				 *
				 * @param os
				 * @param obj The object to be printed.
				 * @return
				 */
				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<GeneralSkeleton>& obj)
				{
					os << obj->str();

					return os;
				}

				/**
				 * Prints the object to the stream.
				 *
				 * @param os
				 * @param obj The object to be printed.
				 * @return
				 */
				friend std::ostream& operator<<(std::ostream& os, const GeneralSkeleton& obj)
				{
					os << obj.str();

					return os;
				}

			private:
				std::unordered_map<int, std::shared_ptr<mae::model::GeneralJoint> > hashmap_joints;
		};

	} // namespace model
} // namespace mae

#endif // GENERALSKELETON_HPP_
