#pragma once
#include "animation.h"

//================================================
// ## 2017.05.16 ## Image Class ## 취업해라 NC 제발 ##
//================================================


class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//From Resource
		LOAD_FILE,			//From File
		LOAD_EMPTY,			//Make Empty BMP file
		LOAD_END		
	};

	typedef struct tagImageInfo
	{
		//DWORD는 호환이 아예 불가능하다 4Byte 딱 그 이상 그 이하도 아님
		//Long은 32비트까지는 호환이 가능한 4Byte다
		//int는 64비트까지 호환이 가능한 4Byte다
		//당연하겠지만 호환이 가능하다면 불안하기 때문에 컴퓨터는
		//호환을 하지 않는 DWORD를 좋아한다

		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;
		int			height;
		int			currentFrameX;		//프레임 이미지 번호(가로)
		int			currentFrameY;		//프레임 이미지 번호(세로)
		int			maxFrameX;			//프레임 최대 갯수(가로)
		int			maxFrameY;			//프레임 최대 갯수(세로)
		int			frameWidth;			//프레임 이미지 한장 가로크기
		int			frameHeight;		//프레임 이미지 한장 세로크기
		BYTE		loadType;

		tagImageInfo()
		{
			resID				= 0;
			hMemDC				= NULL;
			hBit				= NULL;
			hOBit				= NULL;
			x					= 0;
			y					= 0;
			width				= 0;
			height				= 0;
			currentFrameX		= 0;
			currentFrameY		= 0;
			maxFrameX			= 0;
			maxFrameY			= 0;
			frameWidth			= 0;
			frameHeight			= 0;
			loadType = LOAD_RESOURCE;
		}
		//*LPIMAGE_INFO를 해놓는 이유는 이미지를 여러 곳에 할당할 수있게
		//하기 위함(접근용의)
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보 구조체
	CHAR*			_fileName;		//파일이름
	BOOL			_trans;			//특정칼라 날릴껀지 여부
	COLORREF		_transColor;	//특정칼라 레퍼런스

	BLENDFUNCTION	_blendFunc;		//알파블렌드 함수
	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지

public:
	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	//파일 비트맵 초기화
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	//이미지 날려줌
	void release(void);

	//특정 칼라를 날려줄껀지 여부
	void setTransColor(BOOL trans, COLORREF transColor);

	//렌더 
	void render(HDC hdc, int destX, int destY);

	//렌더               뿌려줄 곳X 뿌려줄 곳Y   뿌려올 곳X 뿌려올 곳Y  sourX,Y로부터 크기(가로, 세로)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void alphaAniRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//DC영역의 메모리 접근자
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//========================================================
	// 이미지 조작을 간편하게 위한 접근,설정자
	//========================================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (_imageInfo->maxFrameX < frameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (_imageInfo->maxFrameY < frameY)  _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void){ return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

};

