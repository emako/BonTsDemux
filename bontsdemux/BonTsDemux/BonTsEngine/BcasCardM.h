// BcasCard.h: CBcasCardM �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <string>
#include <winscard.h>


using std::vector;
using std::wstring;
using std::string;


// �G���[�R�[�h
#define BCEC_NOERROR			0x00000000	// �G���[�Ȃ�
#define BCEC_INTERNALERROR		0x00000001	// �����G���[
#define BCEC_NOTESTABLISHED		0x00000002	// �R���e�L�X�g�m�����s
#define BCEC_NOCARDREADERS		0x00000003	// �J�[�h���[�_���Ȃ�
#define BCEC_ALREADYOPEN		0x00000004	// ���ɃI�[�v���ς�
#define BCEC_CARDOPENERROR		0x00000005	// �J�[�h�I�[�v�����s
#define BCEC_CARDNOTOPEN		0x00000006	// �J�[�h���I�[�v��
#define BCEC_TRANSMITERROR		0x00000007	// �ʐM�G���[
#define BCEC_BADARGUMENT		0x00000008	// �������s��
#define BCEC_ECMREFUSED			0x00000009	// ECM��t����


class CBcasCardM
{
public:
	CBcasCardM();
	~CBcasCardM();

	const DWORD GetCardReaderNum(void) const;
	LPCTSTR GetCardReaderName(const DWORD dwIndex = 0) const;

	const bool OpenCard(LPCTSTR lpszReader = NULL);
	void CloseCard(void);

	const BYTE * GetBcasCardID(void);
	const BYTE * GetInitialCbc(void);
	const BYTE * GetSystemKey(void);
	const BYTE * GetKsFromEcm(const BYTE *pEcmData, const DWORD dwEcmSize);

	const DWORD GetLastError(void) const;

protected:
	const bool EnumCardReader(void);
	const bool TransmitCommand(const BYTE *pSendData, const DWORD dwSendSize, BYTE *pRecvData, const DWORD dwMaxRecv, DWORD *pdwRecvSize = NULL);
	const bool InitialSetting(void);

	SCARDCONTEXT m_ScardContext;
	SCARDHANDLE m_hBcasCard;

	bool m_bIsEstablish;

#ifdef _UNICODE	
	vector<wstring> m_CardReaderArray;
#else
	vector<string> m_CardReaderArray;
#endif

	struct TAG_BCASCARDINFO
	{
		BYTE BcasCardID[6];		// Card ID
		BYTE SystemKey[32];		// Descrambling system key
		BYTE InitialCbc[8];		// Descrambler CBC initial value
	} m_BcasCardInfo;
	
	struct TAG_ECMSTATUS
	{
		DWORD dwLastEcmSize;	// �Ō�ɖ₢���킹�̂�����ECM�T�C�Y
		BYTE LastEcmData[256];	// �Ō�ɖ₢���킹�̂�����ECM�f�[�^
		BYTE KsData[16];		// Ks Odd + Even	
	} m_EcmStatus;
	
	DWORD m_dwLastError;

private:
	const bool StoreEcmData(const BYTE *pEcmData, const DWORD dwEcmSize);
};