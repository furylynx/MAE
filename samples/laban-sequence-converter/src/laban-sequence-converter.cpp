//============================================================================
// Name        : laban-sequence-converter.cpp
// Author      : fury lynx
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

//custom includes

//global includes
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>

#include <mae/mae.hpp>
#include <mae/demo/demo.hpp>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/program_options.hpp>

std::string make_regex(std::string regex)
{
	std::string tmp = regex;

    tmp = mae::mstr::replace(tmp, "\\", "\\\\");
    tmp = mae::mstr::replace(tmp, "^", "\\^");
    tmp = mae::mstr::replace(tmp, ".", "\\.");
    tmp = mae::mstr::replace(tmp, "$", "\\$");
    tmp = mae::mstr::replace(tmp, "|", "\\|");
    tmp = mae::mstr::replace(tmp, "(", "\\(");
    tmp = mae::mstr::replace(tmp, ")", "\\)");
    tmp = mae::mstr::replace(tmp, "[", "\\[");
    tmp = mae::mstr::replace(tmp, "]", "\\]");
    tmp = mae::mstr::replace(tmp, "+", "\\+");
    tmp = mae::mstr::replace(tmp, "/", "\\/");

	tmp = mae::mstr::replace(tmp, "?", ".");
    tmp = mae::mstr::replace(tmp, "*", ".*");

    return tmp;
}

int main(int argc, char *argv[])
{
	int w = 1920;
	int h = 1080;
	bool svg = false;
	std::vector<std::string> files_w_pattern;

	// Declare the supported options.
	boost::program_options::options_description desc("Allowed options");
	desc.add_options()("help", "produce help message")
			("w", boost::program_options::value<int>(), "the resulting image(s) width(s)")
			("h", boost::program_options::value<int>(), "the resulting image(s) height(s)")
			("svg", "Set output to svg")
			;

	boost::program_options::options_description hidden("Hidden options");
    hidden.add_options()
       ("input-file", boost::program_options::value< std::vector<std::string> >(), "input file")
       ;

    boost::program_options::options_description cmdline_options;
    cmdline_options.add(desc).add(hidden);

    boost::program_options::positional_options_description p;
    p.add("input-file", -1);


	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), vm);
	boost::program_options::notify(vm);

	bool stop = false;

	if (vm.count("help"))
	{
		std::cout << desc << "\n";
		return 1;
	}

	if (vm.count("svg"))
	{
		svg = true;
	}

	if (!vm.count("w"))
	{
		std::cout << "Width was not specified" << std::endl;
		stop = true;
	}
	else
	{
		w = vm["w"].as<int>();
	}

	if (!vm.count("h"))
	{
		std::cout << "Height was not specified" << std::endl;
		stop = true;
	}
	else
	{
		h = vm["h"].as<int>();
	}

	if (!vm.count("input-file"))
	{
		std::cout << "No file defined." << std::endl;
		stop = true;
	}
	else
	{
		files_w_pattern = vm["input-file"].as<std::vector<std::string> >();
	}

	if (stop)
	{
		std::cout << "\t --help for info" << std::endl;
		return 1;
	}

	std::vector<std::string> files;
	for (unsigned int i = 0; i < files_w_pattern.size(); i++)
	{
		std::string::size_type split_pos = files_w_pattern.at(i).rfind(mae::mos::path_separator());

		std::string path = ".";
		std::string pattern = files_w_pattern.at(i);
		if (split_pos != std::string::npos)
		{
			path = std::string(files_w_pattern.at(i), 0, split_pos);
			pattern = std::string(files_w_pattern.at(i), split_pos +1);
		}

		boost::regex my_filter(  make_regex(pattern) );

		boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
		for( boost::filesystem::directory_iterator it( path ); it != end_itr; it++ )
		{
			boost::filesystem::directory_entry entry = *it;

			//std::cout << entry.path().string() << std::endl;

		    // Skip if not a file
		    if( !boost::filesystem::is_regular_file( entry.status() ) )
		    {
		    	continue;
		    }

		    boost::smatch what;

		    // Skip if no match
		    if( boost::regex_match( entry.path().string(), what, my_filter ) || entry.path().string() == files_w_pattern.at(i))
			{
			    // File matches, store it
			    files.push_back( entry.path().string() );
			}


		}
	}

	if (files.size() == 0)
	{
		std::cout << "Nothing do do." << std::endl;
		return 0;
	}

	std::cout << "Converting sequence" << (files.size() > 0 ? "s" : "") << std::endl;

	mae::demo::fl::laban_visualizer visualizer = mae::demo::fl::laban_visualizer();
	mae::fl::laban::laban_sequence_reader s_reader = mae::fl::laban::laban_sequence_reader();

	for (unsigned int i = 0; i < files.size(); i++)
	{
		std::string file = files.at(i);
		std::shared_ptr<mae::fl::laban::laban_sequence> sequence = s_reader.read_sequence_file(file);

		std::string outfile = file;

		if (svg)
		{
			outfile.append(".svg");
			sequence->svg_file(outfile, w, h);
		}
		else
		{
			outfile.append(".bmp");
			visualizer.png(outfile, sequence, w, h);
		}

		std::cout << "generated " << outfile << std::endl;
	}

	return 0;
}
