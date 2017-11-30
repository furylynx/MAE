//
// mae_similarity_evaluator.cpp - 2017-11-30
//

//custom includes
//...

//global includes
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <mae/mae.hpp>

#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


int main()
{

	std::cout << std::endl << "MAE Similarity Evaluator" << std::endl;
	std::cout << "===============" << std::endl << std::endl;

	std::vector<std::string> directories
	{
		"../mae_evaluator/evaluation_bvhs/clap/",
		"../mae_evaluator/evaluation_bvhs/dontcare/",
		"../mae_evaluator/evaluation_bvhs/hammer/",
		"../mae_evaluator/evaluation_bvhs/pinch/",
		"../mae_evaluator/evaluation_bvhs/rotation/",
		"../mae_evaluator/evaluation_bvhs/scrolldown/",
		"../mae_evaluator/evaluation_bvhs/scrollup/",
		"../mae_evaluator/evaluation_bvhs/swipe/",
		"../mae_evaluator/evaluation_bvhs/throw/",
		"../mae_evaluator/evaluation_bvhs/wave/"
    };

	std::vector<std::pair<std::string, std::shared_ptr<mae::fl::laban::laban_sequence_comparator> > > comparators;
    //TODO add all comparators to be compared


	bool performance_check = true;
	unsigned int buffer_size = 300;
	double hysteresis_value = 30.5;

	std::string rw_rules_file = "rw_rules.xml";

	std::vector<std::vector<int> > directory_recognized;
	std::vector<std::vector<int> > directory_fp;
	std::vector<std::vector<int> > directory_total;

	std::vector<int> recognized;
	std::vector<int> fp;
	std::vector<int> total;

	std::vector<std::string> sequence_titles;

	for (unsigned int j = 0; j < tolerances.size(); j++)
	{
		total.push_back(0);
		fp.push_back(0);
		recognized.push_back(0);
	}

	for (unsigned int i = 0; i < directories.size(); i++)
	{
		directory_recognized.push_back(std::vector<int>());
		directory_fp.push_back(std::vector<int>());
		directory_total.push_back(std::vector<int>());

		for (unsigned int j = 0; j < tolerances.size(); j++)
		{
			directory_recognized.at(i).push_back(0);
			directory_fp.at(i).push_back(0);
			directory_total.at(i).push_back(0);
		}
	}

	//body parts
	std::vector<mae::bone> body_parts
	{ mae::bone(mae::e_bone::LEFT_WHOLE_ARM), mae::bone(mae::e_bone::RIGHT_WHOLE_ARM),
		mae::bone(mae::e_bone::RIGHT_UPPER_ARM),
				mae::bone(mae::e_bone::RIGHT_FOREARM),
				mae::bone(mae::e_bone::LEFT_UPPER_ARM),
						mae::bone(mae::e_bone::LEFT_FOREARM) };
	std::vector<std::shared_ptr<mae::fl::laban::column_definition> > column_definitions
	{ std::shared_ptr<mae::fl::laban::column_definition>(new mae::fl::laban::column_definition(mae::e_bone::RIGHT_UPPER_ARM)),
		std::shared_ptr<mae::fl::laban::column_definition>(new mae::fl::laban::column_definition(mae::e_bone::RIGHT_FOREARM)),
		std::shared_ptr<mae::fl::laban::column_definition>(new mae::fl::laban::column_definition(mae::e_bone::LEFT_UPPER_ARM)),
		std::shared_ptr<mae::fl::laban::column_definition>(new mae::fl::laban::column_definition(mae::e_bone::LEFT_FOREARM))};

	//set up the movement controller
	mae::fl::fl_movement_controller movement_controller = mae::fl::fl_movement_controller(body_parts,
			column_definitions, buffer_size, mae::fl::laban::laban_sequence::default_beats_per_measure(),
			mae::fl::laban::laban_sequence::default_beat_duration(),
			mae::fl::laban::laban_sequence::default_time_unit(), 1.0 / 30.0, false);
	movement_controller.get_fl_pose_detector()->set_hysteresis_val(hysteresis_value);
	//movement_controller.get_laban_sequence_recognizer()->get_decision_forest()->set_cooldown(true);

	//add rewriting rules
	mae::fl::laban::rewriting_rules_reader rw_reader = mae::fl::laban::rewriting_rules_reader();
	std::vector<std::shared_ptr<mae::fl::laban::decision_value<mae::fl::laban::i_movement, std::vector<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > > > rw_rules = rw_reader.read_rules_file(rw_rules_file);

    //TODO use rewriting rules to create similar sequences; should use closest one for comparison


	mae::fl::laban::laban_sequence_reader s_reader = mae::fl::laban::laban_sequence_reader();
	mae::fl::bvh_controller bvh_ctrl = mae::fl::bvh_controller();

    std::unordered_map<std::string, std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > > dir_to_sequences;
    std::unordered_map<std::shared_ptr<mae::fl::laban::laban_sequence>, std::string> sequence_to_filename;

	for (unsigned int directory_id = 0; directory_id < directories.size(); directory_id++)
	{
		std::string directory = directories.at(directory_id);
		std::cout << "*** " << directory << " ***" << std::endl;

		if (boost::filesystem::is_directory(boost::filesystem::path(directory)))
		{
			boost::filesystem::path pp = boost::filesystem::path(directory);

            std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences_to_register;

			//register all sequences
			for (boost::filesystem::directory_iterator file_it = boost::filesystem::directory_iterator(pp);
					file_it != boost::filesystem::directory_iterator(); file_it++)
			{
				//read all sequences in the directory and register them
				boost::filesystem::directory_entry entry = *file_it;
				if (boost::filesystem::is_regular_file(entry.status()))
				{
					std::string file_path = entry.path().string();
					std::string file_name = entry.path().filename().string();

					if (file_name.rfind(".laban") == file_name.length() - 6)
					{
						try
						{
							std::shared_ptr<mae::fl::laban::laban_sequence> sequence = s_reader.read_sequence_file(file_path);

							if (sequence != nullptr)
							{
								std::cout << "registering \"" << sequence->get_title() << "\" from file '" << file_name
										<< "'" << std::endl;

                                sequences_to_register.push_back(sequence);
                                sequence_to_filename[sequence] = file_name;

								if (sequence_titles.size() == directory_id)
								{
									sequence_titles.push_back(sequence->get_title());
								}
							}
							else
							{
								std::cout << "!! Could not parse file '" << file_name << "' for it is null." << std::endl;
							}
						} catch (std::exception& e)
						{
							std::cout << "!! Could not parse file '" << file_name << "' (" << e.what() << ")" << std::endl;
						} catch (...)
						{
							std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
						}
					}
				}
			}

            dir_to_sequences[directory] = sequences_to_register;
        }
	}

	std::cout << std::endl << ">> All sequences registered. Comparing sequences now..." << std::endl << std::endl;

    for (std::pair<std::string, std::shared_ptr<mae::fl::laban::laban_sequence_comparator> > comparator_info : comparators)
    {
        std::string comparator_name = comparator_info.first;
        std::shared_ptr<mae::fl::laban::laban_sequence_comparator> comparator = comparator_info.second;

        for (unsigned int directory_id = 0; directory_id < directories.size(); directory_id++)
        {
            std::string directory = directories.at(directory_id);
            std::cout << "*** " << directory << " ***" << std::endl;

            if (boost::filesystem::is_directory(boost::filesystem::path(directory)))
            {
                boost::filesystem::path pp = boost::filesystem::path(directory);


                std::unordered_map<std::string, std::unordered_map<std::string, double> > values;

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
                                    file_path, mae::fl::bvh_spec::default_spec())->get_skeleton_data();



                            //send data
                            for (unsigned int i = 0; i < skeleton_data.size(); i++)
                            {
                                movement_controller.next_frame(0, skeleton_data.at(i));
                            }

                            //use sequence for comparison with target sequences
                            for (std::shared_ptr<mae::fl::laban::laban_sequence> target_sequence : dir_to_sequences.at(
                                    directory))
                            {
                                double similarity = comparator->similarity(target_sequence,
                                                                           movement_controller.get_current_sequence());

                                if (values.find(directory) != values.end())
                                {
                                    std::unordered_map<std::string, double> tbi;
                                    tbi[file_name] = similarity;
                                    values[sequence_to_filename.at(target_sequence)] = tbi;
                                }
                                else
                                {
                                    values.at(sequence_to_filename.at(target_sequence))[file_name] = similarity;
                                }
                            }

                            //use sequence for comparison with non-target sequences
                            for (std::pair<std::string, std::shared_ptr<mae::fl::laban::laban_sequence> > dir_pair : dir_to_sequences)
                            {
                                if (dir_pair.first != directory)
                                {
                                    for (std::shared_ptr<mae::fl::laban::laban_sequence> non_target_sequence : dir_pair.second)
                                    {

                                        double similarity = comparator->similarity(non_target_sequence, movement_controller.get_current_sequence());

                                        if (values.find(directory) != values.end())
                                        {
                                            std::unordered_map<std::string, double> tbi;
                                            tbi[file_name] = similarity;
                                            values[sequence_to_filename.at(non_target_sequence)] = tbi;
                                        }
                                        else
                                        {
                                            values.at(sequence_to_filename.at(non_target_sequence))[file_name] = similarity;
                                        }
                                    }
                                }
                            }


                            //clear buffer
                            movement_controller.clear_buffer();
                        }
                    }
                }


                //TODO evaluate values, print files, etc
            }
        }
    }

	//print rates
	std::cout << std::endl << std::endl << std::endl;

	for (unsigned int i = 0; i < directories.size(); i++)
	{
		for (unsigned int j = 0; j < tolerances.size(); j++)
		{
			std::cout << "dir " << directories.at(i) << " - tolerance " << tolerances.at(j) << " => "
					<< (double) directory_recognized.at(i).at(j) / directory_total.at(i).at(j) << " = " << directory_recognized.at(i).at(j) << "/" << directory_total.at(i).at(j) << std::endl;

			std::cout << "\t false positive: "
					<< (double) directory_fp.at(i).at(j) / directory_total.at(i).at(j) << " = " << directory_fp.at(i).at(j) << "/" << directory_total.at(i).at(j) << std::endl;
		}
	}

	std::cout << std::endl << std::endl << "::Overall rate::" << std::endl;
	for (unsigned int j = 0; j < tolerances.size(); j++)
	{
		std::cout << "tolerance " << tolerances.at(j) << " => " << (double) recognized.at(j) / total.at(j) << " = " << recognized.at(j) << "/" << total.at(j) << std::endl;
		std::cout << "\t false positive:" << (double) fp.at(j) / total.at(j) << " = " << fp.at(j) << "/" << total.at(j) << std::endl;
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
	std::cout << "Movement & \\multicolumn{" << tolerances.size() << "}{c}{Tolerance in Beats}\\\\";
	std::cout << " & ";
	for (unsigned int j = 0; j < tolerances.size(); j++)
	{
		std::cout << tolerances.at(j);
		if (j != tolerances.size() - 1)
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

		for (unsigned int j = 0; j < tolerances.size(); j++)
		{
			std::cout << std::setprecision(2)
					<< (double) directory_recognized.at(i).at(j) / directory_total.at(i).at(j);
			if (j != tolerances.size() - 1)
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
		std::cout << std::setprecision(2) << (double) recognized.at(j) / total.at(j);

		if (j != tolerances.size() - 1)
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
