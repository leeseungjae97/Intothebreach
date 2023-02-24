#pragma once
#include "yaResource.h"
#include "yaImage.h"
namespace ya {
	class Resources {
	public:
		template <typename T>
		static T* Find(const wstring& key) {
			// ���ҽ��ʿ��� ������ Ž��
			map<wstring, Resource*>::iterator iter = mResources.find(key);
			if (iter != mResources.end())
				return dynamic_cast<T*>(iter->second);

			return nullptr;
		};
		template <typename T>
		static T* Load(const wstring& key, const wstring& path) {
			T* resource = Resources::Find<T>(key);
			if (nullptr != resource) {
				return resource;
			}
			// ���ҽ��� ���ٸ�
			resource = new T();
			if (FAILED(resource->Load(path))) {
				assert(false);
				return nullptr;
			}
			resource->SetKey(key);
			resource->SetPath(path);

			mResources.insert(make_pair(key, dynamic_cast<Resource*>(resource) ) );

			return dynamic_cast<T*>(resource);
		};
		static void Release() {
			for (auto &pair : mResources) {
				delete pair.second;
				pair.second = nullptr;
			}
		}
	private:
		Resources() = delete;
		~Resources() = delete;
	private:
		static map<wstring, Resource*> mResources;
	};
}

