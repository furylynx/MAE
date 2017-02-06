//============================================================================
// Name        : minimal-libmae_nite.cpp
// Author      : furylynx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <exception>

#include <ni/XnCppWrapper.h>
#include <mae/nite/nite.hpp>


int main()
{
	std::cout << "Hello libmae_nite!" << std::endl;

	try
	{
	std::vector<std::shared_ptr<mae::nite::device_info> > devices = mae::nite::nite_farm::list_available_device_infos();

	if (devices.empty())
	{
		std::cout << "No devices are connected to this computer." << std::endl;
	}
	else
	{
		for (size_t i = 0; i < devices.size(); i++)
		{
			std::cout << "[" << i << "] " << devices.at(i)->str() << std::endl;
		}
	}
	}catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		std::cout << "Possible causes are no connected device or an incorrect installation of OpenNI/NiTE." << std::endl;
	}
	catch(...)
	{
		std::cout << "Unknown exception occurred." << std::endl;
		std::cout << "Possible causes are no connected device or an incorrect installation of OpenNI/NiTE." << std::endl;
	}

	return 0;
}
