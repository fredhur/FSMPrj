#include "FSM.hpp"
#include <iostream>
#include <typeinfo>
using namespace msfsm;
using namespace std;
class Up {};
class Up2 {};
class Down {};
class superNightShot {};

enum class myState
{
	GROUND,
	FLOOR1,
	FLOOR2,
	FLOOR3
};

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
		virtual void event(Up) {}
		virtual void event(Down) {}
		virtual void event(Up2) {}

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
		void event(Up2) override// call doble event
		{
			puts("Up2");
			transition(fsm.floor1);
			//fsm.floor1.event(Up());
			static_cast<typename Elevator::State*>(fsm.state())->event(Up());// 이벤트 두번 호출하려면 해야하는 일.
			static_cast<typename Elevator::State*>(fsm.state())->event(Up());
			puts("what?");
		}
		 void event(Up)override {
			 transition(fsm.floor1);
		 }
		 void event(Down)override {
			 
			 cout << "Do nothing" << endl;
			 //transition(fsm.ground);
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
		void event(Up)override {
			transition(fsm.floor2);
		}
		void event(Down)override {
			transition(fsm.ground);
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
		void event(Up)override
		{
			transition(fsm.floor3);
		}
		void event(Down)override
		{
			transition(fsm.floor2);
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
		void event(Up)override
		{
			cout << "Do nothing" << endl;
		}
		void event(Down)override
		{
			cout << "Do nothing" << endl;
		}
	}floor3{ this };
};

int main()
{
	Elevator elevator;
	cout << static_cast<int>(elevator.getState()) << endl;

	elevator.handle(Up());
	cout << static_cast<int>(elevator.getState()) << endl;

	elevator.handle(Up());
	cout << static_cast<int>(elevator.getState()) << endl;
	elevator.handle(Up());
	cout << static_cast<int>(elevator.getState()) << endl;
	elevator.handle(Up());
	cout << static_cast<int>(elevator.getState()) << endl;
	elevator.handle(Up());
	cout << static_cast<int>(elevator.getState()) << endl;

	puts("=====================");

	Elevator elevator2;
	cout << static_cast<int>(elevator2.getState()) << endl;

	elevator2.handle(Up2());

	cout << static_cast<int>(elevator2.getState()) << endl;
}
