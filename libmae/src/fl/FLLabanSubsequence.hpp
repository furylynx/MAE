/*
 * FLLabanSubsequence.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef FLLABANSUBSEQUENCE_HPP_
#define FLLABANSUBSEQUENCE_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes

namespace mae {
	namespace fl {

		class FLLabanSubsequence {
			public:
				FLLabanSubsequence();
				virtual ~FLLabanSubsequence();

				virtual int getRepresentedBodyPart();

				//todo some kind of datatype that can hold all elements
				virtual void getElements();
		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSUBSEQUENCE_HPP_
