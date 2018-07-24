/*
 * evallistener.cpp
 *
 *  Created on: 14.10.2014
 *      Author: furylynx
 */

#include "eval_listener.hpp"

namespace eval
{

	eval_listener::eval_listener()
	{
		recognized_ = false;
		false_positive_ = false;
	}

	eval_listener::~eval_listener()
	{
		// TODO Auto-generated destructor stub
	}

	bool eval_listener::sequence_recognized()
	{
		return recognized_;
	}

	bool eval_listener::sequence_false_positive()
	{
		return false_positive_;
	}

	void eval_listener::add_sequence(std::shared_ptr<mae::fl::laban::laban_sequence> sequence, std::string folder_name)
	{
		sequence_folder_map_[sequence] = folder_name;
		//sequence_folder_map_.insert(std::make_pair<std::shared_ptr<mae::fl::laban::laban_sequence>, std::string>(sequence, folder_name));
	}

	void eval_listener::reset(std::string folder_name)
	{
		current_folder_ = folder_name;

		recognized_ = false;
		false_positive_ = false;
		false_positive_set_.clear();
	}

	void eval_listener::on_recognition(uint64_t timestamp,
			std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences)
	{
		if (sequences.size() == 0)
		{
			std::cout << ">>> recognized, but no sequence transmitted... <<<" << std::endl;
		}

		for (std::size_t i = 0; i < sequences.size(); i++)
		{

			std::shared_ptr<mae::fl::laban::laban_sequence> s = sequences.at(i);
			if (sequence_folder_map_.find(s) != sequence_folder_map_.end())
			{
				std::string sequence_folder = sequence_folder_map_.at(s);

				if (sequence_folder == current_folder_)
				{
					recognized_ = true;
				}
				else
				{
					if (false_positive_set_.find(s) == false_positive_set_.end())
					{
						std::cout << "! false positive : " << s->get_title() << std::endl;
						false_positive_ = true;
						false_positive_set_.insert(s);
					}
				}
			}
			else
			{
				if (false_positive_set_.find(s) == false_positive_set_.end())
				{
					std::cout << "! false positive (not registered) : " << s->get_title() << std::endl;
					false_positive_ = true;
					false_positive_set_.insert(s);
				}
			}
		}
	}

	void eval_listener::on_recognition(uint64_t timestamp, std::vector<std::string> title)
	{
		//do nothing
	}

} // namespace mae
