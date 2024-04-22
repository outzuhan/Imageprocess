#include <Windows.h>
#include <iostream>
#include <fstream> 
using namespace std;

typedef struct
{
    BYTE b;
    BYTE g;
    BYTE r;
}RGB;



class Run
{
    //在function上面一次宣告避免重複宣告
    RGB img[512][512];
    RGB img2[512][512];
    const int height = 512;
    const int width = 512;
    int size = height * width;
    int i, j;

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    fstream inFile;
    fstream outFile;

public:
    //讀檔
    Run(string ip) //建構子-名稱與class相同
    {
        //開檔
        inFile.open(ip, ios::binary | ios::in); //讀入模式
        //讀檔
        inFile.read((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
        inFile.read((char*)&infoHeader, sizeof(BITMAPINFOHEADER));
        inFile.read((char*)img, size * sizeof(RGB));
    }

    //讀取圖檔存到img陣列 複製到img2陣列 輸出img2
    void copy()
    {
        for (i = 0; i < height; i=i+12)
        {
            for (j = 0; j < width; j=j+12)
            {
                //鏡像模式
                img2[i][j].r = img[height - i][j].r;
                img2[i][j].g = img[height - i][j].g;
                img2[i][j].b = img[height - i][j].b;
            }
        }
    }

    //輸出圖檔
    void output()
    {
        outFile.write((char*)&fileHeader, sizeof(fileHeader));
        outFile.write((char*)&infoHeader, sizeof(infoHeader));
        outFile.write((char*)&img2, size * sizeof(RGB));
    }

    //灰階-rgb數值會相同
    void grey()
    {
        for (i = 0; i < height; i=i+12)
        {
            for (j = 0; j < width; j=j+12)
            {
                img2[i][j].r = (img2[i][j].r + img2[i][j].g + img2[i][j].b) / 3;
                img2[i][j].g = img2[i][j].r;
                img2[i][j].b = img2[i][j].r;
            }
        }
    }

    //分階-分10階
    void greyScale()
    {
        for (i = 0; i < height; i=i+12)
        {
            for (j = 0; j < width; j=j+12)
            {
                if (0 <= img2[i][j].r and img2[i][j].r < 10)
                    cout << " ";
                if (10 <= img2[i][j].r and img2[i][j].r < 20)
                    cout << ".";
                if (20 <= img2[i][j].r and img2[i][j].r < 40)
                    cout << "-";
                if (40 <= img2[i][j].r and img2[i][j].r < 82)
                    cout << "~";
                if (82 <= img2[i][j].r and img2[i][j].r < 111)
                    cout << "1";
                if (111 <= img2[i][j].r and img2[i][j].r < 140)
                    cout << "0";
                if (140 <= img2[i][j].r and img2[i][j].r < 169)
                    cout << "5";
                if (169 <= img2[i][j].r and img2[i][j].r < 198)
                    cout << "*";
                if (198 <= img2[i][j].r and img2[i][j].r < 227)
                    cout << "#";
                if (227 <= img2[i][j].r and img2[i][j].r < 256)
                    cout << "@";
                cout << " ";
            }
            cout << endl;
        }
    }

    ~Run()
    {
        inFile.close();
        outFile.close();
    }
};

class App //連續讀檔
{
    string ip;
    int i;
public:
    void imgs()
    {
        while (1)
        {
            for (i = 0; i < 10; i++)
            {
                location(i);
            }
            if (i = 10)
            {
                i = 0;
            }
        }
       
    }
    void location(int i)
    {
        ip = "C:\\Users\\歐品威\\Desktop\\od code\\";
        ip = ip + static_cast<char>('0' + i);
        ip = ip + ".bmp";

        Run A(ip);
        A.copy();
        A.grey();
        A.greyScale();
        Sleep(50);
        system("cls");
    }
};

int main()
{
    App B;
    B.imgs();
}