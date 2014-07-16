/*
 * i_sequence_listener.hpp
 *
 *  Created on: 16.07.2014
 *      Author: keks
 */

#ifndef I_SEQUENCE_LISTENER_HPP_
#define I_SEQUENCE_LISTENER_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes
#include <memory>

namespace mae
{
	template <typename U>
	class i_sequence_listener
	{
		public:
			virtual ~i_sequence_listener(){}

			virtual void on_sequence(long timestamp, std::shared_ptr<U> sequence) = 0;
	};

} // namespace mae

#endif // I_SEQUENCE_LISTENER_HPP_
