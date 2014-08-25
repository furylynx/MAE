//============================================================================
// Name        : maetest.cpp
// Author      : fury lynx
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

#include <mae/fl/math.hpp>
#include <mae/hierarchy.hpp>
#include <mae/hierarchy_element.hpp>

#include <memory>
#include <mae/fl/laban/laban_sequence.hpp>
#include <mae/fl/laban/laban_sequence_reader.hpp>

#include <mae/bone.hpp>
#include <mae/e_bone.hpp>
#include <mae/e_joint.hpp>
#include <mae/fl/laban/laban_sequence_recognizer.hpp>



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

	mae::fl::laban::laban_sequence_reader sr = mae::fl::laban::laban_sequence_reader();

	std::shared_ptr<mae::fl::laban::laban_sequence> sequence = sr.read_sequence_file("/home/keks/new_file.laban");

	std::ofstream outfile("/home/keks/new_file_rewritten.laban");
	outfile << sequence->xml();
	outfile.close();

}

void test_recognition()
{

	//TODO generate decision tree and check whether the recognition work at this point
	mae::fl::laban::laban_sequence_recognizer recog = mae::fl::laban::laban_sequence_recognizer();

	mae::fl::laban::laban_sequence_reader sr = mae::fl::laban::laban_sequence_reader();
	std::shared_ptr<mae::fl::laban::laban_sequence> sequence_one = sr.read_sequence_file("/home/keks/new_file.laban");
//	std::shared_ptr<mae::fl::laban::laban_sequence> sequence_two = sr.read_sequence_file("/home/keks/sequence2.laban");
//	std::shared_ptr<mae::fl::laban::laban_sequence> sequence_three = sr.read_sequence_file("/home/keks/sequence3.laban");
//	std::shared_ptr<mae::fl::laban::laban_sequence> sequence_four = sr.read_sequence_file("/home/keks/sequence4.laban");

	std::vector<mae::bone> bones;
	bones.push_back(mae::bone(mae::e_bone_c::to_int(mae::e_bone::LEFT_WHOLE_ARM), "left arm", mae::e_joint_c::to_int(mae::e_joint::LEFT_SHOULDER), mae::e_joint_c::to_int(mae::e_joint::LEFT_HAND)));
	bones.push_back(mae::bone(mae::e_bone_c::to_int(mae::e_bone::RIGHT_WHOLE_ARM), "right arm", mae::e_joint_c::to_int(mae::e_joint::RIGHT_SHOULDER), mae::e_joint_c::to_int(mae::e_joint::RIGHT_HAND)));


	recog.register_sequence(sequence_one);
	std::cout << "registered the sequences. Trying to recognize now..." << std::endl;
	std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > recognized_sequences = recog.recognize_sequence(sequence_one, bones);

	std::cout << "recognized " << (int)recognized_sequences.size() << " sequences! " << std::endl;
}

int main() {

	// prints Hello
	std::cout << "Hello" << std::endl;

	cv::Vec3d a = cv::Vec3d(1,0,0);
	cv::Vec3d b = cv::Vec3d(-1,-1,0);
	cv::Vec3d normal = cv::Vec3d(0,0,1);
	double result = mae::fl::math::calc_angle_half_deg(a, b);

	std::cout << "result: " << result << std::endl;

	//test_hierarchy();
	//test_sequence();
	test_recognition();

	std::cout << "done" << std::endl;
	return 0;
}




