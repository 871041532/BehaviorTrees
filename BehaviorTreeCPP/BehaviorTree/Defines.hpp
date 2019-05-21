#pragma once
#include <stdio.h>

typedef unsigned int uint;
#define D_Inline inline
#define D_Output printf
#define D_SafeDelete(p)	 if(p)	{ delete p; p = nullptr; }

D_Inline void InnerAssertion(const char* _strExpr, const char* _strFile, int _iLine)
{
	D_Output("Assert failed: %s in %s : %d\n", _strExpr, _strFile, _iLine);

	//TJQ: cause crash
	*reinterpret_cast<int*>(0) = 0;
}

//#ifdef TLIB_DEBUG
#if defined(ASSERT_LEVEL)
#define D_CHECK_P(S,P)	\
		if(P >= ASSERT_LEVEL)	\
			(void)((S) || (InnerAssertion(#S, __FILE__, __LINE__), 0));
#else
#define D_CHECK_P(S,P) (void)((S) || (InnerAssertion(#S, __FILE__, __LINE__), 0));
#endif

#define D_CHECK(S)	D_CHECK_P(S,0)

class AnyData
{
public:
	template<typename RealDataType>
	AnyData(RealDataType* data)
		: m_RealData(data)
	{}
	template<typename RealDataType>
	RealDataType& GetRealDataType() {
		D_CHECK(m_RealData);
		return *reinterpret_cast<RealDataType*>(m_RealData);
	}
	template<typename RealDataType>
	const RealDataType& GetRealDataType() const {
		D_CHECK(m_RealData);
		return *reinterpret_cast<const RealDataType*>(m_RealData);
	}
	template<typename RealDataType>
	AnyData& operator =(RealDataType* _Data)
	{
		Set<RealDataType>(_Data);
		return *this;
	}
private:
	template<typename RealDataType>
	void Set(RealDataType* _Data)
	{
		m_RealData = reinterpret_cast<void*>(_Data);
	}
private:
	void* m_RealData;
};