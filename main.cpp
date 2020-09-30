#include <iostream>
#include <fstream>
#include "picojson.h"
#include "JSONArray.hpp"


int main()
{
	// first json object
	std::vector<JSONArray> JSONArrayVector1;

	JSONArray JSONArray1_1;
	JSONArray1_1.put("name", "apple");
	JSONArray1_1.put("color", "red");

	JSONArray JSONArray1_2;
	JSONArray1_2.put("name", "orange");
	JSONArray1_2.put("color", "orange");

	JSONArrayVector1.push_back(JSONArray1_1);
	JSONArrayVector1.push_back(JSONArray1_2);


	// second json object
	std::vector<JSONArray> JSONArrayVector2;

	JSONArray JSONArray2_1;
	JSONArray2_1.put("name", "chili");
	JSONArray2_1.put("color", "red");

	JSONArray JSONArray2_2;
	JSONArray2_2.put("name", "potato");
	JSONArray2_2.put("color", "yellow");

	JSONArray JSONArray2_3;
	JSONArray2_3.put("name", "gc");
	JSONArray2_3.put("color", "yellow++");

	JSONArrayVector2.push_back(JSONArray2_1);
	JSONArrayVector2.push_back(JSONArray2_2);
	JSONArrayVector2.push_back(JSONArray2_3);
	
	// root json object
	JSONArray JSONArrayRoot;

	JSONArrayRoot.put("fruit number", "2");
	JSONArrayRoot.put("vegetable number", "3");

	JSONArrayRoot.putJSONArray("fruit", JSONArrayVector1);
	JSONArrayRoot.putJSONArray("vegetable", JSONArrayVector2);

	std::string result = JSONArrayRoot.getOutput();

	std::ofstream outputDataFile("JSONArratData.txt");
	outputDataFile << result;

	// write the file "jsonData.txt"
	outputDataFile.close();


	// read the file 
	std::ifstream ifs;
	ifs.open("JSONArratData.txt", std::ios::in);
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

