#ifndef MAE_MATH_MATH_HPP_
#define MAE_MATH_MATH_HPP_

//custom includes
#include "../fl/angular_joint.hpp"

#include "vec3d.hpp"
#include "basis.hpp"
#include "i_distance_measure.hpp"
#include "minkowski_distance.hpp"
#include "cosine_similarity.hpp"
#include "mahalanobis_distance.hpp"
#include "i_similarity_measure.hpp"
#include "dtw.hpp"
#include "discrete_frechet_distance.hpp"
#include "lcs_distance.hpp"
#include "../general_joint.hpp"

//global includes
#include <vector>
#include <cmath>
#include <memory>

//defines
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2		1.57079632679489661923
#endif


namespace mae
{
	namespace math
	{

		class math
		{
			public:


				/**
				 * Projects the point to the new basis given in coordinates of the points current basis.
				 *
				 * @param point The point to be translated.
				 * @param basis The basis
				 * @param position_vector The position vector. Null when using the one from the basis.
				 * @return The result.
				 */
				static std::shared_ptr<vec3d> project_to_basis(std::shared_ptr<vec3d> point, std::shared_ptr<basis> basis, std::shared_ptr<vec3d> position_vector = nullptr);

				/**
				 * Projects the point given by the basis to the default coordinate system.
				 *
				 * @param point The point to be translated.
				 * @param basis The basis
				 * @param position_vector The position vector. Null when using the one from the basis.
				 * @return The result.
				 */
				static std::shared_ptr<vec3d> project_back_to_default(std::shared_ptr<vec3d> point, std::shared_ptr<basis> basis, std::shared_ptr<vec3d> position_vector = nullptr);

				/**
				 * Translates the angle in radian to degree.
				 *
				 * @param val The angle in radian.
				 * @return The angle in degree.
				 */
				static double rad_to_deg(double val);

				/**
				 * Translates the angle in degree to radian.
				 *
				 * @param val The angle in degree.
				 * @return The angle in radian.
				 */
				static double deg_to_rad(double val);

				/**
				 * Returns true if the vectors are approximately collinear.
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @return True if collinear.
				 */
				static bool are_collinear(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b);

				/**
				 * Calculates the angle in radian oriented to the plane whose normal is given (-PI to PI).
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @param normal The normal to the plane.
				 * @return The result.
				 */
				static double calc_angle_plane(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b, std::shared_ptr<vec3d> normal);

				/**
				 * Calculates the angle in degree oriented to the plane whose normal is given (-180 to 180 degree).
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @param normal The normal to the plane.
				 * @return The result.
				 */
				static double calc_angle_plane_deg(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b, std::shared_ptr<vec3d> normal);

				/**
				 * Calculates the angle in radian between the two vectors (0 to PI).
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @return The result.
				 */
				static double calc_angle_half(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b);

				/**
				 * Calculates the angle in degree between the two vectors (0 to 180 degree).
				 *
				 * @param a The vector a.
				 * @param b The vector a.
				 * @return The result.
				 */
				static double calc_angle_half_deg(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b);

				/**
				 * Returns x = a mod b, using the modulo operation for floating-point values. The result is positive only.
				 *
				 * @param a
				 * @param b
				 * @return x = a mod b on [0, b).
				 */
				static double fmod_pos(double a, double b);

				/**
				 * Returns the sign of a double value. Zero if x is zero, -1 if x is less than zero and 1 if x is greater than zero.
				 *
				 * @param x The double value.
				 * @return The sign.
				 */
				static int sign(double x);

				/**
				 * Returns the result of the p-norm.
				 *
				 * @param vector The vector.
				 * @return The result of the p-norm.
				 */
				static double p_norm(std::vector<double> vector, double p);

				/**
				 * Returns the normalized vector using p-norm.
				 *
				 * @param vector The vector.
				 * @return The result of the p-norm.
				 */
				static std::vector<double> p_normalize(std::vector<double> vector, double p);

		};

	} // namespace math
} // namespace mae

#endif // MAE_MATH_MATH_HPP_
