#include <iostream>
#include <fstream>
#include "picojson.h"
#include "jsonObject.hpp"


int main()
{
	// first json object
	std::vector<jsonObject> jsonObjVector1;

	jsonObject jsonObj1_1;
	jsonObj1_1.insertKVPair("name", "apple");
	jsonObj1_1.insertKVPair("color", "red");

	jsonObject jsonObj1_2;
	jsonObj1_2.insertKVPair("name", "orange");
	jsonObj1_2.insertKVPair("color", "orange");

	jsonObjVector1.push_back(jsonObj1_1);
	jsonObjVector1.push_back(jsonObj1_2);


	// second json object
	std::vector<jsonObject> jsonObjVector2;

	jsonObject jsonObj2_1;
	jsonObj2_1.insertKVPair("name", "chili");
	jsonObj2_1.insertKVPair("color", "red");

	jsonObject jsonObj2_2;
	jsonObj2_2.insertKVPair("name", "potato");
	jsonObj2_2.insertKVPair("color", "yellow");

	jsonObject jsonObj2_3;
	jsonObj2_3.insertKVPair("name", "gc");
	jsonObj2_3.insertKVPair("color", "yellow++");

	jsonObjVector2.push_back(jsonObj2_1);
	jsonObjVector2.push_back(jsonObj2_2);
	jsonObjVector2.push_back(jsonObj2_3);
	
	// root json object
	jsonObject jsonRootObject;

	jsonRootObject.insertKVPair("fruit number", "2");
	jsonRootObject.insertKVPair("vegetable number", "3");

	jsonRootObject.insertJsonObject("fruit", jsonObjVector1);
	jsonRootObject.insertJsonObject("vegetable", jsonObjVector2);

	std::string result = jsonRootObject.getOutput();

	std::ofstream outputDataFile("jsonData.txt");
	outputDataFile << result;

	// write the file "jsonData.txt"
	outputDataFile.close();


	// read the file 
	std::ifstream ifs;
	ifs.open("jsonData.txt", std::ios::in);
	picojson::value param;
	picojson::parse(param, ifs);

	int sizeFruit = param.get("fruit").get<picojson::array>().size();
	int sizeVegetable = param.get("vegetable").get<picojson::array>().size();
	int fruitNum = atoi(param.get("fruit number").get<std::string>().c_str());
	int vegetableNum = atoi(param.get("vegetable number").get<std::string>().c_str());

	std::cout << "Fruit Number: " << sizeFruit << std::endl;
	std::cout << "Vegetable Number: " << sizeVegetable << std::endl;

	for (int i = 0; i < sizeFruit; i++) {
		picojson::value fruitData = param.get("fruit").get(i);

		const std::string name = fruitData.get("name").get<std::string>();
		const std::string color = fruitData.get("color").get<std::string>();
	
		std::cout << "Name: " << name << "\n";
		std::cout << "Color: " << color << "\n";
	}

	for (int i = 0; i < sizeVegetable; i++) {
		picojson::value vegetableData = param.get("vegetable").get(i);

		const std::string name = vegetableData.get("name").get<std::string>();
		const std::string color = vegetableData.get("color").get<std::string>();

		std::cout << "Name: " << name << "\n";
		std::cout << "Color: " << color << "\n";
	}

	ifs.close();

}

