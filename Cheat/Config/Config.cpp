//// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
//#include "Config.h"
//#include "base64.h"
//#include <shlobj.h>
//#include "../../Utils/json.hpp"
//
//#include <stdint.h>
//#include <Windows.h>
//#include <psapi.h>
//#include <d3d11.h>
//#include <string>
//#include <codecvt>
//#include <locale>
//#include <cstdint>
//#include <algorithm>
//#include <iostream>
//#include <iomanip>
//#include <emmintrin.h>
//#include "winternl.h"
//#include <iostream>
//#include <vector>
//#include <fstream>
//
//std::unordered_map <std::string, float[4]> colors;
//
//C_ConfigManager* cfg_manager = new C_ConfigManager();
//
//
//void C_ConfigManager::setup()
//{
//	//setup_item(&g_cfg.legitbot.enabled, false, ("Legitbot.enabled"));
//	
//}
//
//void C_ConfigManager::add_item(void* pointer, const char* name, const std::string& type) {
//	items.push_back(new C_ConfigItem(std::string(name), pointer, type));
//}
//
//void C_ConfigManager::setup_item(int* pointer, int value, const std::string& name)
//{
//	add_item(pointer, name.c_str(), ("int"));
//	*pointer = value;
//}
//
//void C_ConfigManager::setup_item(bool* pointer, bool value, const std::string& name)
//{
//	add_item(pointer, name.c_str(), ("bool"));
//	*pointer = value;
//}
//
//void C_ConfigManager::setup_item(float* pointer, float value, const std::string& name)
//{
//	add_item(pointer, name.c_str(), ("float"));
//	*pointer = value;
//}
//
//
//void C_ConfigManager::setup_item(std::vector< int >* pointer, int size, const std::string& name)
//{
//	add_item(pointer, name.c_str(), ("vector<int>"));
//	pointer->clear();
//
//	for (int i = 0; i < size; i++)
//		pointer->push_back(FALSE);
//}
//
//void C_ConfigManager::setup_item(std::vector< std::string >* pointer, const std::string& name)
//{
//	add_item(pointer, name.c_str(), ("vector<string>"));
//}
//
//void C_ConfigManager::setup_item(std::string* pointer, const std::string& value, const std::string& name)
//{
//	add_item(pointer, name.c_str(), ("string"));
//	*pointer = value;
//}
//
//void C_ConfigManager::save(std::string config)
//{
//	std::string folder, file;
//
//	auto get_dir = [&folder, &file, &config]() -> void
//	{
//		static TCHAR path[MAX_PATH];
//
//		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
//		{
//			folder = ("Satanic\\");
//			file = ("Satanic\\") + config;
//		}
//
//		CreateDirectoryA(folder.c_str(), NULL);
//	};
//
//	get_dir();
//	nlohmann::json allJson;
//
//	for (auto it : items)
//	{
//		nlohmann::json j;
//
//		j[("name")] = it->name;
//		j[("type")] = it->type;
//
//		if (!it->type.compare(("int")))
//			j[("value")] = (int)*(int*)it->pointer;
//		else if (!it->type.compare(("float")))
//			j[("value")] = (float)*(float*)it->pointer;
//		else if (!it->type.compare(("bool")))
//			j[("value")] = (bool)*(bool*)it->pointer;
//		else if (!it->type.compare(("vector<int>")))
//		{
//			auto& ptr = *(std::vector<int>*)(it->pointer);
//			nlohmann::json ja;
//
//			for (auto& i : ptr)
//				ja.push_back(i);
//
//			j[("value")] = ja.dump();
//		}
//		else if (!it->type.compare(("vector<string>")))
//		{
//			auto& ptr = *(std::vector<std::string>*)(it->pointer);
//			nlohmann::json ja;
//
//			for (auto& i : ptr)
//				ja.push_back(i);
//
//			j[("value")] = ja.dump();
//		}
//		else if (!it->type.compare(("string")))
//			j[("value")] = (std::string) * (std::string*)it->pointer;
//
//		allJson.push_back(j);
//	}
//
//	//auto get_type = [](menu_item_type type)
//	//{
//	//	switch (type)
//	//	{
//	//	case CHECK_BOX:
//	//		return "bool";
//	//	case COMBO_BOX:
//	//	case SLIDER_INT:
//	//		return "int";
//	//	case SLIDER_FLOAT:
//	//		return "float";
//	//	}
//	//};
//
//	//for (auto i = 0; i < c_lua::get().scripts.size(); ++i)
//	//{
//	//	auto& script = c_lua::get().scripts.at(i);
//
//	//	for (auto& item : c_lua::get().items.at(i))
//	//	{
//	//		if (item.second.type == NEXT_LINE)
//	//			continue;
//
//	//		json j;
//	//		auto type = (std::string)get_type(item.second.type);
//
//	//		j[("name")] = item.first;
//	//		j[("type")] = type;
//
//	//		if (!type.compare(("bool")))
//	//			j[("value")] = item.second.check_box_value;
//	//		else if (!type.compare(("int")))
//	//			j[("value")] = item.second.type == COMBO_BOX ? item.second.combo_box_value : item.second.slider_int_value;
//	//		else if (!type.compare(("float")))
//	//			j[("value")] = item.second.slider_float_value;
//	//		else if (!type.compare(("Color")))
//	//		{
//	//			std::vector <int> color =
//	//			{
//	//				item.second.color_picker_value.r(),
//	//				item.second.color_picker_value.g(),
//	//				item.second.color_picker_value.b(),
//	//				item.second.color_picker_value.a()
//	//			};
//
//	//			json j_color;
//
//	//			for (auto& i : color)
//	//				j_color.push_back(i);
//
//	//			j[("value")] = j_color.dump();
//	//		}
//
//	//		allJson.push_back(j);
//	//	}
//	//}
//
//	std::string data;
//
//	Base64 base64;
//	base64.encode(allJson.dump(), &data);
//
//	std::ofstream ofs;
//	ofs.open(file + '\0', std::ios::out | std::ios::trunc);
//
//	ofs << std::setw(4) << data << std::endl;
//	ofs.close();
//}
//
//void C_ConfigManager::load(std::string config, bool load_script_items)
//{
//	static auto find_item = [](std::vector< C_ConfigItem* > items, std::string name) -> C_ConfigItem*
//	{
//		for (int i = 0; i < (int)items.size(); i++)
//			if (!items[i]->name.compare(name))
//				return items[i];
//
//		return nullptr;
//	};
//
//	std::string folder, file;
//
//	auto get_dir = [&folder, &file, &config]() ->void
//	{
//		static TCHAR path[MAX_PATH];
//
//		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
//		{
//			folder = ("Satanic\\");
//			file = ("Satanic\\") + config;
//		}
//
//		CreateDirectoryA(folder.c_str(), NULL);
//	};
//
//	get_dir();
//	std::string data;
//
//	std::ifstream ifs;
//	ifs.open(file + '\0');
//
//	ifs >> data;
//	ifs.close();
//
//	if (data.empty())
//		return;
//
//	Base64 base64;
//
//	std::string decoded_data;
//	base64.decode(data, &decoded_data);
//
//	std::ofstream ofs;
//	ofs.open(file + '\0', std::ios::out | std::ios::trunc);
//
//	ofs << decoded_data;
//	ofs.close();
//
//	nlohmann::json allJson;
//
//	std::ifstream ifs_final;
//	ifs_final.open(file + '\0');
//
//	ifs_final >> allJson;
//	ifs_final.close();
//
//	base64.encode(allJson.dump(), &data);
//
//	std::ofstream final_ofs;
//	final_ofs.open(file + '\0', std::ios::out | std::ios::trunc);
//
//	final_ofs << data;
//	final_ofs.close();
//
//	for (auto it = allJson.begin(); it != allJson.end(); ++it)
//	{
//		nlohmann::json j = *it;
//
//		std::string name = j[("name")];
//		std::string type = j[("type")];
//
//		auto script_item = std::count_if(name.begin(), name.end(),
//			[](char& c)
//			{
//				return c == '.';
//			}
//		) >= 2;
//
//		//if (load_script_items && script_item)
//		//{
//		//	std::string script_name;
//		//	auto first_point = false;
//
//		//	for (auto& c : name)
//		//	{
//		//		if (c == '.')
//		//		{
//		//			if (first_point)
//		//				break;
//		//			else
//		//				first_point = true;
//		//		}
//
//		//		script_name.push_back(c);
//		//	}
//
//		//	auto script_id = c_lua::get().get_script_id(script_name);
//
//		//	if (script_id == -1)
//		//		continue;
//
//		//	for (auto& current_item : c_lua::get().items.at(script_id))
//		//	{
//		//		if (current_item.first == name)
//		//		{
//		//			if (!type.compare(("bool")))
//		//			{
//		//				current_item.second.type = CHECK_BOX;
//		//				current_item.second.check_box_value = j[("value")].get<bool>();
//		//			}
//		//			else if (!type.compare(("int")))
//		//			{
//		//				if (current_item.second.type == COMBO_BOX)
//		//					current_item.second.combo_box_value = j[("value")].get<int>();
//		//				else
//		//					current_item.second.slider_int_value = j[("value")].get<int>();
//		//			}
//		//			else if (!type.compare(("float")))
//		//				current_item.second.slider_float_value = j[("value")].get<float>();
//		//		}
//		//	}
//		//}
//		//else if (!load_script_items && !script_item)
//		//{
//		//	auto item = find_item(items, name);
//
//		//	if (item)
//		//	{
//		//		if (!type.compare(("int")))
//		//			*(int*)item->pointer = j[("value")].get<int>();
//		//		else if (!type.compare(("float")))
//		//			*(float*)item->pointer = j[("value")].get<float>();
//		//		else if (!type.compare(("bool")))
//		//			*(bool*)item->pointer = j[("value")].get<bool>();
//		//		
//		//		else if (!type.compare(("vector<int>")))
//		//		{
//		//			auto ptr = static_cast<std::vector <int>*> (item->pointer);
//		//			ptr->clear();
//
//		//			json ja = json::parse(j[("value")].get<std::string>().c_str());
//
//		//			for (json::iterator it = ja.begin(); it != ja.end(); ++it)
//		//				ptr->push_back(*it);
//		//		}
//		//		else if (!type.compare(("vector<string>")))
//		//		{
//		//			auto ptr = static_cast<std::vector <std::string>*> (item->pointer);
//		//			ptr->clear();
//
//		//			json ja = json::parse(j[("value")].get<std::string>().c_str());
//
//		//			for (json::iterator it = ja.begin(); it != ja.end(); ++it)
//		//				ptr->push_back(*it);
//		//		}
//		//		else if (!type.compare(("string")))
//		//			*(std::string*)item->pointer = j[("value")].get<std::string>();
//		//	}
//		//}
//	}
//}
//
//void C_ConfigManager::remove(std::string config)
//{
//	std::string folder, file;
//
//	auto get_dir = [&folder, &file, &config]() -> void
//	{
//		static TCHAR path[MAX_PATH];
//
//		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
//		{
//			folder = ("Satanic\\");
//			file = ("Satanic\\") + config;
//		}
//
//		CreateDirectoryA(folder.c_str(), NULL);
//	};
//
//	get_dir();
//
//	std::string path = file + '\0';
//	std::remove(path.c_str());
//}
//void C_ConfigManager::config_files()
//{
//	std::string folder;
//
//	auto get_dir = [&folder]() -> void
//	{
//		PWSTR szPath = NULL;
//		if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &szPath)))
//			folder = ("Satanic\\");
//
//		CreateDirectoryA(folder.c_str(), NULL);
//	};
//
//	get_dir();
//	files.clear();
//
//	std::string path = folder + ("/*.inf");
//	WIN32_FIND_DATAA fd;
//
//	HANDLE hFind = FindFirstFileA(path.c_str(), &fd);
//
//	if (hFind != INVALID_HANDLE_VALUE)
//	{
//		do
//		{
//			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
//				files.push_back(fd.cFileName);
//		} while (FindNextFileA(hFind, &fd));
//
//		FindClose(hFind);
//	}
//}
