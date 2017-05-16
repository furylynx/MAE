#ifndef MAE_FL_LABAN_DECISION_VALUE_HPP_
#define MAE_FL_LABAN_DECISION_VALUE_HPP_

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
					/**
					 * Creates a new decision value for a sequence. It contains the sequence and the associated value.
					 *
					 * @param sequence The sequence.
					 * @param value The value.
					 */
					decision_value(std::vector<std::shared_ptr<T> > sequence, std::shared_ptr<U> value);

					/**
					 * Creates a new decision value for a sequence. It contains the sequence, which in this case is
					 * assumed to be empty, and the associated value.
					 *
					 * @param value The value.
					 */
					decision_value(std::shared_ptr<U> value);
					virtual ~decision_value();

					/**
					 * Returns the sequence.
					 *
					 * @return The sequence.
					 */
					virtual std::vector<std::shared_ptr<T> > get_sequence();

					/**
					 * Returns the value.
					 *
					 * @return The value.
					 */
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
			decision_value<T,U>::decision_value(std::shared_ptr<U> value)
			{
				sequence_ = std::vector<std::shared_ptr<T> >();
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


#endif // MAE_FL_LABAN_DECISION_VALUE_HPP_
