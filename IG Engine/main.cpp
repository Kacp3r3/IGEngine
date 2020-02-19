#define STB_IMAGE_IMPLEMENTATION
#include "Engine/Engine.h"
int main()
{
	try
	{
		return Engine{}.Go();
	}
	catch (const IGException & e)
	{
		printf("%s\n", e.what());
	}
	catch (std::exception& e)
	{
		printf("%s\n", e.what());
	}

	return 0;
}
