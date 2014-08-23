/*
 * i_sequence_recognizer.hpp
 *
 *  Created on: 16.07.2014
 *      Author: keks
 */

#ifndef I_SEQUENCE_RECOGNIZER_HPP_
#define I_SEQUENCE_RECOGNIZER_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "bone.hpp"

//global includes
#include <vector>
#include <memory>

namespace mae
{
	template <typename U>
	class i_sequence_recognizer
	{
		public:
			virtual ~i_sequence_recognizer(){}

			virtual void register_sequence(std::shared_ptr<U> sequence) = 0;
			virtual bool deregister_sequence(std::shared_ptr<U> sequence) = 0;
			virtual bool deregister_sequence(unsigned int list_index) = 0;
			virtual void clear_registered_sequences() = 0;

			virtual int get_sequence_length(std::shared_ptr<U> sequence) = 0;

			virtual std::vector<std::shared_ptr<U> > recognize_sequence(std::shared_ptr<U> sequence, std::vector<bone> body_parts) = 0;
	};

} // namespace mae

#endif // I_SEQUENCE_RECOGNIZER_HPP_
