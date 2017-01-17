#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

vector<Mat>  Img_segmentation(Mat& img1, Mat&img2);
double proCale(Mat& mat1, int width_1, int height_1, int width_2, int height_2);
int getPro(Mat& mat1, int type);


#define NUM 0
#define LET 1
#define CHI 2

#define  match_detect 65

//模版地址索引
string match_pic[match_detect] =
{
	{ ".//match_pic//0.bmp" },
	{ ".//match_pic//1.bmp" },
	{ ".//match_pic//2.bmp" },
	{ ".//match_pic//3.bmp" },
	{ ".//match_pic//4.bmp" },
	{ ".//match_pic//5.bmp" },
	{ ".//match_pic//6.bmp" },
	{ ".//match_pic//7.bmp" },
	{ ".//match_pic//8.bmp" },
	{ ".//match_pic//9.bmp" },

	{ ".//match_pic//A.bmp" },
	{ ".//match_pic//B.bmp" },
	{ ".//match_pic//C.bmp" },
	{ ".//match_pic//D.bmp" },
	{ ".//match_pic//E.bmp" },
	{ ".//match_pic//F.bmp" },
	{ ".//match_pic//G.bmp" },
	{ ".//match_pic//H.bmp" },
	{ ".//match_pic//J.bmp" },
	{ ".//match_pic//K.bmp" },
	{ ".//match_pic//L.bmp" },
	{ ".//match_pic//M.bmp" },
	{ ".//match_pic//N.bmp" },
	{ ".//match_pic//P.bmp" },
	{ ".//match_pic//Q.bmp" },
	{ ".//match_pic//R.bmp" },
	{ ".//match_pic//S.bmp" },
	{ ".//match_pic//T.bmp" },
	{ ".//match_pic//U.bmp" },
	{ ".//match_pic//V.bmp" },
	{ ".//match_pic//W.bmp" },
	{ ".//match_pic//X.bmp" },
	{ ".//match_pic//Y.bmp" },
	{ ".//match_pic//Z.bmp" },

	{ ".//match_pic//zw1.bmp" },
	{ ".//match_pic//zw2.bmp" },
	{ ".//match_pic//zw3.bmp" },
	{ ".//match_pic//zw4.bmp" },
	{ ".//match_pic//zw5.bmp" },
	{ ".//match_pic//zw6.bmp" },
	{ ".//match_pic//zw7.bmp" },
	{ ".//match_pic//zw8.bmp" },
	{ ".//match_pic//zw9.bmp" },
	{ ".//match_pic//zw10.bmp" },
	{ ".//match_pic//zw11.bmp" },
	{ ".//match_pic//zw12.bmp" },
	{ ".//match_pic//zw13.bmp" },
	{ ".//match_pic//zw14.bmp" },
	{ ".//match_pic//zw15.bmp" },
	{ ".//match_pic//zw16.bmp" },
	{ ".//match_pic//zw17.bmp" },
	{ ".//match_pic//zw18.bmp" },
	{ ".//match_pic//zw19.bmp" },
	{ ".//match_pic//zw20.bmp" },
	{ ".//match_pic//zw21.bmp" },
	{ ".//match_pic//zw22.bmp" },
	{ ".//match_pic//zw23.bmp" },
	{ ".//match_pic//zw24.bmp" },
	{ ".//match_pic//zw25.bmp" },
	{ ".//match_pic//zw26.bmp" },
	{ ".//match_pic//zw27.bmp" },
	{ ".//match_pic//zw28.bmp" },
	{ ".//match_pic//zw29.bmp" },
	{ ".//match_pic//zw30.bmp" },
	{ ".//match_pic//zw31.bmp" },
};

//模版索引
string name[match_detect] =
{
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",

	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"J",
	"K",
	"L",
	"M",
	"N",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",

	"藏",
	"川",
	"鄂",
	"甘",
	"赣",
	"贵",
	"桂",
	"黑",
	"沪",
	"吉",
	"冀",
	"津",
	"晋",
	"京",
	"辽",
	"鲁",
	"蒙",
	"闽",
	"宁",
	"青",
	"琼",
	"陕",
	"苏",
	"皖",
	"湘",
	"新",
	"渝",
	"豫",
	"粤",
	"云",
	"浙",
};


int result[7];	//保存识别索引
int type[7] =	//车牌，中英文数字格式
{
	CHI,
	LET,
	LET,
	NUM,
	NUM,
	NUM,
	NUM,
};


int main()
{
//	system("color fc");
	Mat img_gray, img_edge;
	//img_gray = imread("test1.jpg", 0);

		//img_gray = imread("test2.jpg", 0);

		img_gray = imread("test3.jpg", 0);
		imshow("原图（灰度）",img_gray);

	//图像滤波
	GaussianBlur(img_gray, img_gray, Size(3, 3), 0, 0);
	imshow("高斯滤波", img_gray);

	//边缘检测
	Canny(img_gray, img_edge, 100, 200);
	imshow("边缘检测", img_edge);

//	printf("%d,%d", img_gray.cols, img_gray.rows);


	//执行图像分割，分割后的块保存在vector<Mat> ROI中
	vector<Mat> ROI = Img_segmentation(img_edge,img_gray);

	//单个字符匹配
	for (int i = 0; i < 7; i++)
	{
		Mat img = ROI[i];	//从vector<Mat> ROI中读取分割后的块
		resize(img, img, Size(60, 120));  //调整与模版同样大小
		threshold(img, img, 0, 255, CV_THRESH_BINARY + CV_THRESH_OTSU); //自动二值化，好于模版对应
		result[i] = getPro(img, type[i]); //获得索引号，保存到result数组
	}
	//通过result数组中保存的索引对应name索引数组输出字符串
	printf("车牌识别结果是：");
	for (int i = 0; i < 7; i++)
	{
		printf("%s", name[result[i]].c_str());
	}

	waitKey(0);

}
/**********************************************************************/
//车牌分割，寻找边界，缩放到指定大小409*90 等比例切割 得到7个ROI返回
//输入；灰度图，边缘图
//返回：7个切割完成的ROI块
/**********************************************************************/
vector<Mat>  Img_segmentation(Mat& img1,Mat&img2)
{
	#define T 27
	#define T1 2
	int i, j;
	int row_start, row_end;//用来记录车牌开始，结束行
	int col_start, col_end;//用来记录车牌开始，结束列
	int count = 0;//用来记录行或列的白点个数

	row_start = 0;
	row_end = 0;
	col_start = 0;
	col_end = 0;
	int row[320]; //120
	int col[600]; //340
	int k;
	k = 0;
	bool flag = false;

	for (j = 0; j <img1.rows; j++)												//找到上行开始 一行一行扫描
	{
		count = 0;
		for (i = 0; i <img1.cols - 1; i++)
		{
			if (img1.at<uchar>(j, i) != img1.at<uchar>(j, i + 1))				//统计跳变次数，真正有效数据区域跳变数比较大
				count++;
			if (count>T)
			{
				row[k] = j;
				k++;
				break;
			}
		}
	}

	for (i = 0; i<k; i++)														//从上边开始，3行连续有多次跳变认为是起始行
	{
		if ((row[i] == row[i + 1] - 1) && (row[i + 1] == row[i + 2] - 1)){
			row_start = row[i];
			break;
		}
	}
	//	cout << "the start row:" << row_start << endl;
	//printf("the start row:%d\r\n", row_start);
	line(img2, Point(0, row_start), Point(img2.cols, row_start), Scalar(255, 0, 0), 1, 8, 0);
	//cvLine(pImg8u, cvPoint(0, row_start), cvPoint(src->width, row_start), cvScalar(255, 0, 0), 1, 8, 0);


	for (i = k - 1; i>row_start; i--)     //从下边开始，3行连续有多次跳变认为是起始行
	{
		if ((row[i] == row[i - 1] + 1) && (row[i - 1] == row[i - 2] + 1)){
			row_end = row[i];
			break;
		}
	}
	//	cout << "the end row:" << row_end << endl;
	//printf("the end row:%d\r\n", row_end);
	//cvLine(pImg8u, cvPoint(0, row_end), cvPoint(src->width, row_end), cvScalar(255, 0, 0), 1, 8, 0);
	line(img2, Point(0, row_end), Point(img2.cols, row_end), Scalar(255, 0, 0), 1, 8, 0);



	flag = false;
	for (i = 10; i<img1.cols; i++)											//找到左边界 从最左10像素开始 一列一列扫描
	{
		count = 0;
		for (j = row_start; j<row_end; j++)
		{
			if (img1.at<uchar>(j, i) == 255)	
				count++;
			if (count>T1)													//出现大量边界白色信息
			{
				col_start = i;
				flag = true;
				break;
			}
		}
		if (flag) break;
	}
	//	cout << "the start col:" << col_start << endl;
	//printf("the start col:%d\r\n", col_start);
	//cvLine(pImg8u, cvPoint(col_start, row_start), cvPoint(col_start, row_end), cvScalar(255, 0, 0), 1, 8, 0);
	line(img2, Point(col_start, row_start), Point(col_start, row_end), Scalar(255, 0, 0), 1, 8, 0);


	flag = false;
	for (i = img1.cols - 10; i>col_start; i--)           //找到右边界 从最右10像素开始 一列一列扫描
	{
		count = 0;
		for (j = row_start; j<row_end; j++)
		{
			if (img1.at<uchar>(j, i) == 255)
				count++;
			if (count>T1)					//出现大量边界白色信息
			{
				col_end = i;
				flag = true;
				break;
			}
		}
		if (flag) break;
	}
	//	cout << "the end col:" << col_end << endl;
	//printf("the end col:%d\r\n", col_end);
	//cvLine(pImg8u, cvPoint(col_end, row_start), cvPoint(col_end, row_end), cvScalar(255, 0, 0), 1, 8, 0);
	line(img2, Point(col_end, row_start), Point(col_end, row_end), Scalar(255, 0, 0), 1, 8, 0);

	imshow("检测有效信息区域", img2);

	Mat img_ROI = img2(Rect(Point(col_start, row_start), Point(col_end, row_end)));

	imshow("截取有效区域", img_ROI);

	int nWidth = 409;//(409,90)分别为感兴趣图像的宽度与高度
	int nHeight = 90;
	Mat img_Resize;
	resize(img_ROI, img_Resize, Size(409, 90));

	//printf("%d,%d\r\n", img_ROI.rows, img_ROI.cols);
	//printf("%d,%d\r\n", img_Resize.rows, img_Resize.cols);



	int nCharWidth = 45;
	int nSpace = 12;
	for (i = 0; i<7; i++)           //得到每个字符的双边界
	{
		switch (i){
		case 0:
		case 1:
			col[i * 2] = i*nCharWidth + i*nSpace;
			col[i * 2 + 1] = (i + 1)*nCharWidth + i*nSpace;
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			col[i * 2] = i*nCharWidth + i*nSpace + 22;
			col[i * 2 + 1] = (i + 1)*nCharWidth + i*nSpace + 22;
			break;
		}

	}
	for (i = 0; i<14; i++)        //画出每个字符的区域
	{
		line(img_Resize, Point(col[i], 0), Point(col[i], nHeight), Scalar(0, 0, 0), 1, 8, 0);
		//cout<<col[i*2]<<" "<<col[2*i+1]<<" ";
	}

	imshow("字符分割", img_Resize);

	//
	Mat img_ROI1 = img_Resize(Rect(Point(col[0], 0), Point(col[1], img_Resize.rows)));
	//	imshow("1", img_ROI1);
	Mat img_ROI2 = img_Resize(Rect(Point(col[2], 0), Point(col[3], img_Resize.rows)));
	//	imshow("2", img_ROI2);
	Mat img_ROI3 = img_Resize(Rect(Point(col[4], 0), Point(col[5], img_Resize.rows)));
	//	imshow("3", img_ROI3);
	Mat img_ROI4 = img_Resize(Rect(Point(col[6], 0), Point(col[7], img_Resize.rows)));
	//	imshow("4", img_ROI4);
	Mat img_ROI5 = img_Resize(Rect(Point(col[8], 0), Point(col[9], img_Resize.rows)));
	//	imshow("5", img_ROI5);
	Mat img_ROI6 = img_Resize(Rect(Point(col[10], 0), Point(col[11], img_Resize.rows)));
	//	imshow("6", img_ROI6);
	Mat img_ROI7 = img_Resize(Rect(Point(col[12], 0), Point(col[13], img_Resize.rows)));
	vector<Mat> ROI =
	{
		img_ROI1,
		img_ROI2,
		img_ROI3,
		img_ROI4,
		img_ROI5,
		img_ROI6,
		img_ROI7,
	};

	//块依次写入test文件夹
	char name[30];
	for (int i = 0; i < 7; i++)
	{
		sprintf(name,".//test//img_ROI%d.jpg",i);
		string str = name;
		imwrite(str, ROI[i]);
	}

	return ROI;
}

/**********************************************************************/
//统计指定区域中灰度所占比较返回double
//输入；图像，区域，
//返回：灰度所占比例
/**********************************************************************/
double proCale(Mat& mat1, int width_1, int height_1, int width_2, int height_2)
{
	int number = 0, sum = 0;
	int s;
	double result;
	int i, j;

	for (i = width_1; i <= width_2; i++){
		for (j = height_1; j <= height_2; j++){
			s = mat1.at<uchar>(i, j);
			if (s > 100){
				number += 1;
			}
			sum += 1;
		}
	}
	result = (double)number / (double)sum;

	return result;
}
/**********************************************************************/
//字符识别 每个字符切分成9宫格，分别统计各块灰度所占比例与模版比对，找到
//最接近的值返回索引值
//输入；字符图像，类型（汉字CHI，数字NUM，字母LET）
//返回：该字符最接近的索引值
/**********************************************************************/
int getPro(Mat& mat1, int type)
{
	Mat mat2;
	int i, j, k;
	int hArr[4] = { 0, 19, 39, 59 };
	int wArr[4] = { 0, 29, 69, 119 };
	int wArrWidth = 3, wArrHeight = 3, sum;
	double tmp, tmp1, tmp2, all = 0;
	double *allPro;
	int start, end;

	switch (type)
	{
	case NUM:
		start = 0;
		end = 9;
		break;
	case LET:
		start = 10;
		end = 33;
		break;
	case CHI:
		start = 34;
		end = match_detect - 1;
		break;
	}

	allPro = (double*)malloc(match_detect* sizeof(double));
	for (k = start; k <= end; k++)
	{
		all = 0;
		mat2 = imread(match_pic[k], 0);
		resize(mat2, mat2, Size(60, 120));
		for (i = 0; i< wArrWidth; i++)
		{
			for (j = 0; j< wArrHeight; j++)
			{
				tmp1 = proCale(mat1, wArr[i], hArr[j], wArr[i + 1], hArr[j + 1]);
				tmp2 = proCale(mat2, wArr[i], hArr[j], wArr[i + 1], hArr[j + 1]);
				tmp = tmp1 - tmp2;
				if (tmp < 0)
				{
					tmp = -tmp;
				}
				all += tmp;
			}
		}
		allPro[k] = all;
	}

	tmp = allPro[start];
	sum = start;
	for (i = start; i <= end; i++)
	{
		//        printf("allPro[%d]:%lf\n", i, allPro[i]);  
		if (tmp > allPro[i]){
			tmp = allPro[i];
			sum = i;
		}
	}
	//  printf("sum:%d, %lf\n\n\n\n", sum, allPro[sum]);  
	return sum;
}


