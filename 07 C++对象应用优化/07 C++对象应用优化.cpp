#include<iostream>
#include<vector>
#include<string>
using namespace std;
/*
����ʹ�ù����б����������Щ����
*/
#if 0
class Test {
public:
	//д��������캯�� �൱��д��3����
	//(1)ȫ��Ĭ��ֵ Test() (2)����ma Test(10) (3)����ma, mb Test(10, 10)
	Test(int a = 5)
		:ma(a) {
		cout << "Test(int, int)" << endl;
	}

	~Test() { cout << "~Test()" << endl; }

	//��������
	Test(const Test& t) : ma(t.ma) { cout << "Test(const Test& t)" << endl; }

	//��ֵ���������
	void operator=(const Test& t) {
		cout << "operator=" << endl;
		ma = t.ma;
	}

	void getMember() {
		cout << "ma = " << ma << endl;
	}

private:
	int ma;
};

int main() {
	Test t1;
	//���߶��ǿ������캯��
	Test t2(t1);
	Test t3 = t1;
	//�ȼ��� Test t4(20);
	//C++���ڶ�������Ż�������ʱ���������¶����ʱ����ʱ���󲻲����ˣ�ֱ�ӹ����¶���(ʡ������ʱ����Ĺ���͸�ֵ����)
	Test t4 = Test(20); //Test(20)��ʽ������ʱ���� ��ʱ������������ڣ����ڵ����
	cout << "-----------------------------" << endl;

	t4 = t2;
	//�˴�Ҫ������ʱ���� t4.operator=(const Test& t) �����Ǹ�ֵ���� Ҫ�Ȳ���һ����ʱ���� ���������ʱ��������
	//����3�����ȼۣ�
	t4 = Test(30); //��ʽ������ʱ����
	t4 = (Test)30; //int->Test(int) ��ʽ������ʱ����
	t4 = 30;  //int->Test(int) ��ʽ������ʱ����
	cout << "-----------------------------" << endl;


	Test* p = &Test(40); //pָ�����һ����ʱ���� ��ָ��ָ����� ����������������� p��ΪҰָ��
	p->getMember();
	p->getMember();
	const Test& ref = Test(50); //��ʽ������ʱ���� ������ָ����ʱ���� ������䲻������ ��Ϊ���ñ����Ƕ��ǿ��ڴ����˱��� �൱�ڸ���ʱ�������˱���
	cout << "-----------------------------" << endl;

	return 0;
}
#endif


class Test {
public:
	//д��������캯�� �൱��д��3����
	//(1)ȫ��Ĭ��ֵ Test() (2)����ma Test(10) (3)����ma, mb Test(10, 10)
	Test(int a = 5, int b = 5)
		:ma(a), mb(b) {
		cout << "Test(int, int)" << endl;
	}

	~Test() { cout << "~Test()" << endl; }

	//��������
	Test(const Test& t) : ma(t.ma), mb(t.mb) { cout << "Test(const Test& t)" << endl; }

	//��ֵ���������
	void operator=(const Test& t) {
		cout << "operator=" << endl;
		ma = t.ma;
		mb = t.mb;
	}

	void getMember() {
		cout << "ma = " << ma << ", mb = " << mb << endl;
	}

private:
	int ma;
	int mb;
};


//����˳�� t1->t2->t3->t4->p1->p2->p3->p4
//����˳�� p1->p2->p4->t3->t2->t4->t5->t1(p3��ʱ��������)
Test t1(20, 20); //1.Test(int, int)��������ʱ ȫ�ֱ����ȹ��� ��main����ǰ��ʼ��
int main() {
	Test t2(20, 20); //3.Test(int, int) ���������
	Test t3 = t2; //4.Test(const Test& t) ���ĸ�����
	static Test t4 = Test(30, 30); //5.�൱�� static Test t4(30, 30) t4�����ݶ� �������������
	t2 = Test(40, 40); //6.(1)�ȵ���Test(int, int)������ʱ���� (2)Ȼ���ٵ���operator=��ֵ���� (3)�����������ʱ����
	t2.getMember();
	t2 = (Test)(50, 50); //7.,���ű��ʽ,�������һ�����ʽ (50, 50) = 50 �൱�� t2 = Test(50) (1)Test(int, int) (2)operator= (3)������ʱ����
	t2.getMember();
	t2 = 60; //8.��ʽ������ʱ���� (1)Test(int, int) (2)operator=()��60����ma (3)������ʱ����
	Test* p1 = new Test(70, 70); //9.(1)Test(int, int)����(70,70),������䲻���� ��Ϊ�����������ʱ���� ���ڶ���(ֻ��delete���ͷ�)new������
	Test* p2 = new Test[2]; //10.��������Test(int, int) new�ȵ��ö����캯�� �ٿ����ڴ� 
	Test* p3 = &Test(80, 80);//11.�мǲ���ʹ��ָ��ָ����ʱ���� (1)Test(int, int) (2)������ʱ����
	const Test& p4 = Test(90, 90); //12.����ʹ�����ñ���ָ����ʱ���� ���ᱻ���� Test(int, int) ����������
	delete p1; //13.delete�ȵ��ö����������� ���ͷ��ڴ� ~Test() ��һ������
	delete[] p2; //14.(1)~Test() ~Test()����2�������������������еĶ���  (2)ʹ��free�ͷ������ڴ� �ڶ�������
	return 0;
}
Test t5(100, 100); //2.ȫ�ֱ��� Test(int, int)