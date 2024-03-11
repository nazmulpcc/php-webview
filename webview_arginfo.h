/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 10f25ab9fa87903546e2cdfc07ba2e7ec2b9bdba */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_test1, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Webview___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, debug, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Webview_set_title, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Webview_set_html, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, html, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Webview_set_size, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, hint, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Webview_navigate, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, url, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Webview_init, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, js, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Webview_eval arginfo_class_Webview_navigate

#define arginfo_class_Webview_run arginfo_test1

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Webview___destruct, 0, 0, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(test1);
ZEND_METHOD(Webview, __construct);
ZEND_METHOD(Webview, set_title);
ZEND_METHOD(Webview, set_html);
ZEND_METHOD(Webview, set_size);
ZEND_METHOD(Webview, navigate);
ZEND_METHOD(Webview, init);
ZEND_METHOD(Webview, eval);
ZEND_METHOD(Webview, run);
ZEND_METHOD(Webview, __destruct);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(test1, arginfo_test1)
	ZEND_FE_END
};


static const zend_function_entry class_Webview_methods[] = {
	ZEND_ME(Webview, __construct, arginfo_class_Webview___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, set_title, arginfo_class_Webview_set_title, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, set_html, arginfo_class_Webview_set_html, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, set_size, arginfo_class_Webview_set_size, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, navigate, arginfo_class_Webview_navigate, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, init, arginfo_class_Webview_init, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, eval, arginfo_class_Webview_eval, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, run, arginfo_class_Webview_run, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, __destruct, arginfo_class_Webview___destruct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Webview(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Webview", class_Webview_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	zval property_debug_default_value;
	ZVAL_LONG(&property_debug_default_value, 0);
	zend_string *property_debug_name = zend_string_init("debug", sizeof("debug") - 1, 1);
	zend_declare_typed_property(class_entry, property_debug_name, &property_debug_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_debug_name);

	return class_entry;
}
