// AmazonStudio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <set>
#include <map>

using namespace std;


class GameObject 
{ 
public: 
	virtual void onTick() {} // call this when the timer expires
	virtual long getTickMs() const {} // how long until I want to be ticked
	virtual ~GameObject() {}
    virtual void setTickTime(long t) {mTickTime = t;}
    virtual long getTickTime() const {return mTickTime;}
private:
    long mTickTime;
};

typedef set<GameObject*, bool(*)(GameObject*, GameObject*)> MySet;

class TimerService 
{ 
public:
	/*
	// version 1
    void register1(GameObject &obj) {
        if (rec.find(&obj) != rec.end())
            return;
        rec[&obj] = getGameMs();
    }; // implement - called to register the game object for onTick calls
    void onGameLoopTick() {
        for (map<GameObject*, long>::iterator it = rec.begin(); it != rec.end(); ++it) {
            if ((getGameMs() - it->second) > it->first->getTickMs()) {
                it->first->onTick();
                it->second = getGameMs();
            }
        }
    };          // implement - called by the main game loop
	*/

	/*
    // version 2
    void register1(GameObject &obj) {
        rec.push_back(&obj);
        obj.setTickTime(getGameMs());
    }
    void onGameLoopTick() {
        for (vector<GameObject*>::iterator it = rec.begin(); it != rec.end(); ++it) {
            if ((getGameMs() - (*it)->getTickTime()) > (*it)->getTickMs()) {
                (*it)->onTick();
                (*it)->setTickTime(getGameMs());
            }
        }
    }
	*/

	// version 3
	struct objCmp2{
		bool operator() (const GameObject& lobj, const GameObject& robj) const {
			return (getGameMs() - lobj.getTickTime() - lobj.getTickMs()) > 
				(getGameMs() - robj.getTickTime() - robj.getTickMs());
		}
	};
	
	static bool objCmp(GameObject* lobj, GameObject* robj) {
		return (getGameMs() - lobj->getTickTime() - lobj->getTickMs()) > 
				(getGameMs() - robj->getTickTime() - robj->getTickMs());
	}

	void register1(GameObject &obj) {
		if (rec == NULL) {
			bool(*fn_pt)(GameObject*, GameObject*) = TimerService::objCmp;
			rec = new set<GameObject*, bool(*)(GameObject*, GameObject*)>(fn_pt);

			set<int, objCmp2> test; // just a test, passed the test!
		}
        rec->insert(&obj);
        obj.setTickTime(getGameMs());
    }
    void onGameLoopTick() {
		for (MySet::iterator it = rec->begin(); it != rec->end(); ++it) {
			if ((getGameMs() - (*it)->getTickTime()) < (*it)->getTickMs())
				break;
			(*it)->onTick();
			(*it)->setTickTime(getGameMs());
		}
    }
private: 
    static long getGameMs(); // time since the game started - implemented for you 
    // add more fields/methods as needed
    //map<GameObject*, long> rec; // version 1
    //vector<GameObject*> rec; // version 2
    MySet *rec; // version 3
};

//current time - register time - wanted tick time

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}