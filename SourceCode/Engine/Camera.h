#pragma once
#include "Singleton.h"
#include "DXMath.h"
#include <DirectXMath.h>
using namespace DirectX;
using namespace Math;
class Camera : public SINGLETON<Camera>
{
    //Camera() {};
    float range{};
    VECTOR3 position{}, rotation{}, velocity{};
    VECTOR3 eye{};
    VECTOR3 target{};
    VECTOR3 next_target{};
    XMMATRIX viewMatrix{};
    XMFLOAT4X4 view{};
    bool reset{};
public:
    //static Camera* Instance()
    //{
    //    static Camera c;
    //    return &c;
    //}
    void SetPosition(XMFLOAT3 pos)
    {
        position = pos;
    }
    void SetPosition(VECTOR3 pos) { position = pos; }
    void SetVelocity(XMFLOAT3 vel)
    {
        velocity = vel;
    }
    void SetVelocity(VECTOR3 vel) { velocity = vel; }
    void SetRotation(XMFLOAT3 rot)
    {
        rotation = rot;
    }
    void SetTarget(XMFLOAT3 t)
    {
        target = t;
    }
    void SetTarget(VECTOR3 v) { target = v; }
    void SetLookAt()
    {
        VECTOR3 u{ 0, 1, 0 };
        viewMatrix = XMMatrixLookAtLH(eye.XMV(), target.XMV(), u.XMV());
    }
    void SetRange(float r)
    {
        range = r;
    }
    void ResetCamera();
    void ResetToTarget(VECTOR3 t);

    float Range()
    {
        return range;
    }
    XMFLOAT3 Position()
    {
        return position.XMF3();
    }
    XMFLOAT3 Velocity()
    {
        return velocity.XMF3();
    }
    XMFLOAT3 Rotation()
    {
        return rotation.XMF3();
    }
    XMMATRIX ViewMatrix()
    {
        return viewMatrix;
    }
    VECTOR3 Forward();
    VECTOR3 Eye();

    void Initialize(XMFLOAT3 Default_Eye_Position, XMFLOAT3 Target);
    void Execute();
    void Render();
};