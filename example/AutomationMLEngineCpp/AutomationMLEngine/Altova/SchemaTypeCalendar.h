////////////////////////////////////////////////////////////////////////
//
// SchemaTypeCalendar.h
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


#ifndef ALTOVA_SCHEMATYPE_CALENDAR_H_INCLUDED
#define ALTOVA_SCHEMATYPE_CALENDAR_H_INCLUDED

#if _MSC_VER > 1000
	#pragma once
#endif // _MSC_VER > 1000

#include "SchemaTypes.h"
#include <math.h>
#include <time.h>

namespace altova {


////////////////////////////////////////////////////////////////////////
//
//  CSchemaTypeCalendar
//
////////////////////////////////////////////////////////////////////////

class ALTOVA_DECLSPECIFIER CSchemaTypeCalendar
{
public:
	// ---------- Inner Classes ----------

	typedef __int64 TTimeValue;

	static void GetTimeFromTimeValue( TTimeValue tvTime, int& rnHour, int& rnMinute, double& rdSecond );
	static void GetDateFromTimeValue( TTimeValue tvTime, int& rnYear, int& rnMonth, int& rnDay );
	static int GetDayNumberFromTimeValue( TTimeValue tvTime );
	static TTimeValue GetTimeValue( int nYear, int nMonth, int nDay, int nHour, int nMinute, double dSecond, int nTZOffset );

	enum 
	{
		k_PartYear = 1,
		k_PartMonth = 2,
		k_PartDay = 4,
		k_PartDate = 7,
		k_PartTime = 8,
	};

	struct CData 
	{
		int		nYear;	
		unsigned char nMonth;	
		unsigned char nDay;	
		unsigned char nHour;
		unsigned char nMinute;
		double dSecond;
		short	nTimezoneOffset; // timezone offset, from -840 to +840, using -32768 as no timezone.
	};

	static bool ParseDateTime( const TCHAR* szData, unsigned nPartSpec, CData& data );

private:
	static bool IsStdDigit( TCHAR c );
	static bool CheckAndAdvance( const TCHAR*& sz, TCHAR value );
	static bool ReadDigitAndAdvance( const TCHAR*& sz, unsigned& value, unsigned scale, unsigned char maxDigit );

public:


	struct CDuration
	{
		CDuration(
			bool _bPositive = true,
			int	_nYear = 0,
			int	_nMonth = 0,
			int	_nDay = 0,
			int	_nHour = 0,
			int	_nMinute = 0,
			double	_dSecond = 0.0
		)
			: bPositive( _bPositive )
			, nYear( _nYear )
			, nMonth( _nMonth )
			, nDay( _nDay )
			, nHour( _nHour )
			, nMinute( _nMinute )
			, dSecond( _dSecond )
		{};

		bool		bPositive;
		int		nYear;
		int		nMonth;
		int		nDay;
		int		nHour;
		int		nMinute;
		double		dSecond;

		int GetSign() const { return bPositive ? +1 : -1; }
		int GetYearMonthValue() const { return GetSign() * (nYear * 12 + nMonth); }
		TTimeValue GetDayTimeValue() const { return GetSign() * GetTimeValue( 1, 1, nDay + 1, nHour, nMinute, dSecond, 0 ); }

		void SetDayTimeValue(TTimeValue tvDayTimeValue);
		void SetYearMonthValue(int nYearMonthValue);

		void InitZero() { bPositive = true; nYear = 0; nMonth = 0; nDay = 0; nHour = 0; nMinute = 0; dSecond = 0; }

		double	ApproximatedNormalizedSeconds() const
		{
			return ( bPositive ? 1 : -1 ) * ( ((((nYear*12+nMonth)*31+nDay)*24+nHour)*60+nMinute)*60+dSecond );
		}
	};

	struct CDateTimeBase
	{
		enum
		{
			TZ_UTC,
			TZ_Offset,
			TZ_Missing
		};

		CDateTimeBase()
			: nTZMode( TZ_Missing )
			, nOffset( 0 )
		{};

		int	nTZMode;
		int	nOffset;

		bool HasTimezone() const					{ return nTZMode != TZ_Missing; }
		void SetTimezoneUTC( bool bUTC )			{ nTZMode = bUTC ? TZ_UTC : TZ_Missing; nOffset = 0; }
		void SetTimezoneOffset( int offset )		{ nTZMode = TZ_Offset; nOffset = offset; }
		void SetTimezoneMode( int nTZMode )			{ nTZMode = nTZMode; if( nTZMode == TZ_Missing || nTZMode == TZ_UTC) nOffset = 0; }
	};

	struct CDate : public CDateTimeBase
	{
		CDate()
			: nYear( 0 )
			, nMonth( 0 )
			, nDay( 0 )
		{
		};

		CDate(
			int	_nYear,
			int	_nMonth,
			int	_nDay
		)
			: nYear( _nYear )
			, nMonth( _nMonth )
			, nDay( _nDay )
		{};

		int	nYear;
		int	nMonth;
		int	nDay;

		TTimeValue GetTimeValue() const { return CSchemaTypeCalendar::GetTimeValue(nYear, nMonth, nDay, 0, 0, 0, nOffset); }

		long ApproximatedNormalizedDays() const	{ return (nYear*12+nMonth)*31 + nDay; }
	};

	struct CDateTime : public CDateTimeBase
	{
		static CDateTime Now()
		{
			time_t long_time;
			time( &long_time ); 
			struct tm *newtime = localtime( &long_time ); 
			return CDateTime(
				newtime->tm_year + 1900,
				newtime->tm_mon + 1,
				newtime->tm_mday,
				newtime->tm_hour,
				newtime->tm_min,
				newtime->tm_sec);
		}

		CDateTime()
			: nYear( 0 )
			, nMonth( 0 )
			, nDay( 0 )
			, nHour( 0 )
			, nMinute( 0 )
			, dSecond( 0 )
		{
		}

		CDateTime(
			int	_nYear,
			int	_nMonth,
			int	_nDay,
			int	_nHour = 0,
			int	_nMinute = 0,
			double	_dSecond = 0
		)
			: nYear( _nYear )
			, nMonth( _nMonth )
			, nDay( _nDay )
			, nHour( _nHour )
			, nMinute( _nMinute )
			, dSecond( _dSecond )
		{};

		CDateTime(
			int	_nYear,
			int	_nMonth,
			int	_nDay,
			int	_nHour,
			int	_nMinute,
			double	_dSecond,
			int _nTimezone 
		)
			: nYear( _nYear )
			, nMonth( _nMonth )
			, nDay( _nDay )
			, nHour( _nHour )
			, nMinute( _nMinute )
			, dSecond( _dSecond )
		{
			SetTimezoneOffset( _nTimezone );
		};

		CDateTime(
			int	_nYear,
			int	_nMonth,
			int	_nDay,
			int	_nHour,
			int	_nMinute,
			double	_dSecond,
			bool _bIsUTC 
		)
			: nYear( _nYear )
			, nMonth( _nMonth )
			, nDay( _nDay )
			, nHour( _nHour )
			, nMinute( _nMinute )
			, dSecond( _dSecond )
		{
			SetTimezoneUTC( _bIsUTC );
		};

		int	nYear;
		int	nMonth;
		int	nDay;
		int	nHour;
		int	nMinute;
		double	dSecond;

		TTimeValue GetTimeValue() const { return CSchemaTypeCalendar::GetTimeValue(nYear, nMonth, nDay, nHour, nMinute, dSecond, nOffset); }

		double	ApproximatedNormalizedSeconds() const
		{
			return ((((nYear*12+nMonth)*31+nDay)*24+nHour)*60+nMinute)*60+dSecond;
		}
	};

	struct CTime : public CDateTimeBase
	{
		CTime(
			int	_nHour = 0,
			int	_nMinute = 0,
			double	_dSecond = 0.0
		)
			: nHour( _nHour )
			, nMinute( _nMinute )
			, dSecond( _dSecond )
		{};

		CTime(
			int	_nHour,
			int	_nMinute,
			double	_dSecond,
			int _nTimezoneOffset
		)
			: nHour( _nHour )
			, nMinute( _nMinute )
			, dSecond( _dSecond )
		{
			SetTimezoneOffset( _nTimezoneOffset );
		};

		int	nHour;
		int	nMinute;
		double	dSecond;

		TTimeValue GetTimeValue() const { return CSchemaTypeCalendar::GetTimeValue(1, 1, 1, nHour, nMinute, dSecond, nOffset); }

		double NormalizedSeconds() const		{ return nHour * 3600 + nMinute * 60 + dSecond - nOffset * 60; }
	};

	struct CYearMonth : public CDateTimeBase
	{
		CYearMonth()
		{
			time_t long_time;
			time( &long_time ); 
			struct tm *newtime = localtime( &long_time ); 
			nYear = newtime->tm_year + 1900;
			nMonth = newtime->tm_mon + 1;
		};

		CYearMonth(
			int	_nYear,
			int	_nMonth
		)
			: nYear( _nYear )
			, nMonth( _nMonth )
		{};

		int	nYear;
		int	nMonth;

		TTimeValue GetTimeValue() const { return CSchemaTypeCalendar::GetTimeValue(nYear, nMonth, 1, 0, 0, 0, nOffset); }

		long	NormalizedMonths() const { return nYear*12+nMonth; }
	};

	struct CMonthDay : public CDateTimeBase
	{
		CMonthDay()
		{
			time_t long_time;
			time( &long_time ); 
			struct tm *newtime = localtime( &long_time ); 
			nMonth = newtime->tm_mon + 1;
			nDay = newtime->tm_mday;
		};

		CMonthDay(
			int	_nMonth,
			int	_nDay
		)
			: nMonth( _nMonth )
			, nDay( _nDay )
		{};

		int	nMonth;
		int	nDay;

		long ApproximatedNormalizedDays() const	{ return nMonth*31+nDay; }
	};

	struct CYear : public CDateTimeBase
	{
		CYear()
		{
			time_t long_time;
			time( &long_time ); 
			struct tm *newtime = localtime( &long_time ); 
			nYear = newtime->tm_year + 1900;
		};

		CYear( int _nYear )	: nYear( _nYear ) {};

		TTimeValue GetTimeValue() const { return CSchemaTypeCalendar::GetTimeValue(nYear, 1, 1, 0, 0, 0, nOffset); }

		int		nYear;
	};

	struct CMonth : public CDateTimeBase
	{
		CMonth()
		{
			time_t long_time;
			time( &long_time ); 
			struct tm *newtime = localtime( &long_time ); 
			nMonth = newtime->tm_mon + 1;
		};

		CMonth( int _nMonth ) : nMonth( _nMonth ) {};

		int		nMonth;
	};

	struct CDay : public CDateTimeBase
	{
		CDay()
		{
			time_t long_time;
			time( &long_time ); 
			struct tm *newtime = localtime( &long_time ); 
			nDay = newtime->tm_sec;
		};

		CDay( int _nDay ) : nDay( _nDay ) {};

		int		nDay;
	};


	// ---------- Interface ----------
	virtual operator tstring() const = 0;

	virtual operator CDuration() const = 0;
	virtual operator CTime() const = 0;
	virtual operator CDay() const = 0;
	virtual operator CMonth() const = 0;
	virtual operator CMonthDay() const = 0;
	virtual operator CYear() const = 0;
	virtual operator CYearMonth() const = 0;
	virtual operator CDate() const = 0;
	virtual operator CDateTime() const = 0;

	virtual CSchemaType::ETypes CalendarType() const = 0;
	bool	IsConvertableTo(CSchemaType::ETypes eType) const;

	// --------- Helper functions and utilities ---------
	static void				DateTimeAddDuration( int& nYear, int& nMonth, int& nDay, int& nHour, int& nMinute, double& dSecond, const CDuration& dur);

protected:
	static int				ParseInt( const TCHAR** pszData, const TCHAR* szEstimatedType, const TCHAR* szValue, const int nMin = INT_MIN, const int nMax = INT_MAX );
	static double			ParseDouble( const TCHAR** pszData, const TCHAR* szEstimatedType, const TCHAR* szValue );
	static void				ParseChar( const TCHAR** pszData, TCHAR chValue, const TCHAR* szEstimatedType, const TCHAR* szValue );

	static inline double	fQuotient(double a, double b);
	static inline double	fQuotient(double a, double low, double high);
	static inline double	modulo(double a, double b);
	static inline double	modulo(double a, double low, double high);
	static inline bool		isLeapYear(int year);
	static int				maxDayInMonthFor(int year, int month);

	static int				WriteTime( TCHAR* szTarget, size_t count, int nHour, int nMinute, double dSecond );
	static void				ParseTZ( CDateTimeBase& rTimezone, const TCHAR* szValue );
	static void				WriteTZ( const CDateTimeBase& rTimezone, TCHAR* szTarget, size_t count );
};


////////////////////////////////////////////////////////////////////////
//
//  template CSchemaCalendar<...>
//
////////////////////////////////////////////////////////////////////////

template <typename TValue, CSchemaType::ETypes eCalendarType> 
class
#if _MSC_VER >= 1400
	ALTOVA_DECLSPECIFIER
#endif
	CSchemaCalendar : public CSchemaTypeCalendar, public CSchemaType
{
public:
	// Construction
	CSchemaCalendar()																{};
	CSchemaCalendar( const TValue value ) : m_Value( value )						{ SetIsEmpty( false ); };
	CSchemaCalendar( const TCHAR* szValue )											{ Parse( szValue ); }
	CSchemaCalendar( const tstring& szValue )										{ Parse( szValue.c_str() ); }
	CSchemaCalendar( const CSchemaType& rOther )									{ Assign( rOther ); }


	// Operations
	TValue&									GetValue()								{ return m_Value; }
	const TValue&							GetValue() const						{ return m_Value; }
	void									SetValue( TValue value )				{ m_Value = value; SetIsEmpty( false ); }

	virtual CSchemaCalendar& operator=( const CSchemaType& rOther )					{ return ( CSchemaCalendar& )Assign( rOther ); }

	// --------- Interface CSchemaType ----------
	friend class CSchemaType;
	// Operators
	virtual bool							ToBool() const							{ return !IsEmpty(); }
	virtual operator						tstring() const							{ return IsEmpty() ? _T("") : ToString(); }

	// Operations
	virtual void							Empty()
	{
		CSchemaType::Empty();
		m_Value = TValue();
	}

	virtual bool Parse( const TCHAR* sz )
	{
	tstring str = CSchemaType::normalize(CSchemaType::WHITESPACE_COLLAPSE, sz);
	const TCHAR* szValue = str.c_str();

		if( !CSchemaType::Parse( szValue ) )
			return false;

		InternalDTParse( szValue );

		return !IsEmpty();
	}

	virtual CSchemaType&	Assign( const CSchemaType& rOther )
	{
		if( CSchemaType::Assign( rOther ).IsEmpty() )
			return *this;

		const CSchemaTypeCalendar* pCalendarType = dynamic_cast<const CSchemaTypeCalendar*>( &rOther );
		if( pCalendarType == NULL)
			ThrowIncompatibleTypesError();

		m_Value = *pCalendarType;

		return *this;
	}

	// ---------- Interface CSchemaTypeCalendar ----------
	virtual ETypes							CalendarType() const						{ return ( CSchemaType::ETypes )TYPE; }
	virtual operator						CSchemaTypeCalendar::CDuration() const		{ ThrowIncompatibleTypesError(); }
	virtual operator						CSchemaTypeCalendar::CDate() const			{ ThrowIncompatibleTypesError(); }
	virtual operator						CSchemaTypeCalendar::CTime() const			{ ThrowIncompatibleTypesError(); }
	virtual operator						CSchemaTypeCalendar::CDateTime() const		{ ThrowIncompatibleTypesError(); }
	virtual operator						CSchemaTypeCalendar::CYearMonth() const		{ ThrowIncompatibleTypesError(); }
	virtual operator						CSchemaTypeCalendar::CYear() const			{ ThrowIncompatibleTypesError(); }
	virtual operator						CSchemaTypeCalendar::CMonth() const			{ ThrowIncompatibleTypesError(); }
	virtual operator						CSchemaTypeCalendar::CMonthDay() const		{ ThrowIncompatibleTypesError(); }
	virtual operator						CSchemaTypeCalendar::CDay() const			{ ThrowIncompatibleTypesError(); }

	enum { TYPE = eCalendarType };

	typedef const TCHAR*					basetype;

protected:
	tstring									ToString() const							{ return _T(""); }
	void									InternalDTParse( const TCHAR* szValue )		{}

	TValue									m_Value;
};


////////////////////////////////////////////////////////////////////////
//
//  CSchemaDuration
//  CSchemaDate
//  CSchemaTime
//  CSchemaDateTime
//  CSchemaYear
//  CSchemaYearMonth
//  CSchemaMonth
//  CSchemaMonthDay
//  CSchemaDay
//
////////////////////////////////////////////////////////////////////////


typedef CSchemaCalendar< CSchemaTypeCalendar::CDuration, CSchemaType::k_Duration >  CSchemaDuration;
typedef CSchemaCalendar< CSchemaTypeCalendar::CDate,     CSchemaType::k_Date >      CSchemaDate;
typedef CSchemaCalendar< CSchemaTypeCalendar::CTime,     CSchemaType::k_Time >      CSchemaTime;
typedef CSchemaCalendar< CSchemaTypeCalendar::CDateTime, CSchemaType::k_DateTime >  CSchemaDateTime;
typedef CSchemaCalendar< CSchemaTypeCalendar::CYear,     CSchemaType::k_Year >      CSchemaYear;
typedef CSchemaCalendar< CSchemaTypeCalendar::CYearMonth,CSchemaType::k_YearMonth > CSchemaYearMonth;
typedef CSchemaCalendar< CSchemaTypeCalendar::CMonth,    CSchemaType::k_Month >     CSchemaMonth;
typedef CSchemaCalendar< CSchemaTypeCalendar::CMonthDay, CSchemaType::k_MonthDay >  CSchemaMonthDay;
typedef CSchemaCalendar< CSchemaTypeCalendar::CDay,      CSchemaType::k_Day >       CSchemaDay;


#define CSchemaDuration_BASETYPE_LPCTSTR
#define	CSchemaDate_BASETYPE_LPCTSTR
#define	CSchemaTime_BASETYPE_LPCTSTR
#define	CSchemaDateTime_BASETYPE_LPCTSTR
#define	CSchemaYear_BASETYPE_LPCTSTR
#define	CSchemaYearMonth_BASETYPE_LPCTSTR
#define	CSchemaMonth_BASETYPE_LPCTSTR
#define	CSchemaMonthDay_BASETYPE_LPCTSTR
#define	CSchemaDay_BASETYPE_LPCTSTR
#define	CSchemaString_BASETYPE_LPCTSTR

////////////////////////////////////////////////////////////////////////
//
//  CSchemaDuration
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaDuration::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaDuration::ToString() const;

template<>
CSchemaDuration::operator CSchemaTypeCalendar::CDuration() const;


template<>
CSchemaDuration::operator CSchemaTypeCalendar::CTime() const;


////////////////////////////////////////////////////////////////////////
//
//  CSchemaDate
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaDate::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaDate::ToString() const;

template<>
CSchemaDate::operator CSchemaTypeCalendar::CDate() const;

template<>
CSchemaDate::operator CSchemaTypeCalendar::CDateTime() const;

template<>
CSchemaDate::operator CSchemaTypeCalendar::CDay() const;

template<>
CSchemaDate::operator CSchemaTypeCalendar::CMonth() const;

template<>
CSchemaDate::operator CSchemaTypeCalendar::CMonthDay() const;

template<>
CSchemaDate::operator CSchemaTypeCalendar::CYear() const;

template<>
CSchemaDate::operator CSchemaTypeCalendar::CYearMonth() const;


////////////////////////////////////////////////////////////////////////
//
//  CSchemaTime
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaTime::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaTime::ToString() const;

template<>
CSchemaTime::operator CSchemaTypeCalendar::CTime() const;

template<>
CSchemaTime::operator CSchemaTypeCalendar::CDuration() const;


////////////////////////////////////////////////////////////////////////
//
//  CSchemaDateTime
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaDateTime::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaDateTime::ToString() const;

template<>
CSchemaDateTime::operator CSchemaTypeCalendar::CDateTime() const;

template<>
CSchemaDateTime::operator CSchemaTypeCalendar::CDate() const;

template<>
CSchemaDateTime::operator CSchemaTypeCalendar::CDay() const;

template<>
CSchemaDateTime::operator CSchemaTypeCalendar::CMonth() const;

template<>
CSchemaDateTime::operator CSchemaTypeCalendar::CMonthDay() const;

template<>
CSchemaDateTime::operator CSchemaTypeCalendar::CTime() const;

template<>
CSchemaDateTime::operator CSchemaTypeCalendar::CYear() const;

template<>
CSchemaDateTime::operator CSchemaTypeCalendar::CYearMonth() const;

////////////////////////////////////////////////////////////////////////
//
//  CSchemaYear
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaYear::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaYear::ToString() const;

template<>
CSchemaYear::operator CSchemaTypeCalendar::CYear() const;


////////////////////////////////////////////////////////////////////////
//
//  CSchemaYearMonth
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaYearMonth::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaYearMonth::ToString() const;

template<>
CSchemaYearMonth::operator CSchemaTypeCalendar::CYearMonth() const;

template<>
CSchemaYearMonth::operator CSchemaTypeCalendar::CMonth() const;

template<>
CSchemaYearMonth::operator CSchemaTypeCalendar::CYear() const;

////////////////////////////////////////////////////////////////////////
//
//  CSchemaMonth
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaMonth::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaMonth::ToString() const;

template<>
CSchemaMonth::operator CSchemaTypeCalendar::CMonth() const;

////////////////////////////////////////////////////////////////////////
//
//  CSchemaMonthDay
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaMonthDay::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaMonthDay::ToString() const;

template<>
CSchemaMonthDay::operator CSchemaTypeCalendar::CMonthDay() const;

template<>
CSchemaMonthDay::operator CSchemaTypeCalendar::CDay() const;

template<>
CSchemaMonthDay::operator CSchemaTypeCalendar::CMonth() const;


////////////////////////////////////////////////////////////////////////
//
//  CSchemaDay
//
////////////////////////////////////////////////////////////////////////
template<>
void CSchemaDay::InternalDTParse( const TCHAR* szValue );

template<>
tstring CSchemaDay::ToString() const;

template<>
CSchemaDay::operator CSchemaTypeCalendar::CDay() const;


////////////////////////////////////////////////////////////////////////
//
//  Operators
//
////////////////////////////////////////////////////////////////////////

bool			ALTOVA_DECLSPECIFIER operator ==( const CSchemaDate& t1, const CSchemaDate& t2 );
bool 			ALTOVA_DECLSPECIFIER operator <	( const CSchemaDate& t1, const CSchemaDate& t2 );
bool 			ALTOVA_DECLSPECIFIER operator !=( const CSchemaDate& t1, const CSchemaDate& t2 );
bool 			ALTOVA_DECLSPECIFIER operator <=( const CSchemaDate& t1, const CSchemaDate& t2 );
bool 			ALTOVA_DECLSPECIFIER operator >	( const CSchemaDate& t1, const CSchemaDate& t2 );
bool 			ALTOVA_DECLSPECIFIER operator >=( const CSchemaDate& t1, const CSchemaDate& t2 );

bool 			ALTOVA_DECLSPECIFIER operator ==( const CSchemaTime& t1, const CSchemaTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator <	( const CSchemaTime& t1, const CSchemaTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator !=( const CSchemaTime& t1, const CSchemaTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator <=( const CSchemaTime& t1, const CSchemaTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator >	( const CSchemaTime& t1, const CSchemaTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator >=( const CSchemaTime& t1, const CSchemaTime& t2 );

bool 			ALTOVA_DECLSPECIFIER operator ==( const CSchemaDateTime& t1, const CSchemaDateTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator <	( const CSchemaDateTime& t1, const CSchemaDateTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator !=( const CSchemaDateTime& t1, const CSchemaDateTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator <=( const CSchemaDateTime& t1, const CSchemaDateTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator >	( const CSchemaDateTime& t1, const CSchemaDateTime& t2 );
bool 			ALTOVA_DECLSPECIFIER operator >=( const CSchemaDateTime& t1, const CSchemaDateTime& t2 );

CSchemaDuration	ALTOVA_DECLSPECIFIER operator +	( const CSchemaDuration& dur1, const CSchemaDuration& dur2 );
CSchemaDate		ALTOVA_DECLSPECIFIER operator +	( const CSchemaDate& t, const CSchemaDuration& dur );
CSchemaDuration	ALTOVA_DECLSPECIFIER operator -	( const CSchemaDate& t1, const CSchemaDate& t2 );
CSchemaTime		ALTOVA_DECLSPECIFIER operator +	( const CSchemaTime& t, const CSchemaDuration& dur );
CSchemaDuration	ALTOVA_DECLSPECIFIER operator -	( const CSchemaTime& t1, const CSchemaTime& t2 );
CSchemaDateTime	ALTOVA_DECLSPECIFIER operator +	( const CSchemaDateTime& t, const CSchemaDuration& dur );
CSchemaDuration	ALTOVA_DECLSPECIFIER operator -	( const CSchemaDateTime& t1, const CSchemaDateTime& t2 );

#if _MSC_VER >= 1400
template CSchemaCalendar< CSchemaTypeCalendar::CDuration, CSchemaType::k_Duration >;
template CSchemaCalendar< CSchemaTypeCalendar::CDate,		CSchemaType::k_Date >;
template CSchemaCalendar< CSchemaTypeCalendar::CTime,		CSchemaType::k_Time >;
template CSchemaCalendar< CSchemaTypeCalendar::CDateTime, CSchemaType::k_DateTime >;
template CSchemaCalendar< CSchemaTypeCalendar::CYear,		CSchemaType::k_Year >;
template CSchemaCalendar< CSchemaTypeCalendar::CYearMonth,CSchemaType::k_YearMonth >;
template CSchemaCalendar< CSchemaTypeCalendar::CMonth,	CSchemaType::k_Month >;
template CSchemaCalendar< CSchemaTypeCalendar::CMonthDay, CSchemaType::k_MonthDay >;
template CSchemaCalendar< CSchemaTypeCalendar::CDay,		CSchemaType::k_Day >;
#endif


} // namespace altova

#endif // ALTOVA_SCHEMATYPE_CALENDAR_H_INCLUDED