/*
 * FLLabanSequence.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef FLLABANSEQUENCE_HPP_
#define FLLABANSEQUENCE_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "laban_subsequence.hpp"

//global includes
#include <memory>

namespace mae {
	namespace fl {

		class laban_sequence {
			public:
				laban_sequence();
				virtual ~laban_sequence();


				virtual std::shared_ptr<mae::fl::laban_subsequence> get_subsequence(int bodyPart);



		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCE_HPP_
