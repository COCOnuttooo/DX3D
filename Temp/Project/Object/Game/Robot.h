#pragma once
class Robot
{
    enum Parts
    {
        HEAD, NECK, BODY, LSHOULDER, RSHOULDER,
        LARM1, LARM2, LHAND, RARM1, RARM2, RHAND,
        LLEG1, LLEG2, LKNEE, LFOOT,
        RLEG1, RLEG2, RKNEE, RFOOT
    };
public:
	Robot();
	~Robot();

private:

};

