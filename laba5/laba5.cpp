

#include <iostream>
#include <string>
#include <memory>
using namespace std;
class Light {
public:
	Light() { cout << "Light constructor\n"; }
	virtual ~Light() { cout << "Light destructor\n"; }

	virtual bool isA(string name) { return "Light" == name; }
	virtual string className() { return "Light"; }
	virtual void switchOn() { cout << "the Light is on\n"; }
	void switchOff() { cout << "the Light is off\n"; }
};

class Sun : public Light {
public:
	Sun() { cout << "Sun constructor\n"; }
	~Sun() { cout << "Sun destructor\n"; }

	bool isA(string name) { return ("Sun" == name || Light::isA(name)); }
	string className() { return "Sun"; }
	void switchOn() { cout << "the Sun is on\n"; }
	//void switchOff() { cout << "the Sun is off\n"; }
	void toRaise() { cout << "the Sun is rising\n"; }
};

class Lamp : public Light {
public:
	Lamp() { cout << "Lamp constructor\n"; }
	~Lamp() { cout << "Lamp destructor\n"; }

	bool isA(string name) { return ("Lamp" == name || Light::isA(name)); }
	string className() { return "Lamp"; }
	void switchOn() { cout << "the Lamp is on\n"; }
	 void switchOff() { cout << "the Lamp is off\n"; }
	void changePower() { cout << "the power is changed\n"; }
};

class Match : public Lamp {
public:
	Match() { cout << "Match constructor\n"; }
	~Match() { cout << "Match destructor\n"; }

	bool isA(string name) { return ("Match" == name || Lamp::isA(name)); }
	string className() { return "Match"; }
	void switchOn() { cout << "the Match is on\n"; }
	void switchOff() { cout << "the Match is off\n"; }
	void breakMatch() { cout << "the Match is braked\n"; }
};
class Base {
public:
	string prop;
	Base() { cout << "simple constructor Base\n"; }
	Base(Base* b) { cout << "* point constructor Base \n"; }
	Base(Base& b) { cout << "& copy constructor Base\n"; }
	virtual ~Base() { cout << "dest of Base\n"; }
	virtual string className() const { return "Base"; };
	void setProp(string _prop) { prop = _prop; }
	string getProp() const { return prop; }

};
class Desk : public Base {
public:
	Desk() { cout << "simple constructor Desk\n"; }
	Desk(Desk* d) :Base(*d) { cout << "* point constructor  Desk \n"; }
	Desk(Desk& d) : Base(d) { cout << "& copy constructor Desk\n"; }
	~Desk() { cout << "dest of Desk\n"; }
	string className() const { return "Desk"; };
};

void func1(Base obj) {
	obj.setProp("monkey");
	cout << "func1: " << obj.className() << " prop is " << obj.getProp() << endl;
}//even virt destr can't destroy child
void func2(Base* obj) {
	obj->setProp("monkey");
	cout << "func2: " << obj->className() << " prop is " << obj->getProp() << endl;

}
void func3(const Base& obj) {
	//obj.setProp("monkey");
	cout << "func3: " << obj.className() << " prop is " << obj.getProp() << endl;
}
int main()
{
	setlocale(LC_ALL, "rus");
	string skip = "\n=======================================\n";

	/////////////////////////////////////////////////////////
	//___________ВИРТУАЛЬНЫЕ  МЕТОДЫ_______________________//
	/////////////////////////////////////////////////////////
	Light* room[3];
	room[0] = new Light;
	room[1] = new Sun;
	room[2] = new Lamp;
	Lamp* l = new Lamp;
	cout << skip;
	cout << "наследуемый метод" << endl;
	room[1]->switchOff();
	cout << "перекрываемый метод" << endl;
	l->switchOff();
	room[2]->switchOff();
	cout << "виртуальный метод" << endl;
	room[2]->switchOn();
	l->switchOn();
	cout << skip;
	
	/////////////////////////////////////////////////////////
	cout << "___________ПРИВЕДЕНИЕ  ТИПОВ__________________\n";
	/////////////////////////////////////////////////////////

	Sun* sun;
	Lamp* lamp;
	sun = dynamic_cast<Sun*>(room[1]);
	sun->toRaise();
	lamp = dynamic_cast<Lamp*>(room[1]);
	lamp->changePower();
	lamp = (Lamp*)(room[0]);
	lamp->changePower();
	cout << skip;
	/////////////////////////////////////////////////////////
	cout << "___________CLASSNAME  МЕТОД_________________\n";
	/////////////////////////////////////////////////////////

	for (int i = 0; i < 3; i++) {
		cout << room[i]->className() << endl;
	}
	cout << skip;
	/////////////////////////////////////////////////////////
	cout << "___________isA  МЕТОД_______________________\n";
	/////////////////////////////////////////////////////////

	Match m;
	for (int i = 0; i < 3; i++) {
		cout << m.isA(room[i]->className()) << endl;
	}
	cout << skip;
	/////////////////////////////////////////////////////////
	cout << "___________ПРИВЕДЕНИЕ  ТИПОВ с помощью isA()__\n";
	/////////////////////////////////////////////////////////

	Light* light = new Match();
	Match* mat;

	if (m.isA(light->className())) {
		mat = (Match*)(light);
		mat->breakMatch();
	}
	cout << skip;
	for (int i = 0; i < 3; i++)
		delete room[i];
	Base b;
	Desk d;
	//////////////////////////////////////////////
	cout << "______________func1________________\n\n";
	//////////////////////////////////////////////
	b.setProp("horse");
	d.setProp("horse");

	func1(b);
	cout << b.getProp() << endl;
	cout << endl;
	func1(d);
	cout << d.getProp() << endl;
	//////////////////////////////////////////////
	cout << "______________func2________________\n\n";
	//////////////////////////////////////////////
	b.setProp("horse");
	d.setProp("horse");

	func2(&b);
	cout << b.getProp() << endl;
	cout << endl;
	func2(&d);
	cout << d.getProp() << endl;
	//////////////////////////////////////////////
	cout << "______________func3 (read only)____\n\n";
	//////////////////////////////////////////////
	b.setProp("horse");
	d.setProp("horse");

	func3(b);
	cout << b.getProp() << endl;
	cout << endl;
	func3(d);
	cout << d.getProp() << endl;


	cout << endl;
	cout << skip;
	//////////////////////////////////////////////
	cout << "______________Умные указатели\n";
	unique_ptr<int> p1(new int(5));
	//unique_ptr<int> p2(p1); //не будет работать так как  p1 должен быть уникален
	unique_ptr<int> p2;
	cout << *p1 << endl;
	int* point = p1.get();//возвращает указатель
	p2.swap(p1);//меняет значения
	cout << *point << endl;
	shared_ptr<int> sr(new int(6));
	shared_ptr<int> sr1(sr);
	cout << *sr << sr << endl;
	cout << *sr1 << sr1 << endl;


	return 0;
}


