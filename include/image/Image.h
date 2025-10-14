#pragma once

#include <image/ImageData.h>

enum class PixelFormat;

template <typename ColorSpace>
class Image
{
public:
	Image();

	Image(unsigned width, unsigned height);

	Image(const Image<ColorSpace>& other);

	Image<ColorSpace>& operator=(const Image<ColorSpace>& other);

	Image<ColorSpace>& operator=(Image<ColorSpace>&& other) noexcept;

	static std::string adjustCache();

	bool setBufferCacheSize() const;

	bool checkSignal(int x, int y, int r, int g, int b, int tolerance);

	void fastBox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t r, uint8_t g, uint8_t b);

	void gradientHBox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t r, uint8_t g, uint8_t b);

	void gradientVBox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t r, uint8_t g, uint8_t b);

	void insertHorizontal(int x, Image<ColorSpace>& source);

	unsigned width() const;

	unsigned height() const;

	const ColorSpace& operator()(unsigned x, unsigned y) const;

	ColorSpace& operator()(unsigned x, unsigned y);

	void setOriginFormat(PixelFormat pf);

	PixelFormat getOriginFormat() const;

	void resize(unsigned width, unsigned height);

	uint8_t* rawMem();

	const uint8_t* rawMem() const;

	size_t size() const;

		void clear();
		void rotate(int angle);

	bool save(const char* filename) const;

private:
	std::shared_ptr<ImageData<ColorSpace>> _sharedData;
	PixelFormat	_pixelFormat;
};



template <typename ColorSpace>
void Image<ColorSpace>::rotate(int angle)
{
	if (angle == 90)
	{
		Image<ColorSpace> temp(_sharedData->height(), _sharedData->width());
		for (unsigned y = 0; y < _sharedData->height(); ++y)
		{
			for (unsigned x = 0; x < _sharedData->width(); ++x)
			{
				temp(y, _sharedData->width() - 1 - x) = (*this)(x, y);
			}
		}
		*this = temp;
	}
	else if (angle == 180)
	{
		Image<ColorSpace> temp(_sharedData->width(), _sharedData->height());
		for (unsigned y = 0; y < _sharedData->height(); ++y)
		{
			for (unsigned x = 0; x < _sharedData->width(); ++x)
			{
				temp(_sharedData->width() - 1 - x, _sharedData->height() - 1 - y) = (*this)(x, y);
			}
		}
		*this = temp;
	}
	else if (angle == 270)
	{
		Image<ColorSpace> temp(_sharedData->height(), _sharedData->width());
		for (unsigned y = 0; y < _sharedData->height(); ++y)
		{
			for (unsigned x = 0; x < _sharedData->width(); ++x)
			{
				temp(_sharedData->height() - 1 - y, x) = (*this)(x, y);
			}
		}
		*this = temp;
	}
}
