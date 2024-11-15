#include<iostream>
#include<vector>
#include<string>
using namespace std;
/*
对象使用过程中背后调用了哪些方法
*/
#if 0
class Test {
public:
	//写了这个构造函数 相当于写了3个：
	//(1)全部默认值 Test() (2)传给ma Test(10) (3)传给ma, mb Test(10, 10)
	Test(int a = 5)
		:ma(a) {
		cout << "Test(int, int)" << endl;
	}

	~Test() { cout << "~Test()" << endl; }

	//拷贝构造
	Test(const Test& t) : ma(t.ma) { cout << "Test(const Test& t)" << endl; }

	//赋值运算符重载
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
	//两者都是拷贝构造函数
	Test t2(t1);
	Test t3 = t1;
	//等价于 Test t4(20);
	//C++对于对象构造的优化：用临时对象生成新对象的时候，临时对象不产生了，直接构造新对象(省略了临时对象的构造和赋值过程)
	Test t4 = Test(20); //Test(20)显式生成临时对象 临时对象的生存周期：所在的语句
	cout << "-----------------------------" << endl;

	t4 = t2;
	//此处要生成临时对象 t4.operator=(const Test& t) 这里是赋值操作 要先产生一个临时对象 除了语句临时对象析构
	//以下3条语句等价：
	t4 = Test(30); //显式生成临时对象
	t4 = (Test)30; //int->Test(int) 显式生成临时对象
	t4 = 30;  //int->Test(int) 隐式生成临时对象
	cout << "-----------------------------" << endl;


	Test* p = &Test(40); //p指向的是一个临时对象 用指针指向对象 出了语句对象就析构了 p变为野指针
	p->getMember();
	p->getMember();
	const Test& ref = Test(50); //显式生成临时对象 用引用指向临时对象 出了语句不会析构 因为引用变量是对那块内存起了别名 相当于给临时对象起了别名
	cout << "-----------------------------" << endl;

	return 0;
}
#endif


class Test {
public:
	//写了这个构造函数 相当于写了3个：
	//(1)全部默认值 Test() (2)传给ma Test(10) (3)传给ma, mb Test(10, 10)
	Test(int a = 5, int b = 5)
		:ma(a), mb(b) {
		cout << "Test(int, int)" << endl;
	}

	~Test() { cout << "~Test()" << endl; }

	//拷贝构造
	Test(const Test& t) : ma(t.ma), mb(t.mb) { cout << "Test(const Test& t)" << endl; }

	//赋值运算符重载
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


//构造顺序 t1->t2->t3->t4->p1->p2->p3->p4
//析构顺序 p1->p2->p4->t3->t2->t4->t5->t1(p3当时就析构了)
Test t1(20, 20); //1.Test(int, int)程序运行时 全局变量先构造 在main函数前初始化
int main() {
	Test t2(20, 20); //3.Test(int, int) 第五个析构
	Test t3 = t2; //4.Test(const Test& t) 第四个析构
	static Test t4 = Test(30, 30); //5.相当于 static Test t4(30, 30) t4在数据段 程序结束才析构
	t2 = Test(40, 40); //6.(1)先调用Test(int, int)生成临时对象 (2)然后再调用operator=赋值函数 (3)出语句析构临时对象
	t2.getMember();
	t2 = (Test)(50, 50); //7.,逗号表达式,保留最后一个表达式 (50, 50) = 50 相当于 t2 = Test(50) (1)Test(int, int) (2)operator= (3)析构临时对象
	t2.getMember();
	t2 = 60; //8.隐式生成临时对象 (1)Test(int, int) (2)operator=()将60传给ma (3)析构临时对象
	Test* p1 = new Test(70, 70); //9.(1)Test(int, int)构造(70,70),出了语句不析构 因为这个对象不是临时对象 是在堆上(只有delete才释放)new出来的
	Test* p2 = new Test[2]; //10.调用两次Test(int, int) new先调用对象构造函数 再开辟内存 
	Test* p3 = &Test(80, 80);//11.切记不能使用指针指向临时对象 (1)Test(int, int) (2)析构临时对象
	const Test& p4 = Test(90, 90); //12.可以使用引用变量指向临时对象 不会被析构 Test(int, int) 第三个析构
	delete p1; //13.delete先调用对象析构函数 再释放内存 ~Test() 第一个析构
	delete[] p2; //14.(1)~Test() ~Test()调用2次析构函数析构数组中的对象  (2)使用free释放数组内存 第二个析构
	return 0;
}
Test t5(100, 100); //2.全局变量 Test(int, int)