#include<pcl/point_cloud.h>				//�㶨��ͷ�ļ�
#include<pcl/kdtree/kdtree_flann.h>		//kdtreeͷ�ļ�

#include<iostream>
#include<ctime>
#include<vector>

using namespace std;

int main(int argc,char** argv) {
	srand(time(NULL));					//����ϵͳʱ�������������
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);		//ʵ����һ������pointer
	//�趨����
	cloud->width = 1000;				//�趨��������
	cloud->height = 1;					//�趨Ϊ�������
	cloud->points.resize(cloud->width*cloud->height);
	//���������
	for (size_t i = 0; i < cloud->points.size(); i++)
	{
		cloud->points[i].x = 1024.0f * rand() / (RAND_MAX + 1.0f);
		cloud->points[i].y = 1024.0f * rand() / (RAND_MAX + 1.0f);
		cloud->points[i].z = 1024.0f * rand() / (RAND_MAX + 1.0f);
	}

	//����KdTreeFLANN���󣬲��Ѵ����ĵ�������Ϊ����,����һ��searchPoint������Ϊ��ѯ��
	pcl::KdTreeFLANN<pcl::PointXYZ> KDtree;
	KDtree.setInputCloud(cloud);
	pcl::PointXYZ searchPoint;
	searchPoint.x = 1024.0f * rand() / (RAND_MAX + 1.0f);
	searchPoint.y = 1024.0f * rand() / (RAND_MAX + 1.0f);
	searchPoint.z = 1024.0f * rand() / (RAND_MAX + 1.0f);

	//����һ������������Ϊ10���������������洢��������K���ڣ����������У�һ���洢��������ѯ����ڵ���������һ���洢��Ӧ���ڵľ���ƽ��
	int K = 10;
	vector<int> pointIdxNKNSearch(K);
	vector<float> pointNKNSquaredDistance(K);

	std::cout << "K nearest neighbor search at (" << searchPoint.x
		<< " " << searchPoint.y
		<< " " << searchPoint.z
		<< ") with K=" << K << std::endl;

	//K��������
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