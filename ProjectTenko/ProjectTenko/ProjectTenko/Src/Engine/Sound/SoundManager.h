#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <dsound.h>
#include <unordered_map>
#include <string>

struct SoundData
{
	SoundData(LPDIRECTSOUNDBUFFER8 buff_) : m_SoundData(buff_)
	{}

	SoundData() : m_SoundData(nullptr)
	{}

	LPDIRECTSOUNDBUFFER8 m_SoundData;
	std::vector<LPDIRECTSOUNDBUFFER8> m_CopyData;
};

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
	* �w�肵���p�X��wave�f�[�^���Z�J���_���E�o�b�t�@�ɓǂݍ��݂܂��B�d�����čĐ�����K�v�̂Ȃ������ɂ̂ݎg�p���Ă��������B
	* @return ���������ꍇ��true�A�����łȂ��Ȃ�false
	* @param[in] file_name �ǂݍ��ރp�X���܂ރt�@�C����
	* @param[in] key_name �ǂݍ��ރf�[�^���Ǘ�����L�[
	*/
	bool LoadBGMData(std::string filename_, std::string keyname_);

	/**
	* @brief wave�f�[�^�̓ǂݍ��݊֐�
	* �w�肵���p�X��wave�f�[�^���Z�J���_���E�o�b�t�@�ɓǂݍ��݂܂��B�d�����čĐ�����K�v�̂��鉹���ɂ̂ݎg�p���Ă��������B
	* @return ���������ꍇ��true�A�����łȂ��Ȃ�false
	* @param[in] file_name �ǂݍ��ރp�X���܂ރt�@�C����
	* @param[in] key_name �ǂݍ��ރf�[�^���Ǘ�����L�[
	*/
	bool LoadSEData(std::string filename_, std::string keynama_);

	/**
	* @brief �T�E���h�Đ��֐�
	* �w�肵��SEData���̃T�E���h���Đ����܂�
	* @param[in] key_ �Đ��������T�E���h�̃L�[
	*/
	void PlaySE(std::string key_, bool isLoop_);

	/**
	* @brief BGM�Đ��֐�
	* �w�肵��BGMData���̃T�E���h���Đ����܂�
	* @param[in] key_ �Đ��������T�E���h�̃L�[
	*/
	void PlayBGM(std::string key_);

	/**
	* @brief �T�E���h��~�֐�
	* �w�肵���Z�J���_���E�o�b�t�@�̃T�E���h���~���܂�
	* @param[in] key_ ��~�������T�E���h�̃L�[
	*/
	void StopBGM(std::string key_);
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
	bool HasKeyBGM(std::string key_);

	/**
	* @biref �L�[�`�F�b�N�֐�
	* �����̃L�[�����ɓo�^����Ă��邩�m�F����֐��ł�
	* @return �o�^�ς݂̏ꍇ��true�A���o�^��false
	* @param[in] key_ �m�F����L�[
	*/
	bool HasKeySE(std::string key_);

private:
	LPDIRECTSOUND8 m_Interface;
	std::unordered_map<std::string, LPDIRECTSOUNDBUFFER8> m_BGMData;
	std::unordered_map<std::string, SoundData> m_SEData;
};

#endif // !SOUNDMANAGER_H_
