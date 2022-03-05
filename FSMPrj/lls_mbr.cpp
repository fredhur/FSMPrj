#include <iostream>
#include "FSM.hpp"
using namespace std;
using namespace msfsm;


/*
<---lls---|<-------mbr--------|<--------normal---------      
	                                     
---------lls----->|----------mbr-------->|-----normal---->
*/                       
class MBRLLSState :public Fsm<MBRLLSState>
{
	
public:
	MBRLLSState(int llshisdown, int llshisup, int mbrhisdown, int mbrhisup)
	{
		transition(normal);
		mbrhisupths_ = mbrhisup;
		mbrhisdownths_ = mbrhisdown;
		llshisdownths_ = llshisdown;
		llhshisupths_ = llshisup;
	}
private:
	int mbrhisupths_;
	int mbrhisdownths_;
	int llshisdownths_;
	int llhshisupths_;
	friend Fsm;
	class State :public Fsm::State
	{
	public:
		DECL_STATE
		virtual void event(int) {}
		virtual void entry() {}
	};
	class Mbr : public State
	{
		friend Fsm; using State::State;
		void entry()
		{
			FSMDEBUGPRINT(__FUNCSIG__);

			//cout << typeid(*this).name() << endl;
		}
		void event(int bv)
		{
			if (bv >= fsm.mbrhisupths_)
			{
				transition(fsm.normal);
				
				return;
			}
			if (bv < fsm.llshisdownths_)
			{
				transition(fsm.lls);
				return;
			}
		}
	}mbr{ this };
	class Lls : public State
	{
		friend Fsm; using State::State;
		void entry()
		{
			FSMDEBUGPRINT(__FUNCSIG__);
		}
		void event(int bv)
		{
			if (bv >= fsm.llhshisupths_)
			{
				transition(fsm.mbr);
				EVENT_CALL(MBRLLSState) (bv);// 
				// mbr �� �Ѿ��, �ٷ� normal �� ������ ���� �ִ�. 
				// �Ǽ������� �˷��ֽ� event �� ���ο��� �ι� �̻� ���ؾ��ϴ� ���. 
				return;
			}
		}

	}lls{this};
	class normal : public State
	{
		friend Fsm; using State::State;
		void entry()
		{
			FSMDEBUGPRINT(__FUNCSIG__);
			//cout << typeid(*this).name() << endl;
		}
		void event(int bv)
		{
			if (bv < fsm.mbrhisdownths_)
			{
				transition(fsm.mbr);
				EVENT_CALL(MBRLLSState)(bv);// 
				// mbr �� �Ѿ��, �ٷ� lls �� ������ ���� �ִ�. 
				return;
			}

		}
	}normal{ this };
};
int main()
{

	int bv;
	MBRLLSState mbrllsState(-100, -50, -20, 10);
	while (true)
	{
		cin >> bv;

		mbrllsState.handle(bv);
	}


}