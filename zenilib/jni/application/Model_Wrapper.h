#ifndef __game__Model_Wrapper_h__
#define __game__Model_Wrapper_h__

#include <zenilib.h>
#include <memory>

class Model_Wrapper {
public:
	Model_Wrapper(const Zeni::String& file_ = "") : fileName(file_), model(nullptr) {};
	Model_Wrapper(Zeni::Model* model_ = nullptr) : fileName(""), model(std::shared_ptr<Zeni::Model>(model_)) {};
    Model_Wrapper(std::shared_ptr<Zeni::Model> model_ = std::shared_ptr<Zeni::Model>(nullptr)) : fileName(""), model(model_) {};
	~Model_Wrapper() {};

    std::shared_ptr<Zeni::Model> getModel() const {
		if(!model)
		{
            if(fileName.length())
            {
                model = std::shared_ptr<Zeni::Model>(new Zeni::Model(fileName));
            }
            else {
                model = std::shared_ptr<Zeni::Model>(nullptr);
            }
		}
		return model;
	};

private:
	Zeni::String fileName;
    mutable std::shared_ptr<Zeni::Model> model;
};

#endif