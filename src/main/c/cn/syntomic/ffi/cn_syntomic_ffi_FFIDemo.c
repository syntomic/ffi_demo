#include <jni.h>
#include <Python.h>

#ifndef _Included_cn_syntomic_ffi_FFIDemo
#define _Included_cn_syntomic_ffi_FFIDemo
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     cn_syntomic_ffi_FFIDemo
 * Method:    dayOfWeek
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_cn_syntomic_ffi_FFIDemo_dayOfWeek
  (JNIEnv* env, jobject thisObject, jstring date) {
    int weekOfDay;

    // 初始化python解释器
    Py_Initialize();

    // 导入实现Python函数
    const char* pName = "day_of_week";
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./src/main/python/cn/syntomic/ffi')");
    PyObject* pModule = PyImport_Import(PyUnicode_FromString(pName));
    PyObject* pFunc = PyObject_GetAttrString(pModule, pName);

    // java类型转化为python参数
    PyObject* pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyUnicode_FromString((*env)->GetStringUTFChars(env, date, NULL)));

    // 调用python函数
    PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
    weekOfDay = PyLong_AsLong(pValue);

    // 关闭python解释器
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }

    return weekOfDay;
  }

#ifdef __cplusplus
}
#endif
#endif
