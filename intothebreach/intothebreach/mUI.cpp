#include "mUI.h"
#include "mResources.h"
#include "mApplication.h"
#include "mSelectGDI.h"
#include "mCamera.h"
extern m::Application application;
namespace m
{
	UI::UI(const wstring& key
		, const wstring& path
		, int _sizeUp
		, bool _full
		, int _direction
		, bool _alphaCheck
	)
		: mImage(nullptr)
		, mPath(path)
		, mKey(key)
		, mSizeUp(_sizeUp)
		, mIsFull(_full)
		, mDir(_direction)
		, mAlpha(_alphaCheck)
		, effectCamera(false)
		, cutPos(false)
	{
		AddComponent(new Transform());
		if (mKey.empty() && mPath.empty()) return;
		mImage = Resources::Load<Image>(mKey, mPath);

		mSize = Vector2::Zero;
	}
	UI::~UI()
	{

	}
	void UI::Initialize()
	{
	}
	void UI::Update()
	{
	}
	void UI::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();

	}
	void UI::Release()
	{
	}
	float UI::GetWidth()
	{
		return (float)mImage->GetWidth();
	}
	float UI::GetHeight()
	{
		return (float)mImage->GetHeight();
	}
	//void UI::SetSize(Vector2 _size)
	//{
	//	mImage->GetSize();
	//}
	void UI::SetTex(const wstring& key, const wstring& path)
	{
		mImage = Resources::Load<Image>(key, path);
	}
	void UI::SetTex(const wstring& key, const wstring& path, ISLAND_T type)
	{
		mImage = Resources::Load<Image>(key, path);
		mImage->SetOffset(Vector2(ISLAND_OUTLINE_OFFSET[(UINT)type].x, ISLAND_OUTLINE_OFFSET[(UINT)type].y));
	}
	void UI::Clear()
	{
		mImage = Resources::Load<Image>(mKey, mPath);
	}
}