#pragma once

class ENEMY;
class ENEMY_STATE
{
public:

    virtual void Initialize(ENEMY* host) {};
    virtual void Execute(ENEMY* host) {};
    virtual void Finalize(ENEMY* host) {};
};

// Default State
class I_STATE : public ENEMY_STATE
{
    void Initialize(ENEMY* host) override;
    void Execute(ENEMY* host) override;
    void Finalize(ENEMY* host) override;
};

// Wander State
class W_STATE : public ENEMY_STATE
{
    void Initialize(ENEMY* host) override;
    void  Execute(ENEMY* host) override;
    void Finalize(ENEMY* host) override;
};


// Chase State
class C_STATE : public ENEMY_STATE
{
    void Initialize(ENEMY* host) override;
    void  Execute(ENEMY* host) override;
    void Finalize(ENEMY* host) override;
};


// Attack State
class A_STATE : public ENEMY_STATE
{
    int timer;
    void Initialize(ENEMY* host) override;
    void  Execute(ENEMY* host) override;
    void Finalize(ENEMY* host) override;
};

