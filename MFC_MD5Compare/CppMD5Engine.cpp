#include "stdafx.h"
#include "CppMD5Engine.h"

void CppMD5Engine::SetSourceStr(wstring sourceStr)
{
	m_sourceStr = sourceStr;
}

void CppMD5Engine::SetTargetStr(wstring targetStr)
{
	m_targetStr = targetStr;
}

BOOL CppMD5Engine::Compare()
{
	MD5Encode md5source = MD5Encode(FileCommon::UnicodeToStr(m_sourceStr));
	MD5Encode md5target = MD5Encode(FileCommon::UnicodeToStr(m_targetStr));

	string source = md5source.outstr(32);
	string target = md5target.outstr(32);

	if (source.compare(target) == 0)
		return TRUE;
	return FALSE;
}

Engine CppMD5Engine::GetEngineType()
{
	return m_engine;
}
