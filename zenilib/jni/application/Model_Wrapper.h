#ifndef __game__Model_Wrapper_h__
#define __game__Model_Wrapper_h__

#include <zenilib.h>

class Model_Wrapper {
public:
	Model_Wrapper(const Zeni::String& file_) : model(new Zeni::Model(file_)) {};
	Model_Wrapper(Zeni::Model* model_) : model(model_) {};
	~Model_Wrapper() {delete model;};

	Zeni::Model* getModel() const {return model;};

private:
	Zeni::Model* model;
};

#endif