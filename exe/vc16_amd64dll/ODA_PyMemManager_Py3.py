# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _ODA_PyMemManager_Py3
else:
    import _ODA_PyMemManager_Py3

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


import weakref

class ODA_PyMemoryTransaction(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined")
    __repr__ = _swig_repr
    __swig_destroy__ = _ODA_PyMemManager_Py3.delete_ODA_PyMemoryTransaction

    def AddObject(self, *args) -> "void":
        return _ODA_PyMemManager_Py3.ODA_PyMemoryTransaction_AddObject(self, *args)

    def DeleteObjects(self, *args) -> "void":
        return _ODA_PyMemManager_Py3.ODA_PyMemoryTransaction_DeleteObjects(self, *args)

# Register ODA_PyMemoryTransaction in _ODA_PyMemManager_Py3:
_ODA_PyMemManager_Py3.ODA_PyMemoryTransaction_swigregister(ODA_PyMemoryTransaction)

class ODA_PyMemoryManager(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined")
    __repr__ = _swig_repr

    @staticmethod
    def Get_MemoryManager(*args) -> "ODA_PyMemoryManager *":
        return _ODA_PyMemManager_Py3.ODA_PyMemoryManager_Get_MemoryManager(*args)

    @staticmethod
    def GetCurrentTransaction(*args) -> "ODA_PyMemoryTransaction *":
        return _ODA_PyMemManager_Py3.ODA_PyMemoryManager_GetCurrentTransaction(*args)

    def StartTransaction(self, *args) -> "ODA_PyMemoryTransaction *":
        return _ODA_PyMemManager_Py3.ODA_PyMemoryManager_StartTransaction(self, *args)

    def StopTransaction(self, *args) -> "void":
        return _ODA_PyMemManager_Py3.ODA_PyMemoryManager_StopTransaction(self, *args)
    __swig_destroy__ = _ODA_PyMemManager_Py3.delete_ODA_PyMemoryManager

# Register ODA_PyMemoryManager in _ODA_PyMemManager_Py3:
_ODA_PyMemManager_Py3.ODA_PyMemoryManager_swigregister(ODA_PyMemoryManager)

def ODA_PyMemoryManager_Get_MemoryManager(*args) -> "ODA_PyMemoryManager *":
    return _ODA_PyMemManager_Py3.ODA_PyMemoryManager_Get_MemoryManager(*args)

def ODA_PyMemoryManager_GetCurrentTransaction(*args) -> "ODA_PyMemoryTransaction *":
    return _ODA_PyMemManager_Py3.ODA_PyMemoryManager_GetCurrentTransaction(*args)


