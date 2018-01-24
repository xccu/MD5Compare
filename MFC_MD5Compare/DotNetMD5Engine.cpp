#include "stdafx.h"
#include "DotNetMD5Engine.h"

void DotNetMD5Engine::SetSourceStr(wstring sourceStr)
{
	m_sourceStr = sourceStr;
}

void DotNetMD5Engine::SetTargetStr(wstring targetStr)
{
	m_targetStr = targetStr;
}

BOOL DotNetMD5Engine::Compare()
{
	MD5 ^md5 = gcnew MD5();
	MD5KeyType ^key;

	String^ cSoucre = marshal_as<String^>(m_sourceStr);
	String^ cTarget = marshal_as<String^>(m_targetStr);

	String^ SourceResult = md5->Encrypt(cSoucre, key->MD5Key);
	String^ TargetResult = md5->Encrypt(cTarget, key->MD5Key);

	if (SourceResult == TargetResult)
		return TRUE;
	return FALSE;
}

Engine DotNetMD5Engine::GetEngineType()
{
	return m_engine;
}
