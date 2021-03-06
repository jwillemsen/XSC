// file      : CCF/IDL3/SemanticAction/Impl/Consumes.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>

#include "CCF/IDL3/SemanticGraph/Component.hpp"
#include "CCF/IDL3/SemanticAction/Impl/Consumes.hpp"

#include <iostream>

using std::cerr;
using std::endl;

namespace CCF
{
  namespace IDL3
  {
    namespace SemanticAction
    {
      namespace Impl
      {
        using namespace SemanticGraph;

        Consumes::
        Consumes (Context& c)
            : Base (c)
        {
        }

        void Consumes::
        type (IdentifierPtr const& id)
        {
          if (ctx.trace ()) cerr << "consumes " << id;

          type_ = 0;

          Name name (id->lexeme ());
          ScopedName from (ctx.scope ().scoped_name ());

          try
          {
            try
            {
              type_ = &resolve<EventType> (from, name);
            }
            catch (Resolve const&)
            {
              cerr << ctx.file () << ":" << id->line () << ": error: "
                   << "invalid consumes declaration" << endl;
              throw;
            }
          }
          catch (NotFound const&)
          {
            cerr << ctx.file () << ":" << id->line () << ": error: "
                 << "no eventtype with name \'" << name
                 << "\' visible from scope \'" << from << "\'" << endl;
          }
          catch (WrongType const&)
          {
            cerr << ctx.file () << ":" << id->line () << ": error: "
                 << "declaration with name \'" << name
                 << "\' visible from scope \'" << from
                 << "\' is not an eventtype declaration" << endl;

            cerr << ctx.file () << ":" << id->line () << ": error: "
                 << "using non-eventtype in consumes declaration is illegal"
                 << endl;
          }
        }

        void Consumes::
        name (SimpleIdentifierPtr const& id)
        {
          if (ctx.trace ()) cerr << " " << id << endl;

          if (type_)
          {
            Consumer& c (ctx.tu ().new_node<Consumer> (
                           ctx.file (), id->line ()));

            ctx.tu ().new_edge<Belongs> (c, *type_);
            ctx.tu ().new_edge<Defines> (ctx.scope (), c, id->lexeme ());
          }
        }
      }
    }
  }
}
