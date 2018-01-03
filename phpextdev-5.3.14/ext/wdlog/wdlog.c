/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_wdlog.h"

/* If you declare any globals in php_wdlog.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(wdlog)
*/

/* True global resources - no need for thread safety here */
static int le_wdlog;

/* ZEND_BEGIN_ARG_INFO(arginfo_wdlog_write, 0) */
ZEND_BEGIN_ARG_INFO_EX(arginfo_wdlog_write, 0, 0, 2)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

/* {{{ wdlog_functions[]
 *
 * Every user visible function must have an entry in wdlog_functions[].
 */
const zend_function_entry wdlog_functions[] = {
	PHP_FE(confirm_wdlog_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(wdlog_write, arginfo_wdlog_write)
	PHP_FE_END	/* Must be the last line in wdlog_functions[] */
};
/* }}} */

/* {{{ wdlog_module_entry
 */
zend_module_entry wdlog_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"wdlog",
	wdlog_functions,
	PHP_MINIT(wdlog),
	PHP_MSHUTDOWN(wdlog),
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(wdlog),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_WDLOG
ZEND_GET_MODULE(wdlog)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("wdlog.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_wdlog_globals, wdlog_globals)
    STD_PHP_INI_ENTRY("wdlog.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_wdlog_globals, wdlog_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_wdlog_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_wdlog_init_globals(zend_wdlog_globals *wdlog_globals)
{
	wdlog_globals->global_value = 0;
	wdlog_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(wdlog)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(wdlog)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(wdlog)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(wdlog)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(wdlog)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "wdlog support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_wdlog_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_wdlog_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "wdlog", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */

/* {{{
 */
PHP_FUNCTION(wdlog_write)
{
	php_stream *stream;
	char *filename;
	char *content;
	int filename_len, content_len;
	int options = ENFORCE_SAFE_MODE | REPORT_ERRORS;
	int put_chars;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &filename, &filename_len, &content, &content_len) == FAILURE) {
		return;
	}

	stream = php_stream_open_wrapper(filename, "a+", options, NULL);
	if (!stream) {
		RETURN_FALSE;
	}
	put_chars = php_stream_puts(stream, content);
	php_stream_close(stream);
	if (put_chars < 0) {
		RETURN_FALSE;
	}
	ZVAL_TRUE(return_value);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
