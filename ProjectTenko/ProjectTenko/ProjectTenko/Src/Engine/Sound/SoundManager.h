#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <dsound.h>
#include <unordered_map>
#include <string>

class SoundManager
{
public:
	/**
	* @brief �T�E���h�������֐�
	* DirectSound���g�p�\�ɂ��邽�ߏ��������s���܂�
	* @return �����̏ꍇ��true�A���s�����ꍇ��false
	*/
	bool Init(HWND hw_);

	/**
	* @biref �T�E���h�J���֐�
	* �ǂݍ��񂾃f�[�^��DirectSound�̉�����s���܂�
	*/
	void Release();

	/**
	* @brief wave�f�[�^�̓ǂݍ��݊֐�
	* �w�肵���p�X��wave�f�[�^���Z�J���_���E�o�b�t�@�ɓǂݍ��݂܂�
	* @return ���������ꍇ��true�A�����łȂ��Ȃ�false
	* @param[in] file_name �ǂݍ��ރp�X���܂ރt�@�C����
	* @param[in] key_name �ǂݍ��ރf�[�^���Ǘ�����L�[
	*/
	bool LoadSound(std::string filename_, std::string keyname_);

	/**
	* @brief �T�E���h�Đ��֐�
	* �w�肵���Z�J���_���E�o�b�t�@�̃T�E���h���Đ����܂�
	* @param[in] key_ �Đ��������T�E���h�̃L�[
	*/
	void Play(std::string key_);

	/**
	* @brief �T�E���h��~�֐�
	* �w�肵���Z�J���_���E�o�b�t�@�̃T�E���h���~���܂�
	* @param[in] key_ ��~�������T�E���h�̃L�[
	*/
	void Stop(std::string key_);

private:
	/**
	* @biref �R���X�g���N�^
	*/
	SoundManager() : m_Interface(nullptr) { }

	/**
	* @biref �f�X�g���N�^
	*/
	~SoundManager() { }

	/**
	* @biref �L�[�`�F�b�N�֐�
	* �����̃L�[�����ɓo�^����Ă��邩�m�F����֐��ł�
	* @return �o�^�ς݂̏ꍇ��true�A���o�^��false
	* @param[in] key_ �m�F����L�[
	*/
	bool HasKey(std::string key_);

private:
	LPDIRECTSOUND8 m_Interface;
	std::unordered_map<std::string, LPDIRECTSOUNDBUFFER8> m_SoundData;
};

#endif // !SOUNDMANAGER_H_
