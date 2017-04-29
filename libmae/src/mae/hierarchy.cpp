#include "hierarchy_element.hpp"
#include "hierarchy.hpp"

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

	std::vector<std::shared_ptr<hierarchy_element> > hierarchy::get_element_sequence() const
	{
		std::vector<std::shared_ptr<hierarchy_element> > result;

		result.push_back(root);

		std::vector<std::shared_ptr<hierarchy_element> > roots_sequence = root->get_element_sequence();

		result.insert(result.end(), roots_sequence.begin(), roots_sequence.end());

		return result;
	}

	std::vector<std::shared_ptr<hierarchy_element> > hierarchy::get_sorted_element_sequence() const
	{
		std::vector<std::shared_ptr<hierarchy_element> > result = get_element_sequence();

		std::sort(result.begin(), result.end(), compare_elements);

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

	bool hierarchy::compare_elements(const std::shared_ptr<hierarchy_element> &lhs, const std::shared_ptr<hierarchy_element> &rhs)
	{
		return lhs->get_id() < rhs->get_id();
	}

	std::shared_ptr<hierarchy> hierarchy::default_hierarchy()
	{
		//push all joints as hierarchy elements to joint
		std::unordered_map<int, std::shared_ptr<hierarchy_element>> all_elements;
		for (e_joint j : e_joint_c::vec())
		{
			all_elements.insert(std::make_pair(e_joint_c::to_int(j),
					std::shared_ptr<hierarchy_element>(new hierarchy_element(e_joint_c::to_int(j), e_joint_c::str(j), e_joint_c::is_torso(j), e_joint_c::is_dummy(j)))));
		}

		//set parents

		//extremities
		all_elements.at(e_joint_c::to_int(e_joint::TN				))->push_back(all_elements.at(e_joint_c::to_int(e_joint::NECK				)));
		all_elements.at(e_joint_c::to_int(e_joint::NECK				))->push_back(all_elements.at(e_joint_c::to_int(e_joint::HEAD 				)));
		all_elements.at(e_joint_c::to_int(e_joint::HEAD				))->push_back(all_elements.at(e_joint_c::to_int(e_joint::END_H				)));

		all_elements.at(e_joint_c::to_int(e_joint::TLS 				))->push_back(all_elements.at(e_joint_c::to_int(e_joint::LEFT_SHOULDER 		)));
		all_elements.at(e_joint_c::to_int(e_joint::LEFT_SHOULDER 	))->push_back(all_elements.at(e_joint_c::to_int(e_joint::LEFT_ELBOW 		)));
		all_elements.at(e_joint_c::to_int(e_joint::LEFT_ELBOW 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::LEFT_HAND 			)));
		all_elements.at(e_joint_c::to_int(e_joint::LEFT_HAND 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::END_LH 			)));

		all_elements.at(e_joint_c::to_int(e_joint::TRS 				))->push_back(all_elements.at(e_joint_c::to_int(e_joint::RIGHT_SHOULDER 	)));
		all_elements.at(e_joint_c::to_int(e_joint::RIGHT_SHOULDER 	))->push_back(all_elements.at(e_joint_c::to_int(e_joint::RIGHT_ELBOW 		)));
		all_elements.at(e_joint_c::to_int(e_joint::RIGHT_ELBOW 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::RIGHT_HAND 		)));
		all_elements.at(e_joint_c::to_int(e_joint::RIGHT_HAND 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::END_RH 			)));

		all_elements.at(e_joint_c::to_int(e_joint::TLH 				))->push_back(all_elements.at(e_joint_c::to_int(e_joint::LEFT_HIP 			)));
		all_elements.at(e_joint_c::to_int(e_joint::LEFT_HIP 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::LEFT_KNEE 			)));
		all_elements.at(e_joint_c::to_int(e_joint::LEFT_KNEE 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::LEFT_FOOT 			)));
		all_elements.at(e_joint_c::to_int(e_joint::LEFT_FOOT 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::END_LF 			)));

		all_elements.at(e_joint_c::to_int(e_joint::TRH 				))->push_back(all_elements.at(e_joint_c::to_int(e_joint::RIGHT_HIP 			)));
		all_elements.at(e_joint_c::to_int(e_joint::RIGHT_HIP 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::RIGHT_KNEE 		)));
		all_elements.at(e_joint_c::to_int(e_joint::RIGHT_KNEE 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::RIGHT_FOOT 		)));
		all_elements.at(e_joint_c::to_int(e_joint::RIGHT_FOOT 		))->push_back(all_elements.at(e_joint_c::to_int(e_joint::END_RF 			)));

		//set torso
		all_elements.at(e_joint_c::to_int(e_joint::TORSO 			))->push_back(all_elements.at(e_joint_c::to_int(e_joint::TLS 				)));
		all_elements.at(e_joint_c::to_int(e_joint::TORSO 			))->push_back(all_elements.at(e_joint_c::to_int(e_joint::TRS 				)));
		all_elements.at(e_joint_c::to_int(e_joint::TORSO 			))->push_back(all_elements.at(e_joint_c::to_int(e_joint::TLH 				)));
		all_elements.at(e_joint_c::to_int(e_joint::TORSO 			))->push_back(all_elements.at(e_joint_c::to_int(e_joint::TRH 				)));
		all_elements.at(e_joint_c::to_int(e_joint::TORSO 			))->push_back(all_elements.at(e_joint_c::to_int(e_joint::TN 				)));

        //create hierarchy
		return std::make_shared<hierarchy>(all_elements.at(e_joint_c::to_int(e_joint::TORSO)));
	}

	std::shared_ptr<hierarchy> hierarchy::default_hand_hierarchy(bool is_left)
	{
		//push all joints as hierarchy elements to joint
		std::unordered_map<int, std::shared_ptr<hierarchy_element>> all_elements;
		for (e_hand_joint j : e_hand_joint_c::vec())
		{
			all_elements.insert(std::make_pair(e_hand_joint_c::to_int(j),
											   std::make_shared<hierarchy_element>(e_hand_joint_c::to_int(j), e_hand_joint_c::str(j), e_hand_joint_c::is_palm(j), e_hand_joint_c::is_dummy(j))));
		}

		//set parents
		if (is_left)
		{
			//extremities
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_DISTAL_INTERPHALANGEAL_JOINT)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_LT)));

			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPI))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_LI)));

            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPM))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_LM)));

            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPR))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_LR)));

            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPL))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_LL)));

			//set palm
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPT)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPI)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPM)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPR)));
			all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LPL)));


			return std::make_shared<hierarchy>(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::LEFT_WRIST)));
		}
		else
		{
            //extremities
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_DISTAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_RT)));

            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPI))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_RI)));

            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPM))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_RM)));

            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPR))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_RR)));

            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPL))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_TIP)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_TIP))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::END_RL)));

            //set palm
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPT)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPI)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPM)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPR)));
            all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_WRIST))->push_back(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RPL)));

            //create hierarchy
			return std::make_shared<hierarchy>(all_elements.at(e_hand_joint_c::to_int(e_hand_joint::RIGHT_WRIST)));
		}
	}

	std::shared_ptr<hierarchy> hierarchy::default_kinect_hierarchy()
	{
		//push all joints as hierarchy elements to joint
		std::unordered_map<int, std::shared_ptr<hierarchy_element> > all_elements;
		for (e_kinect_joint j : e_kinect_joint_c::vec())
		{
			all_elements.insert(std::make_pair(e_kinect_joint_c::to_int(j),
					std::shared_ptr<hierarchy_element>(new hierarchy_element(e_kinect_joint_c::to_int(j), e_kinect_joint_c::str(j), e_kinect_joint_c::is_torso(j), e_kinect_joint_c::is_dummy(j)))));
		}

		//set parents

		//extremities
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NH				))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::HEAD				)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::HEAD				))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::END_H		)));

		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NLS 				))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_SHOULDER 	)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_SHOULDER 	))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ELBOW 		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ELBOW 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_WRIST 	)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_WRIST 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_HAND 	)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_HAND 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::END_LH 			)));

		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NRS 				))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_SHOULDER 	)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_SHOULDER 	))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ELBOW 		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ELBOW 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_WRIST 		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_WRIST 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_HAND		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_HAND 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::END_RH 			)));

		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WLH 				))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_HIP 			)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_HIP 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_KNEE 		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_KNEE 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ANKLE 		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ANKLE 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_FOOT 		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::LEFT_FOOT 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::END_LF 			)));

		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WRH 				))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_HIP 			)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_HIP 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_KNEE 		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_KNEE 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ANKLE 	)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ANKLE 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_FOOT 	)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_FOOT 		))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::END_RF 		)));

		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WT 				))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::TORSO 		)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::TORSO 				))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NECK 		)));

		//set neck
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NECK 			))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NLS 				)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NECK 			))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NRS 				)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NECK 			))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::NH 				)));

		//set waist
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WAIST 			))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WLH 				)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WAIST 			))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WRH 				)));
		all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WAIST 			))->push_back(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WT 				)));

        //create hierarchy
		return std::make_shared<hierarchy>(all_elements.at(e_kinect_joint_c::to_int(e_kinect_joint::WAIST)));
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
