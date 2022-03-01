//#include "FSM.hpp"
//
//
//using namespace msfsm;
//using namespace std;
//
//// Events
//struct Request {
//	const int floor;
//	Request(int f) : floor(f) {}
//};
//class Roof;
//class Elevator : public Fsm<Elevator> {
//public:
//	Elevator() {
//		transition(*ground);
//	}
//
//private:
//	friend Fsm;
//	class State;
//
//	class Roof;
//
//	Roof* roof;
//	class Middle;
//
//	Middle* middle;
//
//	class Ground;
//	Ground* ground;
//
//
//};
//class Elevator::State : public Fsm::State {
//
//	friend Fsm;
//	using Fsm::State::State;
//	virtual void event(Request) = 0;
//};
//class Elevator::Roof : public Elevator::State
//{
//	friend Fsm;
//	using State::State;
//	void entry();
//	virtual void event(Request);
//};
//void Elevator::Roof::entry()
//{
//	cout << "Entering roof" << endl;
//}
//
//void Elevator::Roof::event(Request r)
//{
//	if (r.floor < 3)
//		transition(*fsm.middle, r);
//}
//
//class Elevator::Middle : public Elevator::State
//{
//	friend Fsm;
//	using State::State;
//	void entry(Request);
//	virtual void event(Request);
//};
//void Elevator::Middle::entry(Request r)
//{
//	cout << "Entering middle" << endl;
//	event(r);
//}
//
//void Elevator::Middle::event(Request r)
//{
//	if (r.floor < 2)
//		transition(*fsm.ground);
//	if (r.floor > 2)
//		transition(*fsm.roof);
//}
//
//class  Elevator::Ground :public Elevator::State
//{
//	friend Fsm;
//	using State::State;
//	void entry();
//	virtual void event(Request);
//};
//
//int main(int argc, char* argv[])
//{
//	Elevator e;
//	e.handle(Request(3));
//	e.handle(Request(1));
//	e.handle(Request(2));
//	return 0;
//}
//
//void Elevator::Ground::entry()
//{
//	cout << "Entering ground" << endl;
//}
//
//void Elevator::Ground::event(Request r)
//{
//	if (r.floor > 1)
//		transition(*fsm.middle, r);
//}
#include "FSM.hpp"
#include <iostream>

using namespace msfsm;
using namespace std;

// Events
struct Request {
    const int floor;
    Request(int f) : floor(f) {}
};

#define DECL_STATE(fsm, state) \
friend fsm; \
using fsm::state::state;

#define FSM_DEBUG 1


#ifdef FSM_DEBUG 

#define DEBUG_PRINT(state) cout<<#state << typeid(this).name()<<endl;

#endif


class Elevator : public Fsm<Elevator> {
public:
    Elevator() {
        transition(ground);// 초기화는 당연히 그라운드 state 
        //transition(middle); // 초기화를 middle 에서 하고 싶을 경우
    }

private:
    friend Fsm;
    class State: public Fsm::State {
        DECL_STATE(Fsm, State)
        virtual void event(Request) = 0;      
    };
    void onTransition(State& nextState) {

        cout <<"onTrnasition to "<< typeid(nextState).name() << endl;
    }
    void afterTransition()
    {
        cout << "after Transition!" << endl;
    }
    struct Roof : public State {
        using State::State;
        void entry();
        void event(Request r) override;
        void exit() override
        {
            cout << "exit at Roof " << endl;
        }
    } roof{ this };

    class Middle : public State {
        friend Fsm;
        using State::State;
        void entry()
        {
            cout << "Start at middle and entering" << endl;// 초기화 middle 시 빈 깡통이 호출되니까. 
            
        }
        void entry(Request r) {
            DEBUG_PRINT(CURRENT)
            cout << "Entering middle" << endl;
            event(r);
        }
        void event(Request r) override {
            if (r.floor < 2)
                transition(fsm.ground);
            if (r.floor > 2) {
                cout << "go to roof " << endl;
                transition(fsm.roof);
            }
        }
    } middle{ this };

    class Ground : public State {
        friend Fsm;
        using State::State;
        void entry() {
            cout << "Entering ground" << endl;
        }
        void event(Request r) override {
            if (r.floor > 1)
                transition(fsm.middle, r);
        }
        void exit()override
        {
            cout << "GROUND EXIT" << endl;
        }
    } ground{ this };
};



void Elevator::Roof::entry()
{
    cout << "Entering roof" << endl;
}
void Elevator::Roof::event(Request r)
{
    if (r.floor < 3)
            transition(fsm.middle, r);
    cout << "I'm in Roof " << endl;
}
//class Roof : public State {
//    friend Fsm;
//    using State::State;
//    void entry() {
//        cout << "Entering roof" << endl;
//    }
//    void event(Request r) override {
//        if (r.floor < 3)
//            transition(fsm.middle, r);
//    }
//} roof{ this };
int main(int argc, char* argv[])
{
    Elevator e;

    puts("finsih init ");
    e.handle(Request(2));
  
    puts("finsih 1");


    e.handle(Request(2));

    puts("finsih 2");

    e.handle(Request(3));

    return 0;
}

