#include <svn_client.h>

#pragma comment(lib, "libsvn_client-1.lib")

namespace cbear_berlios_de
{
namespace svn
{

namespace apr
{

typedef ::apr_pool_t pool_t;

}

/// Version information. Each library contains a function called
/// svn_<i>libname</i>_version() that returns a pointer to a statically
/// allocated object of this type.
typedef ::svn_version_t version_t;

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

namespace client
{

/// Get libsvn_client version information.
inline const version_t &version() { return *::svn_client_version(); }

/// Create and return @a *provider, an authentication provider of type
/// svn_auth_cred_simple_t that gets information by prompting the user
/// with @a prompt_func and @a prompt_baton.  Allocate @a *provider in
/// @a pool.
///
/// If both @c SVN_AUTH_PARAM_DEFAULT_USERNAME and
/// @c SVN_AUTH_PARAM_DEFAULT_PASSWORD are defined as runtime
/// parameters in the @c auth_baton, then @a *provider will return the
/// default arguments when svn_auth_first_credentials() is called.  If
/// svn_auth_first_credentials() fails, then @a *provider will
/// re-prompt @a retry_limit times (via svn_auth_next_credentials()).
inline void get_simple_prompt_provider(
	auth::provider_object_t **provider,
	auth::simple_propmt_func_t prompt_func,
	void *prompt_baton,
	int retry_limit,
	apr::pool_t *pool)
{
	::svn_client_get_simple_prompt_provider(
		provider, prompt_func, prompt_baton, retry_limit, pool);
}

/// Create and return @a *provider, an authentication provider of type @c
/// svn_auth_cred_username_t that gets information by prompting the
/// user with @a prompt_func and @a prompt_baton.  Allocate @a *provider
/// in @a pool.
///
/// If @c SVN_AUTH_PARAM_DEFAULT_USERNAME is defined as a runtime
/// parameter in the @c auth_baton, then @a *provider will return the
/// default argument when svn_auth_first_credentials() is called.  If
/// svn_auth_first_credentials() fails, then @a *provider will
/// re-prompt @a retry_limit times (via svn_auth_next_credentials()).
inline void get_username_prompt_provider(
	auth::provider_object_t **provider,
	auth::username_prompt_func_t prompt_func,
	void *prompt_baton,
	int retry_limit,
	apr::pool_t *pool)
{
	::svn_client_get_username_prompt_provider(
		provider, prompt_func, prompt_baton, retry_limit, pool);
}

/// Create and return @a *provider, an authentication provider of type @c
/// svn_auth_cred_simple_t that gets/sets information from the user's
/// ~/.subversion configuration directory.  Allocate @a *provider in
/// @a pool.
///  
/// If a default username or password is available, @a *provider will
/// honor them as well, and return them when
/// svn_auth_first_credentials() is called.  (see @c
/// SVN_AUTH_PARAM_DEFAULT_USERNAME and @c
/// SVN_AUTH_PARAM_DEFAULT_PASSWORD). 
inline void get_simple_provider(
	auth::provider_object_t **provider, apr::pool_t *pool)
{
	::svn_client_get_simple_provider(provider, pool);
}

/// Create and return @a *provider, an authentication provider of type @c
/// svn_auth_cred_simple_t that gets/sets information from the user's
/// ~/.subversion configuration directory.  Allocate @a *provider in
/// @a pool.
/// 
/// This is like svn_client_get_simple_provider(), except that, when
/// running on Window 2000 or newer (or any other Windows version that
/// includes the CryptoAPI), the provider encrypts the password before
/// storing it to disk. On earlier versions of Windows, the provider
/// does nothing.
/// 
/// @note This function is only available on Windows.
/// 
/// @note An administrative password reset may invalidate the account's
/// secret key. This function will detect that situation and behave as
/// if the password were not cached at all.
inline void get_windows_simple_provider(
	auth::provider_object_t **provider, apr::pool_t *pool)
{
	::svn_client_get_windows_simple_provider(provider, pool);
}

/// Create and return @a *provider, an authentication provider of type @c
/// svn_auth_cred_username_t that gets/sets information from a user's
/// ~/.subversion configuration directory.  Allocate @a *provider in
/// @a pool.
/// 
/// If a default username is available, @a *provider will honor it,
/// and return it when svn_auth_first_credentials() is called.  (see
/// @c SVN_AUTH_PARAM_DEFAULT_USERNAME). 
inline void get_username_provider(
	auth::provider_object_t **provider, apr::pool_t *pool)
{
	::svn_client_get_username_provider(provider, pool);
}

}
}
}

#include <iostream>

namespace Svn = cbear_berlios_de::svn;

int main()
{
	const Svn::version_t &V = Svn::client::version();
	std::cout << 
		V.major << " " << 
		V.minor << " " << 
		V.patch << " " << 
		V.tag <<
		std::endl;
	std::cin.get();
	return 0;
}
