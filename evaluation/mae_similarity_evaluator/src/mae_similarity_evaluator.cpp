//
// mae_similarity_evaluator.cpp - 2017-11-30
//

//custom includes
#include "database.hpp"
#include "convenience.hpp"
#include "comparators.hpp"


//global includes
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <mae/mae.hpp>

#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

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

    std::vector<comparator_info> comparators = initialize_comparators();

    std::vector<std::string> comparator_names;
    std::vector<std::string> comparator_descriptions;
    for (comparator_info cinfo : comparators)
    {
        comparator_names.push_back(cinfo.name);
        comparator_descriptions.push_back(cinfo.description);
    }


	bool performance_check = true;
	unsigned int buffer_size = 300;
	double hysteresis_value = 30.5;

	std::string rw_rules_file = "rw_rules.xml";

    //prepare database
    std::string database_file = "mae_similarity_evaluation.db";
    sqlite3* db = open_database(database_file);
    create_tables_if_not_exist(db);

    //intialize comparators table and set ids
    comparators = map_comparator_ids(comparators, prepare_comparators(db, comparator_names, comparator_descriptions));

    // get rid of comparators already done
    std::cout << "Processing only comparators:" << std::endl;
    for (std::vector<comparator_info>::iterator it = comparators.begin(); it != comparators.end(); )
    {
        if(1 == check_comparator_done(db, (*it).id))
        {
            it = comparators.erase(it);
        }
        else
        {
            std::cout << (*it).id << " " << (*it).name << std::endl;

            //step
            ++it;
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

    //registering target sequences
	mae::fl::laban::laban_sequence_reader s_reader = mae::fl::laban::laban_sequence_reader();

    std::vector<laban_sequence_info> target_sequences;

	for (std::size_t directory_id = 0; directory_id < directories.size(); directory_id++)
	{
		std::string directory = directories.at(directory_id);
		std::cout << "*** " << directory << " ***" << std::endl;

		if (boost::filesystem::is_directory(boost::filesystem::path(directory)))
		{

			//register all sequences
			for (boost::filesystem::directory_iterator file_it = boost::filesystem::directory_iterator(boost::filesystem::path(directory));
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

                                target_sequences.push_back(initialize_laban_sequence_info(insert_sequence(db, file_path, file_name, directory, sequence->get_title(), sequence->xml(), 1), file_path, file_name, directory, sequence));
							}
							else
							{
								std::cout << "!! Could not parse file '" << file_name << "' for it is null." << std::endl;
							}
						}
                        catch (std::exception& e)
						{
							std::cout << "!! Could not parse file '" << file_name << "' (" << e.what() << ")" << std::endl;
						}
                        catch (...)
						{
							std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
						}
					}
				}
			}
        }
	}

    //generating sequences
	std::cout << std::endl << ">> All target sequences registered. Generating sequences for bvh files now..." << std::endl << std::endl;

    mae::fl::bvh_controller bvh_ctrl = mae::fl::bvh_controller();

    std::vector<laban_sequence_info> generated_sequences;

    for (std::size_t directory_id = 0; directory_id < directories.size(); directory_id++)
    {
        std::string directory = directories.at(directory_id);
        std::cout << "*** " << directory << " ***" << std::endl;

        if (boost::filesystem::is_directory(boost::filesystem::path(directory)))
        {
            //handle each bvh - determine recognition rate
            for (boost::filesystem::directory_iterator file_it = boost::filesystem::directory_iterator(boost::filesystem::path(directory));
                 file_it != boost::filesystem::directory_iterator(); file_it++)
            {
                boost::filesystem::directory_entry entry = *file_it;
                if (boost::filesystem::is_regular_file(entry.status()))
                {
                    std::string file_path = entry.path().string();
                    std::string file_name = entry.path().filename().string();

					if (file_name.rfind(".bvh") == file_name.length() - 4)
					{

						sequence_entry entry = select_sequence_by_path(db, file_path);

						if (entry.id >= 0)
						{
							std::shared_ptr<mae::fl::laban::laban_sequence> sequence = s_reader.read_sequence_str(entry.score);

							generated_sequences.push_back(initialize_laban_sequence_info(
									entry.id, file_path, file_name, directory, sequence));

							std::cout << "found generated sequence: " << entry.id << ", " << entry.name << std::endl;
						}
						else
						{
							//parse and send to movement controller
							std::vector<std::shared_ptr<mae::general_skeleton> > skeleton_data = bvh_ctrl.read_bvh_file(
									file_path, mae::fl::bvh_spec::default_spec())->get_skeleton_data();

							//use skeleton data to generate scores
							for (unsigned int i = 0; i < skeleton_data.size(); i++)
							{
								movement_controller.next_frame(0, skeleton_data.at(i));
							}

							std::shared_ptr<mae::fl::laban::laban_sequence> sequence = movement_controller.get_current_sequence();

							generated_sequences.push_back(initialize_laban_sequence_info(
									insert_sequence(db, file_path, file_name, directory, sequence->get_title(),
													sequence->xml(), 0), file_path, file_name, directory, sequence));

							//clear buffer
							movement_controller.clear_buffer();
						}
					}

					if (mae::mos::was_keyboard_hit())
					{
						sqlite3_close(db);
						return 0;
					}
                }
            }
        }
    }

    //comparing sequences
    std::cout << std::endl << ">> All sequences generated. Comparing sequences now..." << std::endl << std::endl;

    for (comparator_info cinfo : comparators)
    {
		for (laban_sequence_info sinfo : generated_sequences)
        {
            for (laban_sequence_info tinfo : target_sequences)
            {
				try
                {
					data_entry entry = select_data_by_ids(db, cinfo.id, tinfo.id, sinfo.id);

					std::cout << "entry: " << cinfo.id << " " << tinfo.id << " " << sinfo.id << std::endl;

					if (entry.id >= 0)
                    {
						//nothing
						std::cout << "data already exists: " << tinfo.filename << " with " << sinfo.filename
								  << std::endl;
					}
                    else
                    {
						std::cout << "comparing: " << tinfo.filename << " with " << sinfo.filename << std::endl;

                        if (nullptr == cinfo.comparator)
                        {
                            std::cout << "comparator is null!" << std::endl;
                        }

                        if (nullptr == tinfo.laban_sequence)
                        {
                            std::cout << "tinfo.laban_sequence is null!" << std::endl;
                        }

                        if (nullptr == sinfo.laban_sequence)
                        {
                            std::cout << "sinfo.laban_sequence is null!" << std::endl;
                        }

						double similarity = cinfo.comparator->similarity(tinfo.laban_sequence, sinfo.laban_sequence);

						std::cout << similarity << std::endl;

						//void insert_data(sqlite3* db, int comparator_id, int is_compare_target_sequence, int compare_sequence_id, int actual_sequence_id, double similarity)
						insert_data(db, cinfo.id, (sinfo.directory == tinfo.directory) ? 1 : 0, tinfo.id, sinfo.id, similarity);
					}
                }
                catch (std::exception& e)
                {
                    std::cout << "Error while comparing " << sinfo.id << " with " << tinfo.id << " (" << e.what() << ")" << std::endl;
                }
                catch (...)
                {
                    std::cout << "Error while comparing " << sinfo.id << " with " << tinfo.id << std::endl;
                }

				if (mae::mos::was_keyboard_hit())
				{
					sqlite3_close(db);
					return 0;
				}

			}
        }
    }

    std::cout << std::endl << ">> All sequences compared. We are done!" << std::endl << std::endl;

    sqlite3_close(db);

	return 0;
}
