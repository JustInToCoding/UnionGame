#include <string>
#include <map>
#include "DDConverter.h"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "../IO/FileReader.h"
#include "../IO/FileWriter.h"

#ifndef DynamicDataObject_IORegistry_H_
#define DynamicDataObject_IORegistry_H_

using namespace std;
using namespace rapidjson;

class DDRegistry {
private:
	static map<string, DDConverter*> ddoIOMap;
public:
	static void reg(DDConverter* converter) {
		ddoIOMap[converter -> getName()] = converter;
	}

	template<typename T>
	static vector<T*> load(string file) {
		vector<T*> result;
		vector<DDObject*> loaded;

		loaded = load(file);

		for each (DDObject* var in loaded) {
			result.push_back(dynamic_cast<T*>(var));
		}

		return result;
	}

	static vector<DDObject*> load(string file) {
		string			 json,
						 DDConverter_Name;
		FileReader		 fileReader;
		Document		 rootValue;
		DDConverter*		 DDConverter;
		vector<DDObject*> result;

		json = fileReader.readFile(file);

		rootValue.Parse<0>(json.c_str());

		if (rootValue.IsObject() && rootValue.HasMember("DDConverter")) {
			DDConverter_Name = rootValue["DDConverter"].GetString();
			DDConverter = ddoIOMap[DDConverter_Name];

			if (&DDConverter != NULL){
				result = DDConverter -> JSONToDDO(rootValue["values"]);
			}
		}
		return result;
	}

	static void save(string file, vector<DDObject*> values, DDConverter* converter) {
		Value* JSONValues;
		Document rootElement;
		rootElement.SetObject();
		Document::AllocatorType& allocator = rootElement.GetAllocator();

		//Get Converter's name
		Value DDConverterName(kStringType);
		DDConverterName.SetString(converter->getName().c_str(), allocator);
		rootElement.AddMember("DDConverter", DDConverterName, allocator);

		//Get Values
		JSONValues = (converter->DDOToJSON(values, allocator));

		//Write Object to String
		StringBuffer result;
		Writer<StringBuffer> writer(result);
		rootElement.AddMember("values", *JSONValues, allocator);
		rootElement.Accept(writer);
		string json = result.GetString();

		//Write out String to File
		FileWriter fileWriter;
		fileWriter.writeFile(file, json);

		delete JSONValues;
	}
	static void save(string file, vector<DDObject*> values, string converterName) {
		DDRegistry::save(file, values, ddoIOMap[converterName]);
	}
};

map<string, DDConverter*> DDRegistry::ddoIOMap;

#endif //DynamicDataObject_IORegistry_H_