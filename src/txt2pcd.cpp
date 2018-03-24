#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
using namespace std;


typedef struct tagPOINT_3D
{
	double x;  //mm world coordinate x
	double y;  //mm world coordinate y
	double z;  //mm world coordinate z
	int r;
  int g;
  int b;

}POINT_WORLD;


struct lin
{
    double a[6];
};

int main()
{
/////加载txt数据
	int number_Txt;
	FILE *fp_txt;
	tagPOINT_3D TxtPoint;
	vector<tagPOINT_3D> m_vTxtPoints;
	fp_txt = fopen("test_data.txt", "r");

	if (fp_txt)
	{
		while (fscanf(fp_txt, "%lf %lf %lf %d %d %d", &TxtPoint.x, &TxtPoint.y, &TxtPoint.z, &TxtPoint.r, &TxtPoint.g, &TxtPoint.b) != EOF)
		{
			m_vTxtPoints.push_back(TxtPoint);
		}
	}
	else
		cout << "txt数据加载失败！" << endl;
	number_Txt = m_vTxtPoints.size();
	pcl::PointCloud<pcl::PointXYZRGB> cloud;


	// Fill in the cloud data
	cloud.width = number_Txt;
	cloud.height = 1;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);


	for (size_t i = 0; i < cloud.points.size(); ++i)
	{
		cloud.points[i].x = m_vTxtPoints[i].x;
		cloud.points[i].y = m_vTxtPoints[i].y;
		cloud.points[i].z = m_vTxtPoints[i].z;
    cloud.points[i].r = m_vTxtPoints[i].r;
    cloud.points[i].g = m_vTxtPoints[i].g;
    cloud.points[i].b = m_vTxtPoints[i].b;

	}
	pcl::io::savePCDFileASCII("test.pcd", cloud);
	std::cerr << "Saved " << cloud.points.size() << " data points to txt2pcd.pcd." << std::endl;


	for (size_t i = 0; i < cloud.points.size(); ++i)
		std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;


	system("pause");
	return 0;
}
