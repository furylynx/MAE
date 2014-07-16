/*
 * laban_sequence_recognizer.cpp
 *
 *  Created on: 16.07.2014
 *      Author: keks
 */

#include "laban_sequence_recognizer.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			laban_sequence_recognizer::laban_sequence_recognizer(bool debug)
			{
				debug_ = debug;
			}

			laban_sequence_recognizer::~laban_sequence_recognizer()
			{
			}


			void laban_sequence_recognizer::register_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				registered_sequences_.push_back(sequence);
			}

			void laban_sequence_recognizer::deregister_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				for (std::list<std::shared_ptr<laban_sequence> >::iterator it = registered_sequences_.begin(); it != registered_sequences_.end(); it++)
				{
					if (sequence == *it)
					{
						registered_sequences_.erase(it);
						break;
					}
				}
			}

			void laban_sequence_recognizer::clear_registered_sequences()
			{
				registered_sequences_.clear();
			}


			std::vector<std::shared_ptr<laban_sequence> > laban_sequence_recognizer::recognize_sequence(std::shared_ptr<laban_sequence> sequence, std::vector<bone> body_parts)
			{
				if (debug_)
				{
					std::cout << "laban_sequence_recognizer: recognize sequence" << std::endl;
				}

				std::vector<std::shared_ptr<laban_sequence> > result;

				//TODO find matches

				return result;
			}



		} // namespace laban
	} // namespace fl
} // namespace mae
