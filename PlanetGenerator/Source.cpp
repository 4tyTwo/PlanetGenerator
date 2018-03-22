#include <iostream>
#include <Windows.h>
#include "HeightGenerator.h"
#include <time.h>

void CreateBmp24(const char *fname, Map* hmap, float sea_level)
{
  HANDLE hFile;
  DWORD RW;
  int i, j;
  RGBTRIPLE color;
  color.rgbtBlue = 255;
  color.rgbtGreen = 0;
  color.rgbtRed = 0;
  // Îáúÿâèì íóæíûå ñòðóêòóðû
  BITMAPFILEHEADER bfh;
  BITMAPINFOHEADER bih;
  BYTE Palette[1024];									// Ïàëèòðà

                                      // Ïóñòü ó íàñ áóäåò êàðòèíêà ðàçìåðîì 35 x 50 ïèêñåëåé
  int Width = hmap->y_size();
  int Height = hmap->x_size();
  memset(Palette, 0, 1024);								// Â ïàëèòðå ó íàñ íóëè

                                          // Çàïîëíèì èõ
  memset(&bfh, 0, sizeof(bfh));
  bfh.bfType = 0x4D42;									// Îáîçíà÷èì, ÷òî ýòî bmp 'BM'
  bfh.bfOffBits = sizeof(bfh) + sizeof(bih) + 1024;		// Ïàëèòðà çàíèìàåò 1Kb, íî ìû åãî èñïîüçîâàòü íå áóäåì
  bfh.bfSize = bfh.bfOffBits +
    sizeof(color) * Width * Height +
    Height * (Width % 4);						// Ïîñ÷èòàåì ðàçìåð êîíå÷íîãî ôàéëà

  memset(&bih, 0, sizeof(bih));
  bih.biSize = sizeof(bih);								// Òàê ïîëîæåíî
  bih.biBitCount = 24;									// 16 áèò íà ïèêñåëü
  bih.biCompression = BI_RGB;								// Áåç ñæàòèÿ
  bih.biHeight = Height;
  bih.biWidth = Width;
  bih.biPlanes = 1;										// Äîëæíî áûòü 1
                                      // À îñòàëüíûå ïîëÿ îñòàþòñÿ 0
  hFile = CreateFile(fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
    return;

  // Çàïèøåì çàãîëîâêè
  WriteFile(hFile, &bfh, sizeof(bfh), &RW, NULL);
  WriteFile(hFile, &bih, sizeof(bih), &RW, NULL);
  // double avg  = hmap.average();
  // Çàïèøåì ïàëèòðó
  WriteFile(hFile, Palette, 1024, &RW, NULL);
  for (i = 0; i < hmap->x_size(); i++) {
    for (j = 0; j < hmap->y_size(); j++) {
      if ((*hmap)[i][j]->Height() > sea_level) {
        color.rgbtGreen = 255 - (int)(((*hmap)[i][j]->Height() - sea_level) * 255);
        color.rgbtBlue = 0;
        color.rgbtRed = 0;
      }
      else {
        color.rgbtGreen = 0;
        color.rgbtBlue = 255 - (int)((sea_level - (*hmap)[i][j]->Height())* 255);
        color.rgbtRed = 0;
        
      }
      WriteFile(hFile, &color, sizeof(color), &RW, NULL);
    }
    // Âûðîâíÿåì ïî ãðàíèöå
    WriteFile(hFile, Palette, Width % 4, &RW, NULL);
  }

  CloseHandle(hFile);
}

int main() {
  srand(time(NULL));
  Map *testmap = new Map(1025,2049);
  HeightGenerator generator(testmap,0.6f,0.4f);
  generator.generate();
  CreateBmp24("C:\\Output\\bit.png",testmap,testmap->avgHeight());
  return 0;
}