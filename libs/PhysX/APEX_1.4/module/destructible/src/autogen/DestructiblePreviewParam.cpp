//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2018 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#include "DestructiblePreviewParam.h"
#include <string.h>
#include <stdlib.h>

using namespace NvParameterized;

namespace nvidia
{
namespace destructible
{

using namespace DestructiblePreviewParamNS;

const char* const DestructiblePreviewParamFactory::vptr =
    NvParameterized::getVptr<DestructiblePreviewParam, DestructiblePreviewParam::ClassAlignment>();

const uint32_t NumParamDefs = 10;
static NvParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 2, 3, 4, 5, 7, 9, 6, 8,
};

#define TENUM(type) nvidia::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NvParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 7 },
	{ TYPE_MAT44, false, (size_t)(&((ParametersStruct*)0)->globalPose), NULL, 0 }, // globalPose
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->chunkDepth), NULL, 0 }, // chunkDepth
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->explodeAmount), NULL, 0 }, // explodeAmount
	{ TYPE_BOOL, false, (size_t)(&((ParametersStruct*)0)->renderUnexplodedChunksStatically), NULL, 0 }, // renderUnexplodedChunksStatically
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->overrideSkinnedMaterialNames), CHILDREN(7), 1 }, // overrideSkinnedMaterialNames
	{ TYPE_STRING, false, 1 * sizeof(NvParameterized::DummyStringStruct), NULL, 0 }, // overrideSkinnedMaterialNames[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->overrideStaticMaterialNames), CHILDREN(8), 1 }, // overrideStaticMaterialNames
	{ TYPE_STRING, false, 1 * sizeof(NvParameterized::DummyStringStruct), NULL, 0 }, // overrideStaticMaterialNames[]
	{ TYPE_U64, false, (size_t)(&((ParametersStruct*)0)->userData), NULL, 0 }, // userData
};


bool DestructiblePreviewParam::mBuiltFlag = false;
NvParameterized::MutexType DestructiblePreviewParam::mBuiltFlagMutex;

DestructiblePreviewParam::DestructiblePreviewParam(NvParameterized::Traits* traits, void* buf, int32_t* refCount) :
	NvParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &DestructiblePreviewParamFactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

DestructiblePreviewParam::~DestructiblePreviewParam()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void DestructiblePreviewParam::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NvParameterized::Traits* traits = mParameterizedTraits;
	int32_t* refCount = mRefCount;
	void* buf = mBuffer;

	this->~DestructiblePreviewParam();

	NvParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NvParameterized::DefinitionImpl* DestructiblePreviewParam::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NvParameterized::DefinitionImpl* DestructiblePreviewParam::getParameterDefinitionTree(void) const
{
	DestructiblePreviewParam* tmpParam = const_cast<DestructiblePreviewParam*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NvParameterized::ErrorType DestructiblePreviewParam::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NvParameterized::ErrorType DestructiblePreviewParam::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void DestructiblePreviewParam::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<DestructiblePreviewParam::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */
/* [0] - overrideSkinnedMaterialNames (not an array of structs) */
/* [0] - overrideStaticMaterialNames (not an array of structs) */

void DestructiblePreviewParam::freeParameterDefinitionTable(NvParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void DestructiblePreviewParam::buildTree(void)
{

	uint32_t allocSize = sizeof(NvParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NvParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(ParamDefTable, 0, allocSize);

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		NV_PARAM_PLACEMENT_NEW(ParamDefTable + i, NvParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="globalPose"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("globalPose", TYPE_MAT44, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The pose for the destructible preview, including scaling.\n", true);
		HintTable[1].init("shortDescription", "The pose for the destructible preview", true);
		ParamDefTable[1].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="chunkDepth"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("chunkDepth", TYPE_U32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Which chunk depth to render.\n", true);
		HintTable[1].init("shortDescription", "Which chunk depth to render.", true);
		ParamDefTable[2].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="explodeAmount"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("explodeAmount", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "How far apart to 'explode' the chunks rendered.  The value is relative to the chunk's initial offset from the origin.\n", true);
		HintTable[1].init("shortDescription", "How far apart to 'explode' the chunks rendered.", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="renderUnexplodedChunksStatically"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("renderUnexplodedChunksStatically", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "If true, unexploded chunks (see explodeAmount) will be renderered statically (without skinning).\nDefault value = false.\n", true);
		HintTable[1].init("shortDescription", "Whether or not to render unexploded chunks statically (without skinning)", true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="overrideSkinnedMaterialNames"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("overrideSkinnedMaterialNames", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Per-actor material names, to override those in the asset, for skinned rendering.", true);
		HintTable[1].init("shortDescription", "Per-actor material names, to override those in the asset, for skinned rendering", true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
		static const uint8_t dynHandleIndices[1] = { 0, };
		ParamDef->setDynamicHandleIndicesMap(dynHandleIndices, 1);

	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="overrideSkinnedMaterialNames[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("overrideSkinnedMaterialNames", TYPE_STRING, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Per-actor material names, to override those in the asset, for skinned rendering.", true);
		HintTable[1].init("shortDescription", "Per-actor material names, to override those in the asset, for skinned rendering", true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="overrideStaticMaterialNames"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("overrideStaticMaterialNames", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Per-actor material names, to override those in the asset, for static rendering.", true);
		HintTable[1].init("shortDescription", "Per-actor material names, to override those in the asset, for static rendering", true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
		static const uint8_t dynHandleIndices[1] = { 0, };
		ParamDef->setDynamicHandleIndicesMap(dynHandleIndices, 1);

	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="overrideStaticMaterialNames[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("overrideStaticMaterialNames", TYPE_STRING, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Per-actor material names, to override those in the asset, for static rendering.", true);
		HintTable[1].init("shortDescription", "Per-actor material names, to override those in the asset, for static rendering", true);
		ParamDefTable[8].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="userData"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("userData", TYPE_U64, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("editorDisplay", "false", true);
		ParamDefTable[9].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("editorDisplay", "false", true);
		HintTable[1].init("shortDescription", "Optional user data pointer associated with the destructible preview", true);
		ParamDefTable[9].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[7];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(2);
		Children[2] = PDEF_PTR(3);
		Children[3] = PDEF_PTR(4);
		Children[4] = PDEF_PTR(5);
		Children[5] = PDEF_PTR(7);
		Children[6] = PDEF_PTR(9);

		ParamDefTable[0].setChildren(Children, 7);
	}

	// SetChildren for: nodeIndex=5, longName="overrideSkinnedMaterialNames"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(6);

		ParamDefTable[5].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=7, longName="overrideStaticMaterialNames"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(8);

		ParamDefTable[7].setChildren(Children, 1);
	}

	mBuiltFlag = true;

}
void DestructiblePreviewParam::initStrings(void)
{
}

void DestructiblePreviewParam::initDynamicArrays(void)
{
	overrideSkinnedMaterialNames.buf = NULL;
	overrideSkinnedMaterialNames.isAllocated = true;
	overrideSkinnedMaterialNames.elementSize = sizeof(NvParameterized::DummyStringStruct);
	overrideSkinnedMaterialNames.arraySizes[0] = 0;
	overrideStaticMaterialNames.buf = NULL;
	overrideStaticMaterialNames.isAllocated = true;
	overrideStaticMaterialNames.elementSize = sizeof(NvParameterized::DummyStringStruct);
	overrideStaticMaterialNames.arraySizes[0] = 0;
}

void DestructiblePreviewParam::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	globalPose = physx::PxMat44(init(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
	chunkDepth = uint32_t(0);
	explodeAmount = float(0);
	renderUnexplodedChunksStatically = bool(false);
	userData = uint64_t(0);

	initDynamicArrays();
	initStrings();
	initReferences();
}

void DestructiblePreviewParam::initReferences(void)
{
}

void DestructiblePreviewParam::freeDynamicArrays(void)
{
	if (overrideSkinnedMaterialNames.isAllocated && overrideSkinnedMaterialNames.buf)
	{
		mParameterizedTraits->free(overrideSkinnedMaterialNames.buf);
	}
	if (overrideStaticMaterialNames.isAllocated && overrideStaticMaterialNames.buf)
	{
		mParameterizedTraits->free(overrideStaticMaterialNames.buf);
	}
}

void DestructiblePreviewParam::freeStrings(void)
{

	for (int i = 0; i < overrideSkinnedMaterialNames.arraySizes[0]; ++i)
	{
		if (overrideSkinnedMaterialNames.buf[i].isAllocated && overrideSkinnedMaterialNames.buf[i].buf)
		{
			mParameterizedTraits->strfree((char*)overrideSkinnedMaterialNames.buf[i].buf);
		}
	}

	for (int i = 0; i < overrideStaticMaterialNames.arraySizes[0]; ++i)
	{
		if (overrideStaticMaterialNames.buf[i].isAllocated && overrideStaticMaterialNames.buf[i].buf)
		{
			mParameterizedTraits->strfree((char*)overrideStaticMaterialNames.buf[i].buf);
		}
	}
}

void DestructiblePreviewParam::freeReferences(void)
{
}

} // namespace destructible
} // namespace nvidia
