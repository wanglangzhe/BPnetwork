#pragma once

#ifndef WMZBP14348121
#define WMZBP14348121

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

namespace bp {
#define SQR(x) ((x)*(x))
#define ABS(x) ((x)<0?(-(x)):(x)) 

#define Type float
#define Layer 5
#define Num 1000

#define A        1  
#define B        1			//A和B是S型函数的参数  
#define ETA_W    0.005		//权值调整率  
#define ETA_B    0.005					//阈值调整率  
#define ITERS 150						//最大训练次数
#define ACCESS_ERROR 0.02 * 2				//单个样本允许的误差
#define ACCESS_ACCU     0.005 * 2			//每次迭代允许的误差  


/*
#define A        5  
#define B        5 				//A和B是S型函数的参数  
#define ETA_W    0.0035*2					//权值调整率  
#define ETA_B    0.001*2					//阈值调整率  
#define ITERS 1000						//最大训练次数
#define ACCESS_ERROR 0.02				//单个样本允许的误差
#define ACCESS_ACCU     0.005			//每次迭代允许的误差  
*/

	struct Data {
		void clear() {
			input.clear(); output.clear();
		}
		std::vector <Type> input, output;
	};

	class bp {
		
	public:
		//bp();
		~bp();
		void getData(const std::vector<Data > &);
		void train();
		void tranInit();
		void tranAgroup(int cnt, float rate = 1.0);
		bool tranAset(float rate = 1.0);
		std::vector<Type> foreCast(const std::vector<Type> &);


		Type getW(int k, int i, int j) const;
		Type getB(int k, int i) const;
		int getLayer() const;
		int getInNum() const;
		int getHdNum() const;
		int getOuNum() const;
		int nodeOfLay(int k) const;
		bool store() const;
		bool load() ;

	private:
		void initNetwork();
		void getNums();
		void forwardTrans();
		void reverseTrans(int cnt, float rate = 1.0);
		void calcDelta(int cnt);
		void updateNetwork(float rate = 1.0);
		Type getError(int cnt);
		Type getAccu();
		Type sigmoid(const Type &);
	private:
		int inNum, ouNum, hdNum, layer;

		std::vector<Data> data;
		Type w[10][Num][Num];
		Type b[10][Num];
			   
		Type x[10][Num];
		Type d[10][Num];
		
	};


	void checkAns(const std::vector<Type> &ans);

	std::string numToString(int num);

	void washData(const char *str, std::vector<Data> &v);

	void testData(const char *str, bp *p);

	int testAdata(const char *str, bp *p);
};

#endif

/*
1.使用模板类导致error LNK2019: 无法解析的外部符号  http://blog.csdn.net/luofeixiongsix/article/details/50619751、http://www.cnblogs.com/onlycxue/archive/2012/12/22/2828863.html
												   https://www.zhihu.com/question/20630104
2.CPaintDC、CClientDC、CWindowDC和CMetaFileDC类的主要特点及区别	 http://blog.sina.com.cn/s/blog_5d97bfa40100w5cf.html

*/


