/*
 * recognition_listener.hpp
 *
 *  Created on: 2017-10-31
 *      Author: furylynx
 */

#ifndef RECOGNITION_LISTENER_HPP_
#define RECOGNITION_LISTENER_HPP_

//custom includes
//...

//global includes
#include <memory>
#include <string>
#include <vector>
#include <cstdint>

#include <mae/mae.hpp>

class recognition_listener : public mae::i_recognition_listener<mae::fl::laban::laban_sequence>
{
	public:
		/**
		 * Creates a new listener that registers recognized sequences.
		 */
		recognition_listener();
		virtual ~recognition_listener();

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
		 * @param titles The recognized sequences' titles.
		 */
		virtual void on_recognition(uint64_t timestamp, std::vector<std::string> titles);

	private:

};


#endif // RECOGNITION_LISTENER_HPP_
