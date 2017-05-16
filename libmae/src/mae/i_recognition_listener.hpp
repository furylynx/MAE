#ifndef MAE_I_RECOGNITION_LISTENER_HPP_
#define MAE_I_RECOGNITION_LISTENER_HPP_

//custom includes
//...

//global includes
#include <vector>
#include <memory>
#include <cstdint>


namespace mae
{

	/**
	 * Listener for poses. In notified each frame after the pose quantization.
	 */
	template <typename U>
	class i_recognition_listener
	{
		public:
			virtual ~i_recognition_listener(){}

			/**
			 * Is invoked each time sequences were recognized and the sequences are present.
			 *
			 * @param timestamp The associated timestamp.
			 * @param sequences The recognized sequences.
			 */
			virtual void on_recognition(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences) = 0;

			/**
			 * Is invoked each time sequences were recognized and only titles of the sequences are present.
			 *
			 * @param timestamp The associated timestamp.
			 * @param sequences The recognized sequences.
			 */
			virtual void on_recognition(uint64_t timestamp, std::vector<std::string> title) = 0;
	};

} // namespace mae

#endif // MAE_I_RECOGNITION_LISTENER_HPP_
