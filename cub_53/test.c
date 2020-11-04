#include <stdio.h>

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int stride);
unsigned char* createBitmapInfoHeader(int height, int width);


int main ()
{
    int height = 100;
    int width = 100;
    unsigned char image[height][width][BYTES_PER_PIXEL];
    char* imageFileName = (char*) "bitmapImage.bmp";

    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // image[i][j][2] = (unsigned char) ( 255 );             ///red
            image[i][j][2] = (unsigned char) ( i * 255 / height );             ///red
            image[i][j][1] = (unsigned char) ( j * 255 / width );              ///green
            image[i][j][0] = (unsigned char) ( (i+j) * 255 / (height+width) ); ///blue
        }
    }

    generateBitmapImage((unsigned char*) image, height, width, imageFileName);
    printf("Image generated!!");
}


void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    FILE* imageFile = fopen(imageFileName, "wb");

    unsigned char* fileHeader = createBitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    unsigned char* infoHeader = createBitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    int i;
    for (i = 0; i < height; i++) {
        fwrite(image + (i*widthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char* createBitmapFileHeader (int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    // bfType : BMP 파일 매직 넘버, 총 2바이트
    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');

    // bfSize : 파일 크기, 총 4바이트
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);

    // bfOffBits : 비트맵 데이터의 시작 위치, 총 1바이트
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader (int height, int width)
{
    static unsigned char infoHeader[] = {
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
        0,0,0,0, /// important color count, biClrImportant : 비트맵을 표현하기 위해 필요한 색상 인덱스 수 (unsigned int, 4bytes)
    };

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE); // biSize
    infoHeader[ 4] = (unsigned char)(width      ); // biWidth
    infoHeader[ 5] = (unsigned char)(width >>  8); // biHeight
    infoHeader[ 6] = (unsigned char)(width >> 16); // biPlanes
    infoHeader[ 7] = (unsigned char)(width >> 24); // biBitCount
    infoHeader[ 8] = (unsigned char)(height      ); // biCompression
    infoHeader[ 9] = (unsigned char)(height >>  8); // biSizeImage
    infoHeader[10] = (unsigned char)(height >> 16); // biXpelsPerMeter
    infoHeader[11] = (unsigned char)(height >> 24); // biYpelsPerMeter
    infoHeader[12] = (unsigned char)(1); // biClrUsed
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8); // biClrImportant

    return infoHeader;
}