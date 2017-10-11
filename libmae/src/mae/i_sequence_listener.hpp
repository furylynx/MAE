#ifndef MAE_I_SEQUENCE_LISTENER_HPP_
#define MAE_I_SEQUENCE_LISTENER_HPP_

//custom includes
//...

//global includes
#include <memory>
#include <cstdint>

namespace mae
{
	/**
	 * Listener for sequences. Is invoked each time a sequence was generated (which occurs in each frame).
	 */
	template <typename U>
	class i_sequence_listener
	{
		public:
			virtual ~i_sequence_listener(){}

			/**
			 * Is invoked each time a sequence was generated (which occurs on every frame).
			 *
			 * @param timestamp The associated timestamp.
			 * @param sequence The generated sequence.
			 */
			virtual void on_sequence(uint64_t timestamp, std::shared_ptr<U> sequence) = 0;
	};

} // namespace mae

#endif // MAE_I_SEQUENCE_LISTENER_HPP_
