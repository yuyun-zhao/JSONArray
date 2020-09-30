#ifndef JSONArray_h
#define JSONArray_h

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class JSONArray
{
public:
	JSONArray()
	{
		m_sstream << "{\n";
	}

	JSONArray(const JSONArray& obj)
	{
		std::string m_string = obj.m_sstream.str();
		m_sstream << m_string;
	};

	void put(std::string key, std::string value)
	{
		JSONKVPair m_JSONKVPair(key, value);
		m_sstream << m_JSONKVPair.getOutput() << ",\n";
	}

	void putJSONArray(std::string key, std::vector<JSONArray> objectVector)
	{
		m_sstream << "\"" + key + "\":\n[\n";

		for (auto iter = objectVector.begin(); iter != objectVector.end(); iter++)
		{
			m_sstream << (*iter).getOutput() << ",\n";
		}

		if (objectVector.size() > 0)
		{
			m_sstream.seekp(-2, std::ios_base::cur);
			m_sstream << "\n],\n";
		}
		else {
			m_sstream << "],\n";
		}
	}


	std::string getOutput()
	{
		m_sstream.seekp(-2, std::ios_base::cur);
		m_sstream << "\n}";

		return m_sstream.str();
	}


private:

	class JSONKVPair
	{
	public:
		JSONKVPair()
			:m_Key("NULL"), m_Value("NULL")
		{
		}

		JSONKVPair(std::string key, std::string value)
			:m_Key(key), m_Value(value)
		{
		}

		std::string getOutput()
		{
			m_stringstream << "\"" + m_Key + "\":\"" + m_Value + "\"";
			return m_stringstream.str();
		}

	private:
		std::string m_Key;
		std::string m_Value;
		std::stringstream m_stringstream;
	};

	JSONKVPair m_JsonKVPair;
	std::stringstream m_sstream;

};






#endif // JSONArray_h

