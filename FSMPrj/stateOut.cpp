#include "FSM.hpp"
#include <iostream>
#include <typeinfo>
using namespace msfsm;
using namespace std;
class Up {};
class Up2 {};
class Down {};
class superNightShot {};

struct DataEvent
{
	int floor;
	int a;
	bool chk()
	{
		return floor == 3 && a == 2;
	}
};

enum class myState
{
	GROUND,
	FLOOR1,
	FLOOR2,
	FLOOR3
};

class StateOutElevator : public Fsm<StateOutElevator>
{
public:
	StateOutElevator();
	~StateOutElevator();

private:
	myState enumstate;
	friend Fsm;
	class State;
	class Ground; Ground* ground;
	class Floor1; Floor1* floor1;
	class Floor2; Floor2* floor2;
	class Floor3; Floor3* floor3;
};
class StateOutElevator::State : public Fsm::State
{
	friend Fsm;
	using Fsm::State::State;
	virtual void event(DataEvent) {}
};
class StateOutElevator::Ground : public StateOutElevator::State
{
	friend Fsm;
	using State::State;
	void entry()
	{
		fsm.enumstate = myState::GROUND;
		cout << "in here " << typeid(*this).name() << endl;
	}
	void event(DataEvent r) override// call doble event
	{
		if (r.chk())
			transition(*fsm.floor1);

	}

};

class StateOutElevator::Floor1 : public StateOutElevator::State
{
	friend Fsm;
	using State::State;
	void entry()
	{
		fsm.enumstate = myState::FLOOR1;
		cout << "in here " << typeid(*this).name() << endl;
	}
	void event(DataEvent r)override {
		if (r.chk())
			transition(*fsm.floor2);
	}

};
class StateOutElevator::Floor2 : public StateOutElevator::State
{
	friend Fsm;
	using State::State;
	void entry()
	{
		fsm.enumstate = myState::FLOOR2;
		cout << "in here " << typeid(*this).name() << endl;
	}
	void event(DataEvent r)override {
		if (r.chk())
			transition(*fsm.floor3);
	}

};
class StateOutElevator::Floor3 : public StateOutElevator::State
{
	friend Fsm;
	using State::State;
	void entry()
	{
		fsm.enumstate = myState::FLOOR3;
		cout << "in here " << typeid(*this).name() << endl;
	}
	void event(DataEvent r)override {
		cout << "Do nothing" << endl;
	}

};
StateOutElevator::StateOutElevator()
	:ground(new Ground(this)),
	floor1(new Floor1(this)),
	floor2(new Floor2(this)),
	floor3(new Floor3(this))
{
	transition(*ground);
}
StateOutElevator::~StateOutElevator()
{
	delete(ground);
	delete(floor1);
	delete(floor2);
	delete(floor3);
}
class Elevator :public Fsm<Elevator>
{
public:
	myState getState()
	{
		return enumstate;
	}
	Elevator()
	{
		transition(ground);
		enumstate = myState::GROUND;
	}
private:
	friend Fsm;
	myState enumstate;
	class State :public Fsm::State {

	public:
		friend Fsm;
		using Fsm::State::State;
		virtual void event(DataEvent r) {}


	};
	class Ground :public State
	{
		friend Fsm;
		using State::State;
		void entry()
		{
			fsm.enumstate = myState::GROUND;
			cout << "in here " << typeid(*this).name() << endl;
		}
		void event(DataEvent r) override// call doble event
		{
			if (r.chk())
				transition(fsm.floor1);

		}


	}ground{ this };

	class Floor1 :public State
	{
		friend Fsm;
		using State::State;
	public:
		void entry()
		{
			fsm.enumstate = myState::FLOOR1;
			cout << "in here " << typeid(*this).name() << endl;
		}
		void event(DataEvent r)override {
			if (r.chk())
				transition(fsm.floor2);
		}

	}floor1{ this };
	class Floor2 :public State
	{
		friend Fsm;
		using State::State;
		void entry()
		{
			fsm.enumstate = myState::FLOOR2;
			cout << "in here " << typeid(*this).name() << endl;
		}
		void event(DataEvent r)override
		{
			if (r.chk())
				transition(fsm.floor3);
		}

	}floor2{ this };
	class Floor3 :public State
	{
		friend Fsm;
		using State::State;
		void entry()
		{
			fsm.enumstate = myState::FLOOR3;
			cout << "in here " << typeid(*this).name() << endl;
		}
		void event(DataEvent r)override
		{

			cout << "Do nothing" << endl;
		}

	}floor3{ this };
};

int main()
{
	Elevator elevator;
	DataEvent r;

	r.floor = 3;
	r.a = 2;

	elevator.handle(r);

	puts("==============================");
	StateOutElevator stateOutElevator;

	stateOutElevator.handle(r);
	stateOutElevator.handle(r);
	stateOutElevator.handle(r);
	stateOutElevator.handle(r);
	stateOutElevator.handle(r);
	stateOutElevator.handle(r);
}
