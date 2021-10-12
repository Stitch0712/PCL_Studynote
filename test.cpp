#include<pcl/point_cloud.h>				//点定义头文件
#include<pcl/kdtree/kdtree_flann.h>		//kdtree头文件

#include<iostream>
#include<ctime>
#include<vector>

using namespace std;

int main(int argc,char** argv) {
	srand(time(NULL));					//利用系统时间生产随机种子
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);		//实例化一个点云pointer
	//设定点云
	cloud->width = 1000;				//设定点云数量
	cloud->height = 1;					//设定为无序点云
	cloud->points.resize(cloud->width*cloud->height);
	//生成随机点
	for (size_t i = 0; i < cloud->points.size(); i++)
	{
		cloud->points[i].x = 1024.0f * rand() / (RAND_MAX + 1.0f);
		cloud->points[i].y = 1024.0f * rand() / (RAND_MAX + 1.0f);
		cloud->points[i].z = 1024.0f * rand() / (RAND_MAX + 1.0f);
	}

	//创建KdTreeFLANN对象，并把创建的点云设置为输入,创建一个searchPoint变量作为查询点
	pcl::KdTreeFLANN<pcl::PointXYZ> KDtree;
	KDtree.setInputCloud(cloud);
	pcl::PointXYZ searchPoint;
	searchPoint.x = 1024.0f * rand() / (RAND_MAX + 1.0f);
	searchPoint.y = 1024.0f * rand() / (RAND_MAX + 1.0f);
	searchPoint.z = 1024.0f * rand() / (RAND_MAX + 1.0f);

	//创建一个整数（设置为10）和两个向量来存储搜索到的K近邻，两个向量中，一个存储搜索到查询点近邻的索引，另一个存储对应近邻的距离平方
	int K = 10;
	vector<int> pointIdxNKNSearch(K);
	vector<float> pointNKNSquaredDistance(K);

	std::cout << "K nearest neighbor search at (" << searchPoint.x
		<< " " << searchPoint.y
		<< " " << searchPoint.z
		<< ") with K=" << K << std::endl;

	//K领域搜索
	int size = KDtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance);
	std::cout << "search points :" << size << std::endl;
	if (size > 0 )
	{
		for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i)
			std::cout << "    " << cloud->points[pointIdxNKNSearch[i]].x
			<< " " << cloud->points[pointIdxNKNSearch[i]].y
			<< " " << cloud->points[pointIdxNKNSearch[i]].z
			<< " (squared distance: " << pointNKNSquaredDistance[i] << ")" << std::endl;
	}
	system("pause");
	return 0;
}