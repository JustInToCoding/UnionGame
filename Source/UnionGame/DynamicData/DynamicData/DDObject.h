#ifndef DynamicDataObject_H_
#define DynamicDataObject_H_

class DDObject {
public:
	virtual ~DDObject() {};
	//Marker to have a uniqu interface and return-type.
	//The returned objects have to be converted to the corresponding type.
};

#endif //DynamicDataObject_H_