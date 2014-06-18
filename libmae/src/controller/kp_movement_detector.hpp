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
#include "general_key_pose_detector.hpp"


//global includes
#include <memory>
#include <queue>
#include <iostream>



namespace mae {

		template <typename T, typename U>
		class kp_movement_detector : public i_movement_detector<T,U>
		{
			public:
				kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg);
				kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_key_pose_detector> ikpd);
				virtual ~kp_movement_detector();

				virtual std::shared_ptr<U> detect_movement(std::shared_ptr<T> skeleton, std::vector<int> body_parts);
				virtual void set_buffer(int size);

			private:
				std::shared_ptr<i_pose_detector<T> > ipd_;
				std::shared_ptr<i_sequence_generator<U> > isg_;
				std::shared_ptr<i_key_pose_detector> ikpd_;

				int buffer_size_;
				std::queue<std::shared_ptr<general_enriched_pose> > queue_;

		};
} // namespace mae


//template implementation
namespace mae
{

	template<typename T, typename U>
	kp_movement_detector<T, U>::kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg)
	{
		this->ipd_ = ipd;
		this->isg_ = isg;
		this->ikpd_ = std::shared_ptr<i_key_pose_detector>(new general_key_pose_detector());

		this->buffer_size_ = 20;

	}

	template<typename T, typename U>
	kp_movement_detector<T, U>::kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_key_pose_detector> ikpd)
	{
		this->ipd_ = ipd;
		this->isg_ = isg;
		this->ikpd_ = ikpd;

		this->buffer_size_ = 20;
	}

	template<typename T, typename U>
	kp_movement_detector<T, U>::~kp_movement_detector()
	{
		//clear the queue
		std::queue<std::shared_ptr<general_enriched_pose> >().swap(queue_);
	}

	template<typename T, typename U>
	std::shared_ptr<U> kp_movement_detector<T, U>::detect_movement(std::shared_ptr<T> skeleton,
			std::vector<int> body_parts)
	{
		std::shared_ptr < general_pose > pose = ipd_->pose(skeleton, body_parts);

		std::shared_ptr < general_enriched_pose > enriched_pose = ikpd_->estimate_frame(pose, queue_, body_parts);

		queue_.push(enriched_pose);
		if (queue_.size() > buffer_size_)
		{
			queue_.pop();
		}

		std::shared_ptr < U > sequence = isg_->generate_sequence(queue_, body_parts);

		return sequence;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::set_buffer(int size)
	{
		buffer_size_ = size;
	}

} // namespace mae

#endif // KPMOVEMENTDETECTOR_HPP_
