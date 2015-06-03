// file      : CCF/CompilerElements/FileSystem.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id$

#ifndef CCF_RUNTIME_FILE_SYSTEM_HPP
#define CCF_RUNTIME_FILE_SYSTEM_HPP

#include <string>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/operations.hpp>

namespace fs
{
  using namespace boost::filesystem;

  inline path
  normalize (path const& p)
  {
    path result;

    for (path::iterator i (p.begin ()), e (p.end ()); i != e; ++i)
    {
      #if BOOST_FILESYSTEM_VERSION == 2
        if (*i != ".") result /= path (*i, native);
      #else
        if (*i != ".") result /= path (*i);
      #endif
    }

    return result;
  }
}

#endif  // CCF_RUNTIME_FILE_SYSTEM_HPP
