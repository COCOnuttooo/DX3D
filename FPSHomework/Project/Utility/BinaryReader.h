#pragma once

class BinaryReader
{
public:
	BinaryReader( string path);
	BinaryReader(wstring path);
	~BinaryReader();

	bool Succeeded() { return file != INVALID_HANDLE_VALUE; }

	    int ReadInt();
	   UINT ReadUint();
	  float ReadFloat();
	 string ReadString();
	wstring ReadWString();

	Vector3 ReadVector3();
	Vector4 ReadVector4();

	 Matrix ReadMatrix();

	   void ReadData(void** data, UINT dataSize);

private:
	HANDLE file = nullptr;
	DWORD  size = 0;
};
