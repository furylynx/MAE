/*
 * FLSkeleton.cpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#include "fl_skeleton.hpp"


namespace mae
{
	namespace fl
	{

		fl_skeleton::fl_skeleton()
		{
		}

		fl_skeleton::~fl_skeleton()
		{
		}

		void fl_skeleton::set_coord_sys(std::shared_ptr<mae::vec3d> u, std::shared_ptr<mae::vec3d> r, std::shared_ptr<mae::vec3d> t)
		{

			if (u != nullptr && r != nullptr && t != nullptr)
			{
				u_ = u;
				r_ = r;
				t_ = t;
			}
			else
			{
				throw std::invalid_argument("At least one parameter is a null pointer.");
			}
		}

		std::vector<std::shared_ptr<mae::vec3d> > fl_skeleton::get_coord_sys() const
		{
			std::vector<std::shared_ptr<mae::vec3d> > coord_sys;
			coord_sys.push_back(u_);
			coord_sys.push_back(r_);
			coord_sys.push_back(t_);

			return coord_sys;
		}

		void fl_skeleton::set_orig_skeleton(std::shared_ptr<general_skeleton> orig_skeleton)
		{
			this->orig_skeleton_ = orig_skeleton;
		}

		std::shared_ptr<general_skeleton> fl_skeleton::get_orig_skeleton() const
		{
			return orig_skeleton_;
		}

		std::string fl_skeleton::str() const
		{
			std::stringstream sstr;
			sstr << "fl skeleton:" << std::endl;

			if (get_hierarchy() != nullptr)
			{
				std::vector<std::shared_ptr<hierarchy_element> > elements = get_hierarchy()->get_element_sequence();

				for (unsigned int i = 0; i < elements.size(); i++)
				{
					sstr << elements.at(i)->get_name() << " " << get_joint(elements.at(i)->get_id()) << std::endl;
				}
			}
			else
			{
				sstr << "--no hierarchy defined--" << std::endl;
			}

			return sstr.str();
		}

	}				// namespace fl
} // namespace mae
