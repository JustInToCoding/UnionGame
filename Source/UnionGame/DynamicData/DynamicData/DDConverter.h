#include "DDObject.h"
#include "../rapidjson/document.h"
#include <vector>
#include <string>
#include <allocators>

#ifndef DynamicDataObject_IO_H_
#define DynamicDataObject_IO_H_

using namespace std;
using namespace rapidjson;

class DDConverter {
	//This is a abstract converter for json-strings to DDOs (vice versa).
	//Each implementation of a DDO needs to have a DDConverter class as well to be loaded.
protected:
	string _name;
	virtual DDObject* getDDObject(Value& value) {
		return new DDObject();
	}
	virtual Value*	  getJSON(DDObject* value, Document::AllocatorType& allocator) {
		return new Value(kObjectType);
	}
public:
	DDConverter(){}
	~DDConverter(){}

	virtual vector<DDObject*> JSONToDDO(Value& values) {
		vector<DDObject*> result;

		if (values.IsArray()) {
			for (SizeType i = 0; i < values.Size(); i++) {
				result.push_back(getDDObject(values[i]));
			}
		}
		
		return result;
	}

	virtual Value* DDOToJSON(vector<DDObject*> ddos, Document::AllocatorType& allocator) {
		Value* result;
		Value* arrayEntry;

		result = new Value(kArrayType);

		for (vector<DDObject>::size_type i = 0; i != ddos.size(); i++) {
			arrayEntry = getJSON(ddos[i], allocator);
			result->PushBack(*arrayEntry, allocator);
		}

		return result;
	}

	string getName() {
		return _name;
	}
};

#endif //DynamicDataObject_IO_H_