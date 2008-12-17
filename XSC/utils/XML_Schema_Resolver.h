/**
 * @file XML_Schema_Resolver.h
 * @author Will Otte <wotte@dre.vanderbilt.edu>
 *
 * $Id$
 *
 * Resolves schema locations.
 */

#ifndef CIAO_XML_SCHEMA_RESOLVER_H
#define CIAO_XML_SCHEMA_RESOLVER_H

#include "XSC_Utils_export.h"
#include "XercesString.h"
#include "XML_Error_Handler.h"
#include "xercesc/sax/EntityResolver.hpp"
#include <vector>
#include <string>

using namespace xercesc;

namespace XSC
{
  namespace XML
  {
    // forward decl.
    struct NoOp_Resolver;

    /**
     * @class CIAO_Schema_Resolver
     * @brief Resolves schema locations for CIAO.
     *
     * Template argument Resolver should be a functor with an operation
     * const char * operator () (...arguments from resolveEntity...)
     */
    template <typename Resolver = NoOp_Resolver>
    class XML_Schema_Resolver
      : public virtual EntityResolver
    {
    public:
      XML_Schema_Resolver (void);

      XML_Schema_Resolver (Resolver &resolver);

      /// This function is called by the Xerces infrastructure to
      /// actually resolve the location of a schema.
      virtual InputSource * resolveEntity (const XMLCh *const publicId,
                                           const XMLCh *const systemId);

    private:
      XML_Schema_Resolver (XML_Schema_Resolver<Resolver> &);

      Resolver &resolver_;
    };

    /**
     * @class NoOp_Resolver
     * @brief Resolver that does nothing.
     */
    struct NoOp_Resolver
    {
      const XMLCh* operator() (const XMLCh *const,
                               const XMLCh *const systemId) const
      { return systemId; };
    };

    /**
     * @class Basic_Resolver
     * @brief Resolves a schema location from a fixed path.
     */
    struct XSC_UTILS_Export Basic_Resolver
    {
      Basic_Resolver (const char *path);

      XMLCh* operator() (const XMLCh *const publicId,
                         const XMLCh *const systemId) const;
      XStr path_;
    };

    /**
     * @class Environment_Resolver
     * @brief Resolves a schema location from a path from an environment variable.
     */
    struct XSC_UTILS_Export Environment_Resolver
    {
      Environment_Resolver (const char *variable = "",
                            const char *path = "./");

      void add_path (const char *variable,
                     const char *path);

      XMLCh* operator() (const XMLCh *const publicId,
                         const XMLCh *const systemId) const;

      std::vector <XStr> paths_;
    };
  }
}

#include "XML_Schema_Resolver_T.cpp"

#endif /*  CIAO_XML_SCHEMA_RESOLVER_H */
