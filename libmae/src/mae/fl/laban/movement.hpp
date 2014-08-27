/*
 * labanmovement.hpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "i_movement.hpp"
#include "ps/i_pre_sign.hpp"
#include "mv/i_symbol.hpp"

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <ios>
#include <iomanip>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

		class movement : public i_movement
		{
			public:
				/**
				 * Creates a movement element which represents a movement symbol in the
				 * score (e.g. direction and level or a turn) and (if present) a hold sign.
				 *
				 * @param column The column to which this symbol is meant to be added.
				 * @param measure The measure in which this symbol starts (and therefore the motion).
				 * @param beat The beat (decimals allowed) of the measure which is the beginning of the motion.
				 * @param duration The duration of the symbol (given in an amount of beats).
				 * @param symbol The symbol defining the kind of movement (e.g. direction+level or turn)
				 * @param hold If true a hold sign is attached to symbol.
				 * @param pre_sign A pre-sign which can be used to address another body part than the one defined by the column.
				 */
				movement(int column, unsigned int measure, double beat, double duration, std::shared_ptr<mv::i_symbol> symbol, bool hold = false, std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr);
				virtual ~movement();

				/**
				 * Returns the column to which this symbol was added.
				 *
				 * @return
				 */
				virtual int get_column();

				/**
				 * Returns the measure in which this symbols begins.
				 * @return
				 */
				virtual unsigned int get_measure();

				/**
				 * Returns the beat in which this symbol begins.
				 *
				 * @return
				 */
				virtual double get_beat();

				/**
				 * Returns the duration of the symbol.
				 *
				 * @return
				 */
				virtual double get_duration();

				/**
				 * Returns the pre sign if assigned. Returns null otherwise.
				 *
				 * @return
				 */
				std::shared_ptr<ps::i_pre_sign> get_pre_sign();

				/**
				 * Returns true if a hold sign is attached.
				 *
				 * @return
				 */
				bool get_hold();

				/**
				 * Returns the movement symbol.
				 *
				 * @return
				 */
				std::shared_ptr<mv::i_symbol> get_symbol();

				/**
				 * Returns the XML representation for this element.
				 *
				 * @param indent The applied indent.
				 * @param namesp The prefixed XML namespace.
				 *
				 * @return The XML string.
				 */
				virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

				/**
				 * Returns the string representation for this element.
				 *
				 * @return The string.
				 */
				virtual std::string str() const;

				friend std::ostream& operator<<(std::ostream& os, const movement& obj)
				{
					os << obj.str();
					return os;
				}

				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<movement>& obj)
				{
					os << obj->str();
					return os;
				}


			private:
				int column_;
				unsigned int measure_;
				double beat_;
				double duration_;
				std::shared_ptr<ps::i_pre_sign> pre_sign_;
				bool hold_;
				std::shared_ptr<mv::i_symbol> symbol_;

		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABANMOVEMENT_HPP_
