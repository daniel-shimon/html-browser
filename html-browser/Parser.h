#ifndef PARSER
#define PARSER

#pragma once
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
	string getCssByClass(string _class);
	string getCssById(string id);
	char current_char;
	char nextChar();
	void newMarkup();
	void newRawText();
	void closeTag(string type);
	bool createTag(string type);
	void setAttribute(string attribue_key, string attribue_value);
	void setStyle(string raw_style);
	void addCSS(string raw_css);
	static string parseColor(string value);
	static string parseSize(string value);
	static string toLower(string str);
	static string cleanWhitespace(string raw);
};

#endif