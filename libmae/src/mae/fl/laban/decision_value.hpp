/*
 * decision_value.hpp
 *
 *  Created on: 14.08.2014
 *      Author: keks
 */

#ifndef DECISION_VALUE_HPP_
#define DECISION_VALUE_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <memory>
#include <vector>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			//T: decision item
			//U: treasure item
			template <typename T, typename U>
			class decision_value
			{
				public:
					decision_value(std::vector<std::shared_ptr<T> > sequence, std::shared_ptr<U> value);
					virtual ~decision_value();

					virtual std::vector<std::shared_ptr<T> > get_sequence();
					virtual std::shared_ptr<U> get_value();

				private:
					std::vector<std::shared_ptr<T> > sequence_;
					std::shared_ptr<U> value_;
			};

		} // namespace laban
	} // namespace fl
} // namespace mae






//------------------------------
// template implementation
//------------------------------



namespace mae
{
	namespace fl
	{
		namespace laban
		{

			template <typename T, typename U>
			decision_value<T,U>::decision_value(std::vector<std::shared_ptr<T> > sequence, std::shared_ptr<U> value)
			{
				sequence_ = sequence;
				value_ = value;
			}

			template <typename T, typename U>
			decision_value<T,U>::~decision_value()
			{
			}

			template <typename T, typename U>
			std::vector<std::shared_ptr<T> > decision_value<T,U>::get_sequence()
			{
				return sequence_;
			}

			template <typename T, typename U>
			std::shared_ptr<U> decision_value<T,U>::get_value()
			{
				return value_;
			}

		}
	}
}


#endif // DECISION_VALUE_HPP_
