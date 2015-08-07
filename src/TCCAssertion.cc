/******************************************************************************
* Copyright (c) 2004, 2015  Ericsson AB
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v1.0
* which accompanies this distribution, and is available at
* http://www.eclipse.org/legal/epl-v10.html

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
//
//  File:               TCCAssertion.cc
//  Description:        TCC Useful Functions: Assert Functions
//  Rev:                R22B
//  Prodnr:             CNL 113 472
//  Updated:            2007-11-12
//  Contact:            http://ttcn.ericsson.se
//
///////////////////////////////////////////////////////////////////////////////

#include "TCCAssertion_Functions.hh"

namespace TCCAssertion__Functions 
{
  
///////////////////////////////////////////////////////////////////////////////
//  Function: f__assert
// 
//  Purpose:
//    Implement TTCN assertion. 
//
//  Parameters:
//    pl__assertMessage - *in* *charstring* - assertion message
//    pl__predicate - *in* *boolean* - boolean predicate
// 
//  Return Value:
//    -
//
//  Errors:
//    - 
// 
//  Detailed description:
//    At the point of this function call, the assertion predicate must be true,
//    else assertion fails that results in a dynamic test case error
//    To use assertion optimized build shall be switched on with switch -O2 and
//    NDEBUG shall not be defined
// 
///////////////////////////////////////////////////////////////////////////////
  void f__assert(const CHARSTRING& pl__assertMessage, const BOOLEAN& pl__predicate)
  {
    #ifdef NDEBUG
    #else
    if (!(pl__predicate)) {
      TTCN_error("Assertion failed: %s!",(const char*)pl__assertMessage);  
    }
    #endif
  }
}
