#include <fstream>
using namespace std;
#pragma once
class Node
{
public:
	double x;// ���������� �
	double y;// ���������� �
	double angle;// ����
	double energy;// ������� � ����


	Node();
	Node(double x,double y,double angle);
	
	bool operator < (Node node);
	bool operator == (Node node);
	void operator = (Node node);
	//void write(ofstream& of);
	void output(ofstream& of);
	//void read(ifstream& in);
	void input(ifstream& in);
	~Node(void);
};

