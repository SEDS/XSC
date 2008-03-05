// $Id$

#include "File.h"

namespace XSCRT
{
namespace utils
{

//
// count_
//
size_t File::count_ = 0;

//
// File
//
File::File (void)
: impl_ (0),
  document_ (0)
{
  // Initiliaze the usage of Xerces-C
  if (++ File::count_ == 1)
    xercesc::XMLPlatformUtils::Initialize ();
}

//
// ~File
//
File::~File (void)
{
  // Close the open file.
  this->close ();

  // Terminate the usage of Xerces-C
  if (-- File::count_ == 0)
    xercesc::XMLPlatformUtils::Terminate ();
}

//
// close
//
void File::close (void)
{
  if (this->document_) 
  {
    // Release the document.
    this->document_->release();
	  this->document_ = 0;
  }
}

//
// document
//
xercesc::DOMDocument * File::document (void)
{
  return this->document_;
}

//
// impl
//
xercesc::DOMImplementation * File::impl (void)
{
  if (this->impl_ == 0)
  {
	  // Get default implementation, which is Load-Store (LS) interface.
    static const XMLCh gLS[] = { xercesc::chLatin_L,
                                 xercesc::chLatin_S,
                                 xercesc::chNull };

    this->impl_ = 
      xercesc::DOMImplementationRegistry::getDOMImplementation (gLS);
  }

  return this->impl_;
}

}
}
