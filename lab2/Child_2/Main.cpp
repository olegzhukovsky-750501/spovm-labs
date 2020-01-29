#include <string>

#include "VegetableShop.h"

int main(int argc, char* argv[])
{
	VegetableShop vegShop;
	vegShop.makeChoice(argc - 1, argv + 1);
	return 0;
}