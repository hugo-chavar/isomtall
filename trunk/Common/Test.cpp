#include "YAMLParser.h"
#include "yaml-cpp/yaml.h"

#define PATH "test.yaml"

using namespace std;
using namespace YAML;
using namespace common;



int main()
{
	YAMLParser yParser;
	yParser.parse(PATH);
	system("PAUSE");
	return 0;
}
