/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef CBEAR_BERLIOS_DE_SVN_AUTH_MAIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_SVN_AUTH_MAIN_HPP_INCLUDED

#include <svn_auth.h>

namespace cbear_berlios_de
{
namespace svn
{
namespace auth
{

/// A provider object, ready to be put into an array and given to 
/// svn::auth_open().
typedef ::svn_auth_provider_object_t provider_object_t;

/// Set @a *cred by prompting the user, allocating @a *cred in @a pool.
/// @a baton is an implementation-specific closure.
///
/// If @a realm is non-null, maybe use it in the prompt string.
///
/// If @a username is non-null, then the user might be prompted only
/// for a password, but @a *creds would still be filled with both
/// username and password.  For example, a typical usage would be to
/// pass @a username on the first call, but then leave it null for
/// subsequent calls, on the theory that if credentials failed, it's
/// as likely to be due to incorrect username as incorrect password.
///
/// If @a may_save is FALSE, the auth system does not allow the credentials
/// to be saved (to disk). A prompt function shall not ask the user if the
/// credentials shall be saved if @a may_save is FALSE. For example, a GUI
/// client with a remember password checkbox would grey out the checkbox if
/// @a may_save is FALSE.
typedef ::svn_auth_simple_prompt_func_t simple_propmt_func_t;

/// Set @a *cred by prompting the user, allocating @a *cred in @a pool.
/// @a baton is an implementation-specific closure.
///
/// If @a realm is non-null, maybe use it in the prompt string.
///
/// If @a may_save is FALSE, the auth system does not allow the credentials
/// to be saved (to disk). A prompt function shall not ask the user if the
/// credentials shall be saved if @a may_save is FALSE. For example, a GUI
/// client with a remember username checkbox would grey out the checkbox if
/// @a may_save is FALSE.
typedef ::svn_auth_username_prompt_func_t username_prompt_func_t;

}
}
}

#endif
