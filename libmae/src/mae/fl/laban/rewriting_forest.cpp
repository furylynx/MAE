/*
 * rewriting_rules.cpp
 *
 *  Created on: 13.08.2014
 *      Author: keks
 */

#include "rewriting_forest.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			rewriting_forest::rewriting_forest()
			{
				// TODO Auto-generated constructor stub

			}

			rewriting_forest::~rewriting_forest()
			{
				// TODO Auto-generated destructor stub
			}

			std::vector<std::vector<std::shared_ptr<i_movement> > > rewriting_forest::replacements(
					std::vector<std::shared_ptr<i_movement> > sequence)
			{
				std::vector<std::vector<std::shared_ptr<i_movement> > > result;

				//TODO handle replacements in here : use decision trees for this

				//check the whole sequence for continous movements (no break, same length) : index pos
				//check decision forest for matches for the continous subsequence
				//replace subsequences of continous subsequence from index pos to size of the match
				//this does replace the first match; any other match must be applied on all previous possible sequences... big mess but must be done


				return result;
			}

			void rewriting_forest::add_rule(std::vector<std::shared_ptr<i_movement> > sequence, std::vector<std::vector<std::shared_ptr<i_movement> > > replacements)
			{
				//TODO add rule to correct decision tree
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
