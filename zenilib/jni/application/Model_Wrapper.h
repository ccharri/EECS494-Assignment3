#ifndef __game__Model_Wrapper_h__
#define __game__Model_Wrapper_h__

#include <zenilib.h>

class Model_Wrapper {
public:
	Model_Wrapper(const Zeni::String& file_) : fileName(file_), model(nullptr) {};
	Model_Wrapper(Zeni::Model* model_) : fileName(""), model(model_) {};
	~Model_Wrapper() {delete model;};

	Zeni::Model* getModel() {
		if(!model)
		{
			model = new Zeni::Model(fileName);
		}
		return model;
	};

private:
	const Zeni::String& fileName;
	Zeni::Model* model;
	int useCount;
};

#endif