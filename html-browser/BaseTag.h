#ifndef BASETAG
#define BASETAG

#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream> // Debugging
#include <string>
using namespace std;

enum TagType
{
	ROOT,
	GENERIC,
	RAWTEXT,
	BR,
	B,
	I,
	BODY,
	P,
	H1, H2, H3, H4, H5, H6
};

enum AttributeType
{
	NONE,
	CLASS,
	ID,
	STYLE,
	WIDTH,
	HEIGHT,
	MARGIN_LEFT,
	MARGIN_TOP,
	MARGIN_RIGHT,
	MARGIN_BOTTOM,
	PADDING_LEFT,
	PADDING_TOP,
	PADDING_RIGHT,
	PADDING_BOTTOM,
	TEXT_CONTENT,
	BackgroundColor,
	// Passables :
	PASSABLE,
	FontSize,
	Color,
	Bold,
	Italic,
	Unlderlined,
	LAST
};

struct Point
{
	int x = 0;
	int y = 0;
	Point() { }
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	
	inline void operator+=(const Point& additive)
	{
		this->x += additive.x;
		this->y += additive.y;
	}
};

inline Point operator+(Point me, const Point& additive)
{
	me.x += additive.x;
	me.y += additive.y;
	return me;
}

inline Point operator-(Point me, const Point& subtractive)
{
	me.x -= subtractive.x;
	me.y -= subtractive.y;
	return me;
}

inline bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
inline bool operator!=(const Point& lhs, const Point& rhs)
{
	return !(lhs == rhs);
}

struct ProccessContext
{
	Point accumulator;
	int max_height = 0;
	int indent = 0;
	sf::Font& font;
	ProccessContext(sf::Font& new_font) : font(new_font)
	{}
};

struct DrawContext
{
	sf::RenderWindow& window;
};

class BaseTag
{
public:
	BaseTag();
	TagType type;
	bool standalone;
	inline vector<BaseTag*>::const_iterator getFirstChild() const 
		{ return this->children.begin(); };
	inline vector<BaseTag*>::const_iterator getEndChild() const 
		{ return this->children.end(); };
	// Parser Related :
	BaseTag* addChild(BaseTag* child);
	inline void setAttribute(AttributeType type, string value) 
	{ this->attributes[type] = value; };
	inline BaseTag* getParent() const 
		{ return this->parent; };
	inline virtual bool isType(string type) const 
		{ return this->type == stringToType(type); };
	static TagType stringToType(string type);
	BaseTag* copy();
	// Proccessor Related :
	void proccess(ProccessContext& context);
	string getAttribute(AttributeType type);
	inline void setLineBreak(bool lb) 
		{ this->block_level = lb; };
	static int safe_stoi(string str, size_t* index = 0, int base = 10);
	// Draw Related :
	void draw(DrawContext& context);
	static sf::Color hexToColor(string hex);
protected:
	int index;
	bool block_level; // not inline element
	bool wrapping;
	Point location;
	Point location_addition;
	Point bounding_box;
	BaseTag* parent;
	vector<BaseTag*> children;
	map<AttributeType, string> attributes;
	// proccessor
	void passStyle(BaseTag* child);
	void passAttribute(BaseTag* child, AttributeType attr);
	void addLocation(int x, int y);
	void setLocation(int x, int y);
	void addLocationAddition(int x, int y);
	void setLocationAddition(int x, int y);
	int getRowHeight();
	virtual void specificProccess(ProccessContext& context) {};
	virtual void specificDraw(DrawContext& context) {};
	virtual BaseTag* specificCopy();
	// drawer
	int accumulateAttribute(AttributeType attribute);
};

#endif
