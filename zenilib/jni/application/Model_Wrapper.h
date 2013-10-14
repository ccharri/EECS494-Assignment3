#ifndef __game__Model_Wrapper_h__
#define __game__Model_Wrapper_h__

#include <zenilib.h>

class Model_Wrapper {
public:
	Model_Wrapper(const Zeni::String& file_);
	Model_Wrapper(Zeni::Model* model_);
	~Model_Wrapper();

	Zeni::Model* getModel() const {return model;};

private:
	Zeni::Model* model;
};

#endif