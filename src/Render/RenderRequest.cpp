#include "RenderRequest.h"

std::queue<RenderRequest::TextDrawRequest> RenderRequest::mTextDrawRequests;
std::queue<RenderRequest::ImageDrawRequest> RenderRequest::mImageDrawRequests;
std::queue<RenderRequest::ImageDrawRequest> RenderRequest::mUIDrawRequests;
std::queue<RenderRequest::PixelDrawRequest> RenderRequest::mPixelDrawRequests;

void RenderRequest::TextDraw(const std::string& text, int x, int y, const std::string& fontFileName, int fontSize, int r, int g, int b, int a)
{
	TextDrawRequest request;
	request.text = text;
	request.x = x;
    request.y = y;
    request.fontFileName = fontFileName;
    request.fontSize = fontSize;
    request.r = r;
    request.g = g;
    request.b = b;
    request.a = a;
    mTextDrawRequests.push(request);
}

void RenderRequest::ImageDraw(const std::string imageName, float x, float y)
{
    ImageDrawRequest request;
    request.imageName = imageName;
    request.x = x;
    request.y = y;
    mImageDrawRequests.push(request);
}

void RenderRequest::ImageDrawEx(const std::string imageName, float x, float y, float rotationDegrees, float scaleX, float scaleY, float pivotX, float pivotY, int r, int g, int b, int a, int sortingOrder)
{
    ImageDrawRequest request;
    request.imageName = imageName;
    request.x = x;
    request.y = y;
    request.rotationDegrees = int(rotationDegrees);
    request.scaleX = scaleX;
    request.scaleY = scaleY;
    request.pivotX = pivotX;
    request.pivotY = pivotY;
    request.r = r;
    request.g = g;
    request.b = b;
    request.a = a;
    request.sortingOrder = sortingOrder;
    mImageDrawRequests.push(request);
}

void RenderRequest::ImageDrawUI(const std::string imageName, float x, float y)
{
    ImageDrawRequest request;
    request.imageName = imageName;
    request.x = x;
    request.y = y;
    request.isUI = true;
    mUIDrawRequests.push(request);
}

void RenderRequest::ImageDrawUIEx(const std::string imageName, float x, float y, float r, float g, float b, float a, int sortingOrder)
{
    ImageDrawRequest request;
    request.imageName = imageName;
    request.x = x;
    request.y = y;
    request.r = r;
    request.g = g;
    request.b = b;
    request.a = a;
    request.sortingOrder = sortingOrder;
    request.isUI = true;
    mUIDrawRequests.push(request);
}

void RenderRequest::ImageDrawPixel(float x, float y, float r, float g, float b, float a)
{
    PixelDrawRequest request;
    request.x = x;
    request.y = y;
    request.r = r;
    request.g = g;
    request.b = b;
    request.a = a;
    mPixelDrawRequests.push(request);
}
