#pragma once

namespace Utility
{
	wstring GetExtension(wstring file);

	 string  ToString(wstring str);
	wstring ToWString( string str);

	bool StartsWith( string str,  string start);
	bool StartsWith(wstring str, wstring start);

	string GetFileName(string file);

	void CreateFolder(string file);

	vector<string> SplitString(string origin, string token);
}