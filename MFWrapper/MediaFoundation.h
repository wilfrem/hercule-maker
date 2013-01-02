#pragma once
namespace Wilfrem
{
namespace HerculeMaker
{
namespace MFWrapper
{
	//Media Foundation���p�J�n�E�I�����̏������s���N���X�B
	ref class MediaFoundation sealed{
	private:
		static MediaFoundation^ m_instance;
		MediaFoundation();
	public:
		virtual ~MediaFoundation();
		static property MediaFoundation^ Instance{
			MediaFoundation^ get(){
				if(m_instance == nullptr){
					m_instance = ref new MediaFoundation();
				}
				return m_instance;
			}
		}

	};
}
}
}