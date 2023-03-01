#pragma once
#include "mEntity.h"
namespace m {
	class Resource : public Entity{
	public:
		Resource();
		virtual ~Resource();

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

