#include "Camera.h"
#include "Input.h"
#include "DEBUG_PRIMITIVE.h"
#include "IMGUI.h"
std::shared_ptr<DEBUG_SPHERE>s;

using namespace DirectX;
void Camera::Initialize(XMFLOAT3 Default_Eye_Position, XMFLOAT3 Target)
{
    
    eye = Default_Eye_Position;
    target = Target;
    XMVECTOR UP{ 0.0f, 1.0f, 0.0f, 0.0f };
    viewMatrix = XMMatrixLookAtLH(eye.XMV(), target.XMV(), UP);

    s = std::make_shared<DEBUG_SPHERE>();
    


}
VECTOR2 clicked_pos{}, move_pos{};
VECTOR2 movement;

void Camera::Execute()
{
    
    INPUTMANAGER* i = INPUTMANAGER::Instance();
    INPUTMANAGER::MOUSE* m = INPUTMANAGER::Instance()->Mouse().get();
    float wheel{};
    if (m->Wheel().Up().Held())
        wheel = 5.0f;
    if (m->Wheel().Down().Held())
        wheel = -5.0f;
    VECTOR2 pos, pos2, drag_pos;
    static bool start{};
    if (i->AltKeys()->State().Held())
    {
        if (m->LButton().Triggered()) {
            clicked_pos += m->fPosition();
            start = true;
        }
        if (m->LButton().Held() && start)
        {
            pos = m->fPosition();
            VECTOR2 vector{ pos - clicked_pos };
            vector *= 0.1f;
            rotation.y += ToRadians(vector.x);
            rotation.x += -ToRadians(vector.y);
            clicked_pos = pos;
        }
        if (m->LButton().Released()) {
            clicked_pos = {};
            start = false;
        }
        if (m->RButton().Triggered()) {
            move_pos += m->fPosition();
            start = true;
        }
        if (m->RButton().Held() && start)
        {
            pos2 = m->fPosition();
            movement.x += -(pos2.x - move_pos.x);
            movement.y += pos2.y - move_pos.y;
            movement *= 0.03f;
            move_pos = pos2;
        }
        if (m->RButton().Released())
        {
            move_pos = {};
            movement = {};
            start = false;
        }
    }

    XMMATRIX temp{ XMMatrixRotationRollPitchYawFromVector(rotation.XMV()) };
    VECTOR3 horizontol, vertical, forward;
    horizontol.Load(temp.r[0]);
    vertical.Load(temp.r[1]);
    horizontol.Normalize();
    vertical.Normalize();
    forward = eye - target;
    forward.Normalize();
    target += horizontol * movement.x + vertical * movement.y;
    //rotation.x = Math::Clamp(rotation.x, ToRadians(-89), ToRadians(89));
    range += -forward.Length() * wheel * 0.5f;

    range = (std::max)(1.0f, range);
    XMMATRIX T{ XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, 0) };
    XMVECTOR F{ T.r[2] };
    XMFLOAT3 f;
    XMStoreFloat3(&f, F);

    eye.x = target.x + (f.x * -range);
    eye.y = target.y + (f.y * range);
    eye.z = target.z + (f.z * -range);

    SetLookAt();
    s->SetPosition(target);
    s->Execute();

    if (reset)
    {
        target.Load(XMVectorLerp(target.XMV(), next_target.XMV(), 0.1f));
        range = Math::Lerp(range, 10.0f, 0.1f);
        if ((target - next_target).Length() < 0.001f && range - 10.0f < 0.001f)
        {
            reset = false;
            target = next_target;
            range = 10.0f;
        }
    }

}

void Camera::Render()
{
    ImGui::Begin("Position");
    ImGui::InputFloat3("Eye", &eye.x);
    ImGui::InputFloat2("Movement", &movement.x);
    ImGui::InputFloat2("clicked", &clicked_pos.x);

    ImGui::InputFloat3("Target", &target.x);
    ImGui::End();
    s->Render();
}

void Camera::ResetCamera()
{
    target = {};
    eye = {};
    rotation = {};
}

void Camera::ResetToTarget(VECTOR3 t)
{
    next_target = t;
    reset = true;
}

VECTOR3 Camera::Forward()
{
    XMMATRIX rot = XMMatrixRotationRollPitchYawFromVector(rotation.XMV());
    VECTOR3 forward;
    forward.Load(rot.r[2]);
    return forward;
}
VECTOR3 Camera::Eye()
{
    return eye;
}