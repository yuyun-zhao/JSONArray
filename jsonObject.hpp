#ifndef jsonObject_h
#define jsonObject_h

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class jsonObject
{
public:
	jsonObject()
	{
		m_sstream << "{\n";
	}

	jsonObject(const jsonObject& obj)
	{
		std::string m_string = obj.m_sstream.str();
		m_sstream << m_string;
	};

	void insertKVPair(std::string key, std::string value)
	{
		jsonKVPair m_JsonKVPair(key, value);
		m_sstream << m_JsonKVPair.getOutput() << ",\n";
	}

	void insertJsonObject(std::string key, std::vector<jsonObject> objectVector)
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

	class jsonKVPair
	{
	public:
		jsonKVPair()
			:m_Key("NULL"), m_Value("NULL")
		{
		}

		jsonKVPair(std::string key, std::string value)
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

	jsonKVPair m_JsonKVPair;
	std::stringstream m_sstream;

};






#endif // jsonObject_h

