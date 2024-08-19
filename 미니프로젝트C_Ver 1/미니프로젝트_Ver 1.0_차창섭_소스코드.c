#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>//GUI 지원 기능
#include <math.h>
/////////////////////
// 전역 변수부
/////////////////////
HWND hwnd;// 윈도 화면(위부, 물리적)
HDC hdc;// 윈도 화면 (내부, 논리적) nfc있어서 중요하지 않음

FILE* rfp, * wfp;//
char fileName[200];
int inH, inW, outH, outW;
// 메모리 확보
unsigned char** inImage = NULL, ** outImage = NULL;

/////////////////////
// 함수 선언부
/////////////////////
void loadImage(); int getIntValue(); void printImage();
void saveImage(); double  getFloatValue();
void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory();
unsigned char getUnCharValue(); double** mallocDoubleMemory(int, int);
void freeDoubleMemory(double**, int);

void equalImage(); void addImage(); void printMenu();
void subImage(); void reverImage(); void blwhImage();
void gammaImage(); void andImage(); void zoomOut();
void zoomIn(); void zoomIn2();
void rotate(); void rotate2(); void transImage();
void mirrorLRImage(); void mirrorHLImage();
void histoStretch(); void andIn(); void histoEqual();
void emboss(); void blur(); void sharp(); void sharpNomal();
void sharpHf(); void sharpLf(); void edge1(); void operator();
void homoImage(); void diffImage(); void firstDifferentiation();
void roberts(); void roberts1(); void roberts2(); void roberts3();
void prewitt(); void prewitt1(); void prewitt2(); void prewitt3();
void sobel(); void sobel1(); void sobel2(); void sobel3();
void secundDifferentiation(); void dogGaussian(); void logGaussian();
void laplacian(); void laplacian1(); void laplacian2(); void laplacian3();



void main() {
	hwnd = GetForegroundWindow;
	hdc = GetWindowDC(NULL);//11은 null 10은 GetWindowDC(hwnd) 이지만 null 만됨
	char inKey = 0;
	while (inKey != '9')// !=역(반대)
	{
		printMenu();
		inKey = _getch();//문자 하나를 받아오는 
		//system("cls");//시스템 명령


		switch (inKey)
		{
		case'0':loadImage(); break;
		case'1':saveImage(); break;
		case'9': break;
		case'a':case'A': equalImage(); break;
		case'b':case'B': addImage(); break;
		case'c':case'C': subImage(); break;
		case'd':case'D': reverImage(); break;
		case'e':case'E': blwhImage(); break;
		case'f':case'F': gammaImage(); break;
		case'g': case'G': andImage(); break;//화소 점 처리
		case'h': case'H': zoomOut(); break;
		case'i': case'I': zoomIn(); break;
		case'j': case'J': zoomIn2(); break;
		case'k': case'K': rotate(); break;
		case'l': case'L': rotate2(); break;
		case'n': case'N': transImage(); break;
		case'm': case'M': mirrorLRImage(); break;
		case'o': case'O': mirrorHLImage(); break;//기하학
		case'p': case'P': histoStretch(); break;
		case'q': case'Q': andIn(); break;
		case'r': case'R': histoEqual(); break;
		case's': case'S': emboss();  break;//화소 영역
		case't': case'T': blur(); break;
		case'u': case'U': sharp(); break;
		case'v': case'V': edge1(); break;
		case'w': case'W': operator(); break;//화소 영역 엣지
		case'x': case'X': firstDifferentiation(); break;
		case'y': case'Y': secundDifferentiation(); break;
		case'z': case'Z':  break;
		}
	}
	freeInputMemory();
	freeOutputMemory();
}

/////////////////////
// 함수 정의부
/////////////////////
/// 공통 함수
//////////////
void printMenu() {
	puts("\n#GrayScale Image Proseccing(Beta4)#");
	puts("\n0.열기  1.저장  9.종료");
	puts("\nA.동일 B.밝게 C.어둡게 D.반전 E.흑백 F.감마 G.AND H.축소 I.확대");
	puts("\nJ.확대자세히 K. 회전 L.회전 중앙 N.이동 M.좌우 미러링 O.상하 미러링");
	puts("\nP.히스토그램 명암 스트래칭 Q.앤드인 탐색 R.평활화 S.엠보싱 T.블러링 ");
	puts("\nU. 샤프닝 Q.엣지 W.연산자 X.1차 미분 회선 Y.2차 미분 회선");
}

void printImage() {
	system("cls");
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int px = outImage[i][k];//px 픽스 점 
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
			//red blue grean 같은 값이면 그래이
		}
	}
}

void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("파일명-->");//flower512, LENA256
	scanf("%s", tmpName);
	strcat(fullName, tmpName);//strcat 이어붙인다
	strcat(fullName, ".raw");
	strcat(fileName, fullName);

	//(중요!) 이미지의 폭과 높이를 결정
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END);//파일의 끝으로 이동
	long long fsize = ftell(rfp);// 나 어디쯤이지? 256,144-->512
	fclose(rfp);
	// 메모리 해제
	freeInputMemory();
	// 높이,폭 구하기
	inH = inW = (int)sqrt(fsize);//sqrt제곱근
	//메모리 할당
	mallocInputMemory();
	//파일 메모리
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)

		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	//printf("%d \n", inImage[100][100]);
	equalImage();
}

void saveImage() {
	if (outImage == NULL)
		return;
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("파일명-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// 메모리 --> 파일 (한행씩)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
	printf("저장 완료");
}

int getIntValue() {
	int retValue;
	printf("정수값-->"); scanf("%d", &retValue);
	return retValue;
}
double getFloatValue() {
	double retFloatValue;

	printf("실수값-->"); scanf("%lf", &retFloatValue);

	return retFloatValue;
}
void freeInputMemory() {
	if (inImage == NULL)
		return;
	for (int i = 0; i < inH; i++)
		free(inImage[i]);
	free(inImage);
	inImage = NULL;
}
void mallocInputMemory() {
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
}

void freeOutputMemory() {
	if (outImage == NULL)
		return;
	for (int i = 0; i < outH; i++)
		free(outImage[i]);
	free(outImage);
	outImage = NULL;
}
void mallocOutputMemory() {
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);
	for (int i = 0; i < outH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
}
unsigned char getUnCharValue() {
	unsigned char retUnCharValue;
	printf("255>자연수-->");
	scanf("%hhu", &retUnCharValue);
	return retUnCharValue;
}
double** mallocDoubleMemory(int h, int w) {//인 아웃 포함
	double** retMemory;

	retMemory = (double**)malloc(sizeof(double*) * h);
	for (int i = 0; i < h; i++)
		retMemory[i] = (double*)malloc(sizeof(double) * w);
	return retMemory;
}
void freeDoubleMemory(double** memory, int h) {

	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(memory[i]);

	free(memory);
	memory = NULL;

}


//////////////////
//  영상처리 함수
////////////////////
void equalImage() { // 동일영상 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}
void addImage() { // 더하기 알고리즘
	// 메모리 할당
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}
void subImage() {
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();


	// 입력 배열 --> 출력 배열
	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] - val > 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}
void reverImage() {
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();


	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			outImage[i][k] = 255 - inImage[i][k];

		}
	}
	printImage();
}
void blwhImage() {
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();


	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] >= 128)
				outImage[i][k] = 255;

		}
	}
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < 128)
				outImage[i][k] = 0;

		}
	}
	printImage();
}
void gammaImage() {
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();


	// 입력 배열 --> 출력 배열
	double  val = getFloatValue();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//outImage[i][k] = pow((double)inImage[i][k],1/val);
			outImage[i][k] = pow((double)inImage[i][k] / 255, val) * 255;
		}
	}
	printImage();
}
void andImage() { // 더하기 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	unsigned char val = getUnCharValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k] & val;
		}
	}
	printImage();
}
void zoomOut() { // 동일영상 알고리즘
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH / scale);
	outW = (int)(inW / scale);
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}
	}
	printImage();
}
void zoomIn() { // 동일영상 알고리즘
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i * scale)][(int)(k * scale)] = inImage[i][k];
		}
	}
	printImage();
}
void zoomIn2() { // 동일영상 알고리즘
	//빽 워딩
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	// 기준이 아웃풋
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
	printImage();
}
void rotate() { // 회전 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	//short angle= 도 가능 효율적이지만 차이가 얼마 안나서int도 가능 
	int degree = getIntValue();
	//xd=cos*(xs)-sin*(ys) 인풋
	//yd=sin*(xs)+cos*(ys)
	//인간은 디그리값(360) 컴터는 라디안 값
	double radian = degree * 3.141592 / 180.0;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xs = i;
			int ys = k;
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);


			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}
void rotate2() { // 회전 알고리즘
	//백워딩
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	//short angle= 도 가능 효율적이지만 차이가 얼마 안나서int도 가능 
	int degree = getIntValue();
	//xd=cos*(xs)-sin*(ys) 인풋
	//yd=sin*(xs)+cos*(ys)
	//인간은 디그리값(360) 컴터는 라디안 값
	double radian = -degree * 3.141592 / 180.0;
	//중앙값
	int cx = inH / 2;
	int cy = inW / 2;

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xd = i;
			int yd = k;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;


			if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}
void transImage() { // 이동 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 이동 값
	double tx = getFloatValue();
	double ty = getFloatValue();
	// 입력 배열 --> 출력 배열
	//똑같이 - 대입 실패
	/*for (int i = 0; i < inH - tx; i++) {
		for (int k = 0; k < inW - ty; k++) {
			int xt = i;
			int yt = k;
			int xtt = xt + tx;
			int ytt = yt + ty;

			if ((0 <= xtt && xtt < outH) && (0 <= ytt && ytt < outW))
				outImage[xtt][ytt] = inImage[i][k];
			if ((0 > xtt && xtt > outH) && (0 > ytt && ytt > outW))
				outImage[xtt][ytt] = 0;
		}
	}
	printImage();
}*/
	for (int i = 0; i < inH - tx; i++) {
		for (int k = 0; k < inW - ty; k++) {
			outImage[(int)(i + tx)][(int)(k + ty)] = inImage[i][k];
		}
	}
	printImage();
}
void mirrorLRImage() { // 동일영상 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int mk = inW - 1 - k;//i < inW 이기 때문에 inW에 1을뺌
			outImage[i][k] = inImage[i][mk];
		}
	}
	printImage();
}
void mirrorHLImage() { // 동일영상 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int mi = inH - 1 - i;
			outImage[i][k] = inImage[mi][k];
		}
	}
	printImage();
}
void histoStretch() { // 동일영상 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	//진짜 영상처리 알고리즘
	//new=(old - low)/(high-low)*255.0
	int high = inImage[0][0], low = inImage[0][0];

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}
	int old, new;

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			old = inImage[i][k];
			new = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printImage();
}
void andIn() { // 동일영상 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	//진짜 영상처리 알고리즘
	//new=(old - low)/(high-low)*255.0
	int high = inImage[0][0], low = inImage[0][0];

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}
	high -= 50;
	low += 50;

	int old, new;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			old = inImage[i][k];
			new = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printImage();
}
void histoEqual() { // 히스토그램 평활화 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//1단계 : 빈도수 세기 (=히스토그램) histo[256]
	int histo[256] = { 0 };//{0} 나머지 값도 0으로 초기화 

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			histo[inImage[i][k]]++;
		}
	}
	//2단계 : 히스토그램 누적합 sumHisto[i]
	int sumHisto[256] = { 0 };//{0} 나머지 값도 0으로 초기화 
	sumHisto[0] = histo[0];
	for (int i = 0; i < 256; i++)
	{
		sumHisto[i] = sumHisto[i - 1] + histo[i];

	}

	//3단계 : 정규화된 히스토그램 생성 normalHisto=sumHisto*(1.0/(inH*inW))*255.0;
	double normalHisto[256] = { 1.0 };
	for (int i = 0; i < 256; i++)
	{
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;


	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalHisto[inImage[i][k]];
		}
	}
	printImage();
}
void emboss() { // 화소영역처리 엠보싱
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{-1.0,0.0,0.0},
		{ 0.0,0.0,0.0},
		{ 0.0,0.0,1.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}
	//후처리(마스크 값의 합계에 따라서..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void blur() { // 화소영역처리 블러
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{ 1. / 9,1. / 9,1. / 9},
		{ 1. / 9,1. / 9,1. / 9},
		{ 1. / 9,1. / 9,1. / 9}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}
void sharp() {
	system("cls");
	char mirKey = 0;
	puts("\n 샤프닝");
	puts("\n 1.일반 2.고주파 3.저주파 9.취소");
	mirKey = _getch();
	switch (mirKey) {
	case '1': sharpNomal(); return;
	case '2': sharpHf(); return;
	case '3': sharpLf(); return;
	case '9': return; // 메뉴
	default: printf("잘못된 입력 \n"); return;
	}
}
void sharpNomal() { // 화소영역처리 엠보싱
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{ 0. ,-1. , 0.},
		{ -1., 5., -1.},
		{ 0. ,-1. , 0.}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}
	//후처리(마스크 값의 합계에 따라서..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}
void sharpHf() { // 화소영역처리 엠보싱
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{ -1. / 9,-1. / 9,-1. / 9},
		{ -1. / 9,8. / 9,-1. / 9},
		{ -1. / 9,-1. / 9,-1. / 9}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}
	//후처리(마스크 값의 합계에 따라서..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}
void sharpLf() { // 화소영역처리 엠보싱
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
	{ 1. / 9,1. / 9,1. / 9},
	{ 1. / 9,1. / 9,1. / 9},
	{ 1. / 9,1. / 9,1. / 9}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 블러처리된 회선연산 
	double S;
	double hx;
	int val = getIntValue();


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;
			hx = val * inImage[i][k] - S * (val - 1);
			tmpOutImage[i][k] = hx;


		}
	}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}
void edge1() { // 에지 검출기
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//수직 에지 검출 마스크
		{ 0.0,0.0,0.0},
		{-1.0,1.0,0.0},
		{ 0.0,0.0,0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}




void operator() {//연산자 기법
	system("cls");
	char mirKey = 0;
	puts("\n 연산자");
	puts("\n 1.유사 2.차 9.취소");
	mirKey = _getch();
	switch (mirKey) {
	case '1': homoImage(); return;
	case '2': diffImage(); return;
	case '9': return; // 메뉴
	default: printf("잘못된 입력 \n"); return;
	}
}


double doublePlus(double x);//절대값 함수 지정
double doublePlus(double x) {//정의
	if (x >= 0)
		return x;
	else
		return -x;
}
void homoImage() {// 유사 연산자
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//기존 이미지값이라 1 마스크로 범위 정해주기
		{ 1.0,1.0,1.0},
		{ 1.0,1.0,1.0},
		{ 1.0,1.0,1.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double max;//최대값

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			max = 0.0;//블록 이동할 때마다 최대값 초기화
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					if (doublePlus(tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n] >= max))
						//블록의 가운데 값 빼기 주변 픽셀 값의 절대 값
						//fabs 라이브러리에 있는 절대값함수
						max = doublePlus(tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n]);
				}
			}
			tmpOutImage[i][k] = max;



		}
	}
	//후처리(마스크 값의 합계에 따라서..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void diffImage() {//차 연산자
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[4] = {//기존 이미지값이라 1 마스크로 범위 정해주기
		0.0,1.0,2.0,3.0 };

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double max;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			max = 0.0;//블록 이동할 때마다 최대값 초기화
			mask[0] = doublePlus(tmpInImage[i][k] - tmpInImage[i + 2][k + 2]);
			mask[1] = doublePlus(tmpInImage[i][k + 1] - tmpInImage[i + 2][k + 1]);
			mask[2] = doublePlus(tmpInImage[i][k + 2] - tmpInImage[i + 2][k]);
			mask[3] = doublePlus(tmpInImage[i + 1][k + 2] - tmpInImage[i + 1][k]);
			for (int m = 0; m < 4; m++)
			{
				if (mask[m] >= max)max = mask[m];
			}

			tmpOutImage[i][k] = max;
		}
	}
	//후처리(마스크 값의 합계에 따라서..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}
void firstDifferentiation() {//1차 미분을 이용한 에지 검출
	system("cls");
	char mirKey = 0;
	puts("\n 1차 미분 회선 마스크 종류");
	puts("\n 1.로버츠 2.프리윗 3.소벨 9.취소");
	mirKey = _getch();
	switch (mirKey) {
	case '1': roberts(); return;
	case '2': prewitt(); return;
	case '3': sobel(); return;
	case '9': return; // 메뉴
	default: printf("잘못된 입력 \n"); return;
	}
}
void secundDifferentiation() {//2차 미분을 이용한 에지 검출
	system("cls");
	system("cls");
	char mirKey = 0;
	puts("\n 2차 미분 회선 마스크 종류");
	puts("\n 1.라플라시안 2.로그 3.도그 9.취소");
	mirKey = _getch();
	switch (mirKey) {
	case '1': laplacian(); return;
	case '2': logGaussian(); return;
	case '3': dogGaussian(); return;
	case '9': return; // 메뉴
	default: printf("잘못된 입력 \n"); return;
	}
}
void roberts() {
	system("cls");
	char mirKey = 0;
	puts("\n 로버츠 회선 마스크 종류");
	puts("\n 1.수직 2.수평 3.둘다 9.취소");
	mirKey = _getch();
	switch (mirKey) {
	case '1': roberts1(); return;
	case '2': roberts2(); return;
	case '3': roberts3(); return;
	case '9': return; // 메뉴
	default: printf("잘못된 입력 \n"); return;
	}
}
void prewitt() {
	system("cls");
	char mirKey = 0;
	puts("\n 로버츠 회선 마스크 종류");
	puts("\n 1.수직 2.수평 3.둘다 9.취소");
	mirKey = _getch();
	switch (mirKey) {
	case '1': prewitt1(); return;
	case '2': prewitt2(); return;
	case '3': prewitt3(); return;
	case '9': return; // 메뉴
	default: printf("잘못된 입력 \n"); return;
	}
}
void sobel() {
	system("cls");
	char mirKey = 0;
	puts("\n 로버츠 회선 마스크 종류");
	puts("\n 1.수직 2.수평 3.둘다 9.취소");
	mirKey = _getch();
	switch (mirKey) {
	case '1': sobel1(); return;
	case '2': sobel2(); return;
	case '3': sobel3(); return;
	case '9': return; // 메뉴
	default: printf("잘못된 입력 \n"); return;
	}
}

void laplacian() {
	system("cls");
	char mirKey = 0;
	puts("\n 라플라시안 연산자 마스크");
	puts("\n 1.마스크1 2.마스크2 3.마스크3 9.취소");
	mirKey = _getch();
	switch (mirKey) {
	case '1': laplacian1(); return;
	case '2': laplacian2(); return;
	case '3': laplacian3(); return;
	case '9': return; // 메뉴
	default: printf("잘못된 입력 \n"); return;
	}
}





void roberts1() { // 로버츠 마스크1
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{-1.0,0.0,0.0},
	   { 0.0,1.0,0.0},
	   { 0.0,0.0,0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void roberts2() { // 로버츠 마스크2
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{0.0,0.0,-1.0},
		{ 0.0,1.0,0.0},
		{ 0.0,0.0,0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void roberts3() { // 로버츠 마스크3
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{-1.0,0.0,-1.0},
		{ 0.0,2.0,0.0},
		{ 0.0,0.0,0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void prewitt1() { // 프리윗 마스크1
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{-1.0,-1.0,-1.0},
	   { 0.0,0.0,0.0},
	   { 1.0,1.0,1.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void prewitt2() { // 프리윗 마스크2
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{ 1.0,0.0,-1.0},
		{ 1.0,0.0,-1.0},
		{ 1.0,0.0,-1.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void prewitt3() { // 프리윗 마스크3
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{0.0,-1.0,-2.0},
		{ 1.0,0.0,-1.0},
		{ 2.0,1.0,0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void sobel1() { // 소벨 마스크1
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{-1.0,-2.0,-1.0},
	   { 0.0,0.0,0.0},
	   { 1.0,2.0,1.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void sobel2() { // 소벨 마스크2
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{ 1.0,0.0,-1.0},
		{ 2.0,0.0,-2.0},
		{ 1.0,0.0,-1.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void sobel3() { // 소벨 마스크3
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{ 0.0,-2.0,-2.0},
		{ 2.0,0.0,-2.0},
		{ 2.0,2.0,0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void laplacian1() { // 라플라시안 연산자 마스크1
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
	   { 0.0,-1.0, 0.0},
	   {-1.0, 4.0,-1.0},
	   { 0.0,-1.0, 0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void laplacian2() { // 라플라시안 연산자 마스크2
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{ 1.0, 1.0,1.0},
		{ 1.0,-8.0,1.0},
		{ 1.0, 1.0,1.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void laplacian3() { // 라플라시안 연산자 마스크3
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[3][3] = {//엠보싱 마스크
		{-1.0,-1.0,-1.0},
		{-1.0, 8.0,-1.0},
		{-1.0,-1.0,-1.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void logGaussian() { // LoG 연산자
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[5][5] = {//엠보싱 마스크
	   { 0.0, 0.0,-1.0, 0.0, 0.0},
	   { 0.0,-1.0,-2.0,-1.0, 0.0},
	   {-1.0,-2.0,16.0,-2.0,-1.0},
	   { 0.0,-1.0,-2.0,-1.0, 0.0},
	   { 0.0, 0.0,-1.0, 0.0, 0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 4, inW + 4);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 4; i++)
		for (int k = 0; k < inW + 4; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(5x5)와 한점을 중심으로한 5x5을 곱하기
			S = 0.0;
			//마스크 25개와 입력값 25개를 각각 곱해서 합한값
			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 4);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}
void dogGaussian() { // DoG 연산자
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();
	//////////////////////
	// 화소 영역 처리
	///////////////////////
	double mask[7][7] = {//엠보싱 마스크
	   { 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0},
	   { 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0},
	   {-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0},
	   {-1.0,-3.0, 5.0,16.0, 5.0,-3.0,-1.0},
	   {-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0},
	   { 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0},
	   { 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0}
	};

	//임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 6, inW + 6);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//임시 입력 메모리를 초기화(127): 필요시 평균값
	for (int i = 0; i < inH + 6; i++)
		for (int k = 0; k < inW + 6; k++)
			tmpInImage[i][k] = 127;
	//입력 이미지--> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//중요! 회선연산 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			S = 0.0;
			//마스크 9개와 입력값 9개를 각각 곱해서 합한값
			for (int m = 0; m < 7; m++)
				for (int n = 0; n < 7; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//임시 출력 영상--> 출력영상
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 6);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}