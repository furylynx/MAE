/*
 * GeneralSkeleton.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef GENERALSKELETON_HPP_
#define GENERALSKELETON_HPP_

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

				virtual void setJoint(int bodyPart, std::shared_ptr<GeneralJoint> joint);
				virtual std::shared_ptr<GeneralJoint> getJoint(int bodyPart);

				virtual std::string ply_str();
				virtual void ply_file(std::string filename);


				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<GeneralSkeleton>& obj)
				{
					os << "GeneralSkeleton:" << std::endl;
					for ( int joint_id = MAEJ_INVALID+1; joint_id != MAEJ_SIZE; joint_id++ )
					{
					   os << maej_str[joint_id] << " " << obj->getJoint(joint_id) << std::endl;
					}

					return os;
				}

			private:
				std::unordered_map<int, std::shared_ptr<mae::model::GeneralJoint> > hashmap_joints;
		};

	} // namespace model
} // namespace mae

#endif // GENERALSKELETON_HPP_
