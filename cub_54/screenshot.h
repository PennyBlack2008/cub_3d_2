#ifndef _SCREENSHOT_H_
# define _SCREENSHOT_H_

#define BYTES_PER_PIXEL		3
#define FILE_HEADER_SIZE	14
#define INFO_HEADER_SIZE	40

unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0 /// start of pixel array
    };

unsigned char infoHeader[] = {
		0,0,0,0, /// header size, biSize : 현재 구조체의 크기 (unsigned int, 4bytes)
		0,0,0,0, /// image width, biWidth : 비트맵 이미지의 가로 크기 (int, 4bytes)
		0,0,0,0, /// image height, biHeight : 비트맵 이미지의 세로 크기 (int, 4bytes)
		0,0,     /// number of color planes, biPlanes : 사용하는 색상판의 수 (unsigned short, 2bytes)
		0,0,     /// bits per pixel, biBitCount : 픽셀 하나를 표현하는 비트 수 (unsigned short, 2bytes)
		0,0,0,0, /// compression, biCompression : 압축 방식 (unsigned int, 4bytes)
		0,0,0,0, /// image size, biSizeImage : 비트맵 이미지의 픽셀 데이터 크기 (unsigned int, 4bytes)
		0,0,0,0, /// horizontal resolution, biXpelsPerMeter : 그림의 가로 해상도(미터당 픽셀) (int, 4bytes)
		0,0,0,0, /// vertical resolution, biYpelsPerMeter : 그림의 세로 해상도(미터당 픽셀) (int, 4bytes)
		0,0,0,0, /// colors in color table, biClrUsed : 색상 테이블에서 실제 사용되는 색상 수 (unsigned int, 4bytes)
		0,0,0,0 /// important color count, biClrImportant : 비트맵을 표현하기 위해 필요한 색상 인덱스 수 (unsigned int, 4bytes)
	};


void						generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName);
unsigned char*				createBitmapFileHeader(int height, int stride);
unsigned char*				createBitmapInfoHeader(int height, int width);

#endif