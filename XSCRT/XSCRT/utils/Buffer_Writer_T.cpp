// $Id$

#include <string.h>

namespace XSCRT
{
namespace utils
{
//
// Buffer_Writer_T
//
template <typename T, typename CHAR_TYPE>
Buffer_Writer_T <T, CHAR_TYPE>::
Buffer_Writer_T (const CHAR_TYPE * ns,
               const CHAR_TYPE * root,
               typename writer_function <T>::result_type writer)
: Writer_T <T, CHAR_TYPE> (ns, root, writer),
  target_ (new xercesc::MemBufFormatTarget ())
{

}

//
// Buffer_Writer_T
//
template <typename T, typename CHAR_TYPE>
Buffer_Writer_T <T, CHAR_TYPE>::~Buffer_Writer_T (void)
{

}

//
// open
//
template <typename T, typename CHAR_TYPE>
bool Buffer_Writer_T <T, CHAR_TYPE>::write (char * buffer, size_t & size)
{
  // Get the size of the XML document.
  size_t copy_n = this->get_buffer_size ();
//  std::cout << "SIZE in Writer = " << copy_n << std::endl;

  if (copy_n > size)
    return false;

//  std::cout << "buffer size =  " << ACE_OS::strlen(buffer) << std::endl;
//  std::cout << "getRawBuffer size =  " << this->target_->getRawBuffer () << std::endl;
  
  // Copy the buffer, and set the size.
  ::memcpy (buffer, this->target_->getRawBuffer (), copy_n);

  

  size = copy_n;

  return true;
}

//
// operator <<=
//
template <typename T, typename CHAR_TYPE>
void Buffer_Writer_T <T, CHAR_TYPE>::operator <<= (const T & entity)
{
  // First, let the base class construct the DOM object.
  Writer_T <T, CHAR_TYPE>::operator <<= (entity);

  // Now, save the XML document into an internal buffer.
  if (this->dom_writer_)
    this->dom_writer_->writeNode (this->target_.get (), *this->document_);
}

//
// get_buffer_size
//
template <typename T, typename CHAR_TYPE>
size_t Buffer_Writer_T <T, CHAR_TYPE>::get_buffer_size (void) const
{
  return this->target_->getLen ();
}

}
}
