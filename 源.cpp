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

//ģ���ַ����
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

//ģ������
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

	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"³",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"ԥ",
	"��",
	"��",
	"��",
};


int result[7];	//����ʶ������
int type[7] =	//���ƣ���Ӣ�����ָ�ʽ
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
		imshow("ԭͼ���Ҷȣ�",img_gray);

	//ͼ���˲�
	GaussianBlur(img_gray, img_gray, Size(3, 3), 0, 0);
	imshow("��˹�˲�", img_gray);

	//��Ե���
	Canny(img_gray, img_edge, 100, 200);
	imshow("��Ե���", img_edge);

//	printf("%d,%d", img_gray.cols, img_gray.rows);


	//ִ��ͼ��ָ�ָ��Ŀ鱣����vector<Mat> ROI��
	vector<Mat> ROI = Img_segmentation(img_edge,img_gray);

	//�����ַ�ƥ��
	for (int i = 0; i < 7; i++)
	{
		Mat img = ROI[i];	//��vector<Mat> ROI�ж�ȡ�ָ��Ŀ�
		resize(img, img, Size(60, 120));  //������ģ��ͬ����С
		threshold(img, img, 0, 255, CV_THRESH_BINARY + CV_THRESH_OTSU); //�Զ���ֵ��������ģ���Ӧ
		result[i] = getPro(img, type[i]); //��������ţ����浽result����
	}
	//ͨ��result�����б����������Ӧname������������ַ���
	printf("����ʶ�����ǣ�");
	for (int i = 0; i < 7; i++)
	{
		printf("%s", name[result[i]].c_str());
	}

	waitKey(0);

}
/**********************************************************************/
//���ƷָѰ�ұ߽磬���ŵ�ָ����С409*90 �ȱ����и� �õ�7��ROI����
//���룻�Ҷ�ͼ����Եͼ
//���أ�7���и���ɵ�ROI��
/**********************************************************************/
vector<Mat>  Img_segmentation(Mat& img1,Mat&img2)
{
	#define T 27
	#define T1 2
	int i, j;
	int row_start, row_end;//������¼���ƿ�ʼ��������
	int col_start, col_end;//������¼���ƿ�ʼ��������
	int count = 0;//������¼�л��еİ׵����

	row_start = 0;
	row_end = 0;
	col_start = 0;
	col_end = 0;
	int row[320]; //120
	int col[600]; //340
	int k;
	k = 0;
	bool flag = false;

	for (j = 0; j <img1.rows; j++)												//�ҵ����п�ʼ һ��һ��ɨ��
	{
		count = 0;
		for (i = 0; i <img1.cols - 1; i++)
		{
			if (img1.at<uchar>(j, i) != img1.at<uchar>(j, i + 1))				//ͳ�����������������Ч���������������Ƚϴ�
				count++;
			if (count>T)
			{
				row[k] = j;
				k++;
				break;
			}
		}
	}

	for (i = 0; i<k; i++)														//���ϱ߿�ʼ��3�������ж��������Ϊ����ʼ��
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


	for (i = k - 1; i>row_start; i--)     //���±߿�ʼ��3�������ж��������Ϊ����ʼ��
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
	for (i = 10; i<img1.cols; i++)											//�ҵ���߽� ������10���ؿ�ʼ һ��һ��ɨ��
	{
		count = 0;
		for (j = row_start; j<row_end; j++)
		{
			if (img1.at<uchar>(j, i) == 255)	
				count++;
			if (count>T1)													//���ִ����߽��ɫ��Ϣ
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
	for (i = img1.cols - 10; i>col_start; i--)           //�ҵ��ұ߽� ������10���ؿ�ʼ һ��һ��ɨ��
	{
		count = 0;
		for (j = row_start; j<row_end; j++)
		{
			if (img1.at<uchar>(j, i) == 255)
				count++;
			if (count>T1)					//���ִ����߽��ɫ��Ϣ
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

	imshow("�����Ч��Ϣ����", img2);

	Mat img_ROI = img2(Rect(Point(col_start, row_start), Point(col_end, row_end)));

	imshow("��ȡ��Ч����", img_ROI);

	int nWidth = 409;//(409,90)�ֱ�Ϊ����Ȥͼ��Ŀ����߶�
	int nHeight = 90;
	Mat img_Resize;
	resize(img_ROI, img_Resize, Size(409, 90));

	//printf("%d,%d\r\n", img_ROI.rows, img_ROI.cols);
	//printf("%d,%d\r\n", img_Resize.rows, img_Resize.cols);



	int nCharWidth = 45;
	int nSpace = 12;
	for (i = 0; i<7; i++)           //�õ�ÿ���ַ���˫�߽�
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
	for (i = 0; i<14; i++)        //����ÿ���ַ�������
	{
		line(img_Resize, Point(col[i], 0), Point(col[i], nHeight), Scalar(0, 0, 0), 1, 8, 0);
		//cout<<col[i*2]<<" "<<col[2*i+1]<<" ";
	}

	imshow("�ַ��ָ�", img_Resize);

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

	//������д��test�ļ���
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
//ͳ��ָ�������лҶ���ռ�ȽϷ���double
//���룻ͼ������
//���أ��Ҷ���ռ����
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
//�ַ�ʶ�� ÿ���ַ��зֳ�9���񣬷ֱ�ͳ�Ƹ���Ҷ���ռ������ģ��ȶԣ��ҵ�
//��ӽ���ֵ��������ֵ
//���룻�ַ�ͼ�����ͣ�����CHI������NUM����ĸLET��
//���أ����ַ���ӽ�������ֵ
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


