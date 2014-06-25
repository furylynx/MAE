/*
 * KPMovementDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef KPMOVEMENTDETECTOR_HPP_
#define KPMOVEMENTDETECTOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "i_movement_detector.hpp"
#include "i_pose_detector.hpp"
#include "i_sequence_generator.hpp"
#include "kp_detector.hpp"

#include "../model/bone.hpp"
#include "../model/pose_listener.hpp"

//global includes
#include <memory>
#include <queue>
#include <iostream>

namespace mae
{

	template<typename T, typename U>
	class kp_movement_detector: public i_movement_detector<T, U>
	{
		public:
			kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
					std::shared_ptr<i_sequence_generator<U> > isg);
			kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
					std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_kp_detector> ikpd);
			virtual ~kp_movement_detector();

			virtual std::shared_ptr<U> detect_movement(std::shared_ptr<T> skeleton, std::vector<bone> body_parts);
			virtual void set_buffer(int size);

			virtual void add_listener(std::shared_ptr<pose_listener> listener);
			virtual void remove_listener(std::shared_ptr<pose_listener> listener);
			virtual void clear_listeners();

			virtual void notify_listeners(long timestamp, std::shared_ptr<general_pose> pose);

		private:
			std::shared_ptr<i_pose_detector<T> > ipd;
			std::shared_ptr<i_sequence_generator<U> > isg;
			std::shared_ptr<i_kp_detector> ikpd;

			std::list<std::shared_ptr<pose_listener> > listeners_;
			int pose_buffer_size;
			std::list<std::shared_ptr<general_enriched_pose> > poses;

	};
} // namespace mae

//template implementation
namespace mae
{

	template<typename T, typename U>
	kp_movement_detector<T, U>::kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg)
	{
		this->ipd = ipd;
		this->isg = isg;
		this->ikpd = std::shared_ptr<i_kp_detector>(new kp_detector());

		this->pose_buffer_size = 20;

	}

	template<typename T, typename U>
	kp_movement_detector<T, U>::kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_kp_detector> ikpd)
	{
		this->ipd = ipd;
		this->isg = isg;
		this->ikpd = ikpd;

		this->pose_buffer_size = 20;
	}

	template<typename T, typename U>
	kp_movement_detector<T, U>::~kp_movement_detector()
	{
		//clear the queue
		poses.clear();
	}

	template<typename T, typename U>
	std::shared_ptr<U> kp_movement_detector<T, U>::detect_movement(std::shared_ptr<T> skeleton,
			std::vector<bone> body_parts)
	{
		std::cout << "detect movement" << std::endl;
		std::cout << body_parts.size() << std::endl;

		std::shared_ptr<U> sequence;

		if (ipd)
		{
			std::shared_ptr<general_pose> pose = ipd->pose(skeleton, body_parts);

			notify_listeners(0, pose); //TODO timestamp??

			if (ikpd)
			{
				std::shared_ptr<general_enriched_pose> enriched_pose = ikpd->estimate_frame(pose, poses, body_parts);

				poses.push_front(enriched_pose);
				if (poses.size() > pose_buffer_size)
				{
					poses.pop_back();
				}

				if (isg)
				{
					sequence = isg->generate_sequence(poses, body_parts);
				}
			}
		}

		return sequence;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::set_buffer(int size)
	{
		pose_buffer_size = size;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::add_listener(std::shared_ptr<pose_listener> listener)
	{
		listeners_.push_back(listener);
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::remove_listener(std::shared_ptr<pose_listener> listener)
	{
		for (std::list<std::shared_ptr<pose_listener>>::iterator it = listeners_.begin(); it != listeners_.end(); it++)
		{
			if (listener == *it)
			{
				listeners_.erase(it);
				break;
			}
		}
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::clear_listeners()
	{
		listeners_.clear();
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::notify_listeners(long timestamp, std::shared_ptr<general_pose> pose)
	{
		for (std::list<std::shared_ptr<pose_listener>>::iterator it = listeners_.begin(); it != listeners_.end(); it++)
		{
			(*it)->on_pose(timestamp, pose);
		}
	}

} // namespace mae

#endif // KPMOVEMENTDETECTOR_HPP_
