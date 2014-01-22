/*
 * main.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: hesterg
 */
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
using namespace rapidxml;

int main(int argc, char **argv)
{
    rapidxml::file<> myfile("example.xml");
    xml_document<> doc;  // character type defaults to char
    doc.parse<parse_full>(myfile.data());
    std::cout << "Name of first node is: " << doc.first_node()->name() << std::endl;
    return 0;
}
