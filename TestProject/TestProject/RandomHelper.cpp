#include "RandomHelper.h"
#include <assert.h>

RandomHelper::RandomHelper()
{

}

RandomHelper::~RandomHelper()
{

}

void RandomHelper::threeCarTest()
{
	auto fangZhiJiangPing = [](vector<int> &v1)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, v1.size() - 1);
		int index = dis(gen);
		assert(index>=0 || index<= v1.size() -1, "1231231");
		v1[index] = 1;
		cout<<"已经放置奖品"<<endl;
	};
	auto chouJiang_buhuan = [](const vector<int> &v1)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, v1.size() - 1);
		if (v1[dis(gen)] == 1)
		{
			//cout<<"中奖"<<endl;
			return true;
		}
		else
			return false;
	};
	vector<int> cars(3, 0);
	const int ciShu = 10000;
	cout<<cars.size()<<endl;
	fangZhiJiangPing(cars);
	int zhongjiang = 0;
	for (int i = 0; i < ciShu; i++)
	{
		if (chouJiang_buhuan(cars))
		{
			++zhongjiang;
		}
	}
	cout<<"---------------结果----------------"<<endl;
	float baifengbi = (float)zhongjiang/(float)ciShu;
	char dest[10];
	sprintf(dest, "%0.2f%%", baifengbi*100);
	cout<<"中奖率为"<<dest<<endl;
}