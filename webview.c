/* webview extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "webview.h"
#include "ext/standard/info.h"
#include "php_webview.h"
#include "webview_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

static zend_object_handlers webview_object_handlers;

typedef struct php_webview_t
{
	webview_t native;
	zend_object std;
} php_webview_t;

#define Z_WEBVIEW_P(zv) \
	((php_webview_t *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_webview_t, std)))

zend_object *webview_new(zend_class_entry *ce)
{
	php_webview_t *wv = zend_object_alloc(sizeof(php_webview_t), ce);

	zend_object_std_init(&wv->std, ce);
	wv->std.handlers = &webview_object_handlers;
	return &wv->std;
}

PHP_METHOD(Webview, __construct)
{
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);
	zend_long debug = 0;

	ZEND_PARSE_PARAMETERS_START(0, 1)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(debug)
	ZEND_PARSE_PARAMETERS_END();

	if (ZEND_NUM_ARGS() > 0)
	{
		zend_update_property_long(Z_OBJCE_P(ZEND_THIS), Z_OBJ_P(ZEND_THIS),
								  "debug", sizeof("debug") - 1, debug);
	}

	container->native = webview_create(debug, NULL);
}

PHP_METHOD(Webview, hello)
{
	zval *salutation;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ZVAL(salutation)
	ZEND_PARSE_PARAMETERS_END();

	webview_set_title(container->native, Z_STRVAL(*salutation));
	webview_set_html(container->native, "Hello World");

	zend_print_zval(salutation, 0);
	webview_run(container->native);
}

/* {{{ void test1() */
PHP_FUNCTION(test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "webview");

	webview_t w = webview_create(0, NULL);
	webview_set_title(w, "Hello World");
	webview_navigate(w, "https://php.net");
	webview_run(w);
}
/* }}} */

/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
	Z_PARAM_OPTIONAL
	Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

PHP_MINIT_FUNCTION(webview)
{
	zend_class_entry *ce = register_class_Webview();

	ce->create_object = webview_new;

	memcpy(&webview_object_handlers, &std_object_handlers,
		   sizeof(zend_object_handlers));
	webview_object_handlers.offset = XtOffsetOf(php_webview_t, std);

	return SUCCESS;
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(webview)
{
#if defined(ZTS) && defined(COMPILE_DL_WEBVIEW)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(webview)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "webview support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ webview_module_entry */
zend_module_entry webview_module_entry = {
	STANDARD_MODULE_HEADER,
	"webview",			 /* Extension name */
	ext_functions,		 /* zend_function_entry */
	PHP_MINIT(webview),	 /* PHP_MINIT - Module initialization */
	NULL,				 /* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(webview),	 /* PHP_RINIT - Request initialization */
	NULL,				 /* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(webview),	 /* PHP_MINFO - Module info */
	PHP_WEBVIEW_VERSION, /* Version */
	STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_WEBVIEW
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(webview)
#endif
