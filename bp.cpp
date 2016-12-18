#include "stdafx.h"
#include "bp.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>

namespace bp {

	using std::cin;
	using std::cout;
	using std::endl;
	/*
	template <typename Type, int layer, int Num>
	bp::bp() {
		data.clear();
	}
	*/

	std::string numToString(int num) {
		if (num < 0) {
			std::cerr << "error in numToString" << std::endl;
			return "";
		}
		std::string res = "";
		do {
			res += (num % 10 + '0');
			num /= 10;
		} while (num);

		reverse(res.begin(), res.end());
		return res;
	}

	void washData(const char *str, std::vector<Data> &v) {
		std::string path(str);
		std::ifstream ifs;
		v.clear();
		int now, t;
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; 1 && j < 40; ++j) {
				ifs.open((path + numToString(i) + "_" + numToString(j) + ".txt").c_str());
				std::cout << path + numToString(i) + "_" + numToString(j) + ".txt" << std::endl;
				if (!ifs.is_open()) break;
				int now = v.size(); v.push_back(Data());
				for (int x = 0; x < 10; ++x) {
					v[now].output.push_back(x == i);
				}
				for (int x = 0; x < 32; ++x) {              //可以考虑压缩向量？
					for (int y = 0; y < 32; ++y) {
						char t;
						do {
							ifs >> t;
						} while (t < 32);
						v[now].input.push_back(t - '0');
					}
				}
				ifs.close();
			}
		}
		for (int i = 0; i < v[0].input.size(); ++i) {
			if (i % 32 == 0) cout << endl;
			cout << v[0].input[i];
		} cout << endl;
	}

	void testData(const char *str, bp *p) {
		int sumTest = 0, correct = 0;
		std::string path(str);
		std::ifstream ifs;

		std::vector<Type> myans;
		Data ans;

		int t;
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; 1; ++j) {
				ifs.open((path + numToString(i) + "_" + numToString(j) + ".txt").c_str());
				std::cout << path + numToString(i) + "_" + numToString(j) + ".txt" << std::endl;
				if (!ifs.is_open()) break;
				//std::vector<Type> foreCast(const std::vector<Type> &)
				ans.clear();
				
				for (int x = 0; x < 32; ++x) {
					for (int y = 0; y < 32; ++y) {
						char t;
						do {
							ifs >> t;
						} while (t < 32);
						ans.input.push_back(t - '0');
					}
				}
				myans = p->foreCast(ans.input);

				double maxx = myans[0], t = 0;
				for (int i = 1; i < 10; ++i) if (myans[i] > maxx) {
					maxx = myans[i]; t = i;
				}

				++sumTest;
				if (t == i) ++correct;

				ifs.close();
			}
		}
		cout << "correct rate: " << correct << " / " << sumTest << "     ::      " << 1.0 * correct / sumTest << endl;
	}

	int testAdata(const char * str, bp * p)
	{
		std::string path(str);
		std::ifstream ifs;

		std::vector<Type> myans;
		Data ans;

		
		ifs.open("col.txt");
		
		if (!ifs.is_open()) ;
		//std::vector<Type> foreCast(const std::vector<Type> &)
		ans.clear();

		for (int x = 0; x < 32; ++x) {
			for (int y = 0; y < 32; ++y) {
				char t;
				do {
					ifs >> t;
				} while (t < 33);
				ans.input.push_back(t - '0');
			}
		}
		myans = p->foreCast(ans.input);

		double maxx = myans[0];
		int t = 0;

		for (int i = 1; i < 10; ++i) if (myans[i] > maxx) {
			maxx = myans[i]; t = i;
		}

		ifs.close();
	
		return t;
	}

	int bp::nodeOfLay(int k) const {
		if (k == 0) return inNum;
		if (k + 1 == layer) return ouNum;
		return hdNum;
	}

	bool bp::store() const {
		std::ofstream os("sv.txt");

		os << inNum << ' ' << hdNum << ' ' << ouNum << ' ' << layer << endl;

		for (int k = 0; k + 1 < layer; ++k) {
			for (int i = 0; i < nodeOfLay(k+1); ++i) os << b[k+1][i] << ' '; os << endl;
			
			for (int i = 0; i < nodeOfLay(k); ++i) {
				for (int j = 0; j < nodeOfLay(k + 1); ++j) os << w[k+1][i][j] << ' '; 
				os << endl;
			}			
		}
		os.close();
		return true;
	}

	bool bp::load()	{
		std::ifstream is("sv.txt");

		is >> inNum >>  hdNum >> ouNum >>  layer;

		for (int k = 0; k + 1 < layer; ++k) {
			for (int i = 0; i < nodeOfLay(k+1); ++i) is >> b[k + 1][i];

			for (int i = 0; i < nodeOfLay(k); ++i) {
				for (int j = 0; j < nodeOfLay(k + 1); ++j) is >> w[k+1][i][j];
			}
		}

		is.close();
		return true;
	}

	float random() {
		return 1.0 * rand() / RAND_MAX;
	}

	void checkAns(const std::vector<Type> &ans) {
		std::vector<Type> u = ans;
		double sum = 0;
		for (int i = 0; i < u.size(); ++i) sum += u[i];
		for (int i = 0; i < u.size(); ++i) {
			u[i] = 100.0 * (u[i] / sum);
			printf("%d: %.5f\n", i, u[i]);
		}
	}

	bp::~bp()	{
		data.clear();
	}

	void bp::getData(const std::vector<Data>& v)	{
		data = v;
	}
	void bp::train() {
		getNums();
		initNetwork();

		std::cout << inNum << ' ' << hdNum << ' ' << ouNum << std::endl;

		size_t num = data.size();

		for (int tim = 0; tim <= ITERS; ++tim) {
			std::cout << tim << std::endl;
			for (size_t cnt = 0; cnt < num; ++cnt) {
				for (int i = 0; i < inNum; ++i)
					x[0][i] = data[cnt].input[i];
				for (;;) {
					forwardTrans();
					double t = getError(cnt);
					if (t < ACCESS_ERROR)
						break;
					reverseTrans(cnt);
				}
			}

			Type accu = getAccu();
			if (accu < ACCESS_ACCU) break;
			
		}
	
	}

	void bp::tranInit()	{
		getNums();
		initNetwork();
	}

	void bp::tranAgroup(int cnt, float rate) {
		for (int i = 0; i < inNum; ++i)
			x[0][i] = data[cnt].input[i];
		for (;;) {
			forwardTrans();
			double t = getError(cnt);
			if (t < ACCESS_ERROR)
				break;
			reverseTrans(cnt, rate);
		}
	}

	bool bp::tranAset(float rate)	{
		size_t num = data.size();

		for (size_t cnt = 0; cnt < num; ++cnt) {
			tranAgroup(cnt, rate);
		}

		Type accu = getAccu();
		if (accu < ACCESS_ACCU) return true;
				
		return false;
	}

	std::vector<Type> bp::foreCast(const std::vector<Type> &data) {
		size_t n = data.size();
		//assert(n == inNum);

		for (size_t i = 0; i < inNum; ++i)
			x[0][i] = data[i];

		forwardTrans();
		std::vector<Type> v;
		for (size_t i = 0; i < ouNum; ++i)
			v.push_back(x[layer - 1][i]);

		return v;
	}

	Type bp::getW(int k, int i, int j) const
	{
		return w[k][i][j];
	}

	Type bp::getB(int k, int i) const
	{
		return b[k][i];
	}

	int bp::getLayer() const
	{
		return layer;
	}

	int bp::getInNum() const
	{
		return inNum;
	}

	int bp::getHdNum() const
	{
		return hdNum;
	}

	int bp::getOuNum() const
	{
		return ouNum;
	}

	void bp::initNetwork() {
		//rand ? 
		//memset(w, 0, sizeof(w));
		//memset(b, 0, sizeof(b));
		srand(time(0));
		for (size_t k = 1; k < layer; ++k) {
			for (int i = 0; i < (k + 1 == layer ? ouNum : hdNum); ++i) b[k][i] = 0.5 - random();
			for (int i = 0; i < (k == 1 ? inNum : hdNum); ++i)
				for (int j = 0; j < (k + 1 == layer ? ouNum : hdNum); ++j)
					w[k][i][j] = 0.5 - random();
		}
	}

	void bp::getNums() {
		layer = input_hdnum == 0 ? Layer : input_hdnum;
		inNum = data[0].input.size();
		ouNum = data[0].output.size();
		hdNum = (int)sqrt(max(inNum + ouNum, 0) * 1.0) + 5;
		if (hdNum > Num) hdNum = Num;
	}

	void bp::forwardTrans()	{
		size_t last = layer - 1;

		for (size_t k = 0; k < last; ++k) {
			for (size_t j = 0; j < (k + 1 == last ? ouNum : hdNum); ++j) {
				Type t = 0;
				for (size_t i = 0; i < (k == 0 ? inNum : hdNum); ++i)
					t += w[k+1][i][j] * x[k][i];
				t += b[k+1][j];
				x[k+1][j] = sigmoid(t);
			}
		}
	}

	void bp::reverseTrans(int cnt, float rate) {
		calcDelta(cnt);
		updateNetwork(rate);
	}

	void bp::calcDelta(int cnt) {
		/*
		//计算输出层的delta值  
		for (int i = 0; i < ouNum; i++)
			d[2][i] = (x[2][i] - data.at(cnt).output[i]) * x[2][i] * (A - x[2][i]) / (A * B);
		//计算隐含层的delta值  
		for (int i = 0; i < hdNum; i++)
		{
			Type t = 0;
			for (int j = 0; j < ouNum; j++)
				t += w[2][i][j] * d[2][j];
			d[1][i] = t * x[1][i] * (A - x[1][i]) / (A * B);
		}
		return ;
		*/


		size_t last = layer - 1;
		//计算输出层的delta值  
		for (size_t i = 0; i < ouNum; ++i)
			d[last][i] = (x[last][i] - data[cnt].output[i]) * x[last][i] * (A - x[last][i]) / (A * B * 1.0);
		//计算隐含层的delta值
		for (size_t k = last - 1; k >= 1; --k) {
			for (size_t i = 0; i < hdNum; ++i) {
				Type t = 0;
				for (size_t j = 0; j < (k == last - 1 ? ouNum : hdNum); ++j)
					t += w[k + 1][i][j] * d[k + 1][j];
				d[k][i] = t * x[k][i] * (A - x[k][i]) / (A * B * 1.0);
			}
		}
	}

	void bp::updateNetwork(float rate) {
		/*
		//隐含层和输出层之间权值和阀值调整  
		for (int i = 0; i < hdNum; i++)
		{
			for (int j = 0; j < ouNum; j++)
				w[2][i][j] -= ETA_W * rate * d[2][j] * x[1][i];
		}
		for (int i = 0; i < ouNum; i++)
			b[2][i] -= ETA_B * rate * d[2][i];

		//输入层和隐含层之间权值和阀值调整  
		for (int i = 0; i < inNum; i++)
		{
			for (int j = 0; j < hdNum; j++)
				w[1][i][j] -= ETA_W * rate * d[1][j] * x[0][i];
		}
		for (int i = 0; i < hdNum; i++)
			b[1][i] -= ETA_B * rate * d[1][i];

		return;
		*/


		size_t last = layer - 1;

		for (size_t k = last; k >= 1; --k) {
			for (size_t i = 0; i < (k == last ? hdNum: inNum); ++i) {
				for (size_t j = 0; j < (k == last ? ouNum: hdNum); ++j)
					w[k][i][j] -= ETA_W * rate * d[k][j] * x[k - 1][i];
			}
			for (size_t i = 0; i < (k == last ? ouNum: hdNum); ++i)
				b[k][i] -= ETA_B  * rate * d[k][i];
		}
	}

	Type bp::getError(int cnt) {
		size_t last = layer - 1;
		double ans = 0;
		for (size_t i = 0; i < ouNum; ++i) 
			ans += 0.5 * SQR(x[last][i] - data[cnt].output[i]);
		return ans;
	}

	Type bp::getAccu() {
		size_t last = layer - 1;
		double ans = 0;

		size_t num = data.size();
		for (size_t i = 0; i < num; ++i) {
			int m = data[i].input.size();
			for (size_t j = 0; j < m; ++j)
				x[0][j] = data[i].input[j];
			forwardTrans();
			int n = data[i].output.size();
			for (size_t j = 0; j < n; ++j)
				ans += 0.5 * SQR(x[last][j] - data[i].output[j]);
		}
		return ans;		
	}

	Type bp::sigmoid(const Type &x)
	{
		return A / (1 + exp(-x / B));
	}

	void bp::set_hdnum(int x)
	{
		input_hdnum = x;
	}

};

