///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright Test Competence Center (TCC) ETH 2008                           //
//                                                                           //
// The copyright to the computer  program(s) herein  is the property of TCC. //
// The program(s) may be used and/or copied only with the written permission //
// of TCC or in accordance with  the terms and conditions  stipulated in the //
// agreement/contract under which the program(s) have been supplied          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
//  File:               TCCXPathSupport_Functions.ttcn
//  Description:        TCC Useful Functions: XPath Support Functions
//  Rev:                R25A
//  Prodnr:             CNL 113 472
//  Updated:            2008-08-26
//  Contact:            http://ttcn.ericsson.se
//
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "tinyxml.h"
#include "xpath_processor.h"

#include "TCCXPathSupport_Functions.hh"


///////////////////////////////////////////////////////////////////////////////
//  Function: XPathQuery
// 
//  Purpose:
//    apply an XPath query on an XML document
// 
//  Parameters:
//    xml_doc: the XML document to be processed. It is modeled by a pure TTCN-3
//                universal charstring and passed as an input parameter to this 
//                function
//
//    xpath_query: the XPath Query. With this technology we can access a node of
//                    the XML tree. It is passed to the function as a universal 
//                    charstring
//  
//  Return Value:
//    universal charstring - result of the query (information about one node of
//                              the XML tree)
// 
//  Errors:
//    - 
// 
//  Detailed description:
//    -
// 
///////////////////////////////////////////////////////////////////////////////

namespace TCCXPathSupport__Functions { 

char * extract_string(const UNIVERSAL_CHARSTRING & us)
{
  TTCN_Buffer buf;
  us.encode_utf8(buf);
  
  
  size_t len = buf.get_len();
  char * return_string = (char*) Malloc(len+1);
  memcpy(return_string,buf.get_data(),len);
  return_string[len] = '\0';
  
  return return_string;
}

UNIVERSAL_CHARSTRING XPathQuery(const UNIVERSAL_CHARSTRING& xml__doc, const UNIVERSAL_CHARSTRING& xpath__query)
{
  
	char* xml_document = extract_string( xml__doc );
  char* xpath_query  = extract_string( xpath__query );
  
      
  TiXmlDocument * XDp_doc  = new TiXmlDocument();
  
  XDp_doc->Parse( xml_document );
	  
  TiXmlElement  * XEp_root = XDp_doc->RootElement();
  
  
  
  TinyXPath::xpath_processor *proc = new TinyXPath::xpath_processor( XEp_root, xpath_query );
      
  TIXML_STRING res = proc->S_compute_xpath(); 
  
	
  
  delete XDp_doc;
  delete proc;
  Free(xml_document);
  Free(xpath_query);

  
  UNIVERSAL_CHARSTRING result;
  result.decode_utf8(res.size(),(const unsigned char*)res.c_str());
  return result;

}

BOOLEAN XPathCheckXML(const UNIVERSAL_CHARSTRING& xml__doc, CHARSTRING& error__string){
	char* xml_document = extract_string( xml__doc );
  TiXmlDocument * XDp_doc  = new TiXmlDocument();
  
  XDp_doc->Parse( xml_document );

  bool ret_val= ! XDp_doc->Error();
  if(ret_val){ // no error
    error__string="OK";
  } else { // error
    char * e_str=mprintf("Error at line: %d, pos: %d, description: %s",XDp_doc->ErrorRow(),XDp_doc->ErrorCol(),XDp_doc->ErrorDesc());
    error__string=e_str;
    Free(e_str);
  }
  delete XDp_doc;
  Free(xml_document);
  return ret_val;
}


}
