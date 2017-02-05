#include "Parser.h"

Parser::Parser(string address)
{
	this->file.open(address);
	this->root = new Root();
	this->current_tag = root;
}

BaseTag* Parser::parse()
{
	nextChar();
	while (this->file.is_open() && !this->file.eof())
	{
		if (current_char == '<')
		{
			newMarkup();
			nextChar();
		}
		else if (current_char == '\n')
		{
			nextChar();
		}
		else
		{
			newRawText();
		}
	}
	return this->root;
}

void Parser::newMarkup()
{
	bool close_tag = false;
	string type;
	// is it a closing tag?
	if (nextChar() == '/')
	{
		close_tag = true;
		nextChar();
	}
	// is it a comment or other? (<!...-->)
	else if (current_char == '!')
	{
		string combo;
		while (combo != "-->")
		{
			if (combo.size() == 3)
			{
				combo.erase(0, 1);
				combo += nextChar();
			}
			else combo += nextChar();
		}
		return;
	}
	// get name
	for (; current_char != ' ' && current_char != '>'; nextChar())
	{
		type += current_char;
	}
	type = toLower(type);
	// is it a title tag? (<!)
	if (type == "title")
	{
		string combo, value;
		while (current_char != '>')
		{
			nextChar();
		}
		while (toLower(combo) != "</title")
		{
			if (combo.size() == 7)
			{
				combo.erase(0, 1);
				combo += nextChar();
			}
			else combo += nextChar();
			value += current_char;
		}
		value = value.substr(0, value.size() - 7);
		this->title = value;
		while (current_char != '>')
		{
			nextChar();
		}
		return;
	}
	// is it a style tag? (<!)
	if (type == "style")
	{
		string combo, value;
		while (current_char != '>')
		{
			nextChar();
		}
		while (toLower(combo) != "</style")
		{
			if (combo.size() == 7)
			{
				combo.erase(0, 1);
				combo += nextChar();
			}
			else combo += nextChar();
			value += current_char;
		}
		value = value.substr(0, value.size() - 7);
		this->parseCssChunk(value);
		while (current_char != '>')
		{
			nextChar();
		}
		return;
	}
	// close tag
	if (close_tag)
	{
		for (; current_char != '>'; nextChar()) { continue; }
		closeTag(type);
		return;
	}
	// create tag
	if (!createTag(type))
	{
		current_tag = current_tag->addChild(new GenericTag(type));
	}
	// attributes
	while (current_char == ' ')
	{
		string attribue_key;
		string attribue_value;
		for (nextChar(); current_char != '=' && current_char != ' ' && current_char != '>'; nextChar())
		{
			attribue_key += current_char;
		}
		if (current_char != '=') break;
		nextChar();
		if (current_char == '\"')
		{
			for (nextChar(); current_char != '\"'; nextChar())
			{
				attribue_value += current_char;
			}
			nextChar();
		}
		else if (current_char == '\'')
		{
			for (nextChar(); current_char != '\''; nextChar())
			{
				attribue_value += current_char;
			}
			nextChar();
		}
		else
		{
			for (; current_char != ' ' && current_char != '>'; nextChar())
			{
				attribue_value += current_char;
			}
		}
		this->setAttribute(toLower(attribue_key), attribue_value);
	}
	// is it a <link> tag?
	if (type == "link" && current_tag->getAttribute(rel) == "stylesheet")
	{
		parseCssFile(current_tag->getAttribute(href));
	}
	// set style
	setStyle(gatherCss(type));
	// standalone
	if (current_tag->standalone)
	{
		closeTag(type);
	}
}

void Parser::newRawText()
{
	string text;
	bool in_whitespace = false;
	for (;current_char != '<' && !this->file.eof(); nextChar())
	{
		if (current_char == ' ' || current_char == '\n')
		{
			if (!in_whitespace)
			{
				text += ' ';
				in_whitespace = true;
			}
		}
		else
		{
			text += current_char;
			in_whitespace = false;
		}
	}
	BaseTag* raw_text = new RawText;
	raw_text->setAttribute(TEXT_CONTENT, text);
	this->current_tag->addChild(raw_text);
}

void Parser::closeTag(string type)
{
	// Find Ancestor :
	BaseTag* closing_tag = this->current_tag;
	while (!closing_tag->isType(type))
	{
		closing_tag = closing_tag->getParent();
		if (closing_tag == nullptr)
		{
			return;
		}
	}
	// Copy Lineage :
	BaseTag* current_dest = closing_tag->getParent();
	if (closing_tag != this->current_tag)
	{
		BaseTag* current_source = *(closing_tag->getEndChild() - 1);
		current_dest = current_dest->addChild(current_source->copy());
		while (current_source != this->current_tag)
		{
			current_dest = current_dest->addChild(current_source->copy());
 			current_source = *(current_source->getEndChild()-1);
		}
	}
	this->current_tag = current_dest;
}

bool Parser::createTag(string type)
{
	if (type == "br") current_tag = current_tag->addChild(new BreakTag);
	else if (type == "b") current_tag = current_tag->addChild(new BoldTag);
	else if (type == "i") current_tag = current_tag->addChild(new ItalicTag);
	else if (type == "body") current_tag = current_tag->addChild(new BodyTag);
	else if (type == "p") current_tag = current_tag->addChild(new ParagraphTag);
	else if (type == "h1") current_tag = current_tag->addChild(new H1Tag);
	else if (type == "h2") current_tag = current_tag->addChild(new H2Tag);
	else if (type == "h3") current_tag = current_tag->addChild(new H3Tag);
	else if (type == "h4") current_tag = current_tag->addChild(new H4Tag);
	else if (type == "h5") current_tag = current_tag->addChild(new H5Tag);
	else if (type == "h6") current_tag = current_tag->addChild(new H6Tag);
	else if (type == "div") current_tag = current_tag->addChild(new DivTag);
	else if (type == "a") current_tag = current_tag->addChild(new ATag);
	else return false;
	return true;
}

void Parser::setAttribute(string key, string value)
{
	if (key == "id") current_tag->setAttribute(ID, value);
	else if (key == "class") current_tag->setAttribute(CLASS, value);
	else if (key == "style") current_tag->setAttribute(STYLE, cleanWhitespace(value));
	else if (key == "width") current_tag->setAttribute(WIDTH, parseSize(toLower(value)));
	else if (key == "height") current_tag->setAttribute(HEIGHT, parseSize(toLower(value)));
	else if (key == "color") current_tag->setAttribute(Color, parseColor(value));
	else if (key == "background-color") { current_tag->setAttribute(BackgroundColor, parseColor(value)); }
	else if (key == "font-size") current_tag->setAttribute(FontSize, parseSize(toLower(value)));
	else if (key == "rel") current_tag->setAttribute(rel, value);
	else if (key == "href") current_tag->setAttribute(href, value);
	else if (key == "padding")
	{
		current_tag->setAttribute(PADDING_TOP, value);
		current_tag->setAttribute(PADDING_LEFT, value);
		current_tag->setAttribute(PADDING_BOTTOM, value);
		current_tag->setAttribute(PADDING_RIGHT, value);
	}
	else if (key == "margin")
	{
		current_tag->setAttribute(MARGIN_TOP, value);
		current_tag->setAttribute(MARGIN_LEFT, value);
		current_tag->setAttribute(MARGIN_BOTTOM, value);
		current_tag->setAttribute(MARGIN_RIGHT, value);
	}
}

void Parser::setStyle(string raw_style)
{
	while (raw_style != "")
	{
		int top = raw_style.find(':');
		string key = toLower(raw_style.substr(0, top));
		raw_style.erase(0, top+1);
		top = raw_style.find(';');
		string value;
		if (top == -1)
		{
			value = raw_style;
			raw_style = "";
		}
		else
		{
			value = toLower(raw_style.substr(0, top));
			raw_style.erase(0, top + 1);
		}
		// apply style :
		setAttribute(key, value);
	}
}

string Parser::getCss(string type)
{
	try
	{
		return this->css.at(type);
	}
	catch (...)
	{
		return "";
	}
}

string Parser::gatherCss(string type)
{
	string css;
	css = current_tag->getAttribute(STYLE);
	css += getCss(type);
	css += getCss("." + current_tag->getAttribute(CLASS));
	css += getCss(type + "." + current_tag->getAttribute(CLASS));
	css += getCss("#" + current_tag->getAttribute(ID));
	css += getCss(type + "#" + current_tag->getAttribute(ID));
	return css;
}

void Parser::parseCssFile(string address)
{
	ifstream css_file(address);
	string raw_css, buffer;
	while (css_file.is_open() && !css_file.eof())
	{
		getline(css_file, buffer);
		raw_css += buffer;
	}
	css_file.close();
	parseCssChunk(raw_css);
}

void Parser::parseCssChunk(string raw_css)
{
	while (raw_css != "")
	{
		int top = raw_css.find('{');
		string key = raw_css.substr(0, top);
		raw_css.erase(0, top + 1);
		top = raw_css.find('}');
		string value;
		if (top == -1)
		{
			value = raw_css;
			raw_css = "";
		}
		else
		{
			value = raw_css.substr(0, top);
			raw_css.erase(0, top + 1);
		}
		if (value.size() != 0 && value.at(value.size()-1) != ';')
		{
			value.append(1,';');
		}
		while (key.find(',') != -1)
		{
			top = key.find(',');
			string specific_key = cleanWhitespace(key.substr(0, top));
			key.erase(0, top + 1);
			addToCss(specific_key, value);
		}
		addToCss(key, value);
	}
}

void Parser::addToCss(string key, string value)
{
	// clean data
	key = toLower(cleanWhitespace(key));
	value = toLower(cleanWhitespace(value));
	if (this->getCss(key) == "") this->css[key] = value;
	else
	{
		this->css.at(key) += value;
	}
}

string Parser::parseColor(string value)
{
	if (value.at(0) == '#' && value.size() == 7)
	{
		return value.substr(1);
	}
	else if (value == "white")
	{
		return "ffffff";
	}
	else if (value == "black")
	{
		return "000000";
	}
	else if (value == "red")
	{
		return "ff0000";
	}
	else if (value == "green")
	{
		return "00ff00";
	}
	else if (value == "blue")
	{
		return "0000ff";
	}
	else if (value == "yellow")
	{
		return "ffff00";
	}
	else return "abcdef";
}

string Parser::parseSize(string value)
{
	if (value != "")
	{
		if (value.substr(value.size() - 2, 2) == "px") return value.substr(0, value.size() - 2);
		if (value.at(value.size() - 1) == '%') return value.substr(0, value.size() - 1).insert(0, 1,'%');
		else return value;
	}
}

string Parser::toLower(string str)
{
	string new_str;
	for (string::iterator i = str.begin(); 
		i != str.end(); i++)
	{
		if ('A' <= (*i) && (*i) <= 'Z')
		{
			new_str += (*i + 32);
		}
		else new_str += *i;
	}
	return new_str;
}

string Parser::cleanWhitespace(string raw)
{
	while (true)
	{
		if (raw.find(' ') != -1)
		{
			raw.erase(raw.find(' '), 1);
		}
		else if (raw.find('\n') != -1)
		{
			raw.erase(raw.find('\n'), 1);
		}

		else if (raw.find('\t') != -1)
		{
			raw.erase(raw.find('\t'), 1);
		}
		else return raw;
	}
}

char Parser::nextChar()
{
	if (!file.eof())
	{
		this->file.get(this->current_char);
		return this->current_char;
	}
	cout << current_tag->type << " - End Of File !" << endl;
}
