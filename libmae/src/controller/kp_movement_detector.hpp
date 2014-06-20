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
				kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_kp_detector> ikpd);
				virtual ~kp_movement_detector();

				virtual std::shared_ptr<U> detect_movement(std::shared_ptr<T> skeleton, std::vector<bone> body_parts);
				virtual void set_buffer(int size);

			private:
				std::shared_ptr<i_pose_detector<T> > ipd;
				std::shared_ptr<i_sequence_generator<U> > isg;
				std::shared_ptr<i_kp_detector> ikpd;

				int pose_buffer_size;
				std::queue<std::shared_ptr<general_enriched_pose> > queue;

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
		std::queue<std::shared_ptr<general_enriched_pose> >().swap(queue);
	}

	template<typename T, typename U>
	std::shared_ptr<U> kp_movement_detector<T, U>::detect_movement(std::shared_ptr<T> skeleton,
			std::vector<bone> body_parts)
	{
		std::cout << "detect movement" << std::endl;
		std::cout << body_parts.size() << std::endl;


		std::shared_ptr < general_pose > pose = ipd->pose(skeleton, body_parts);

		std::shared_ptr < general_enriched_pose > enriched_pose = ikpd->estimate_frame(pose, queue, body_parts);

		queue.push(enriched_pose);
		if (queue.size() > pose_buffer_size)
		{
			queue.pop();
		}

		std::shared_ptr < U > sequence = isg->generate_sequence(queue, body_parts);

		return sequence;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::set_buffer(int size)
	{
		pose_buffer_size = size;
	}

} // namespace mae

#endif // KPMOVEMENTDETECTOR_HPP_
