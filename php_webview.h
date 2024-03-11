/* webview extension for PHP */

#ifndef PHP_WEBVIEW_H
# define PHP_WEBVIEW_H

extern zend_module_entry webview_module_entry;
# define phpext_webview_ptr &webview_module_entry

# define PHP_WEBVIEW_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_WEBVIEW)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_WEBVIEW_H */
