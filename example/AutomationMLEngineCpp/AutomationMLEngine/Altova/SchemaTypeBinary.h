////////////////////////////////////////////////////////////////////////
//
// SchemaTypeBinary.h
//
// This file was generated by XMLSpy 2008 Enterprise Edition.
//
// YOU SHOULD NOT MODIFY THIS FILE, BECAUSE IT WILL BE
// OVERWRITTEN WHEN YOU RE-RUN CODE GENERATION.
//
// Refer to the XMLSpy Documentation for further details.
// http://www.altova.com/xmlspy
//
////////////////////////////////////////////////////////////////////////


#ifndef ALTOVA_SCHEMATYPEBINARY_H_INCLUDED
#define ALTOVA_SCHEMATYPEBINARY_H_INCLUDED

#if _MSC_VER > 1000
	#pragma once
#endif // _MSC_VER > 1000

#include "SchemaTypes.h"


namespace altova {


////////////////////////////////////////////////////////////////////////
//
//  CSchemaBinaryBase
//
////////////////////////////////////////////////////////////////////////


class ALTOVA_DECLSPECIFIER CSchemaBinaryBase : public CSchemaType
{
public:
	// Construction and destruction
	CSchemaBinaryBase();
	CSchemaBinaryBase( const CSchemaBinaryBase& rOther );
	CSchemaBinaryBase( const unsigned char* pData, size_t nSize );

	virtual ~CSchemaBinaryBase();

	// Operations
	size_t									GetSize() const	{ return m_nSize; }
	const unsigned char*					GetData() const	{ return m_pData; }
	unsigned char*							GetData()		{ return m_pData; }

	void									SetData(const unsigned char* pData, size_t nSize);

	// ---------- Interface CSchemaType ----------
	friend class CSchemaType;
	// Operators
	virtual bool							ToBool() const;
	virtual operator						tstring() const = 0;

	// Operations
	virtual void							Empty();
	virtual bool							Parse( const TCHAR* szValue ) = 0;
	virtual CSchemaType&					Assign( const CSchemaType& rOther );

	typedef const TCHAR* basetype;
	#define	CSchemaBinaryBase_BASETYPE_LPCTSTR
protected:
	void									Clone( const CSchemaBinaryBase& rOther );
	void									Clone( const unsigned char* pData, size_t nSize );


	size_t									m_nSize;
	unsigned char*							m_pData;

};


////////////////////////////////////////////////////////////////////////
//
//  CSchemaHexBinary
//
////////////////////////////////////////////////////////////////////////


class ALTOVA_DECLSPECIFIER CSchemaHexBinary : public CSchemaBinaryBase
{
public:
	CSchemaHexBinary() {};
	CSchemaHexBinary( const CSchemaBinaryBase& rOther ) : CSchemaBinaryBase( rOther ) {};
	CSchemaHexBinary( const unsigned char* pData, size_t nSize ) : CSchemaBinaryBase( pData, nSize ) {};
	CSchemaHexBinary( const TCHAR* szValue )	{ Parse(szValue); }
	CSchemaHexBinary( const tstring& sValue ) { Parse(sValue.c_str()); }
	CSchemaHexBinary( const CSchemaType& rOther )	{ Assign( rOther ); }

	// Operations
	/*virtual*/ CSchemaHexBinary& operator=(const CSchemaType& rOther) { return (CSchemaHexBinary&)Assign(rOther); }
	/*virtual*/ CSchemaHexBinary& operator=(const CSchemaHexBinary& rOther)	{ return (CSchemaHexBinary&)Assign(rOther); }

	// ---------- Interface CSchemaType --------
	friend class CSchemaType;
	// Operators
	virtual operator tstring() const;
	// Operations
	virtual bool							Parse(const TCHAR* szValue);
	virtual CSchemaType&					Assign(const CSchemaType& rOther);

	enum { TYPE = CSchemaType::k_HexBinary };
	typedef const TCHAR*					basetype;
	#define	CSchemaHexBinary_BASETYPE_LPCTSTR
protected:
	static const TCHAR						sm_EncodeArray[];
	static const char						sm_DecodeArray[];
};


////////////////////////////////////////////////////////////////////////
//
//  CSchemaBase64Binary
//
////////////////////////////////////////////////////////////////////////


class ALTOVA_DECLSPECIFIER CSchemaBase64Binary : public CSchemaBinaryBase
{
public:
	CSchemaBase64Binary()  {};
	CSchemaBase64Binary( const CSchemaBinaryBase& rOther ) : CSchemaBinaryBase( rOther ) {};
	CSchemaBase64Binary( const unsigned char* pData, size_t nSize ) : CSchemaBinaryBase( pData, nSize ) {};
	CSchemaBase64Binary( const TCHAR* szValue );
	CSchemaBase64Binary( const CSchemaType& rOther )	{ Assign( rOther ); }

	// Operations
	/*virtual*/ CSchemaBase64Binary& operator=( const CSchemaType& rOther )	{ return (CSchemaBase64Binary&)Assign( rOther ); }
	/*virtual*/ CSchemaBase64Binary& operator=( const CSchemaBase64Binary& rOther )	{ return (CSchemaBase64Binary&)Assign( rOther ); }

	// ---------- Interface CSchemaType --------
	friend class CSchemaType;
	// Operators
	virtual operator tstring() const;
	// Operations
	virtual bool							Parse( const TCHAR* szValue );
	virtual CSchemaType&					Assign( const CSchemaType& rOther );

	enum { TYPE = CSchemaType::k_Base64Binary };
	typedef const TCHAR*					basetype;
	#define	CSchemaBase64Binary_BASETYPE_LPCTSTR
protected:
	void									Encode( unsigned char* pSrc, size_t nSrcSize, TCHAR*& rszDst, size_t& rnDstSize, size_t nMaxLineLength = 76 ) const;
	void									Decode( const TCHAR* szSrc, unsigned char*& rpDst, size_t& rnDstSize );

	static const TCHAR						sm_EncodeArray[];
	static const char						sm_DecodeArray[];
};



} // namespace altova


#endif // ALTOVA_SCHEMATYPEBINARY_H_INCLUDED