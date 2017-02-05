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
	H1, H2, H3, H4, H5, H6,
	DIV,
	A
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
	rel,
	href,
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
	Point& operator+(const Point& additive) const
	{
		Point new_point;
		new_point.x = this->x + additive.x;
		new_point.y = this->y + additive.y;
		return new_point;
	}
	Point& operator-(const Point& subtractive) const
	{
		Point new_point;
		new_point.x = this->x - subtractive.x;
		new_point.y = this->y - subtractive.y;
		return new_point;
	}
	inline void operator+=(const Point& additive)
	{
		this->x += additive.x;
		this->y += additive.y;
	}
	inline bool operator==(const Point& other)
	{
		return this->x == other.x && this->y == other.y;
	}
	inline bool operator!=(const Point& other)
	{
		return !(*this == other);
	}
};

struct ProccessContext
{
	Point current_starting_point = Point(); // Accumulator
	Point location_addition = Point();
	int& max_height;
	sf::Font& font;
	int indent = 0;
	//vector<AttributeType, string> attributes;
	ProccessContext(int& max_height_reference, sf::Font& font_reference) :
		font(font_reference), max_height(max_height_reference)
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
	inline void setAttribute(AttributeType type, string value) 
	{ this->attributes[type] = value; };
	// Parser Related :
	BaseTag* addChild(BaseTag* child);
	inline BaseTag* getParent() const 
		{ return this->parent; };
	inline virtual bool isType(string type) const 
		{ return this->type == stringToType(type); };
	static TagType stringToType(string type);
	BaseTag* copy();
	// Proccessor Related :
	Point proccess(ProccessContext context);
	inline vector<BaseTag*>::const_iterator getFirstChild() const 
		{ return this->children.begin(); };
	inline vector<BaseTag*>::const_iterator getEndChild() const 
		{ return this->children.end(); };
	string getAttribute(AttributeType type);
	inline Point absoluteLocation() const { return this->location + this->location_addition; };
	static int safe_stoi(string str, size_t* index = 0, int base = 10);
	// Draw Related :
	void draw(DrawContext& context);
	static sf::Color hexToColor(string hex);
protected:
	int index;
	bool block_level; // not inline element
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
	virtual void specificProccess(ProccessContext context) {};
	virtual void specificDraw(DrawContext& context) {};
	virtual BaseTag* specificCopy();
	// drawer
	int accumulateAttribute(AttributeType attribute);
};