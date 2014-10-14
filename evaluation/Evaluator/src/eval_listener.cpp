/*
 * evallistener.cpp
 *
 *  Created on: 14.10.2014
 *      Author: keks
 */

#include "eval_listener.hpp"

namespace eval
{

	eval_listener::eval_listener()
	{
		recognized_ = false;
	}

	eval_listener::~eval_listener()
	{
		// TODO Auto-generated destructor stub
	}

	bool eval_listener::sequence_recognized()
	{
		return recognized_;
	}

	void eval_listener::reset()
	{
		recognized_ = false;
	}

	void eval_listener::on_recognition(long timestamp,
			std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences)
	{
		recognized_ = true;
	}

	void eval_listener::on_recognition(long timestamp, std::vector<std::string> title)
	{
		//do nothing
	}

} // namespace mae
