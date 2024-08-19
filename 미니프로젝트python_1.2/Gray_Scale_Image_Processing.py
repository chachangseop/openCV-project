import math
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
import os.path
from tkinter.simpledialog import *
### 함수부
#*****************
# 공통 함수부
#*****************
def malloc2D(h, w, initValue=0) :
    memory = [ [initValue for _ in range(w)] for _ in range(h)]
    return memory

# def malloc2D(h, w, initValue=0) :
#     memory = [ [initValue for _ in range(w)] for _ in range(h)]
#     return memory

def openImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    fullname = askopenfilename(parent=window, filetypes=(('RAW파일', '*.raw'),('모든파일','*.*'))  )
    # 중요! 입력 이미지 크기를 결정
    fsize = os.path.getsize(fullname)  # 파일 크기(Byte)
    inH = inW = int(math.sqrt(fsize))
    # 메모리 할당
    inImage = malloc2D(inH, inW)
    # 파일 --> 메모리
    rfp = open(fullname, 'rb')
    for i in range(inH) :
        for k in range(inW) :
            inImage[i][k] = ord(rfp.read(1))
    rfp.close()
    equalImage()

def saveImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    if (outImage == None) :
        return
    wfp = asksaveasfile(parent=window, mode='wb', defaultextension='*.raw',
                        filetypes=(('RAW파일', '*.raw'),('모든파일','*.*')) )
    import struct
    for i in range(outH) :
        for k in range(outW) :
            wfp.write( struct.pack('B', outImage[i][k]))
    wfp.close()
    messagebox.showinfo('성공', wfp.name + '저장완료!')

def displayImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    ## 기존에 이미지를 오픈한적이 있으면, 캔버스 뜯어내기
    if (canvas != None) :
        canvas.destroy()
    ## 벽, 캔버스, 종이 설정
    window.geometry(str(outH)+'x'+str(outW)) # "512x512"
    canvas = Canvas(window, height=outH, width=outW, bg='yellow')  # 칠판
    paper = PhotoImage(height=outH, width=outW)  # 종이
    canvas.create_image((outH // 2, outW // 2), image=paper, state='normal')
    ## 메모리 --> 화면
    # for i in range(outH):
    #     for k in range(outW):
    #         r = g = b = inImage[i][k]
    #         paper.put('#%02x%02x%02x' % (r, g, b), (k, i))
    # 더블 버퍼링... 비슷한 기법 (모두다 메모리상에 출력형태로 생성한 후에, 한방에 출력)
    rgbString = "" # 전체에 대한 16진수 문자열
    for i in range(outH) :
        oneString = "" # 한줄에 대한 16진수 문자열
        for k in range(outW) :
            r = g = b = outImage[i][k]
            oneString += '#%02x%02x%02x ' % (r, g, b)
        rgbString += '{' + oneString + '} '
    paper.put(rgbString)
    canvas.pack()

#*****************
# 영상처리 함수부
#*****************
def equalImage() : # 동일 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    #### 진짜 영상처리 알고리즘 ###
    for i in range(inH) :
        for k in range(inW) :
            outImage[i][k] = inImage[i][k]
    ############################
    displayImage()

def addImage() : # 동일 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    #### 진짜 영상처리 알고리즘 ###
    value = askinteger('정수입력','-255~255 입력', maxvalue=255, minvalue=-255)
    for i in range(outH) :
        for k in range(outW) :
            px = inImage[i][k] + value
            if (px > 255) :
                px = 255
            if (px < 0) :
                px = 0
            outImage[i][k] = px
    displayImage()



def reverImage():
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##

    for i in range(inH):
        for k in range(inW):
                outImage[i][k] = 255 - inImage[i][k]
    displayImage()

def blwhImage():
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    for i in range(inH):
        for k in range(inW):
            if (inImage[i][k] >= 128):
                    outImage[i][k] = 255
    for i in range(inH):
        for k in range(inW):
            if (inImage[i][k] < 128):
                    outImage[i][k] = 0
    displayImage()

def gammaImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    value = askfloat('실수입력', '0~2.5 입력', maxvalue=2.5, minvalue=0)
    for i in range(inH) :
        for k in range(inW) :
            outImage[i][k] = pow(inImage[i][k] / 255, value) * 255
    displayImage()


def andImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    value = askinteger('정수입력','0~255 입력', maxvalue=255, minvalue=0)
    for i in range(inH) :
        for k in range(inW) :
            outImage[i][k] = inImage[i][k] & value
    displayImage()

def zoomOut() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    value = askinteger('정수입력','0~ 입력', minvalue=0)
    for i in range(inH) :
        for k in range(inW) :
            outImage[int(i/value)][int(k/value)] = inImage[i][k]#c언어와 다르게 (int) 에서 ()빼기
    displayImage()


def zoomIn2Image() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    value = askinteger('정수입력','0~ 입력', minvalue=0)
    for i in range(inH) :
        for k in range(inW) :
            outImage[i][k] = inImage[int(i/value)][int(k/value)]
    displayImage()

def rotate2() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    cx = int(inH / 2)
    cy = int(inW / 2)
    degree = askinteger('정수입력', '각도', maxvalue=360, minvalue=-360)
    radian = float(degree * 3.141592 / 180.0)
    for i in range(inH) :
        for k in range(inW) :
            xd = i
            yd = k
            xs = int(math.cos(radian) * (xd - cx) + math.sin(radian) * (yd - cy))
            ys = int(-math.sin(radian) * (xd - cx) + math.cos(radian) * (yd - cy))
            xs += cx
            ys += cy
            if ((0 <= xs < outH) and (0 <= ys < outW)) :
                outImage[xd][yd] = inImage[xs][ys]
    displayImage()

def transImage() : # 동일 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    #### 진짜 영상처리 알고리즘 ###
    value1 = askinteger('입력','x 입력')
    value2 = askinteger('입력', 'y 입력')
    # value1 = askfloat('실수입력', 'x 입력', minvalue=0)
    # value2 = askfloat('실수입력', 'y 입력', minvalue=0)
    tx, ty = value1, value2
    #실패
    tty = inH-ty
    ttx = inW-tx
    # tty = float(inH - ty)
    # ttx = float(inW - tx)
    # for k in range() 안에 ttx를 넣든 inW-tx를 넣든 전부 에러 float 실수 안됨
    # for i in range(tty) :
    #     for k in range(ttx) : 범위 밖이라고 실패 아마 캔버스 밖범위 포함이라?
    #         outImage[int(i + ty)][int(k + tx)] = inImage[i][k]
    for i in range(tty):
        for k in range(ttx) :
            outImage[int(i + ty)][int(k + tx)] = inImage[i][k]
    # for i in range(inH) :
    #     for k in range(inW) :
    #
    #         outImage[int(i + ty)][int(k + tx)] = inImage[i][k]


#c언어
    # for (int i = 0; i < inH - tx; i++) {
    # for (int k = 0; k < inW - ty; k++) {
    # outImage[(int)(i + tx)][(int)(k + ty)] = inImage[i][k];

    ############################
    displayImage()

def mirrorLRImage() : # 동일 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    #### 진짜 영상처리 알고리즘 ###
    for i in range(inH) :
        for k in range(inW) :
            mk = inW - 1 - k
            outImage[i][k] = inImage[i][mk]
    ############################
    displayImage()


def mirrorHLImage() : # 동일 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    #### 진짜 영상처리 알고리즘 ###
    for i in range(inH) :
        for k in range(inW) :
            mi = inW - 1 - i
            outImage[i][k] = inImage[mi][k]
    ############################
    displayImage()
def histoStretch() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    high = inImage[0][0]
    low = inImage[0][0]
    for i in range(inH):
        for k in range(inW):
            if (inImage[i][k] < low) :
                low = inImage[i][k]
            if (inImage[i][k] > high) :
                high = inImage[i][k]
    old, new = 0, 0   # int old;는 old = 0 로 (초기화?)
    for i in range(inH):
        for k in range(inW):
            old = inImage[i][k]
            new = int(float(old - low) / float(high - low) * 255)
            # new = int(old - low) / int(high - low) * 255
            # if (new < 0) :
            #     new = None
            if (new > 255) :
                new = 255
            if (new < 0) :
                new = 0
            outImage[i][k] = new

    displayImage()




def andIn() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    high = inImage[0][0]
    low = inImage[0][0]
    for i in range(inH):
        for k in range(inW):
            if (inImage[i][k] < low) :
                low = inImage[i][k]
            if (inImage[i][k] > high) :
                high = inImage[i][k]
    high -= 50
    low += 50
    old, new = 0, 0   # int old;는 old = 0 로 (초기화?)
    for i in range(inH):
        for k in range(inW):
            old = inImage[i][k]
            new = int(float(old - low) / float(high - low) * 255)
            # new = int(old - low) / int(high - low) * 255
            # if (new < 0) :
            #     new = None
            if (new > 255) :
                new = 255
            if (new < 0) :
                new = 0
            outImage[i][k] = new

    displayImage()


def histoEqual() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##\
    #1단계 빈도수 세기
    #int histo[256] = { 0 };
    histo = []
    for _ in range(256) :
        histo.append(0)

    for i in range(inH):
        for k in range(inW):
            histo[inImage[i][k]] += 1
    # 2단계
    # 히스토그램 누적합 sumHisto[i]
    sumHisto = []
    for _ in range(256):
        sumHisto.append(0)
    sumHisto[0] = histo[0]
    for i in range(256):
        sumHisto[i] = sumHisto[i - 1] + histo[i]
    # 3단계
    # 정규화된 히스토그램 생성 normalHisto=sumHisto*(1.0/(inH*inW))*255.0
    normalHisto = []
    for _ in range(256):
        normalHisto.append(1.0)
    for i in range(256):
        normalHisto[i] = sumHisto[i]*(1.0/(inH*inW))*255.0
    # 4단계 : inImage를 정규화된 값으로 치환
    for i in range(inH):
        for k in range(inW):
            # if (normalHisto[inImage[i][k]] < 0):
            #     normalHisto[inImage[i][k]]= False
            # if (normalHisto[inImage[i][k]] > 255):
            #     normalHisto[inImage[i][k]] = False
            outImage[i][k] = int(normalHisto[inImage[i][k]])


    displayImage()

def emboss() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[-1.0, 0.0, 0.0], [0.0, 0.0, 0.0], [0.0, 0.0, 1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    #후처리
    for i in range(outH):
        for k in range(outW):
            tmpOutImage[i][k] += 127.0
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()


def blur() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[1./9, 1./9, 1./9], [1./9, 1./9, 1./9], [1./9, 1./9, 1./9]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def sharpNomal() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[0. ,-1. , 0.], [-1., 5., -1.], [0. ,-1. , 0.]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    #후처리
    for i in range(outH):
        for k in range(outW):
            tmpOutImage[i][k] += 127.0
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()


def sharpHf() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[-1. / 9, -1. / 9, -1. / 9], [-1. / 9, 8. / 9, -1. / 9], [-1. / 9, -1. / 9, -1. / 9]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    #후처리
    for i in range(outH):
        for k in range(outW):
            tmpOutImage[i][k] += 127.0
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()

def sharpLf() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[1. / 9, 1. / 9, 1. / 9], [1. / 9, 1. / 9, 1. / 9], [1. / 9, 1. / 9, 1. / 9]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!블러 처리된 회선연산!!!
    S = 0
    hx = 0
    val = askinteger('정수입력', '')
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
            hx = val * inImage[i][k] - S * (val - 1)
            tmpOutImage[i][k] = hx


    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()


def similarImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[1.0, 1.0, 1.0], [1.0, 1.0, 1.0], [1.0, 1.0, 1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    max = 0
    for i in range(inH):
        for k in range(inW):
            max = 0.0
            for m in range(3):
                for n in range(3):
                    if (int(tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n] >= max)) :
                        max = int(tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n])
            tmpOutImage[i][k] = max
    # 후처리
    for i in range(outH):
        for k in range(outW):
            tmpOutImage[i][k] += 127.0

    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()


def diffImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [0.0, 1.0, 2.0, 3.0]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    max = 0 # 최대값
    for i in range(inH):
        for k in range(inW):
            max = 0.0
            mask[0] = int(tmpInImage[i][k] - tmpInImage[i + 2][k + 2])
            mask[1] = int(tmpInImage[i][k + 1] - tmpInImage[i + 2][k + 1])
            mask[2] = int(tmpInImage[i][k + 2] - tmpInImage[i + 2][k])
            mask[3] = int(tmpInImage[i + 1][k + 2] - tmpInImage[i + 1][k])
            for m in range(3):
                if (mask[m] >= max) :
                    max = mask[m]
            tmpOutImage[i][k] = max
    # 후처리
    for i in range(outH):
        for k in range(outW):
            tmpOutImage[i][k] += 127.0
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()

def roberts1() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[-1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()

def roberts2() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[0.0,0.0,-1.0], [0.0,1.0,0.0], [0.0,0.0,0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()

def roberts3() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[-1.0,0.0,-1.0], [0.0,2.0,0.0], [ 0.0,0.0,0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()

def prewitt1() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[-1.0,-1.0,-1.0], [0.0,0.0,0.0], [1.0,1.0,1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()

def prewitt2() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[1.0,0.0,-1.0], [1.0,0.0,-1.0], [1.0,0.0,-1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def prewitt3() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[0.0,-1.0,-2.0], [1.0,0.0,-1.0], [2.0,1.0,0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def sobel1() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[-1.0,-2.0,-1.0], [0.0,0.0,0.0], [1.0,2.0,1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def sobel2() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[1.0,0.0,-1.0], [2.0,0.0,-2.0], [1.0,0.0,-1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def sobel3() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[0.0,-2.0,-2.0], [2.0,0.0,-2.0], [2.0,2.0,0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def laplacian1() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[0.0,-1.0, 0.0], [-1.0, 4.0,-1.0], [0.0,-1.0, 0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def laplacian2() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[1.0, 1.0,1.0], [1.0,-8.0,1.0], [1.0, 1.0,1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def laplacian3() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[-1.0,-1.0,-1.0], [-1.0, 8.0,-1.0], [-1.0,-1.0,-1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+2):
        for k in range(inW+2):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def logGaussian() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[0.0, 0.0,-1.0, 0.0, 0.0],
            [0.0,-1.0,-2.0,-1.0, 0.0],
            [-1.0,-2.0,16.0,-2.0,-1.0],
            [0.0,-1.0,-2.0,-1.0, 0.0],
            [0.0, 0.0,-1.0, 0.0, 0.0]
            ]
    tmpInImage = malloc2D(inH + 4, inW + 4)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+4):
        for k in range(inW+4):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(5):
                for n in range(5):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
def dogGaussian() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #(중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ## 진짜 영상처리 알고리즘 ##
    #엠보싱 마스크\
    mask = [[ 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0],
            [ 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0],
            [1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0],
            [-1.0,-3.0, 5.0,16.0, 5.0,-3.0,-1.0],
            [-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0],
            [ 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0],
            [ 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0]]
    tmpInImage = malloc2D(inH + 6, inW + 6)
    tmpOutImage = malloc2D(outH, outW)
    #임시 입력 메모리를 초기화(127): 필요시 평균값
    for i in range(inH+6):
        for k in range(inW+6):
            tmpInImage[i][k] = 127
    #입력 이미지--> 임시 입력 이미지
    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    #!!!회선연산!!!
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(7):
                for n in range(7):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 임시 출력 영상--> 출력영상
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0) :
                outImage[i][k] = 0
            else :
                if (tmpOutImage[i][k] > 255.0) :
                    outImage[i][k] = 255
                else :
                        outImage[i][k] = int(tmpOutImage[i][k])

    displayImage()
############################
### 전역 변수부
window, canvas, paper = None, None, None
inImage, outImage = [], []
inH, inW, outH, outW = [0]*4
fullname = ''

### 메인 코드부
window = Tk() # 벽
window.geometry("500x500")
window.resizable(width=False, height=False)
window.title("영상처리 (RC 1)")

# 메뉴 만들기
mainMenu = Menu(window) # 메뉴의 틀
window.config(menu=mainMenu)


fileMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴 (파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=openImage)
fileMenu.add_command(label='저장', command=saveImage)
fileMenu.add_separator()
fileMenu.add_command(label='종료', command=None)

# pixelMenu = Menu(mainMenu,tearoff=0)  # 상위 메뉴 (화소점처리)
# mainMenu.add_cascade(label='화소점 처리', menu=pixelMenu)
# pixelMenu.add_command(label='동일 이미지', command=equalImage)
# pixelMenu.add_command(label='밝게/어둡게', command=addImage)
# pixelMenu.add_command(label='반전 이미지', command=addImage)
# pixelMenu.add_command(label='평균 흑백 이미지', command=addImage)
# pixelMenu.add_command(label='감마 이미지', command=addImage)
# pixelMenu.add_command(label='앤드 이미지', command=addImage)
# #
# geometryMenu = Menu(mainMenu,tearoff=0)  # 상위 메뉴 (기하학)
# mainMenu.add_cascade(label='기하학', menu=geometryMenu)
# geometryMenu.add_command(label='이미지 축소', command=equalImage)
# geometryMenu.add_command(label='이미지 확대', command=addImage)
# geometryMenu.add_command(label='이미지 회전', command=addImage)
# geometryMenu.add_command(label='이미지 이동', command=addImage)
# geometryMenu.add_command(label='이미지 좌우 미러링', command=addImage)
# geometryMenu.add_command(label='이미지 상하 미러링', command=addImage)

# pixelAreaMenu = Menu(mainMenu,tearoff=0)  # 상위 메뉴 (화소 영역 처리)
# mainMenu.add_cascade(label='화소 영역', menu=pixelAreaMenu)
# pixelAreaMenu.add_command(label='엠보싱', command=equalImage)
# pixelAreaMenu.add_command(label='블러', command=equalImage)
# pixelAreaMenu.add_command(label='샤프', command=equalImage)
# pixelAreaMenu.add_command(label='연산자 기법', command=equalImage)
# pixelAreaMenu.add_command(label='1차 미분 엣지 ', command=equalImage)
# pixelAreaMenu.add_command(label='2차 미분 엣지', command=equalImage)

#시도 실패
editMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴 (파일)
mainMenu.add_cascade(label='편집', menu=editMenu)

pixelMenu = Menu(editMenu,tearoff=0) # 상위 메뉴 (기하학)
editMenu.add_cascade(label='화소점 처리', menu=pixelMenu)
pixelMenu.add_command(label='동일 이미지', command=equalImage)
pixelMenu.add_command(label='밝게/어둡게', command=addImage)
pixelMenu.add_command(label='반전 이미지', command=reverImage)
pixelMenu.add_command(label='평균 흑백 이미지', command=blwhImage)
pixelMenu.add_command(label='감마 이미지', command=gammaImage)
pixelMenu.add_command(label='앤드 이미지', command=andImage)

geometryMenu = Menu(editMenu,tearoff=0)  # 상위 메뉴 (기하학)
editMenu.add_cascade(label='기하학', menu=geometryMenu)
geometryMenu.add_command(label='이미지 축소', command=zoomOut)
geometryMenu.add_command(label='이미지 확대', command=zoomIn2Image)
geometryMenu.add_command(label='이미지 회전', command=rotate2)
geometryMenu.add_command(label='이미지 이동', command=transImage)
geometryMenu.add_command(label='이미지 좌우 미러링', command=mirrorLRImage)
geometryMenu.add_command(label='이미지 상하 미러링', command=mirrorHLImage)

histogramMenu = Menu(editMenu,tearoff=0)  # 상위 메뉴 (기하학)
editMenu.add_cascade(label='히스토그램 처리', menu=histogramMenu)
histogramMenu.add_command(label='히스토그램 스트레칭', command=histoStretch)
histogramMenu.add_command(label='앤드 인 탐색', command=andIn)
histogramMenu.add_command(label='히스토그램 평활화', command=histoEqual)




pixelAreaMenu = Menu(editMenu,tearoff=0)  # 상위 메뉴 (화소 영역 )
editMenu.add_cascade(label='화소 영역', menu=pixelAreaMenu)
pixelAreaMenu.add_command(label='엠보싱', command=emboss)
pixelAreaMenu.add_command(label='블러', command=blur)

sharpMenu = Menu(pixelAreaMenu,tearoff=0)  # 상위 메뉴 (화소 영역 )
pixelAreaMenu.add_cascade(label='샤프', menu=sharpMenu)
sharpMenu.add_command(label='샤프 노말', command=sharpNomal)
sharpMenu.add_command(label='샤프 하이', command=sharpHf)
sharpMenu.add_command(label='샤프 로우', command=sharpLf)

pixelAreaEdgeMenu = Menu(pixelAreaMenu,tearoff=0)  # 상위 메뉴 (편집)
pixelAreaMenu.add_cascade(label='에지', menu=pixelAreaEdgeMenu)

operatorMenu = Menu(pixelAreaEdgeMenu,tearoff=0)  # 상위 메뉴 (화소 영역 처리)
pixelAreaEdgeMenu.add_cascade(label='연산자 기법', menu=operatorMenu)
operatorMenu.add_command(label='유사 연산자', command=similarImage)
operatorMenu.add_command(label='차 연산자', command=diffImage)

firstDerivativeMenu = Menu(pixelAreaEdgeMenu,tearoff=0)  # 상위 메뉴 (화소 영역 처리)
pixelAreaEdgeMenu.add_cascade(label='1차 미분 엣지', menu=firstDerivativeMenu)

robertsMenu = Menu(firstDerivativeMenu,tearoff=0)  # 상위 메뉴 (화소 영역 처리)
firstDerivativeMenu.add_cascade(label='로버츠', menu=robertsMenu)
robertsMenu.add_command(label='마스크1', command=roberts1)
robertsMenu.add_command(label='마스크2', command=roberts2)
robertsMenu.add_command(label='마스크1+마스크2', command=roberts3)

prewittMenu = Menu(firstDerivativeMenu,tearoff=0)  # 상위 메뉴 (화소 영역 처리)
firstDerivativeMenu.add_cascade(label='프리윗', menu=prewittMenu)
prewittMenu.add_command(label='마스크1', command=prewitt1)
prewittMenu.add_command(label='마스크2', command=prewitt2)
prewittMenu.add_command(label='마스크1+마스크2', command=prewitt3)

sobelMenu = Menu(firstDerivativeMenu,tearoff=0)  # 상위 메뉴 (화소 영역 처리)
firstDerivativeMenu.add_cascade(label='소벨', menu=sobelMenu)
sobelMenu.add_command(label='마스크1', command=sobel1)
sobelMenu.add_command(label='마스크2', command=sobel2)
sobelMenu.add_command(label='마스크1+마스크2', command=sobel3)


secondDerivativeMenu = Menu(pixelAreaEdgeMenu,tearoff=0)
pixelAreaEdgeMenu.add_cascade(label='2차 미분 엣지', menu=secondDerivativeMenu)
secondDerivativeMenu.add_command(label='Log', command=logGaussian)
secondDerivativeMenu.add_command(label='Dog', command=dogGaussian)

laplacianMenu = Menu(secondDerivativeMenu,tearoff=0)
secondDerivativeMenu.add_cascade(label='라플라시안', menu=laplacianMenu)
laplacianMenu.add_command(label='라플라시안1', command=laplacian1)
laplacianMenu.add_command(label='라플라시안2', command=laplacian2)
laplacianMenu.add_command(label='라플라시안1+라플라시안2', command=laplacian3)








# pixelMenu = Menu(editMenu,tearoff=0)  # 상위 메뉴 (화소점처리)
# editMenu.add_cascade(label='편집', menu=pixelMenu)
# pixelMenu.add_command(label='동일 이미지', command=equalImage)
# pixelMenu.add_command(label='밝게/어둡게', command=addImage)




window.mainloop()