#ifndef SINGLETONTEMPLATE_H_
#define SINGLETONTEMPLATE_H_

/**
* @namespace MySingletonTemplate
* @brief SingleTonTemplate���O���
*/
namespace MySingletonTemplate
{
	/**
	* @brief �ȒP�ȃN���X�̐���
	* @details �ڍׂȃN���X�̐���
	*/
	template <class T>
	class SingletonTemplate
	{
	public:
		typedef T InstanceType;

	public:
		/**
		* @brief �C���X�^���X�̍쐬
		* @details �g�p�O�Ɉ�x�����Ăяo��
		*/
		static void Create()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new InstanceType();
			}
		}

		/**
		* @brief �C���X�^���X��j������֐�
		* @details �s�K�v�ɂȂ�����Ăяo��
		*/
		static void Destory()
		{
			if (m_Instance != nullptr)
			{
				delete m_Instance;
				m_Instance = nullptr;
			}
		}

		/**
		* @brief �C���X�^���X��Ԃ��֐�
		* @return InstanceType �C���X�^���X��Ԃ�
		*/
		static InstanceType* GetInstance()
		{
			return m_Instance;
		}


	private:
		//! �C���X�^���X
		static InstanceType* m_Instance;

	private:
		//! �R���X�g���N�^�֎~
		SingletonTemplate() {}
		SingletonTemplate(const SingletonTemplate&);

		virtual ~SingletonTemplate() {}
	};

	template<class T>
	typename SingletonTemplate<T>::InstanceType* SingletonTemplate<T>::m_Instance = nullptr;
}

#endif