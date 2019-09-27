////////////////////////////////////////////////////////////////////////
//
// InternalXML.h
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


#ifndef INTERNAL_XML_H_INCLUDED
#define INTERNAL_XML_H_INCLUDED

#if _MSC_VER > 1000
	#pragma once
#endif // _MSC_VER > 1000

namespace altova {

class ALTOVAXML_DECLSPECIFIER InternalXML
{
public:
	static tstring XMLToString( xercesc::DOMDocument* pXMLTree );
	static std::vector< unsigned char > XMLToBase64Binary( xercesc::DOMDocument* pXMLTree, const tstring& encoding, const tstring& byteorder, bool bBOM );
	static xercesc::DOMDocument* XMLFromString( const tstring& sXMLString );
	static xercesc::DOMDocument* XMLFromBase64Binary( const std::vector< unsigned char >& sXMLString );
};



} // namespace altova

#endif // ALTOVA_NODE_H_INCLUDED
