/*
 * laban_sequence_recognizer.h
 *
 *  Created on: 16.07.2014
 *      Author: keks
 */

#ifndef LABAN_SEQUENCE_RECOGNIZER_H_
#define LABAN_SEQUENCE_RECOGNIZER_H_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "laban_sequence.hpp"
#include "../../i_sequence_recognizer.hpp"
#include "../../bone.hpp"

//global includes
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <list>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class laban_sequence_recognizer: public i_sequence_recognizer<laban_sequence>
			{
				public:
					laban_sequence_recognizer(bool debug = false);
					virtual ~laban_sequence_recognizer();


					virtual void register_sequence(std::shared_ptr<laban_sequence> sequence);
					virtual void deregister_sequence(std::shared_ptr<laban_sequence> sequence);
					virtual void clear_registered_sequences();

					virtual std::vector<std::shared_ptr<laban_sequence> > recognize_sequence(std::shared_ptr<laban_sequence> sequence, std::vector<bone> body_parts);


				private:
					bool debug_;

					std::list<std::shared_ptr<laban_sequence> > registered_sequences_;
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_SEQUENCE_RECOGNIZER_H_
