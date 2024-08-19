#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>//GUI ���� ���
#include <math.h>
/////////////////////
// ���� ������
/////////////////////
HWND hwnd;// ���� ȭ��(����, ������)
HDC hdc;// ���� ȭ�� (����, ����) nfc�־ �߿����� ����

FILE* rfp, * wfp;//
char fileName[200];
int inH, inW, outH, outW;
// �޸� Ȯ��
unsigned char** inImage = NULL, ** outImage = NULL;

/////////////////////
// �Լ� �����
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
	hdc = GetWindowDC(NULL);//11�� null 10�� GetWindowDC(hwnd) ������ null ����
	char inKey = 0;
	while (inKey != '9')// !=��(�ݴ�)
	{
		printMenu();
		inKey = _getch();//���� �ϳ��� �޾ƿ��� 
		//system("cls");//�ý��� ���


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
		case'g': case'G': andImage(); break;//ȭ�� �� ó��
		case'h': case'H': zoomOut(); break;
		case'i': case'I': zoomIn(); break;
		case'j': case'J': zoomIn2(); break;
		case'k': case'K': rotate(); break;
		case'l': case'L': rotate2(); break;
		case'n': case'N': transImage(); break;
		case'm': case'M': mirrorLRImage(); break;
		case'o': case'O': mirrorHLImage(); break;//������
		case'p': case'P': histoStretch(); break;
		case'q': case'Q': andIn(); break;
		case'r': case'R': histoEqual(); break;
		case's': case'S': emboss();  break;//ȭ�� ����
		case't': case'T': blur(); break;
		case'u': case'U': sharp(); break;
		case'v': case'V': edge1(); break;
		case'w': case'W': operator(); break;//ȭ�� ���� ����
		case'x': case'X': firstDifferentiation(); break;
		case'y': case'Y': secundDifferentiation(); break;
		case'z': case'Z':  break;
		}
	}
	freeInputMemory();
	freeOutputMemory();
}

/////////////////////
// �Լ� ���Ǻ�
/////////////////////
/// ���� �Լ�
//////////////
void printMenu() {
	puts("\n#GrayScale Image Proseccing(Beta4)#");
	puts("\n0.����  1.����  9.����");
	puts("\nA.���� B.��� C.��Ӱ� D.���� E.��� F.���� G.AND H.��� I.Ȯ��");
	puts("\nJ.Ȯ���ڼ��� K. ȸ�� L.ȸ�� �߾� N.�̵� M.�¿� �̷��� O.���� �̷���");
	puts("\nP.������׷� ��� ��Ʈ��Ī Q.�ص��� Ž�� R.��Ȱȭ S.������ T.���� ");
	puts("\nU. ������ Q.���� W.������ X.1�� �̺� ȸ�� Y.2�� �̺� ȸ��");
}

void printImage() {
	system("cls");
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int px = outImage[i][k];//px �Ƚ� �� 
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
			//red blue grean ���� ���̸� �׷���
		}
	}
}

void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�-->");//flower512, LENA256
	scanf("%s", tmpName);
	strcat(fullName, tmpName);//strcat �̾���δ�
	strcat(fullName, ".raw");
	strcat(fileName, fullName);

	//(�߿�!) �̹����� ���� ���̸� ����
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END);//������ ������ �̵�
	long long fsize = ftell(rfp);// �� ���������? 256,144-->512
	fclose(rfp);
	// �޸� ����
	freeInputMemory();
	// ����,�� ���ϱ�
	inH = inW = (int)sqrt(fsize);//sqrt������
	//�޸� �Ҵ�
	mallocInputMemory();
	//���� �޸�
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
	printf("���ϸ�-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// �޸� --> ���� (���྿)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
	printf("���� �Ϸ�");
}

int getIntValue() {
	int retValue;
	printf("������-->"); scanf("%d", &retValue);
	return retValue;
}
double getFloatValue() {
	double retFloatValue;

	printf("�Ǽ���-->"); scanf("%lf", &retFloatValue);

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
	printf("255>�ڿ���-->");
	scanf("%hhu", &retUnCharValue);
	return retUnCharValue;
}
double** mallocDoubleMemory(int h, int w) {//�� �ƿ� ����
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
//  ����ó�� �Լ�
////////////////////
void equalImage() { // ���Ͽ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}
void addImage() { // ���ϱ� �˰���
	// �޸� �Ҵ�
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
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
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();


	// �Է� �迭 --> ��� �迭
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
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();


	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			outImage[i][k] = 255 - inImage[i][k];

		}
	}
	printImage();
}
void blwhImage() {
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();


	// �Է� �迭 --> ��� �迭
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
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();


	// �Է� �迭 --> ��� �迭
	double  val = getFloatValue();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//outImage[i][k] = pow((double)inImage[i][k],1/val);
			outImage[i][k] = pow((double)inImage[i][k] / 255, val) * 255;
		}
	}
	printImage();
}
void andImage() { // ���ϱ� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	unsigned char val = getUnCharValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k] & val;
		}
	}
	printImage();
}
void zoomOut() { // ���Ͽ��� �˰���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH / scale);
	outW = (int)(inW / scale);
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}
	}
	printImage();
}
void zoomIn() { // ���Ͽ��� �˰���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i * scale)][(int)(k * scale)] = inImage[i][k];
		}
	}
	printImage();
}
void zoomIn2() { // ���Ͽ��� �˰���
	//�� ����
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	// ������ �ƿ�ǲ
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
	printImage();
}
void rotate() { // ȸ�� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	//short angle= �� ���� ȿ���������� ���̰� �� �ȳ���int�� ���� 
	int degree = getIntValue();
	//xd=cos*(xs)-sin*(ys) ��ǲ
	//yd=sin*(xs)+cos*(ys)
	//�ΰ��� ��׸���(360) ���ʹ� ���� ��
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
void rotate2() { // ȸ�� �˰���
	//�����
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	//short angle= �� ���� ȿ���������� ���̰� �� �ȳ���int�� ���� 
	int degree = getIntValue();
	//xd=cos*(xs)-sin*(ys) ��ǲ
	//yd=sin*(xs)+cos*(ys)
	//�ΰ��� ��׸���(360) ���ʹ� ���� ��
	double radian = -degree * 3.141592 / 180.0;
	//�߾Ӱ�
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
void transImage() { // �̵� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �̵� ��
	double tx = getFloatValue();
	double ty = getFloatValue();
	// �Է� �迭 --> ��� �迭
	//�Ȱ��� - ���� ����
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
void mirrorLRImage() { // ���Ͽ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int mk = inW - 1 - k;//i < inW �̱� ������ inW�� 1����
			outImage[i][k] = inImage[i][mk];
		}
	}
	printImage();
}
void mirrorHLImage() { // ���Ͽ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int mi = inH - 1 - i;
			outImage[i][k] = inImage[mi][k];
		}
	}
	printImage();
}
void histoStretch() { // ���Ͽ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	//��¥ ����ó�� �˰���
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
void andIn() { // ���Ͽ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	//��¥ ����ó�� �˰���
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
void histoEqual() { // ������׷� ��Ȱȭ �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//1�ܰ� : �󵵼� ���� (=������׷�) histo[256]
	int histo[256] = { 0 };//{0} ������ ���� 0���� �ʱ�ȭ 

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			histo[inImage[i][k]]++;
		}
	}
	//2�ܰ� : ������׷� ������ sumHisto[i]
	int sumHisto[256] = { 0 };//{0} ������ ���� 0���� �ʱ�ȭ 
	sumHisto[0] = histo[0];
	for (int i = 0; i < 256; i++)
	{
		sumHisto[i] = sumHisto[i - 1] + histo[i];

	}

	//3�ܰ� : ����ȭ�� ������׷� ���� normalHisto=sumHisto*(1.0/(inH*inW))*255.0;
	double normalHisto[256] = { 1.0 };
	for (int i = 0; i < 256; i++)
	{
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;


	}
	// 4�ܰ� : inImage�� ����ȭ�� ������ ġȯ
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalHisto[inImage[i][k]];
		}
	}
	printImage();
}
void emboss() { // ȭ�ҿ���ó�� ������
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{-1.0,0.0,0.0},
		{ 0.0,0.0,0.0},
		{ 0.0,0.0,1.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}
	//��ó��(����ũ ���� �հ迡 ����..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//�ӽ� ��� ����--> ��¿���
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
void blur() { // ȭ�ҿ���ó�� ��
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{ 1. / 9,1. / 9,1. / 9},
		{ 1. / 9,1. / 9,1. / 9},
		{ 1. / 9,1. / 9,1. / 9}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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
	puts("\n ������");
	puts("\n 1.�Ϲ� 2.������ 3.������ 9.���");
	mirKey = _getch();
	switch (mirKey) {
	case '1': sharpNomal(); return;
	case '2': sharpHf(); return;
	case '3': sharpLf(); return;
	case '9': return; // �޴�
	default: printf("�߸��� �Է� \n"); return;
	}
}
void sharpNomal() { // ȭ�ҿ���ó�� ������
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{ 0. ,-1. , 0.},
		{ -1., 5., -1.},
		{ 0. ,-1. , 0.}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}
	//��ó��(����ũ ���� �հ迡 ����..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//�ӽ� ��� ����--> ��¿���
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
void sharpHf() { // ȭ�ҿ���ó�� ������
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{ -1. / 9,-1. / 9,-1. / 9},
		{ -1. / 9,8. / 9,-1. / 9},
		{ -1. / 9,-1. / 9,-1. / 9}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}
	//��ó��(����ũ ���� �հ迡 ����..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//�ӽ� ��� ����--> ��¿���
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
void sharpLf() { // ȭ�ҿ���ó�� ������
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
	{ 1. / 9,1. / 9,1. / 9},
	{ 1. / 9,1. / 9,1. / 9},
	{ 1. / 9,1. / 9,1. / 9}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ��ó���� ȸ������ 
	double S;
	double hx;
	int val = getIntValue();


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;
			hx = val * inImage[i][k] - S * (val - 1);
			tmpOutImage[i][k] = hx;


		}
	}


	//�ӽ� ��� ����--> ��¿���
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
void edge1() { // ���� �����
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//���� ���� ���� ����ũ
		{ 0.0,0.0,0.0},
		{-1.0,1.0,0.0},
		{ 0.0,0.0,0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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




void operator() {//������ ���
	system("cls");
	char mirKey = 0;
	puts("\n ������");
	puts("\n 1.���� 2.�� 9.���");
	mirKey = _getch();
	switch (mirKey) {
	case '1': homoImage(); return;
	case '2': diffImage(); return;
	case '9': return; // �޴�
	default: printf("�߸��� �Է� \n"); return;
	}
}


double doublePlus(double x);//���밪 �Լ� ����
double doublePlus(double x) {//����
	if (x >= 0)
		return x;
	else
		return -x;
}
void homoImage() {// ���� ������
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//���� �̹������̶� 1 ����ũ�� ���� �����ֱ�
		{ 1.0,1.0,1.0},
		{ 1.0,1.0,1.0},
		{ 1.0,1.0,1.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double max;//�ִ밪

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			max = 0.0;//��� �̵��� ������ �ִ밪 �ʱ�ȭ
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					if (doublePlus(tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n] >= max))
						//����� ��� �� ���� �ֺ� �ȼ� ���� ���� ��
						//fabs ���̺귯���� �ִ� ���밪�Լ�
						max = doublePlus(tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n]);
				}
			}
			tmpOutImage[i][k] = max;



		}
	}
	//��ó��(����ũ ���� �հ迡 ����..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//�ӽ� ��� ����--> ��¿���
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
void diffImage() {//�� ������
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[4] = {//���� �̹������̶� 1 ����ũ�� ���� �����ֱ�
		0.0,1.0,2.0,3.0 };

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double max;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			max = 0.0;//��� �̵��� ������ �ִ밪 �ʱ�ȭ
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
	//��ó��(����ũ ���� �հ迡 ����..)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	//�ӽ� ��� ����--> ��¿���
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
void firstDifferentiation() {//1�� �̺��� �̿��� ���� ����
	system("cls");
	char mirKey = 0;
	puts("\n 1�� �̺� ȸ�� ����ũ ����");
	puts("\n 1.�ι��� 2.������ 3.�Һ� 9.���");
	mirKey = _getch();
	switch (mirKey) {
	case '1': roberts(); return;
	case '2': prewitt(); return;
	case '3': sobel(); return;
	case '9': return; // �޴�
	default: printf("�߸��� �Է� \n"); return;
	}
}
void secundDifferentiation() {//2�� �̺��� �̿��� ���� ����
	system("cls");
	system("cls");
	char mirKey = 0;
	puts("\n 2�� �̺� ȸ�� ����ũ ����");
	puts("\n 1.���ö�þ� 2.�α� 3.���� 9.���");
	mirKey = _getch();
	switch (mirKey) {
	case '1': laplacian(); return;
	case '2': logGaussian(); return;
	case '3': dogGaussian(); return;
	case '9': return; // �޴�
	default: printf("�߸��� �Է� \n"); return;
	}
}
void roberts() {
	system("cls");
	char mirKey = 0;
	puts("\n �ι��� ȸ�� ����ũ ����");
	puts("\n 1.���� 2.���� 3.�Ѵ� 9.���");
	mirKey = _getch();
	switch (mirKey) {
	case '1': roberts1(); return;
	case '2': roberts2(); return;
	case '3': roberts3(); return;
	case '9': return; // �޴�
	default: printf("�߸��� �Է� \n"); return;
	}
}
void prewitt() {
	system("cls");
	char mirKey = 0;
	puts("\n �ι��� ȸ�� ����ũ ����");
	puts("\n 1.���� 2.���� 3.�Ѵ� 9.���");
	mirKey = _getch();
	switch (mirKey) {
	case '1': prewitt1(); return;
	case '2': prewitt2(); return;
	case '3': prewitt3(); return;
	case '9': return; // �޴�
	default: printf("�߸��� �Է� \n"); return;
	}
}
void sobel() {
	system("cls");
	char mirKey = 0;
	puts("\n �ι��� ȸ�� ����ũ ����");
	puts("\n 1.���� 2.���� 3.�Ѵ� 9.���");
	mirKey = _getch();
	switch (mirKey) {
	case '1': sobel1(); return;
	case '2': sobel2(); return;
	case '3': sobel3(); return;
	case '9': return; // �޴�
	default: printf("�߸��� �Է� \n"); return;
	}
}

void laplacian() {
	system("cls");
	char mirKey = 0;
	puts("\n ���ö�þ� ������ ����ũ");
	puts("\n 1.����ũ1 2.����ũ2 3.����ũ3 9.���");
	mirKey = _getch();
	switch (mirKey) {
	case '1': laplacian1(); return;
	case '2': laplacian2(); return;
	case '3': laplacian3(); return;
	case '9': return; // �޴�
	default: printf("�߸��� �Է� \n"); return;
	}
}





void roberts1() { // �ι��� ����ũ1
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{-1.0,0.0,0.0},
	   { 0.0,1.0,0.0},
	   { 0.0,0.0,0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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
void roberts2() { // �ι��� ����ũ2
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{0.0,0.0,-1.0},
		{ 0.0,1.0,0.0},
		{ 0.0,0.0,0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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
void roberts3() { // �ι��� ����ũ3
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{-1.0,0.0,-1.0},
		{ 0.0,2.0,0.0},
		{ 0.0,0.0,0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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
void prewitt1() { // ������ ����ũ1
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{-1.0,-1.0,-1.0},
	   { 0.0,0.0,0.0},
	   { 1.0,1.0,1.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//�ӽ� ��� ����--> ��¿���
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
void prewitt2() { // ������ ����ũ2
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{ 1.0,0.0,-1.0},
		{ 1.0,0.0,-1.0},
		{ 1.0,0.0,-1.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//�ӽ� ��� ����--> ��¿���
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
void prewitt3() { // ������ ����ũ3
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{0.0,-1.0,-2.0},
		{ 1.0,0.0,-1.0},
		{ 2.0,1.0,0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//�ӽ� ��� ����--> ��¿���
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
void sobel1() { // �Һ� ����ũ1
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{-1.0,-2.0,-1.0},
	   { 0.0,0.0,0.0},
	   { 1.0,2.0,1.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//�ӽ� ��� ����--> ��¿���
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
void sobel2() { // �Һ� ����ũ2
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{ 1.0,0.0,-1.0},
		{ 2.0,0.0,-2.0},
		{ 1.0,0.0,-1.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//�ӽ� ��� ����--> ��¿���
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
void sobel3() { // �Һ� ����ũ3
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{ 0.0,-2.0,-2.0},
		{ 2.0,0.0,-2.0},
		{ 2.0,2.0,0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}


	//�ӽ� ��� ����--> ��¿���
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
void laplacian1() { // ���ö�þ� ������ ����ũ1
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
	   { 0.0,-1.0, 0.0},
	   {-1.0, 4.0,-1.0},
	   { 0.0,-1.0, 0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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
void laplacian2() { // ���ö�þ� ������ ����ũ2
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{ 1.0, 1.0,1.0},
		{ 1.0,-8.0,1.0},
		{ 1.0, 1.0,1.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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
void laplacian3() { // ���ö�þ� ������ ����ũ3
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[3][3] = {//������ ����ũ
		{-1.0,-1.0,-1.0},
		{-1.0, 8.0,-1.0},
		{-1.0,-1.0,-1.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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
void logGaussian() { // LoG ������
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[5][5] = {//������ ����ũ
	   { 0.0, 0.0,-1.0, 0.0, 0.0},
	   { 0.0,-1.0,-2.0,-1.0, 0.0},
	   {-1.0,-2.0,16.0,-2.0,-1.0},
	   { 0.0,-1.0,-2.0,-1.0, 0.0},
	   { 0.0, 0.0,-1.0, 0.0, 0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 4, inW + 4);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 4; i++)
		for (int k = 0; k < inW + 4; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(5x5)�� ������ �߽������� 5x5�� ���ϱ�
			S = 0.0;
			//����ũ 25���� �Է°� 25���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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
void dogGaussian() { // DoG ������
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	//////////////////////
	// ȭ�� ���� ó��
	///////////////////////
	double mask[7][7] = {//������ ����ũ
	   { 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0},
	   { 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0},
	   {-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0},
	   {-1.0,-3.0, 5.0,16.0, 5.0,-3.0,-1.0},
	   {-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0},
	   { 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0},
	   { 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0}
	};

	//�ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 6, inW + 6);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	//�ӽ� �Է� �޸𸮸� �ʱ�ȭ(127): �ʿ�� ��հ�
	for (int i = 0; i < inH + 6; i++)
		for (int k = 0; k < inW + 6; k++)
			tmpInImage[i][k] = 127;
	//�Է� �̹���--> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	//�߿�! ȸ������ 
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			//����ũ(3x3)�� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0;
			//����ũ 9���� �Է°� 9���� ���� ���ؼ� ���Ѱ�
			for (int m = 0; m < 7; m++)
				for (int n = 0; n < 7; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];
			tmpOutImage[i][k] = S;


		}
	}

	//�ӽ� ��� ����--> ��¿���
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