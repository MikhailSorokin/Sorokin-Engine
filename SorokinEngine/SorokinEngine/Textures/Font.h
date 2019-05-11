#pragma once
class Font
{
public:
	Font(int id, int width, int height);
	~Font();

private:
	int width;
	int height;
	
	int id;
};

