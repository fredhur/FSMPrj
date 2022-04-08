#include <iostream>
using namespace std;

class State;
class HisTheSisUpDownState {
public:
    HisTheSisUpDownState();
    void chageState(State* newState);
    void onPushedRequest();
    void offPushedRequest();
private:
    State* currentState;
};

class State {
public:
    virtual ~State() {}
    virtual void HisTheSisUpEvent(HisTheSisUpDownState* HisTheSisUpDownState) = 0;
    virtual void HisTheSisDownEvent(HisTheSisUpDownState* HisTheSisUpDownState) = 0;
};
class HisTheSisDownState : public State {
public:
    static State* getInstance() {
        static  HisTheSisDownState HisTheSisDownState;
        return &HisTheSisDownState;
    }
    virtual void HisTheSisUpEvent(HisTheSisUpDownState* HisTheSisUpDownState) override;
    virtual void HisTheSisDownEvent(HisTheSisUpDownState* HisTheSisUpDownState) override;
};
class HisTheSisUpState : public State {
public:
    static State* getInstance() {
         static HisTheSisUpState HisTheSisUpState;// 반드시 static 으로 선언. 안되면 런타임 에러 + 비정적멤버함수 호출
        return &HisTheSisUpState;
    }
    virtual void HisTheSisUpEvent(HisTheSisUpDownState* HisTheSisUpDownState);
    virtual void HisTheSisDownEvent(HisTheSisUpDownState* HisTheSisUpDownState);
};

void HisTheSisDownState::HisTheSisUpEvent(HisTheSisUpDownState* HisTheSisUpDownState) {
    cout << "HisTheSisup" << endl;
    HisTheSisUpDownState->chageState(HisTheSisUpState::getInstance());
}

void HisTheSisDownState::HisTheSisDownEvent(HisTheSisUpDownState* HisTheSisUpDownState) {
    cout << "No event ocucr at HisTheSisdown state" << endl;

   // HisTheSisDownEvent(HisTheSisUpDownState); event 안에서 event 를 콜하기 위해서는 재귀가 된다..
}


void HisTheSisUpState::HisTheSisUpEvent(HisTheSisUpDownState* HisTheSisUpDownState) {
    cout << "no event occur in histhesisup state" << endl;
}

void HisTheSisUpState::HisTheSisDownEvent(HisTheSisUpDownState* HisTheSisUpDownState) {
    cout << "HisThesisDown event" << endl;
    HisTheSisUpDownState->chageState(HisTheSisDownState::getInstance());
}



HisTheSisUpDownState::HisTheSisUpDownState() {
    currentState = HisTheSisDownState::getInstance();
}
void HisTheSisUpDownState::chageState(State* newState) {
    currentState = newState;
}
void HisTheSisUpDownState::onPushedRequest() {
    currentState->HisTheSisUpEvent(this);
}
void HisTheSisUpDownState::offPushedRequest() {
    currentState->HisTheSisDownEvent(this);
}

int main(int argc, const char* argv[]) {
    //HisTheSisUpDownState* fredhur = new HisTheSisUpDownState();
    HisTheSisUpDownState fredhur;
    fredhur.onPushedRequest();
    fredhur.onPushedRequest();
           
    fredhur.offPushedRequest();
    fredhur.offPushedRequest();

    return 0;
}
