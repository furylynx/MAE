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

		void fl_skeleton::set_torso_basis(std::shared_ptr<mae::math::basis> basis)
		{
			set_basis(basis);
		}

		std::shared_ptr<mae::math::basis> fl_skeleton::get_torso_basis() const
		{
			return get_basis();
		}

		void fl_skeleton::set_basis(std::shared_ptr<mae::math::basis> basis)
		{
			basis_ = basis;
		}

		std::shared_ptr<mae::math::basis> fl_skeleton::get_basis() const
		{
			return basis_;
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
