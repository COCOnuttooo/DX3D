#pragma once
class BinaryWriter
{
public:
	BinaryWriter(wstring path);
	BinaryWriter(string  path);
	~BinaryWriter();

	void WriteData(int data);
	void WriteData(UINT data);
	void WriteData(float data);

	void WriteData(string data);
	void WriteData(wstring data);

	void WriteData(Vector3 data);
	void WriteData(Vector4 data);

	void WriteData(Matrix data);

	void WriteData(size_t data);
	
	void WriteData(void* data, UINT dataSize);
private:
	HANDLE file = nullptr;
	DWORD  size = 0;

};

