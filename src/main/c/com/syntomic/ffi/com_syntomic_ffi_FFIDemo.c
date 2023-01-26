#include <jni.h>
#include <Python.h>

#ifndef _Included_com_syntomic_ffi_FFIDemo
#define _Included_com_syntomic_ffi_FFIDemo
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_syntomic_ffi_FFIDemo
 * Method:    dayOfWeek
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_syntomic_ffi_FFIDemo_dayOfWeek
  (JNIEnv* env, jobject thisObject, jstring date) {
    int weekOfDay;

    PyObject *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    // 获取java参数
    const char* jArgs = (*env)->GetStringUTFChars(env, date, NULL);

    // 初始化python解释器
    Py_Initialize();

    // 导入相应模块
    const char* pName = "day_of_week";
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./src/main/python/com/syntomic/ffi')");

    pModule = PyImport_Import(PyUnicode_FromString(pName));
    pFunc = PyObject_GetAttrString(pModule, pName);

    // 调用函数
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(jArgs));
    pValue = PyObject_CallObject(pFunc, pArgs);

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
