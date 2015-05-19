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

			/**
			 * Registers the sequence to the recognizer.
			 *
			 * @param sequence The sequence.
			 */
			virtual void register_sequence(std::shared_ptr<U> sequence) = 0;

			/**
			 * Removes the sequence from the recognizer.
			 *
			 * @param sequence The sequence to be deregistered.
			 * @return True if the sequence was registered.
			 */
			virtual bool deregister_sequence(std::shared_ptr<U> sequence) = 0;

			/**
			 * Removes the sequence from the recognizer.
			 *
			 * @param list_index The index of the sequence in the list.
			 * @return True if the sequence was registered.
			 */
			virtual bool deregister_sequence(unsigned int list_index) = 0;

			/**
			 * Clears the registered sequences.
			 */
			virtual void clear_registered_sequences() = 0;

			/**
			 * Clears the buffer.
			 */
			virtual void clear_buffer() = 0;

			/**
			 * Returns the length of the sequence in milliseconds.
			 *
			 * @param sequence The sequence.
			 * @return The length of the sequence.
			 */
			virtual int get_sequence_length(std::shared_ptr<U> sequence) const = 0;

			/**
			 * Recognized subsequences in the sequence for the given body parts.
			 *
			 * @param framerate The framerate to be applied.
			 * @param sequence The sequences to be looked at.
			 * @param body_parts The body parts.
			 * @return All matches.
			 */
			virtual std::vector<std::shared_ptr<U> > recognize_sequence(double framerate, std::shared_ptr<U> sequence, std::vector<bone> body_parts) = 0;
	};

} // namespace mae

#endif // I_SEQUENCE_RECOGNIZER_HPP_
