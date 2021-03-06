// This file implements the IOleControl Interface and Gateway for Python.
// Generated by makegw.py

#include "axcontrol_pch.h"
#include "PyIOleControl.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIOleControl::PyIOleControl(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIOleControl::~PyIOleControl() {}

/* static */ IOleControl *PyIOleControl::GetI(PyObject *self) { return (IOleControl *)PyIUnknown::GetI(self); }

// @pymethod |PyIOleControl|GetControlInfo|Description of GetControlInfo.
PyObject *PyIOleControl::GetControlInfo(PyObject *self, PyObject *args)
{
    IOleControl *pIOC = GetI(self);
    if (pIOC == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":GetControlInfo"))
        return NULL;
    HRESULT hr;
    CONTROLINFO ci;
    ci.cb = sizeof(ci);
    PY_INTERFACE_PRECALL;
    hr = pIOC->GetControlInfo(&ci);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return OleSetOleError(hr);

    // TODO - Build this array!!
    return Py_BuildValue("Oi", Py_None, ci.dwFlags);
}

// @pymethod |PyIOleControl|OnMnemonic|Description of OnMnemonic.
PyObject *PyIOleControl::OnMnemonic(PyObject *self, PyObject *args)
{
    IOleControl *pIOC = GetI(self);
    if (pIOC == NULL)
        return NULL;
    MSG msg;
    memset(&msg, 0, sizeof(msg));
    // @pyparm iiiii(ii)|msg||A tuple representing a MSG structure.
    if (!PyArg_ParseTuple(args, "((iiiii(ii))):OnMnemonic", &msg.hwnd, &msg.message, &msg.wParam, &msg.lParam,
                          &msg.time, &msg.pt.x, &msg.pt.y))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pIOC->OnMnemonic(&msg);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return OleSetOleError(hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIOleControl|OnAmbientPropertyChange|Description of OnAmbientPropertyChange.
PyObject *PyIOleControl::OnAmbientPropertyChange(PyObject *self, PyObject *args)
{
    IOleControl *pIOC = GetI(self);
    if (pIOC == NULL)
        return NULL;
    // @pyparm long|dispID||Description for dispID
    DISPID dispID;
    if (!PyArg_ParseTuple(args, "l:OnAmbientPropertyChange", &dispID))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pIOC->OnAmbientPropertyChange(dispID);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return OleSetOleError(hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIOleControl|FreezeEvents|Description of FreezeEvents.
PyObject *PyIOleControl::FreezeEvents(PyObject *self, PyObject *args)
{
    IOleControl *pIOC = GetI(self);
    if (pIOC == NULL)
        return NULL;
    // @pyparm int|bFreeze||Description for bFreeze
    BOOL bFreeze;
    if (!PyArg_ParseTuple(args, "i:FreezeEvents", &bFreeze))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pIOC->FreezeEvents(bFreeze);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return OleSetOleError(hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @object PyIOleControl|Description of the interface
static struct PyMethodDef PyIOleControl_methods[] = {
    {"GetControlInfo", PyIOleControl::GetControlInfo, 1},  // @pymeth GetControlInfo|Description of GetControlInfo
    {"OnMnemonic", PyIOleControl::OnMnemonic, 1},          // @pymeth OnMnemonic|Description of OnMnemonic
    {"OnAmbientPropertyChange", PyIOleControl::OnAmbientPropertyChange,
     1},  // @pymeth OnAmbientPropertyChange|Description of OnAmbientPropertyChange
    {"FreezeEvents", PyIOleControl::FreezeEvents, 1},  // @pymeth FreezeEvents|Description of FreezeEvents
    {NULL}};

PyComTypeObject PyIOleControl::type("PyIOleControl", &PyIUnknown::type, sizeof(PyIOleControl), PyIOleControl_methods,
                                    GET_PYCOM_CTOR(PyIOleControl));
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGOleControl::GetControlInfo(
    /* [out] */ CONTROLINFO __RPC_FAR *pCI)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetControlInfo", &result);
    if (FAILED(hr))
        return hr;
    pCI->hAccel = 0;
    pCI->cAccel = 0;
    PyObject *obAccel;
    if (!PyArg_ParseTuple(result, "(Oi):GetControlInfo", &obAccel, &pCI->dwFlags))
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetControlInfo");
    else {
        if (obAccel != Py_None) {
            PyErr_SetString(PyExc_TypeError, "Only None is supported for ControlInfo.");
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetControlInfo");
        }
    }
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGOleControl::OnMnemonic(
    /* [in] */ MSG __RPC_FAR *pMsg)
{
    PY_GATEWAY_METHOD;
    PyObject *obMsg = Py_BuildValue("((iiiii(ii)))", pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam, pMsg->time,
                                    pMsg->pt.x, pMsg->pt.y);
    if (obMsg == NULL)
        return PyCom_HandlePythonFailureToCOM();
    HRESULT hr = InvokeViaPolicy("OnMnemonic", NULL, "O", obMsg);
    Py_DECREF(obMsg);
    return hr;
}

STDMETHODIMP PyGOleControl::OnAmbientPropertyChange(
    /* [in] */ DISPID dispID)
{
    PY_GATEWAY_METHOD;
    HRESULT hr = InvokeViaPolicy("OnAmbientPropertyChange", NULL, "l", dispID);
    return hr;
}

STDMETHODIMP PyGOleControl::FreezeEvents(
    /* [in] */ BOOL bFreeze)
{
    PY_GATEWAY_METHOD;
    HRESULT hr = InvokeViaPolicy("FreezeEvents", NULL, "i", bFreeze);
    return hr;
}
