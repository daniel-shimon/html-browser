#include "Parser.h"
#include "Renderer.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	char* filePath = "index.html";
	if (argc >= 2) {
		filePath = argv[1];
	}

	Parser parser(filePath);
	parser.parse();
	Renderer renderer(parser.getRoot(), parser.getTitle());
	renderer.proccessTree();
	renderer.drawTree();
	renderer.maintainWindow();
}
