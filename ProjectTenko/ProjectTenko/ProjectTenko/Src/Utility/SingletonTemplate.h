#ifndef SINGLETONTEMPLATE_H_
#define SINGLETONTEMPLATE_H_

/**
* @namespace MySingletonTemplate
* @brief SingleTonTemplate名前空間
*/
namespace MySingletonTemplate
{
	/**
	* @brief 簡単なクラスの説明
	* @details 詳細なクラスの説明
	*/
	template <class T>
	class SingletonTemplate
	{
	public:
		typedef T InstanceType;

	public:
		/**
		* @brief インスタンスの作成
		* @details 使用前に一度だけ呼び出す
		*/
		static void Create()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new InstanceType();
			}
		}

		/**
		* @brief インスタンスを破棄する関数
		* @details 不必要になったら呼び出す
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
		* @brief インスタンスを返す関数
		* @return InstanceType インスタンスを返す
		*/
		static InstanceType* GetInstance()
		{
			return m_Instance;
		}


	private:
		//! インスタンス
		static InstanceType* m_Instance;

	private:
		//! コンストラクタ禁止
		SingletonTemplate() {}
		SingletonTemplate(const SingletonTemplate&);

		virtual ~SingletonTemplate() {}
	};

	template<class T>
	typename SingletonTemplate<T>::InstanceType* SingletonTemplate<T>::m_Instance = nullptr;
}

#endif