
#include "Model_Wrapper.h"

using namespace Zeni;
using namespace std;

Model_Wrapper::Model_Wrapper(const String& filepath_) : model(new Model(filepath_))
{
}

Model_Wrapper::Model_Wrapper(Model* model_) : model(model_)
{
}

Model_Wrapper::~Model_Wrapper()
{
	delete model;
}