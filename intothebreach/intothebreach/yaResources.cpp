#include "yaResources.h"
namespace ya {
	map<wstring, Resource*> Resources::mResources = {};
	void Resources::Release() {
		//map<wstring, Resource*>::iterator iter = mResources.begin();
		//for (; iter != mResources.end(); iter++) {
		//	if (nullptr != iter->second) {
		//		delete iter->second;
		//		iter->second = nullptr;
		//	}
		//}
		//mResources.clear();
		for (auto pair : mResources) {
			delete pair.second;
			pair.second = nullptr;
		}
	}
}
