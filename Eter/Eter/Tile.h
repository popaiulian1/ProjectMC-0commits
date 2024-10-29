#pragma once
class Tile
{
public:
	Tile();
	~Tile() = default;
	Tile(const Tile&) = default;
	Tile& operator=(const Tile&) = default;
	char getValue() const;
	void setValue(char value);
	bool isEmpty() const;
	void setIsEmpty(bool isEmpty);
private:
	char m_value; // valoarea casutei
	bool m_isEmpty; // true daca casuta este goala, false daca este ocupata
};

