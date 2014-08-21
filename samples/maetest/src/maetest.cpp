//============================================================================
// Name        : maetest.cpp
// Author      : fury lynx
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <mae/fl/math.hpp>
#include <mae/hierarchy.hpp>
#include <mae/hierarchy_element.hpp>

#include <mae/fl/laban/laban_sequence_reader.hpp>

void test_hierarchy()
 {
		mae::hierarchy h = mae::hierarchy(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(1, "root")));
		h.get_root()->push_front(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(2, "child1")));
		h.get_root()->push_front(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(3, "child2")));
		h.get_root()->get_children().at(0)->push_front(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(4, "child3")));

		std::shared_ptr<mae::hierarchy_element> element = std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(5, "child4"));
		element->push_back(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(6, "child5")));
		element->push_back(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(7, "child6")));
		element->get_children().at(0)->push_back(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(8, "child7")));
		element->get_children().at(0)->push_back(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(9, "child8")));
		element->get_children().at(1)->push_back(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(10, "child9")));
		element->get_children().at(1)->push_back(std::shared_ptr<mae::hierarchy_element>(new mae::hierarchy_element(11, "child10")));

		h.get_root()->push_back(element);

		mae::hierarchy h2 = mae::hierarchy(std::shared_ptr<mae::hierarchy_element>(h.get_root()));

		std::cout << "h " << h.str() << std::endl;

		std::cout << "h2 " << h2.str() << std::endl;
 }

void test_sequence()
{

	//mae::fl::laban::laban_sequence_reader::read_sequence()

}

int main() {

	// prints Hello
	std::cout << "Hello" << std::endl;

	cv::Vec3d a = cv::Vec3d(1,0,0);
	cv::Vec3d b = cv::Vec3d(-1,-1,0);
	cv::Vec3d normal = cv::Vec3d(0,0,1);
	double result = mae::fl::math::calc_angle_half_deg(a, b);

	std::cout << "result: " << result << std::endl;

	test_hierarchy();

	std::cout << "done" << std::endl;
	return 0;
}




