#include <string>
#include <vector>
#include <filesystem>
#include <Windows.h>
template <typename T>
class VarType
{
public:
	VarType(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};
namespace config_manager {
	void read_directory(const std::string& name, std::vector<std::string>& v);
	void save(std::string config_file);
	void load(std::string config_file);
	int upload_share_settings(std::string file);
	int download_share_settings(std::string file);
}
void  config_manager::read_directory(const std::string& name, std::vector<std::string>& v) {
	std::string pattern(name);
	pattern.append("\\*");

	WIN32_FIND_DATA data;
	HANDLE find;

	if ((find = FindFirstFileA(pattern.c_str(), (LPWIN32_FIND_DATAA)&data)) != INVALID_HANDLE_VALUE) {
		do {
			std::string filename((char*)data.cFileName);
			if (filename.substr(filename.find_last_of(".") + 1) == ("cfg"))
				v.push_back(filename);
		} while (FindNextFileA(find, (LPWIN32_FIND_DATAA)&data) != 0);
		FindClose(find);
	}
}

class CConfig
{
public:
	CConfig()
	{
		ints = std::vector<VarType<int>*>();
		bools = std::vector<VarType<bool>*>();
		floats = std::vector<VarType<float>*>();
	}

	void Initialize()
	{
		szPath = "C:\\Satanic\\";
		//Setup();
	}
	void Create()
	{
		std::string file;
		file = szPath + vars::stuff::ConfigName + ".cfg";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}
	std::vector < std::string > GetConfigList()
	{
	//	std::filesystem::create_directory("C:\\Satanic\\");

		std::vector < std::string > m_ConfigList;
		for (const auto& p : std::filesystem::recursive_directory_iterator(("C:\\Satanic\\")))
		{
			if (!std::filesystem::is_directory(p) && p.path().extension().string() == (".ini"))
			{
				auto file = p.path().filename().string();
				m_ConfigList.push_back(file.substr(0, file.size() - 4));
			}
		}

		return m_ConfigList;
	}

	void Save(const char* szConfigName)
	{
		std::string file;
		file = szPath + szConfigName + ".cfg";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}

	void Remove(const char* szConfigName)
	{
		std::string file;
		file = szPath + szConfigName + ".ini";
		std::remove(file.c_str());
	}

	void Load(const char* szConfigName)
	{
		std::string file;
		file = szPath + szConfigName + ".cfg";
		CreateDirectoryA(szPath.c_str(), NULL);

		char value_l[32] = { '\0' };

		for (VarType<int>* pValue : ints)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = atoi(value_l);
		}

		for (VarType<float>* pValue : floats)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = (float)atof(value_l);
		}

		for (VarType<bool>* pValue : bools)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = !strcmp(value_l, "1");
		}
	}

private:
	void SetupValue(int& value, int def, std::string category, std::string name)
	{
		value = def;
		ints.push_back(new VarType<int>(category, name, &value));
	}

	void SetupValue(bool& value, bool def, std::string category, std::string name)
	{
		value = def;
		bools.push_back(new VarType<bool>(category, name, &value));
	}

	void SetupValue(float& value, float def, std::string category, std::string name)
	{
		value = def;
		floats.push_back(new VarType<float>(category, name, &value));
	}

	std::string szPath = "";

protected:
	std::vector<VarType<int>*> ints;
	std::vector<VarType<bool>*> bools;
	std::vector<VarType<float>*> floats;
};

CConfig config;