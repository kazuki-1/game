#pragma once
#include "MODEL.h"
#include "Engine/Singleton.h"
#include "Engine/DXMath.h"
#include "OBJECT_DATA.h"

class COMPONENT;


/*------------------------------------------GAMEOBJECT--------------------------------------------*/

/// <summary>
/// <para>GAMEOBJECT class. This one is for 3D objects. To Create 2D objects, create GAMEOBJECT_2D </para>
/// <para>3D�Q�[���I�u�W�F�N�g�B�QD�Q�[���I�u�W�F�N�g�̏ꍇ�ɂ�GAMEOBJECT_2D���g�p </para>
/// </summary>
class GAMEOBJECT
{
protected:
    //  Data for loading file is stored here 
    // �X�e�[�W�f�[�^�ǂݍ��݃f�[�^���i�[����
    std::shared_ptr<OBJECT_DATA>data;

    // List of components
    // �R���|�l���g���X�g
    std::vector<std::shared_ptr<COMPONENT>>components;
    char name_buffer[256] = "";

    friend class OBJECT_DATA;

    void __InternalAddComponent(COMPONENT_TYPE t);
    void __InternalAddComponent(COMPONENT_TYPE t, std::shared_ptr<COMPONENT_DATA>d);
public:
    GAMEOBJECT() {};
    GAMEOBJECT(std::shared_ptr<OBJECT_DATA>d);
    ~GAMEOBJECT() {}
    /// <summary>
    /// <para> virtual function. Initializes the gameObject by creating components from the data member</para>
    /// <para>�@���z�֐��B�f�[�^���g���ăQ�[���I�u�W�F�N�g�̃R���|�l���g�𐶐�
    /// </summary>
    /// <returns></returns>
    virtual HRESULT Initialize();
    /// <summary>
    /// <para> Virtual function. Performs the Execute() function in each component </para>
    /// <para> ���z�֐��B�e�R���|�l���g��Execute()�֐����Ăяo��
    /// </summary>
    virtual void Execute();
    /// <summary>
    /// <para> Virtual function. Calls the Render() function in each component </para>
    /// <para> ���z�֐��B�e�R���|�l���g��Render()�֐����Ăяo���B</para>
    /// </summary>
    virtual void Render();
    /// <summary>
    /// <para> Adds a component to the gameObject </para>
    /// <para> �Q�[���I�u�W�F�N�g�ɃR���|�l���g��ǉ�</para>
    /// </summary>
    void AddComponent(COMPONENT_TYPE t);
    void RemoveComponent(int id);
    template <class T>
    T* GetComponent(int id = 0)
    {
        int ind{};
        for (auto& c : components)
        {
            T* t = dynamic_cast<T*>(c.get());
            if (t && ind == id)
                return t;
            else if (t)
                ++ind;
        }
        return nullptr;
    }
    std::vector<std::shared_ptr<COMPONENT>>Components();
    std::shared_ptr<OBJECT_DATA>Data();
};

/*------------------------------------------GAMEOBJECT_MANAGER--------------------------------------------*/

class GAMEOBJECT_MANAGER : public SINGLETON<GAMEOBJECT_MANAGER>
{
    std::map<std::string, std::shared_ptr<GAMEOBJECT>>gameObjects;
public:
    /// <summary>
    /// <para> Initializes all the gameObjects in the map </para>
    /// <para> �}�b�v�����ׂẴQ�[���I�u�W�F�N�g�����Z�b�g���� </para>
    /// </summary>
    void Initialize();
    /// <summary>
    /// <para> Called every frame to perform Execute() of all gameObjects and its components </para>
    /// <para> �Q�[���I�u�W�F�N�g�y�т��̃R���|�l���g��Execute()�֐����Ăяo���悤�ɖ��t���[���ɌĂяo�� </para>
    /// </summary>
    void Execute();
    /// <summary>
    /// <para> Called every frame to perform Render() of all gameObjects and its components </para>
    /// <para> �Q�[���I�u�W�F�N�g�y�т��̃R���|�l���g��Render()�֐����Ăяo���悤�ɖ��t���[���ɌĂяo�� </para>
    /// </summary>
    void Render();
    /// <summary>
    /// <para> Generally unneeded. Called when closing to finalize all gameObjects</para>
    /// <para> ��{�I�ɕK�v�Ȃ��B�Q�[�����I�����ɃQ�[���I�u�W�F�N�g���I����������悤�ɌĂяo���B</para>
    /// </summary>
    void Finalize();



    /// <summary>
    /// <para> Create a gameObject and insert it into the map </para>
    /// <para> �Q�[���I�u�W�F�N�g�𐶐����ă}�b�v�ɓo�^���� </para>
    /// </summary>
    /// <param name="n"> : Name of gameObject</param>
    /// <param name="d"> : Dataset of gameObject with data of components</param>
    void Insert(std::string n, std::shared_ptr<OBJECT_DATA>d);
    /// <summary>
    /// <para> Remove the gameObject from the map, and from the game </para>
    /// <para> �Q�[���I�u�W�F�N�g���}�b�v�y�уQ�[������폜���� </para>
    /// </summary>
    /// <param name="name"> : name of gameObject to remove</param>
    void Remove(std::string name);
    void Remove(std::shared_ptr<GAMEOBJECT>gameObject);
    void Clear();
    std::shared_ptr<GAMEOBJECT>Retrieve(std::string);
    std::string RetrieveName(std::shared_ptr<GAMEOBJECT>go);
    std::map<std::string, std::shared_ptr<GAMEOBJECT>>GameObjects();
};


