/*
 * evallistener.h
 *
 *  Created on: 14.10.2014
 *      Author: keks
 */

#ifndef EVALLISTENER_H_
#define EVALLISTENER_H_

//eclipse indexer fix
#include <mae/indexer_fix.hpp>

//custom includes
//...

//global includes
#include <memory>
#include <string>
#include <vector>
#include <cstdint>

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
			 * Returns true if a sequence was recognized since the last reset.
			 *
			 * @return True if recognized.
			 */
			virtual bool sequence_recognized();

			/**
			 * Resets the boolean for the recognition, allowing to check for the next recognition.
			 */
			virtual void reset();

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

	};

} // namespace mae

#endif // EVALLISTENER_H_
