#pragma once

#include <queue>
#include <string>

class RenderRequest
{
public:
	struct TextDrawRequest
	{
		std::string text;
		std::string fontFileName;
		int x, y;
		int fontSize;
		int r, g, b, a;
	};

	struct ImageDrawRequest
	{
		std::string imageName;
		float x, y;
		float scaleX = 1.0f, scaleY = 1.0f;
		float pivotX = 0.5f, pivotY = 0.5f;
		float rotationDegrees = 0.0f;
		int r = 255, g = 255, b = 255, a = 255;
		int sortingOrder = 0;
		bool isUI = false;
	};

	struct PixelDrawRequest
	{
		float x, y;
		float r, g, b, a;
	};

	static void TextDraw(const std::string& text, int x, int y, const std::string& fontFileName, int fontSize, int r, int g, int b, int a);
	static void ImageDraw(const std::string image_name, float x, float y);
	static void ImageDrawEx(const std::string image_name, float x, float y, float rotation_degrees, float scale_x, float scale_y, float pivot_x, float pivot_y, int r, int g, int b, int a, int sorting_order);
	static void ImageDrawUI(const std::string image_name, float x, float y);
	static void ImageDrawUIEx(const std::string image_name, float x, float y, float r, float g, float b, float a, int sorting_order);
	static void ImageDrawPixel(float x, float y, float r, float g, float b, float a);

	static std::queue<TextDrawRequest>& GetTextDrawRequests() { return mTextDrawRequests; }
	static std::queue<ImageDrawRequest>& GetImageDrawRequests() { return mImageDrawRequests; }
	static std::queue<ImageDrawRequest>& GetUIDrawRequests() { return mUIDrawRequests; }
	static std::queue<PixelDrawRequest>& GetPixelDrawRequests() { return mPixelDrawRequests; }

private:
	static std::queue<TextDrawRequest> mTextDrawRequests;
	static std::queue<ImageDrawRequest> mImageDrawRequests;
	static std::queue<ImageDrawRequest> mUIDrawRequests;
	static std::queue<PixelDrawRequest> mPixelDrawRequests;

};

