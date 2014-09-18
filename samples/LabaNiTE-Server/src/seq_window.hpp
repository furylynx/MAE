/*
 * seq_window.hpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#ifndef SEQ_WINDOW_HPP_
#define SEQ_WINDOW_HPP_

//custom includes
//...

//global includes
#include <mae/demo/demo.hpp>
#include <mae/mae.hpp>

namespace lni
{

	class seq_window : public mae::demo::sdl_window, mae::i_recognition_listener<mae::fl::laban::laban_sequence>
	{
		public:

			seq_window();
			virtual ~seq_window();

		protected:

			virtual void paint(SDL_Surface* graphics);
			virtual void handle_event(SDL_Event& e);


		private:

			/**
			 * Is invoked each time sequences were recognized and the sequences are present.
			 *
			 * @param timestamp The associated timestamp.
			 * @param sequences The recognized sequences.
			 */
			virtual void on_recognition(long timestamp, std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences);

			/**
			 * Is invoked each time sequences were recognized and only titles of the sequences are present.
			 *
			 * @param timestamp The associated timestamp.
			 * @param sequences The recognized sequences.
			 */
			virtual void on_recognition(long timestamp, std::vector<std::string> title);
	};

} // namespace lni

#endif // SEQ_WINDOW_HPP_
