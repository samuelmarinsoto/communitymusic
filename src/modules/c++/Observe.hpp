#ifndef OBSERVE_H
#define OBSERVE_H

#include "LinkedList.hpp"

enum State{
    type0,
    type1,
    type2,
    type3,
    type4
};

// C++ parent class for observer objects
class Observer{
    public:
        // Receive an update of state changes in the object being observer
        virtual void update(State state){};
        // Stop observing behaviour
        virtual void stopObserving(){};
    protected:
        // For comparing any observer
        bool operator==(Observer other){
            if (this == &other){
                return true;
            }
            return false;
        }
};

// C++ parent class for observable objects 
class Observable {
    private:
        LinkedList<Observer*> observers;
    public:
        // Adds a new observer to the list
        void AddObserver(Observer* observer){
            this->observers.insert(observer);
        };
        // Removes an observer from the list
        void RemoveObserver(Observer* observer){
            this->observers.find_remove(observer);
        };
        // Gets the current state and type of change
        State getState(){
            return this->current;
        };
        void passive_notify(){
            for(int i = 0; i<this->observers.size; i++){
                this->observers[i]->update(State::type2);
            }
        }
    protected:
        State current;
        // Notifies all current observers
        void notifyObservers(){
            for(int i = 0; i<this->observers.size; i++){
                this->observers[i]->update(this->current);
            }
            this->current = type0;
        };
    
};
#endif // OBSERVE_H