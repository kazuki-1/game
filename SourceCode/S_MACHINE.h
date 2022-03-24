#pragma once
#include "STATE.h"
#include "Engine\Singleton.h"
#include <memory>
#include <map>

class ENEMY;
enum E_STATE
{
    IDLE,
    WANDER,
    CHASE,
    ATTACK,

};


// Enemy State Machine for behavioural control
class S_MACHINE
{
    ENEMY* host;
    std::shared_ptr<ENEMY_STATE> cur_State;

public:
    S_MACHINE(ENEMY* h) : host(h) {}
    void Change(E_STATE es);
    void Initialize();
    void Execute();
    void Finalize();
};

class STATEMANAGER : public SINGLETON<STATEMANAGER>
{
    std::map<E_STATE, std::shared_ptr<ENEMY_STATE>>states;

public:
    void Initialize()
    {
        states.emplace(std::make_pair<E_STATE , std::shared_ptr<ENEMY_STATE>>(E_STATE::IDLE, std::make_shared<I_STATE>()));
        states.emplace(std::make_pair<E_STATE, std::shared_ptr<ENEMY_STATE>>(E_STATE::WANDER, std::make_shared<W_STATE>()));
        states.emplace(std::make_pair<E_STATE , std::shared_ptr<ENEMY_STATE>>(E_STATE::CHASE, std::make_shared<C_STATE>()));
        states.emplace(std::make_pair<E_STATE , std::shared_ptr<ENEMY_STATE>>(E_STATE::ATTACK, std::make_shared<A_STATE>()));
    }

    std::shared_ptr<ENEMY_STATE>Get(E_STATE host)
    {
        return states.find(host)->second;
    }

    std::map<E_STATE, std::shared_ptr<ENEMY_STATE>>States()
    {
        return states;
    }
};
