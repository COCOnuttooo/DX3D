#include "Framework.h"
#include "ModelClip.h"
ModelClip::ModelClip()
{
}

ModelClip::~ModelClip()
{
	for (pair<string, KeyFrame*> pair : keyFrames)
		delete pair.second;

	keyFrames.clear();
}