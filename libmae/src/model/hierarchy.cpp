/*
 * Hierarchy.cpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#include "hierarchy.hpp"
#include "hierarchy_element.hpp"

namespace mae
{

	hierarchy::hierarchy()
	{
	}

	hierarchy::hierarchy(std::shared_ptr<hierarchy_element> root)
	{
		this->root = root;

		if (root)
		{
			root->update_ph(nullptr, this, false, true);
		}
	}

	hierarchy::~hierarchy()
	{
		if (root)
		{
			root->update_ph(nullptr, nullptr, false, false);
		}
	}

	std::shared_ptr<hierarchy_element> hierarchy::get_root() const
	{
		return root;
	}

	void hierarchy::set_root(std::shared_ptr<hierarchy_element> root)
	{
		//fix former root if existing
		if (root)
		{
			root->update_ph(nullptr, nullptr, false, false);
		}

		this->root = root;
		if (root)
		{
			root->update_ph(nullptr, this, false, true);
		}
	}

	std::vector<std::shared_ptr<hierarchy_element> > hierarchy::get_element_sequence()
	{
		std::vector<std::shared_ptr<hierarchy_element> > result;

		result.push_back(root);

		std::vector<std::shared_ptr<hierarchy_element> > roots_sequence = root->get_element_sequence();

		result.insert(result.end(), roots_sequence.begin(), roots_sequence.end());

		return result;
	}

	hierarchy_element * const hierarchy::at(int element_id) const
	{
		if (hashmap_elements.find(element_id) == hashmap_elements.end())
		{
			// returns nullpointer
			std::cout << "element not in map: " << element_id << std::endl;
			return nullptr;
		}
		else
		{
			// returns the element
			return hashmap_elements.at(element_id);
		}
	}

	std::shared_ptr<hierarchy> hierarchy::default_hierarchy()
	{
		//push all joints as hierarchy elements to joint
		std::vector<std::shared_ptr<hierarchy_element>> all_elements;
		for (int i = MAEJ_INVALID + 1; i != MAEJ_SIZE; i++)
		{
			bool dummy = false;
			if (i == MAEJ_TLS || i == MAEJ_TRS || i == MAEJ_TLH || i == MAEJ_TRH || i == MAEJ_TN || i == MAEJ_END_LH
					|| i == MAEJ_END_RH || i == MAEJ_END_LF || i == MAEJ_END_RF || i == MAEJ_END_H)
			{
				dummy = true;
			}

			bool torso = false;
			if (i == MAEJ_TORSO || i == MAEJ_LEFT_SHOULDER || i == MAEJ_RIGHT_SHOULDER || i == MAEJ_LEFT_HIP
					|| i == MAEJ_RIGHT_HIP || i == MAEJ_NECK)
			{
				torso = true;
			}

			all_elements.push_back(
					std::shared_ptr<hierarchy_element>(new hierarchy_element(i, maej_str[i], torso, dummy)));
		}

		//set parents

		//extremities
		all_elements.at(MAEJ_TN - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_NECK - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_NECK - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_HEAD - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_HEAD - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_END_H - MAEJ_INVALID - 1));

		all_elements.at(MAEJ_TLS - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_LEFT_SHOULDER - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_LEFT_SHOULDER - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_LEFT_ELBOW - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_LEFT_ELBOW - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_LEFT_HAND - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_LEFT_HAND - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_END_LH - MAEJ_INVALID - 1));

		all_elements.at(MAEJ_TRS - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_RIGHT_SHOULDER - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_RIGHT_SHOULDER - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_RIGHT_ELBOW - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_RIGHT_ELBOW - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_RIGHT_HAND - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_RIGHT_HAND - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_END_RH - MAEJ_INVALID - 1));

		all_elements.at(MAEJ_TLH - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_LEFT_HIP - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_LEFT_HIP - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_LEFT_KNEE - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_LEFT_KNEE - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_LEFT_FOOT - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_LEFT_FOOT - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_END_LF - MAEJ_INVALID - 1));

		all_elements.at(MAEJ_TRH - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_RIGHT_HIP - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_RIGHT_HIP - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_RIGHT_KNEE - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_RIGHT_KNEE - MAEJ_INVALID - 1)->push_back(
				all_elements.at(MAEJ_RIGHT_FOOT - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_RIGHT_FOOT - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_END_RF - MAEJ_INVALID - 1));

		//set torso
		all_elements.at(MAEJ_TORSO - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_TLS - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_TORSO - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_TRS - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_TORSO - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_TLH - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_TORSO - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_TRH - MAEJ_INVALID - 1));
		all_elements.at(MAEJ_TORSO - MAEJ_INVALID - 1)->push_back(all_elements.at(MAEJ_TN - MAEJ_INVALID - 1));

		std::shared_ptr<hierarchy> result = std::shared_ptr<hierarchy>(
				new hierarchy(all_elements.at(MAEJ_TORSO - MAEJ_INVALID - 1)));

		return result;
	}

	void hierarchy::add_element(hierarchy_element* element)
	{
		if (hashmap_elements.find(element->get_id()) == hashmap_elements.end())
		{
			//not in hashmap, therefore element will be added
			hashmap_elements.insert(std::make_pair(element->get_id(), element));
		}
		else
		{
			std::stringstream sstr;
			sstr << "An element with the id " << element->get_id();
			sstr << " (known: " << hashmap_elements.at(element->get_id())->get_name() << " - added: ";
			sstr << element->get_name() << ")";
			sstr << " is already mapped. Please use a unique id and make sure an element is not added twice.";
			throw std::invalid_argument(sstr.str().c_str());
		}
	}

	void hierarchy::remove_element(hierarchy_element* element)
	{
		if (hashmap_elements.find(element->get_id()) != hashmap_elements.end())
		{
			//in hashmap, therefore element will be erased
			hashmap_elements.erase(element->get_id());
		}
	}

	std::string hierarchy::str() const
	{
		if (root)
		{
			return root->str();
		}
		else
		{
			return "--No root set--";
		}
	}

} // namespace mae
