/*
 * basis.hpp
 *
 *  Created on: 01.10.2014
 *      Author: keks
 */

#ifndef BASIS_HPP_
#define BASIS_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "vec3d.hpp"

//global includes
#include <memory>

namespace mae
{

	class basis
	{
		public:
			/**
			 * Creates a new coordinate basis.
			 *
			 * @param position_vector The position vector of the basis.
			 * @param u The first direction.
			 * @param r The second direction.
			 * @param t The third direction.
			 */
			basis(std::shared_ptr<vec3d> position_vector, std::shared_ptr<vec3d> u, std::shared_ptr<vec3d> r, std::shared_ptr<vec3d> t);
			virtual ~basis();

			/**
			 * Returns the first component of the basis.
			 *
			 * @return The u.
			 */
			virtual std::shared_ptr<vec3d> get_u();

			/**
			 * Returns the second component of the basis.
			 *
			 * @return The r.
			 */
			virtual std::shared_ptr<vec3d> get_r();

			/**
			 * Returns the third component of the basis.
			 *
			 * @return The t.
			 */
			virtual std::shared_ptr<vec3d> get_t();

			/**
			 * Returns the position vector of the basis.
			 *
			 * @return The position_vector.
			 */
			virtual std::shared_ptr<vec3d> get_position_vector();

			/**
			 * Sets the first component for the basis.
			 *
			 * @param u The u.
			 */
			virtual void set_u(std::shared_ptr<vec3d> u);

			/**
			 * Sets the second component for the basis.
			 *
			 * @param r The r.
			 */
			virtual void set_r(std::shared_ptr<vec3d> r);

			/**
			 * Sets the third component for the basis.
			 *
			 * @param t The t.
			 */
			virtual void set_t(std::shared_ptr<vec3d> t);

			/**
			 * Sets the position_vector for the basis.
			 *
			 * @param position_vector The t.
			 */
			virtual void set_position_vector(std::shared_ptr<vec3d> position_vector);

		private:
			std::shared_ptr<vec3d> position_vector_;

			std::shared_ptr<vec3d> u_;
			std::shared_ptr<vec3d> r_;
			std::shared_ptr<vec3d> t_;

	};

} // namespace mae

#endif // BASIS_HPP_
