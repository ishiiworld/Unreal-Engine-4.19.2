// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IncludePython.h"
#include "CoreMinimal.h"

#if WITH_PYTHON

/** Python type for FPyConstantDescrObject */
extern PyTypeObject PyConstantDescrType;

/** Initialize the PyConstant types */
void InitializePyConstant();

/** Function pointer used to convert a constant value pointer into a Python object */
typedef PyObject*(*PyConstantGetter)(const void*);

/**
 * Definition for a constant value
 * This takes a pointer to some static or otherwise persistent data, along with a function used to convert this pointer into a Python object when needed
 * Compared to a template, this avoids variance in the Python-type which would require a new Python-type to be registered for each instantiation
 * Compared to storing a PyObject*, this avoids returning an instance that could be mutated and affect the constant value
 */
struct FPyConstantDef
{
	/** A pointer to the constant value */
	const void* ConstantPtr;

	/** Function pointer used to convert a constant value pointer into a Python object */
	PyConstantGetter ConstantGetter;

	/** The name of the constant value */
	const char* ConstantName;

	/** The doc string of the constant value (may be null) */
	const char* ConstantDoc;

	/** Add the given null-terminated table of constants to the given type */
	static bool AddConstantsToType(FPyConstantDef* InConstants, PyTypeObject* InType);

	/** Add the given null-terminated table of constants to the given type */
	static bool AddConstantsToModule(FPyConstantDef* InConstants, PyObject* InModule);

	/** Add the given null-terminated table of constants to the given type */
	static bool AddConstantsToDict(FPyConstantDef* InConstants, PyObject* InDict);
};

/**
 * Python object for the descriptor of an constant value
 */
struct FPyConstantDescrObject
{
	/** Common Python Object */
	PyObject_HEAD

	/** Name of the constant being described */
	PyObject* ConstantName;

	/** Pointer to the definition of this constant */
	const FPyConstantDef* ConstantDef;

	/** New an instance */
	static FPyConstantDescrObject* New(const FPyConstantDef* InConstantDef);

	/** Free this instance */
	static void Free(FPyConstantDescrObject* InSelf);
};

#endif	// WITH_PYTHON
