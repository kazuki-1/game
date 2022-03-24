#pragma once
#include <DirectXMath.h>
#include <vector>
#include "MODEL.h"
#include "DXMath.h"
#include "CerealHeaders.h"
using namespace Math;

using namespace DirectX;
//using namespace Math;
class MESH;
class COMPONENT_DATA;
class OBB_COLLIDER_DATA;
class CAPSULE_COLLIDER_DATA;

namespace COLLIDERS
{

#pragma region BASE CLASSES

    /// <summary>
    /// For Storing RayCast data
    /// </summary>
    struct RAYCASTDATA
    {
        std::string model_name{};
        VECTOR3 position{ 0, 0, 0 };
        VECTOR3 normal{ 0, 0, 0 };
        float distance;
        int m_Index{ -1 };
    };
    struct OBB_DIRECTION
    {
        bool horizontol;
        bool vertical;
    };

    /// <summary>
    /// Collider Base class. Inherited by OBB, CAPSULE and SPHERE
    /// </summary>
    class COLLIDER_BASE
    {
    protected:
        bool isActive{ true };
        VECTOR3 offset;
        VECTOR3 rotation;
        XMMATRIX world;
        XMMATRIX bone_World{ XMMatrixIdentity() };
    public:
        COLLIDER_BASE() {};
        /// <summary>
        /// <para> Pure virtual Function. Initializes the object </para>
        /// <para> �������z�֐��B�N���X������������ </para>
        /// </summary>
        /// <returns></returns>
        virtual HRESULT Initialize() { return S_OK; }
        /// <summary>
        /// <para> Pure virtual Function. Called every frame to perform functions</para>
        /// <para> �������z�֐��B�֐������s����悤�ɖ��t���[���ɌĂяo��</para>
        /// </summary>
        /// <returns></returns>
        virtual void Execute(XMMATRIX mat) {}
        /// <summary>
        /// <para> Pure virtual Function. Called to render any objects within</para>
        /// <para> �������z�֐��B�����_�[�֐������s����悤�ɖ��t���[���ɌĂяo��</para>
        /// </summary>
        /// <returns></returns>
        virtual void Render() {}
        /// <summary>
        /// <para> Pure virtual Function. Called to perform collision check with the other object</para>
        /// <para> �������z�֐��B�����ɂ���R���C�_�[�Ɠ����蔻����v�Z</para>
        /// </summary>
        /// <returns></returns>
        virtual bool Collide(COLLIDER_BASE* o) { return false; }
        /// <summary>
        /// <para> Pure virtual Function. Called to perform collision check with the point</para>
        /// <para> �������z�֐��B�����ɂ�����W�Ɠ����蔻����v�Z</para>
        /// </summary>
        /// <returns></returns>
        virtual bool Collide(VECTOR3 p) { return false; }
        /// <summary>
        /// <para> virtual Function. Called to fit the collider to the bone of the model</para>
        /// <para> ���z�֐��B���f���ɂ��Ă��ꂽ�{�[���ɃR���C�_�[���Z�b�g</para>
        /// </summary>
        /// <param name="name"> : Name of bone</param>
        /// <param name="m"> : Pointer of model</param>
        virtual void FitToBone(std::string name, MODEL* m);
        virtual void SetData(COMPONENT_DATA* data) {}
        /// <summary>
        /// Offsets the collider 
        /// </summary>
        /// <param name="off"> : User declared offset</param>
        virtual void OffsetCollider(VECTOR3 off) { offset = off; }
        virtual void RotateCollider(VECTOR3 rot) { rotation = rot; }

        /// <summary>
        /// Activates the collider
        /// </summary>
        virtual void Activate() { isActive = true; }
        /// <summary>
        /// Deactivates the collider
        /// </summary>
        virtual void Deactivate() { isActive = false; }
        /// <summary>
        /// Returns true if collider is active
        /// </summary>
        /// <returns></returns>
        virtual bool IsActive() { return isActive; }
        /// <summary>
        /// Cast the data into the desired type
        /// </summary>
        /// <returns></returns>
        template <class T>
        T* CastData(COMPONENT_DATA* d)
        {
            T* t = dynamic_cast<T*>(d);
            return t;
                
        }
        /// <summary>
        /// Returns the offset of the collider in Vector3 Form
        /// </summary>
        /// <returns></returns>
        VECTOR3 Offset() { return offset; }
        /// <summary>
        /// Generates a XMMATRIX from the offset vector
        /// </summary>
        /// <returns></returns>
        XMMATRIX MatrixOffset();
        /// <summary>
        /// Returns the world matrix of the collider after being fitted to a bone. Will return identity if unfitted
        /// </summary>
        /// <returns></returns>
        XMMATRIX WorldMatrix() { return bone_World; }
        virtual float Size() { return 0; };
    };


    /// <summary>
    /// BOUNDING_BOX base. Currently only inherited by OBB, will implement AABB if needed
    /// </summary>
    class BOUNDING_BOX : public COLLIDER_BASE
    {
    public:
        BOUNDING_BOX() {};
        virtual void Collide(BOUNDING_BOX& tar) {};
    };

#pragma endregion
#pragma region SPHERE

    /// <summary>
    /// SPHERE Collider
    /// </summary>
    class SPHERE : public COLLIDER_BASE
    {
        VECTOR3 center;
        float radius;
        std::shared_ptr<MODEL>cube;
    public:
        SPHERE(VECTOR3 pos, float rad);
        void Execute(XMMATRIX mat) override;
        void Render() override;
        bool Collide(COLLIDER_BASE* other) override;
        bool Collide(VECTOR3 p) override;
        VECTOR3 Center();
        float Radius();
        float Size() override { return radius; }

        void SetCenter(VECTOR3 v);
        void SetRadius(float rad);
        void SetData(COMPONENT_DATA* data) override;

    };

#pragma endregion
#pragma region OBB

    class OBB : public BOUNDING_BOX
    {
        std::vector<VECTOR3>points;
        VECTOR3 oriMin, oriMax;
        VECTOR3 rotation;

        /// <summary>
        /// Update the coordinates of each of the points
        /// </summary>
        /// <param name="mat"></param>
        void UpdatePosition(XMMATRIX mat);
    public:

        // Main Functions
        OBB();
        OBB(VECTOR3 vMin, VECTOR3 vMax);
        /// <summary>
        /// Initializes the collider. Call after creating 
        /// </summary>
        /// <returns></returns>
        HRESULT Initialize() override;
        void Update(VECTOR3 pos, VECTOR3 rot);
        void Execute(XMMATRIX mat) override;
        void Render() override;
        bool Collide(COLLIDER_BASE* other) override;
        bool Collide(VECTOR3 p) override;

        // Sub Functions

        void SetMin(VECTOR3 min);
        void SetMax(VECTOR3 max);
        void SetData(COMPONENT_DATA* d)override;

        std::vector<VECTOR3>Points();
        VECTOR3 Rotation();
        VECTOR3 Center();
        float Size() override;
    

        bool Status();
    };

#pragma endregion
#pragma region CYLINDER

    class CYLINDER : public COLLIDER_BASE
    {
        VECTOR3 top, bottom;
        VECTOR3 center;
        float height;
        float radius;
    public:
        CYLINDER();
        CYLINDER(VECTOR3 tp, VECTOR3 bot, float rad);
        HRESULT Initialize() override;
        void Execute(XMMATRIX mat) override;
        void Render() override;
        bool Collide(COLLIDER_BASE* other) override;
        void SetData(VECTOR3 tp, VECTOR3 bot, float rad);

        VECTOR3 Top();
        VECTOR3 Bottom();
        float Height();
        float Radius();
    };

#pragma endregion
#pragma region CAPSULE

    class CAPSULE : public COLLIDER_BASE
    {
        VECTOR3 center;
        float radius{};
        float height;
    public:
        VECTOR3 Top();
        VECTOR3 Bottom();
        CAPSULE();
        CAPSULE(float rad);
        CAPSULE(VECTOR3 cent, float rad, float ht);
        HRESULT Initialize() override;
        void Execute(XMMATRIX mat) override;
        void Render() override;
        bool Collide(COLLIDER_BASE* other) override;
        bool Collide(VECTOR3 p) override;

        VECTOR3 Center();
        float Radius();
        float Size() override;
        void OffsetCenter(XMMATRIX world);
        void SetCenter(VECTOR3 c);
        void SetRadius(float r);
        void SetHeight(float h);
        void SetData(COMPONENT_DATA* d) override;
    };

#pragma endregion
#pragma region RAYCAST_MANAGER

    /// <summary>
    /// MESH_COLLIDER models are inserted here.
    /// </summary>
    class RAYCAST_MANAGER : public SINGLETON<RAYCAST_MANAGER>
    {
        std::vector<MESH*>meshes;
    public:
        /// <summary>
        /// <para> Inserts the model into the map and allow it to perform collision check </para>
        /// <para> ���f�����}�b�v�ɓo�^���AMESH COLLIDER�̑Ώۓ��ɂȂ�</para>
        /// </summary>
        /// <param name="name"> : Name of model</param>
        /// <param name="m"> : Model pointer</param>
        void Insert(MESH* m);
        /// <summary>
        /// <para> Perform ray casting collision check </para>
        /// <para> ���C�[�L���X�g�𗘗p���ē����蔻����v�Z </para>
        /// </summary>
        /// <param name="startOfRay"> : Starting point of object</param>
        /// <param name="endOfRay"> : Direction of movement</param>
        /// <param name="cur_mesh"> : Pointer of current mesh component. Collision check will not be performed onto this mesh</param>
        /// <param name="rcd"> : Output. RayCastData is stored here. Create a new and put it here</param>
        /// <returns></returns>
        bool Collide(VECTOR3 startOfRay, VECTOR3 endOfRay, MESH* cur_mesh, RAYCASTDATA& rcd);
        /// <summary>
        /// <para> Performs ray cast on all models in the vector and returns a list of collided model and collision data </para>
        /// <para> ���f�����X�g�̂��ׂẴ��f�������C�[�L���X�g�����蔻����v�Z���A�����������f���̃��X�g��Ԃ� </para>
        /// </summary>
        /// <param name="cur_mesh"> : Pointer of current mesh component. Collision check will not be performed onto this mesh</param>
        /// <param name="startOfRay"> : Starting point of object</param>
        /// <param name="direction_vector"> : Direction of movement</param>
        /// <param name="rcd"> : Output. RayCastData is stored here. Create a new and put it here</param>
        /// <returns></returns>
        void GetListOfCollided(MESH* cur_Mesh, VECTOR3 startOfRay, VECTOR3 directionVector, std::vector<RAYCASTDATA>& rcd);
        std::vector<MESH*>Meshes();


    };

#pragma endregion
    /// <summary>
    /// <para> Calculates a point on a line that is closest to the target point </para>
    /// <para> �ڕW�_�Ɉ�ԋ߂��_���v�Z </para>
    /// </summary>
    /// <param name="top"> : Starting point of vector</param>
    /// <param name="bot"> : Ending point of vector</param>
    /// <returns></returns>
    VECTOR3 PointLineClosest(VECTOR3 top, VECTOR3 bot, VECTOR3 target);
    /// <summary>
    /// <para> Calculates a point on a line that is closest to the target point </para>
    /// <para> �ڕW�_�Ɉ�ԋ߂��_���v�Z </para>
    /// </summary>
    /// <param name="top"> : Starting point of vector</param>
    /// <param name="bot"> : Ending point of vector</param>
    /// <returns></returns>
    VECTOR3 PointLineClosest(VECTOR3 origin, CAPSULE* target);
    /// <summary>
    /// <para> Performs axis casting, where each point is casted onto the axis, and is compared </para>
    /// <para> �e�_�����ɃL���X�g���Ĕ�r����� </para>
    /// </summary>
    /// <param name="oriMin"> �F Minimum point of first collider</param>
    /// <param name="oriMax"> �F Maximum point of first collider</param>
    /// <param name="tarMin"> �F Minimum point of second collider</param>
    /// <param name="tarMax"> �F Maximum point of second collider</param>
    /// <param name="rotation"> : Rotation of first collider</param>
    /// <param name="colCount"> : Output. Shows how many time it is a hit</param>
    void AxisCasting(VECTOR3 oriMin, VECTOR3 oriMax, VECTOR3 tarMin, VECTOR3 tarMax, VECTOR3 rotation, int* colCount);
    /// <summary>
    /// <para> Performs collision check between 2 OBBs </para>
    /// <para> 2��OBB�ɓ����蔻����v�Z </para>
    /// </summary>
    /// <returns></returns>
    bool OBBCollision(OBB* ori, OBB* tar);
    /// <summary>
    /// <para> Perform Raycasting </para>
    /// <para> ���C�[�L���X�g���v�Z </para>
    /// </summary>
    /// <param name="s"> : Starting point of ray</param>
    /// <param name="e"> : Direction of ray</param>
    /// <param name="m"> : Target model</param>
    /// <param name="hr"> : Output. RayCastData is stored here. Create a new and put it here</param>
    /// <returns></returns>
    bool RayCast(VECTOR3& s, VECTOR3& e, MODEL* m, RAYCASTDATA& hr);
    
}