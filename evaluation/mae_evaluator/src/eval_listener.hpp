/*
 * evallistener.h
 *
 *  Created on: 14.10.2014
 *      Author: furylynx
 */

#ifndef EVALLISTENER_H_
#define EVALLISTENER_H_

//custom includes
//...

//global includes
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <set>

#include <mae/mae.hpp>

namespace eval
{
	class eval_listener: public mae::i_recognition_listener<mae::fl::laban::laban_sequence>
	{
		public:
			/**
			 * Creates a new evaluation listener which can be used to check whether a recognition was made.
			 */
			eval_listener();
			virtual ~eval_listener();

			/**
			 * Returns true if a correct sequence was recognized since the last reset.
			 *
			 * @return True if recognized.
			 */
			virtual bool sequence_recognized();

			/**
			 * Returns true if a false sequence was recognized since the last reset.
			 *
			 * @return True if false positive.
			 */
			virtual bool sequence_false_positive();

			/**
			 * Adds a sequence in order to check for correctly or incorrectly recognized sequences (false positives).
			 *
			 * @param sequence The sequence to be added.
			 * @param folder_name The folder name.
			 */
			virtual void add_sequence(std::shared_ptr<mae::fl::laban::laban_sequence> sequence, std::string folder_name);

			/**
			 * Resets the boolean for the recognition and false positive, allowing to check for the next recognition.
			 *
			 * @param folder_name
			 */
			virtual void reset(std::string folder_name);

		protected:
			/**
			 * Is invoked each time sequences were recognized and the sequences are present.
			 *
			 * @param timestamp The associated timestamp.
			 * @param sequences The recognized sequences.
			 */
			virtual void on_recognition(uint64_t timestamp,
					std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences);

			/**
			 * Is invoked each time sequences were recognized and only titles of the sequences are present.
			 *
			 * @param timestamp The associated timestamp.
			 * @param sequences The recognized sequences.
			 */
			virtual void on_recognition(uint64_t timestamp, std::vector<std::string> title);

		private:
			bool recognized_;
			bool false_positive_;

			std::string current_folder_;

			std::unordered_map<std::shared_ptr<mae::fl::laban::laban_sequence>, std::string> sequence_folder_map_;
			std::set<std::shared_ptr<mae::fl::laban::laban_sequence> > false_positive_set_;

	};

} // namespace mae

#endif // EVALLISTENER_H_
