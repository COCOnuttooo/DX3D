#pragma once

namespace Utility
{
	wstring GetExtension(wstring file);
	string ToString(wstring str);
	wstring ToWString(string str);
	bool StartsWith(string str, string start);
	bool StartsWith(wstring str, wstring start);
}
