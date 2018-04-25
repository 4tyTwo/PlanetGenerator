#include <iostream>
#include <Windows.h>
#include "HeightGenerator.h"
#include <time.h>
#include <iostream>
#include <chrono>
#include <algorithm>
#include "RiverGenerator.h"
#include "TemperatureSetter.h"
#include "HumidityGenerator.h"
#include "MapDrawer.h"
using namespace std::chrono;


void CreateBmp24(const char *fname, Map* hmap, float sea_level) //Комментарии умерли
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
  int Width = hmap->Width();
  int Height = hmap->Height();
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
  for (i = 0; i < hmap->Height(); i++) {
    for (j = 0; j < hmap->Width(); j++) {
      if ((*hmap)[i][j]->Height() > sea_level) {
        color.rgbtGreen = 255 - (int)(((*hmap)[i][j]->Height() - sea_level) * 255);
        color.rgbtBlue = 0;
        color.rgbtRed = 0;
      }
      else {
        color.rgbtGreen = 0;
        color.rgbtBlue = 255 - (int)((sea_level - (*hmap)[i][j]->Height()) * 255);
        color.rgbtRed = 0;

      }
      WriteFile(hFile, &color, sizeof(color), &RW, NULL);
    }
    // Âûðîâíÿåì ïî ãðàíèöå
    WriteFile(hFile, Palette, Width % 4, &RW, NULL);
  }

  CloseHandle(hFile);
}

void CreateBmp242(const char *fname, Map* hmap) //Комментарии умерли
{
  std::string water = "water", mountain = "mountain";
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
  int Width = hmap->Width();
  int Height = hmap->Height();
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
  for (i = 0; i < hmap->Height(); i++) {
    for (j = 0; j < hmap->Width(); j++) {
      if (!(*hmap)[i][j]->Type().compare(water)) {
        color.rgbtRed = 0;
        color.rgbtGreen = 0;
        color.rgbtBlue = 255;
      }
      else {
        if (!(*hmap)[i][j]->Type().compare(mountain)) {
          color.rgbtRed = 142;
          color.rgbtGreen = 71;
          color.rgbtBlue = 53;
        }
        else {
          color.rgbtRed = 0;
          color.rgbtGreen = 255;
          color.rgbtBlue = 0;
        }
      }
      WriteFile(hFile, &color, sizeof(color), &RW, NULL);
    }
    // Âûðîâíÿåì ïî ãðàíèöå
    WriteFile(hFile, Palette, Width % 4, &RW, NULL);
  }

  CloseHandle(hFile);
}

void createHumidMap(const char *fname, Map* hmap) //Комментарии умерли
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
  int Width = hmap->Width();
  int Height = hmap->Height();
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
  color.rgbtGreen = 0;
  color.rgbtRed = 0;
  for (i = 0; i < hmap->Height(); i++) {
    for (j = 0; j < hmap->Width(); j++) {
      color.rgbtBlue = (*hmap)[i][j]->Humidity()*255;
      WriteFile(hFile, &color, sizeof(color), &RW, NULL);
    }
    // Âûðîâíÿåì ïî ãðàíèöå
    WriteFile(hFile, Palette, Width % 4, &RW, NULL);
  }
  CloseHandle(hFile);
}

void createTempMap(const char *fname, Map* hmap) //Комментарии умерли
{
  std::string water = "water";
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
  int Width = hmap->Width();
  int Height = hmap->Height();
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
  for (i = 0; i < hmap->Height(); i++) {
    for (j = 0; j < hmap->Width(); j++) {
      if ((*hmap)[i][j]->Type().compare(water)){
        if ((*hmap)[i][j]->Temperature() > 25){
        // 25+
        color.rgbtRed = 255;
        color.rgbtGreen = 0 + ((*hmap)[i][j]->Temperature() - 25) * 83 / 20; //из 0 в 83
        color.rgbtBlue = 0;        
      }
        else {
          if ((*hmap)[i][j]->Temperature() > 20){
            //20-25
            color.rgbtRed = 255;
            color.rgbtGreen = 83 + ((*hmap)[i][j]->Temperature() - 20) * 172 / 5; //Из 83 в 255
            color.rgbtBlue = 0;
          }
          else {
            if ((*hmap)[i][j]->Temperature() > 15) {
              //15-20
              color.rgbtRed = 255 - ((*hmap)[i][j]->Temperature() - 15) * 35; // Из 255 в 80
              color.rgbtGreen = 255 - ((*hmap)[i][j]->Temperature() - 15) * 11; //Из 255 в 200
              color.rgbtBlue = 0 + ((*hmap)[i][j]->Temperature() - 15) * 24; //Из 0 в 120
            }
            else {
              if ((*hmap)[i][j]->Temperature() > 10) {
                //10-15
                color.rgbtRed = 80 + ((*hmap)[i][j]->Temperature() - 10); //Из 80 в 85
                color.rgbtGreen = 200 - ((*hmap)[i][j]->Temperature() - 10) * 5; //Из 200 в 175
                color.rgbtBlue = 120 + ((*hmap)[i][j]->Temperature() - 10) * 27; //Из 120 в 255
              }
              else {
                if ((*hmap)[i][j]->Temperature() > 5) {
                  //5-10
                  color.rgbtRed = 85 + ((*hmap)[i][j]->Temperature() - 5) * 170 / 5;
                  color.rgbtGreen = 175 + ((*hmap)[i][j]->Temperature() - 5) * 80 / 5;
                  color.rgbtBlue = 255;
                }
                else {
                  //5-
                  color.rgbtRed = 255;
                  color.rgbtGreen = 255;
                  color.rgbtBlue = 255;
                }
              }
            }
          }
      }
      }
      else {
        color.rgbtRed = 0;
        color.rgbtGreen = 0;
        color.rgbtBlue = 0;
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
  high_resolution_clock::time_point t1 = high_resolution_clock::now(), t2, t3, t4;
  Map *testmap = new Map(1025, 2049);
  HeightGenerator generator(testmap, 0.56f, 0.5f);
  generator.generate();
  RiverGenerator rivergenerator(testmap, 30);
  rivergenerator.generate();
  //HumiditySetter::setHumidity(testmap);
  HumidityGenerator humgenerator(testmap,0.3f);
  humgenerator.generate();
  TemperatureSetter::setTemperature(testmap,45);
  //createHumidMap("C:\\Output\\Humid.png",testmap);
  t2 = high_resolution_clock::now();
  //createTempMap("C:\\Output\\Temp.png",testmap);
  //CreateBmp242("C:\\Output\\bit.png", testmap);//Довольно медленно, что не удивительно. Примерно дважды дольше версии со сравнением высот
  MapDrawer drawer(testmap);
  drawer.drawPhysicalMap("C:\\Output\\Map.png");
  t3 = high_resolution_clock::now();
  // CreateBmp24("C:\\Output\\bit2.png", testmap,testmap->avgHeight()*1.25);
  t4 = high_resolution_clock::now();
  // auto duration1 = duration_cast<microseconds>(t4 - t3).count();
  // auto duration2 = duration_cast<microseconds>(t3 - t2).count();
  //std::cout<< duration1<<" regular way"<<std::endl<<duration2<<" new way"<<std::endl;
  //  system("pause");
  return 0;
}