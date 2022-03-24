#pragma once
#include "Engine/MODEL.h"
#include "Engine/DXMath.h"
#include "Engine/COLLISION.h"
#include "GAMEOBJECT.h"
using namespace Math;
using namespace DirectX;

class CHARACTER : public GAMEOBJECT
{
protected:
    bool isAlive{ true };
    bool isAttacking{};
    bool isHit{};
    //std::shared_ptr<MODEL>model;                  
    //std::map<std::string, std::shared_ptr<COLLIDER>>colliders;
    VECTOR3 position{};                            
    VECTOR3 rotation{};                            
    VECTOR3 scale{ 0.01f, 0.01f, 0.01f };             
    VECTOR3 velocity{};                            
    VECTOR3 movement{};
    VECTOR4 quaternion;
    
    float samplingRate{};                          
    float move;
    bool isMoving{};
public:
#pragma region MAIN FUNCTIONS

    CHARACTER() {}
    ///// <summary>
    ///// Reads the data from the OBJECT_DATA class loaded from the DATAMANGER
    ///// </summary>
    ///// <param name="d"></param>
    //virtual void ReadData(OBJECT_DATA* d);
    /// <summary>
    /// Initializes the model used. Call this after creating CHARACTER as contructor does not initializes.
    /// </summary>
    /// <returns></returns>
    virtual HRESULT Initialize(std::string model_path) { return S_OK; };


    
    /// <summary>
    /// Adds the velocity to the position
    /// </summary>
    virtual void Movement()
    {
        position.x += velocity.x * FRAMETIME;
        position.y += velocity.y * FRAMETIME;
        position.z += velocity.z * FRAMETIME;
    }


    /// <summary>
    /// Main functions. Call this every frame
    /// </summary>
    //virtual void Execute() {};

    /// </summary>
    /// <summary>
    /// Updates the transformation matrix with the scale, quaternion and position
    /// </summary>
    virtual void UpdateTransform()
    {
        //Model()->SetTransformationQ(scale, quaternion, position);
        //Model()->UpdateTransform();
    }
    /// <summary>
    /// Main animation setting. Call every frame
    /// </summary>
    virtual void AnimationSetting() {};
    /// <summary>
    /// Renders the model with the specified RGBA values
    /// </summary>
    /// <param name="colour"></param>
    virtual void Render(XMFLOAT4 colour = { 1.0f, 1.0f, 1.0f, 1.0f })
    {
        GAMEOBJECT::Render();
        //model->Render(samplingRate, colour);
        //for (auto& c : colliders)
        //    c.second->RenderDebug();
        //collider->RenderDebug();
        //weaponCollider->RenderDebug();
    }
    /// <summary>
    /// Finalizes the entity. Usually unneeded as most if not all objects are using smart pointers
    /// </summary>
    virtual void Finalize() {};

#pragma endregion
#pragma region SUBFUNCTIONS

    /// <summary>
    /// Controls the velocity so that it gradually decreases 
    /// </summary>
    virtual void VelocityControl()
    {
        if (!movement.x && !movement.z)
            return;
        if (isMoving)
            return;
        // movement.x *= 0.9f;
        // movement.z *= 0.9f;
        // velocity.x *= 0.9f;
        // velocity.z *= 0.9f;
        movement *= 0.9f;
        velocity *= 0.9f;
        if (fabs(movement.x) < 0.001f)
        {
            velocity.x = 0;
            movement.x = 0;
        }
        if (fabs(movement.z) < 0.001f)
        {
            velocity.z = 0;
            movement.z = 0;
        }
    };
    /// <summary>
    /// Manually adds an animation to the model. Use Fbx files without skin
    /// </summary>
    void AddAnimation(std::string anim_path)
    {
        //model->Resource()->AddAnimation(anim_path);
    }
    /// <summary>
    /// Call when entity is attacked
    /// </summary>
    virtual void Hit() {};
    /// <summary>
    /// Call when entity has died
    /// </summary>
    virtual void Kill() {};
    /// <summary>
    /// Sets death animation
    /// </summary>
    //virtual void DeathAnimation()
    //{
    //    if (Status())
    //        return;
    //    SetAnimation(6);
    //}
    ///// <summary>
    ///// Creates a capsule collider with the radius. Update top and bottom with capsule->Update();
    ///// </summary>
    //virtual void CreateCapsule(float rad)
    //{
    //    capsule = std::make_shared<CAPSULE>(rad);
    //}
    /// <summary>
    /// Adjusts the Bounding boxes according to the scale
    /// </summary>
    virtual void AdjustBB()
    {
        //boxes.resize(model->GetBB().size());

        //for (auto& b : model->GetBB())
        //{
        //    b->Min.x *= scale.x;
        //    b->Max.x *= scale.x;
        //    b->Min.y *= scale.y;
        //    b->Max.y *= scale.y;
        //    b->Min.z *= scale.z;
        //    b->Max.z *= scale.z;
        //}
    }
    /// <summary>
    /// Fits the weapon collider to the specified bone
    /// </summary>
    /// <param name="bone_name"> : Name of bone to be fitted onto</param>
    //virtual void FitWeaponOBBToBone(std::string bone_name)
    //{
    //    uint64_t index{};
    //    XMMATRIX m_Hand, player;
    //    for (auto& b : Model()->Resource()->Meshes[0].Bind_Pose.Bones)
    //    {
    //        if (b.Name == bone_name)
    //        {
    //            index = b.n_Index;
    //            break;
    //        }
    //    }
    //    if (index != -1)
    //    {
    //        XMFLOAT4X4 temp = Model()->Resource()->Animations[Model()->CurrentTake()].Keyframes[Model()->CurrentFrame()].Nodes.at(index).g_Transform;
    //        m_Hand = XMLoadFloat4x4(&temp);
    //    }
    //    player = Model()->TransformMatrix();
    //    XMFLOAT4X4 temp{ Model()->Resource()->Axises.AxisCoords };

    //    m_Hand *= XMLoadFloat4x4(&temp);
    //    m_Hand *= player;
    //    weaponCollider->Update(m_Hand);

    //}

    //virtual void FitWeaponOBBToBoneQ(std::string bone_name)
    //{
    //    uint64_t index{};
    //    XMMATRIX m_Hand, player;
    //    for (auto& b : Model()->Resource()->Meshes[0].Bind_Pose.Bones)
    //    {
    //        if (b.Name == bone_name)
    //        {
    //            index = b.n_Index;
    //            break;
    //        }
    //    }
    //    if (index != -1)
    //    {
    //        XMFLOAT4X4 temp = Model()->Resource()->Animations[Model()->CurrentTake()].Keyframes[Model()->CurrentFrame()].Nodes.at(index).g_Transform;
    //        m_Hand = XMLoadFloat4x4(&temp);
    //    }
    //    player = Model()->TransformMatrix();
    //    XMFLOAT4X4 temp{ Model()->Resource()->Axises.AxisCoords };

    //    m_Hand *= XMLoadFloat4x4(&temp);
    //    m_Hand *= player;
    //    weaponCollider->Update(m_Hand);

    //}

#pragma endregion

#pragma region PARAMETER RETRIEVAL

    /// <summary>
    /// Returns movement velocity of character
    /// </summary>
    /// <returns></returns>
    VECTOR3 Velocity()
    {
        return velocity;
    }         
    /// <summary>
    /// Returns position of character
    /// </summary>
    /// <returns></returns>
    VECTOR3 Position()
    {
        return position;
    }
    /// <summary>
    /// Returns rotation (Euler angles) of character
    /// </summary>
    /// <returns></returns>
    VECTOR3 Rotation()
    {
        return rotation;
    }
    /// <summary>
    /// Returns scale (size) of character
    /// </summary>
    /// <returns></returns>
    VECTOR3 Scale()
    {
        return scale;
    }
    /// <summary>
    /// Returns the rotation quaternion
    /// </summary>
    /// <returns></returns>
    VECTOR4 Quaternion()
    {
        return quaternion;
    }
    /// <summary>
    /// Returns the capsule class of the character
    /// </summary>
    /// <returns></returns>
    /// 
    /// TODO:UNUSED
    /// 
    //std::shared_ptr<CAPSULE>Capsule()
    //{
    //    return capsule;
    //}
    ///// <summary>
    ///// Returns the OBB class of the character
    ///// </summary>
    ///// <returns></returns>
    //std::shared_ptr<OBB>Collider()
    //{
    //    return collider;
    //}
    ///// <summary>
    ///// Returns the weapon OBB collider of the character
    ///// </summary>
    ///// <returns></returns>
    //std::shared_ptr<OBB>WeaponCollider()
    //{
    //    return weaponCollider;
    //}
    //
    // TODO:UNSUED
    //
    /// <summary>
    /// Returns the sampling rate used in Animation
    /// </summary>
    /// <returns></returns>
    float SamplingRate()
    {
        return samplingRate;
    }
    /// <summary>
    /// Returns the model class of the character
    /// </summary>
    /// <returns></returns>
    //MODEL* Model()
    //{
    //    return model.get();
    //}
    /// <summary>
    /// Returns true if alive
    /// </summary>
    /// <returns></returns>
    bool Status()
    {
        return isAlive;
    }
    /// <summary>
    /// Returns true if character is attacking
    /// </summary>
    /// <returns></returns>
    bool IsAttacking()
    {
        return isAttacking;
    }
    /// <summary>
    /// Returns true if character is attacked
    /// </summary>
    /// <returns></returns>
    bool IsHit()
    {
        return isHit;
    }
    /// <summary>
    /// Returns the Map of colliders
    /// </summary>
    //std::map<std::string, std::shared_ptr<COLLIDER>>Colliders() { return colliders; }

#pragma endregion
#pragma region PARAMETER SETTING

    /// <summary>
    /// Sets velocity to v
    /// </summary>
    void SetVelocity(XMFLOAT3 v)
    {
        velocity = v;
    }
    /// <summary>
    /// Sets scale to s
    /// </summary>
    void SetScale(XMFLOAT3 s)
    {
        scale = s;
    }
    /// <summary>
    /// Sets rotation to r
    /// </summary>
    void SetRotation(XMFLOAT3 r)
    {
        rotation = r;
    }
    /// <summary>
    /// Sets position to p
    /// </summary>
    void SetPosition(XMFLOAT3 p)
    {
        position = p;
    }
    /// <summary>
    /// Sets the Scale, rotation and position to s, r, and p respectively
    /// </summary>
    /// <param name="s"> : Scale</param>
    /// <param name="r"> : Rotation</param>
    /// <param name="p"> : Position</param>
    void SetTransformation(XMFLOAT3 s, XMFLOAT3 r, XMFLOAT3 p)
    {
        scale = s;
        rotation = r;
        position = p;
    }
    /// <summary>
    /// Sets the sampling rate used in animation to s
    /// </summary>
    void SetSamplingRate(float s)
    {
        samplingRate = s;
    }
    /// <summary>
    /// Sets the status of the character (Alive or not)
    /// </summary>
    /// <param name="stat"> : True if alive</param>
    void SetStatus(bool stat)
    {
        isAlive = stat;
    }
    /// <summary>
    /// Sets the current current animation take to AnimationTake
    /// </summary>
    //void SetTake(int AnimationTake)
    //{
    //    model->SetTake(AnimationTake);
    //}
    /// <summary>
    /// Sets the current Keyframe (For animations) to frame
    /// </summary>
    //void SetFrame(int frame)
    //{
    //    model->SetFrame(frame);
    //}
    /// <summary>
    /// Sets the current animation take to the variable and reset the frame
    /// </summary>
    //void SetAnimation(int take)
    //{
    //    SetTake(take);
    //    SetFrame(0);
    //}

#pragma endregion

};