#include "TagSystem.h"
#include <iostream>
#include <fstream>

#pragma once
class Parser
{
public:
	Parser(string address);
	BaseTag* parse();
	inline Root* getRoot() const { return this->root; };
	inline string getTitle() const { return this->title; };
private:
	Root* root;
	ifstream file;
	BaseTag* current_tag;
	string title;
	map<string, string> css;
	string getCss(string type);
	string gatherCss(string type);
	char current_char;
	char nextChar();
	void newMarkup();
	void newRawText();
	void closeTag(string type);
	bool createTag(string type);
	void setAttribute(string attribue_key, string attribue_value);
	void setStyle(string raw_style);
	void parseCssFile(string address);
	void parseCssChunk(string raw_css);
	void addToCss(string key, string value);
	static string parseColor(string value);
	static string parseSize(string value);
	static string toLower(string str);
	static string cleanWhitespace(string raw);
};

