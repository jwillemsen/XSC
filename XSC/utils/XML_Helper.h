//============================================================
/**
 * @file XML_Helper.h
 *
 * @brief Some helper functions for XML
 *
 * @author Bala Natarajan <bala@dre.vanderbilt.edu>
 * @author William R. Otte <wotte@dre.vanderbilt.edu>
 */
//============================================================
#ifndef CIAO_XML_HELPER_H
#define CIAO_XML_HELPER_H

#include "XML_Error_Handler.h"
#include "XML_Schema_Resolver.h"
#include "xercesc/util/XercesDefs.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"

namespace XERCES_CPP_NAMESPACE
{
  class DOMDocument;
  class DOMWriter;
  class DOMImplementation;
  class DOMDocumentType;
}

namespace XSC
{
  namespace XML
  {
    /**
     * @class XML_Helper
     *
     * @brief Helper class for some routine XML stuff.
     */
    template <typename Resolver = XML_Schema_Resolver <>,
              typename Error_Handler = XML_Error_Handler>
    class XML_Helper
    {
    public:
      //      XML_Helper (void);

      // Initialize the resolver we should use.
      XML_Helper (Resolver &resolver, Error_Handler &eh);

      ~XML_Helper (void);

      /// Create a DOM tree
      XERCES_CPP_NAMESPACE::DOMDocument *
      create_dom (const char *uri) const;

      XERCES_CPP_NAMESPACE::DOMDocument *
      create_dom (const char *root,
                  const char *ns,
                  XERCES_CPP_NAMESPACE::DOMDocumentType * doctype = 0) const;

      XERCES_CPP_NAMESPACE::DOMDocumentType *
      create_doctype (const char *qn,
                      const char *pid,
                      const char *sid) const;

      //Writes out a DOMDocument to an XML file
      bool write_DOM (XERCES_CPP_NAMESPACE::DOMDocument *doc,
                      const char *file) const;

      bool is_initialized (void) const;

    protected:
      /// Intialize the parser
      void init_parser (void);

      /// Terminate the parser
      void terminate_parser (void);

    private:
      bool initialized_;
      XERCES_CPP_NAMESPACE::DOMImplementation *impl_;
      mutable std::auto_ptr<XERCES_CPP_NAMESPACE::XercesDOMParser> parser_;

      Resolver &resolver_;
      Error_Handler &e_handler_;
    };


  }
}

#include "XML_Helper_T.cpp"

#endif/*CIAO_CONFIG_HANDLERS_XML_HELPER_H*/
