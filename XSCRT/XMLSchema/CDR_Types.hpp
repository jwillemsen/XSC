// file      : XMLSchema/CDR_Types.hpp
// author    : Arvind S. Krishna <arvindkr@qualcomm.com>

#ifndef XMLSCHEMA_CDR_TYPES_HPP
#define XMLSCHEMA_CDR_TYPES_HPP

//-- ACE includes
#include "ace/CDR_Stream.h"

/*
 * Following typedefs define generic Stream interfaces
 * for (de) marshaling XML types generated by XSC.
 * We leverage the ACE_CDRInput and ACE_CDROutput
 * stream classes that provides reusable classes for
 * encoding data using the Common Data Representation
 * encoding format.
 *
 * A corresponding traits class for argument passing
 * is also provided for enabling a clean CORBA like
 * semantics for passing arguments.
 *
 * Different encoding schemes such as
 * XDR encoding schemes should define similar types.
 */

namespace XMLSchema
{
  // CDR Reader/Writer Stream Type
  typedef ACE_OutputCDR CDR_OutputStream;
  typedef ACE_InputCDR  CDR_InputStream;

  // An argument traits class that defines
  // parameter passing in a CORBA like syntax
  // NOTE: Mainly in place for reference types.
  // Need to specialize for pointer types
  template <typename T>
  struct cdr_arg_traits
  {
    typedef T const &   in_type;
    typedef T &         out_type;
    typedef T           ret_type;
    typedef T *&        inout_type;
  };
}

template <typename T>
bool
operator << (::XMLSchema::CDR_OutputStream &stream,
	     const ::XMLSchema::string < T > &element)
{
  // For strings types, conver to the c style string
  // representations that can be marshaled
  return (stream << element.c_str ());
}

template <typename T>
bool
operator << (::XMLSchema::CDR_OutputStream &stream,
	     const ::XMLSchema::IDREF < T > &element)
{
  // Marshal the ID stored in the IDREF
  // id () operations returns a NCName which
  // itself is a string
  return (stream << element.id ().c_str ());
}

template <typename T>
void
operator << (::XMLSchema::CDR_OutputStream &stream,
             const ::XMLSchema::ID<T> &element)
{
  stream << element.c_str ();
}

#endif //XMLSCHEMA_CDR_TYPES_HPP
