#pragma once

class SolarBackground
{
public:
	SolarBackground();
	~SolarBackground();
	void Render();
	void Update();

private:
	SolarBackgroundQuad* background;
};

