// Copytight (C) 2019 Michal Sojka <ms@2x.cz>
//
// SPDX-License-Identifier: MIT

#ifndef MSFSM_HPP
#define MSFSM_HPP

#include <iostream>
#include <stdexcept>
//#include <boost/type_index.hpp> // Only needed if StateName is used

#define EVENT_CALL(StateClass) static_cast<typename StateClass::State*>(fsm.state())->event

#define DECL_STATE friend Fsm;               \
                   using Fsm::State::State;


#define FSM_DEBUG 0


void FSMDEBUGPRINT(const char* s)
{
#ifdef FSM_DEBUG
	std::cout <<"current State " <<  s << std::endl;
#endif
	return;
}



namespace msfsm {
	template <class C>
	class Fsm
	{
	protected:
		// Base class for all states
		class State {
		public:
			State(C* fsm) : fsm(*fsm) {}
			virtual ~State() {}
		private:
			friend Fsm;
			virtual void exit() {}

		protected:
			C& fsm;

			// Convenience method
			template<class S, class ... Types>
			void transition(S& nextState, Types... args) { fsm.Fsm<C>::transition(nextState, args...); }
		};

		template<class S, class ... Types>
		void transition(S& nextState, Types... args) {
			if (m_state)
				m_state->exit();
			static_cast<C*>(this)->onTransition(nextState);
			m_state = &nextState;
			nextState.entry(args...);
			static_cast<C*>(this)->afterTransition();
		}

		// Call this from derived class destructor if needed. We cannot
		// make this in our destructor, because the states are already
		// destoyed when it runs.
		void destroy() {
			if (m_state)
				m_state->exit();
			m_state = nullptr;
		}

	private:
		State* m_state = nullptr;

		// Prevent compile error if derived class does not have its own onTransition() method
		void onTransition(State& nextState) {}
		void afterTransition() {}

	public:
		State* state() const { return m_state; }
		//using F = typename FSM::State*;
		template <typename EV>
		void handle(EV event) {
			if (!m_state)
				throw std::domain_error(__func__);
			static_cast<typename C::State*>(m_state)->event(event);
		}
	};

	 //Mix-in class for named states
	//template <class S>
	//class Named {
	//    std::string m_name;

	//public:
	//    // Unfortunately, type_id does not correspond to derived class
	//    // in constructor, so we must retrieve (and cache) the name
	//    // later.
	//    const std::string& name() {
	//        if (m_name.empty())
	//            m_name = boost::typeindex::type_id_runtime(static_cast<S&>(*this)).pretty_name();
	//        return m_name;
	//    }
	//};

}

#endif // MSFSM_HPP