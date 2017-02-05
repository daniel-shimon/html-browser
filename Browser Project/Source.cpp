#include "TagSystem.h"
#include "Parser.h"
#include "Renderer.h"

int main()
{
	Parser parser("index.html");
	parser.parse();
	Renderer renderer(parser.getRoot(), parser.getTitle());
	renderer.proccessTree();
	renderer.drawTree();
	renderer.maintainWindow();
}