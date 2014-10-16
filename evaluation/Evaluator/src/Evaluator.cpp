//============================================================================
// Name        : Evaluator.cpp
// Author      : fury lynx
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

//custom includes
#include "eval_listener.hpp"

//global includes
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>

//#include <mae/indexer_fix.hpp>

#include <mae/mae.hpp>
#include <mae/demo/demo.hpp>

#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{

	std::cout << std::endl << "Evaluator" << std::endl;
	std::cout << "===============" << std::endl << std::endl;

	std::vector<std::string> directories
	{ //"bvhs/cut/", "bvhs/dontcare/" , "bvhs/indi/" , "bvhs/raise/" , "bvhs/sequential/" , "bvhs/wheel/"
		"bvhs/cut_single/"
	};

	std::vector<double> tolerances
	{ 0.5
		//, 1.0, 1.5, 2.0, 2.5
		//, 3.0
		//, 3.5
		//, 4.0
		//, 4.5
		//, 5.0
	};

	std::vector<std::vector<int> > directory_recognized;
	std::vector<std::vector<int> > directory_total;

	std::vector<int> recognized;
	std::vector<int> total;

	std::vector<std::string> sequence_titles;

	for (unsigned int j = 0; j < tolerances.size(); j++)
	{
		total.push_back(0);
		recognized.push_back(0);
	}

	for (unsigned int i = 0; i < directories.size(); i++)
	{
		directory_recognized.push_back(std::vector<int>());
		directory_total.push_back(std::vector<int>());

		for (unsigned int j = 0; j < tolerances.size(); j++)
		{
			directory_recognized.at(i).push_back(0);
			directory_total.at(i).push_back(0);
		}
	}

	//body parts
	std::vector<mae::bone> body_parts
	{ mae::bone(mae::e_bone::LEFT_WHOLE_ARM), mae::bone(mae::e_bone::RIGHT_WHOLE_ARM), mae::bone(
			mae::e_bone::RIGHT_UPPER_ARM), mae::bone(mae::e_bone::RIGHT_FOREARM) };
	std::vector<std::shared_ptr<mae::fl::laban::column_definition> > column_definitions
	{ std::shared_ptr<mae::fl::laban::column_definition>(
			new mae::fl::laban::column_definition(mae::e_bone::RIGHT_UPPER_ARM)), std::shared_ptr<
			mae::fl::laban::column_definition>(new mae::fl::laban::column_definition(mae::e_bone::RIGHT_FOREARM)) };

	//set up the movement controller
	int buffer_size = 4800;
	mae::fl::fl_movement_controller movement_controller = mae::fl::fl_movement_controller(body_parts,
			column_definitions, buffer_size, mae::fl::laban::laban_sequence::default_beats_per_measure(),
			mae::fl::laban::laban_sequence::default_beat_duration(),
			mae::fl::laban::laban_sequence::default_time_unit(), 1.0 / 30.0, false);

	//add listener to the controller
	std::shared_ptr<eval::eval_listener> eval_listener = std::shared_ptr<eval::eval_listener>(new eval::eval_listener());
	movement_controller.add_listener(eval_listener);

	mae::fl::laban::laban_sequence_reader s_reader = mae::fl::laban::laban_sequence_reader();
	mae::fl::bvh_controller bvh_ctrl = mae::fl::bvh_controller();
	mae::demo::fl::laban_visualizer vis = mae::demo::fl::laban_visualizer();

	for (unsigned int directory_id = 0; directory_id < directories.size(); directory_id++)
	{
		std::string directory = directories.at(directory_id);
		std::cout << "*** " << directory << " ***" << std::endl;

		if (boost::filesystem::is_directory(boost::filesystem::path(directory)))
		{
			boost::filesystem::path pp = boost::filesystem::path(directory);

			//set tolerance to 0.5 for sequence registration
			movement_controller.set_recognition_tolerance(0.5);

			//register all sequences
			for (boost::filesystem::directory_iterator file_it = boost::filesystem::directory_iterator(pp);
					file_it != boost::filesystem::directory_iterator(); file_it++)
			{
				//read all sequences in the directory and register them to the controller

				boost::filesystem::directory_entry entry = *file_it;
				if (boost::filesystem::is_regular_file(entry.status()))
				{
					std::string file_path = entry.path().string();
					std::string file_name = entry.path().filename().string();

					if (file_name.rfind(".laban") == file_name.length() - 6)
					{
						try
						{
							std::shared_ptr<mae::fl::laban::laban_sequence> sequence = s_reader.read_sequence_file(
									file_path);
							if (sequence != nullptr)
							{
								std::cout << "registering \"" << sequence->get_title() << "\" from file '" << file_name
										<< "'" << std::endl;
								movement_controller.register_sequence(sequence);

								if (sequence_titles.size() == directory_id)
								{
									sequence_titles.push_back(sequence->get_title());
								}
							}
							else
							{
								std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
							}
						} catch (std::exception& e)
						{
							std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
						} catch (...)
						{
							std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
						}
					}
				}
			}

			//handle each bvh - determine recognition rate
			for (boost::filesystem::directory_iterator file_it = boost::filesystem::directory_iterator(pp);
					file_it != boost::filesystem::directory_iterator(); file_it++)
			{
				boost::filesystem::directory_entry entry = *file_it;
				if (boost::filesystem::is_regular_file(entry.status()))
				{
					std::string file_path = entry.path().string();
					std::string file_name = entry.path().filename().string();

					if (file_name.rfind(".bvh") == file_name.length() - 4)
					{
						//parse and send to movement controller
						std::vector<std::shared_ptr<mae::general_skeleton> > skeleton_data = bvh_ctrl.read_bvh_file(
								file_path, mae::fl::bvh_spec::default_spec()).first;

						for (unsigned int tolerance_id = 0; tolerance_id < tolerances.size(); tolerance_id++)
						{
							//update tolerance
							double tolerance = tolerances.at(tolerance_id);
							movement_controller.set_recognition_tolerance(tolerance);
							eval_listener->reset();

							double max_dur = 0;
							double mean_dur = 0;
							//send data
							for (unsigned int i = 0; i < skeleton_data.size(); i++)
							{
								boost::posix_time::ptime time1 = boost::posix_time::microsec_clock::universal_time();
								movement_controller.next_frame(0, skeleton_data.at(i));
								boost::posix_time::ptime time2 = boost::posix_time::microsec_clock::universal_time();
								std::cout << "frame " << i << " / " << skeleton_data.size() << " # " << time1 << " -> ";
								std::cout << time2 << " ::  " << (time2 - time1).total_milliseconds() <<  std::endl;
								if (i >= buffer_size)
								{
									mean_dur += (time2 - time1).total_milliseconds();
								}

								if ((time2 - time1).total_milliseconds() > max_dur)
								{
									max_dur = (time2 - time1).total_milliseconds();
								}
							}

							std::cout << "max dur : " << max_dur << " | mean dur : " << std::setprecision(2) << (mean_dur/(skeleton_data.size()-buffer_size)) << std::endl;

							if (tolerance_id == 0 && movement_controller.get_current_sequence() != nullptr)
							{
								std::stringstream exp_path;
								exp_path << "labansequences/" << file_name << ".laban";

								std::stringstream png_exp_path;
								png_exp_path << "labansequences/" << file_name << ".bmp";

								//print sequence
								movement_controller.get_current_sequence()->xml_file(exp_path.str());
								//draw png
								vis.png(png_exp_path.str(), movement_controller.get_current_sequence(), 1280, 720);
							}

							//clear buffer
							movement_controller.clear_buffer();

							//update results
							total[tolerance_id]++;
							directory_total.at(directory_id)[tolerance_id]++;
							if (eval_listener->sequence_recognized()) //check listener whether recognition was made
							{
								recognized[tolerance_id]++;
								directory_recognized.at(directory_id)[tolerance_id]++;

								std::cout << " ++ " << file_path << " : was recognized with tolerance "
																		<< tolerances.at(tolerance_id) << " °° " << std::endl;
							}
							else
							{
								std::cout << " -- " << file_path << " : not recognized with tolerance "
										<< tolerances.at(tolerance_id) << " ## " << std::endl;
							}
						}

					}
				}
			}

			//clear all registered sequences
			movement_controller.clear_registered_sequences();

		}

	}

	//print rates
	std::cout << std::endl << std::endl << std::endl;

	for (unsigned int i = 0; i < directories.size(); i++)
	{
		for (unsigned int j = 0; j < tolerances.size(); j++)
		{
			std::cout << "dir " << directories.at(i) << " - tolerance " << tolerances.at(j) << " => "
					<< (double) directory_recognized.at(i).at(j) / directory_total.at(i).at(j) << std::endl;
		}
	}

	std::cout << std::endl << std::endl << "::Overall rate::" << std::endl;
	for (unsigned int j = 0; j < tolerances.size(); j++)
	{
		std::cout << "tolerance " << tolerances.at(j) << " => " << (double) recognized.at(j) / total.at(j) << std::endl;
	}


	//LATEX table
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "::: LaTeX table :::" << std::endl << std::endl;


	std::cout << "\\begin{table}[H]%" << std::endl;
	std::cout << "\\setlength\\extrarowheight{5pt}" << std::endl;
	std::cout << "\\begin{tabular}{l | ";
	for (unsigned int j = 0; j < tolerances.size(); j++)
	{
		std::cout << " c";
	}
	std::cout << "}" << std::endl;
	std::cout << "\\hline" << std::endl;
	std::cout << "Tolerance in beats & ";
	for (unsigned int j = 0; j<tolerances.size(); j++)
	{
		std::cout << tolerances.at(j);
		if (j != tolerances.size()-1)
		{
			std::cout << " & ";
		}
	}
	std::cout << "\\\\" << std::endl;
	std::cout << "\\hline" << std::endl;
	for (unsigned int i = 0; i < directories.size(); i++)
	{
		if (sequence_titles.size() > i)
		{
			std::cout << sequence_titles.at(i) << " & ";
		}
		else
		{
			std::cout << directories.at(i) << " & ";
		}

		for (unsigned int j = 0; j<tolerances.size(); j++)
		{
			std::cout << std::setprecision(2) << (double)directory_recognized.at(i).at(j)/directory_total.at(i).at(j);
			if (j != tolerances.size()-1)
			{
				std::cout << " & ";
			}
		}

		std::cout << " \\\\" << std::endl;
	}

	std::cout << "\\hline" << std::endl;
	std::cout << "Total" << " & ";

	for (unsigned int j = 0; j < tolerances.size(); j++)
	{
		std::cout << std::setprecision(2) << (double)recognized.at(j)/total.at(j);

		if (j != tolerances.size()-1)
		{
			std::cout << " & ";
		}
	}

	std::cout << " \\\\" << std::endl;
	std::cout << "\\hline" << std::endl;
	std::cout << "\\end{tabular}" << std::endl;
	std::cout << "\\caption[The recognition rates of the engine.]{The recognition rates of the engine.}" << std::endl;
	std::cout << "\\label{tab:recognition-rates}" << std::endl;
	std::cout << "\\end{table}" << std::endl;


	return 0;
}
