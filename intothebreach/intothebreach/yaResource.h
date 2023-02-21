#pragma once
#include "yaEntity.h"
namespace ya {
	class Resource{
	public:
		Resource();
		~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;
		const wstring& GetKey() { return mKey; }
		const wstring& GetPath() { return mPath; }
		void SetKey(const wstring& key) { mKey = key; }
		void SetPath(const wstring& path) { mPath = path; }
	private:
		wstring mKey;
		wstring mPath;
	};
	//class Image : public Resource {

	//};
	//class Sound : public Resource {

	//};
}

